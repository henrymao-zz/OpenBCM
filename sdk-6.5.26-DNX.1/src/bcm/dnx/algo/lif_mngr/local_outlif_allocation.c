
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif

#define BSL_LOG_MODULE BSL_LS_BCMDNX_LIF

#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_lif.h>
#include <bcm_int/dnx/algo/swstate/auto_generated/access/lif_mngr_access.h>
#include <shared/utilex/utilex_integer_arithmetic.h>
#include <bcm_int/dnx/algo/res_mngr/resource_tag_bitmap.h>
#include <bcm_int/dnx/algo/lif_mngr/lif_mngr.h>
#include <soc/dnx/dbal/dbal.h>
#include <soc/dnx/mdb.h>
#include <shared/dbx/dbx_xml.h>
#include <shared/dbx/dbx_file.h>
#include <soc/dnx/swstate/auto_generated/access/algo_lif_access.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_l3.h>
#include "lif_mngr_internal.h"
#include <soc/dnx/dnx_state_snapshot_manager.h>
#include <soc/dnx/utils/dnx_pp_programmability_utils.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_pp.h>
#include <sal/appl/sal.h>
#include "src/bcm/dnx/algo/lif_mngr/auto_generated/dbx_pre_compiled_lif_mdb_auto_generated_xml_parser.h"
#include <appl/diag/bslenable.h>

#define DNX_ALGO_LOCAL_OUTLIF_RESOURCE          "Local outlif."

#define NOF_EEDB_PHASE_PAIRS        (DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES / 2)

#define EEDB_MAX_GRANULARITY        MDB_NOF_CLUSTER_ROW_BITS

#define EEDB_MIN_GRANLARITY         MDB_DIRECT_BASIC_ENTRY_SIZE

#define EEDB_GRANULARITY_UNIT       EEDB_MIN_GRANLARITY

#define OUTLIF_RESOURCE_ILLEGAL_TAG     (0x3)

#define EEDB_LL_DATA_MAX_SIZE           10

#define INVALID_LOCAL_OUTLIF           -1

#define EEDB_PHYSICAL_PHASE_TO_PHYSICAL_TABLE(_physical_phase) (_physical_phase + DBAL_PHYSICAL_TABLE_EEDB_1)

#define EEDB_PHYSICAL_TABLE_TO_PHYSICAL_PHASE(_physical_table) (_physical_table - DBAL_PHYSICAL_TABLE_EEDB_1)

#define EEDB_PHYSICAL_TABLE_PHYSICAL_PHASE_TO_PHASE_PAIR(_array_index) \
        (_array_index / 2)

#define EEDB_PHYSICAL_TABLE_PHASE_PAIR_TO_FIRST_PHYSICAL_PHASE(_phase_pair) \
        (_phase_pair * 2)

#define EEDB_PHYSICAL_PHASE_TO_PARTNER_PHASE(_eedb_physical_phase) \
        (_eedb_physical_phase ^ 1)

#define OUTLIF_RESOURCE_ALLOCATION_SIZE_TO_TAG(_allocation_size) (utilex_msb_bit_on(_allocation_size))

#define OUTLIF_RESOURCE_TAG_TO_ALLOCATION_SIZE(_tag)    (1 << (_tag))

typedef struct
{
    uint32 nof_outlifs_per_entry;
    uint32 nof_outlifs_per_alternative_entry;
    uint32 use_tag_and_align;
} dnx_algo_lif_local_outlif_resource_info_t;

extern shr_error_e dbal_tables_mdb_hw_payload_size_get(
    int unit,
    dbal_tables_e table_id,
    int res_type_idx,
    int *p_size);
extern shr_error_e dbal_tables_eedb_link_list_indication_get(
    int unit,
    uint32 local_outlif,
    uint32 *has_ll);

static shr_error_e
dnx_algo_local_outlif_result_type_and_granularity_to_nof_outlifs(
    int unit,
    int address_granularity,
    dbal_tables_e dbal_table_id,
    int dbal_result_type,
    uint32 *nof_outlifs_per_entry)
{
    int entry_size_in_bits;
    int extra_data_exists_rv = 0;
    uint8 rt_has_ll;
    uint32 actual_extradata_bits = 0;
    dbal_table_field_info_t extra_data_field_info, ll_field_info;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dbal_tables_mdb_hw_payload_size_get(unit, dbal_table_id, dbal_result_type, &entry_size_in_bits));

    SHR_IF_ERR_EXIT(dnx_lif_mngr_eedb_table_rt_has_linked_list(unit, dbal_table_id, dbal_result_type, &rt_has_ll));

    if (rt_has_ll)
    {

        SHR_IF_ERR_EXIT(dbal_tables_field_info_get_no_err(unit, dbal_table_id, DBAL_FIELD_NEXT_OUTLIF_POINTER, 0,
                                                          dbal_result_type, 0, &ll_field_info));

        entry_size_in_bits -= ll_field_info.field_nof_bits;

        extra_data_exists_rv = dbal_tables_field_info_get_no_err(unit, dbal_table_id, DBAL_FIELD_EEDB_LL_EXTRA_DATA, 0,
                                                                 dbal_result_type, 0, &extra_data_field_info);

        if (extra_data_exists_rv == _SHR_E_NONE)
        {
            entry_size_in_bits -= extra_data_field_info.field_nof_bits;
        }
    }

    *nof_outlifs_per_entry = UTILEX_DIV_ROUND_UP(entry_size_in_bits, address_granularity);

    if (address_granularity == 30 && *nof_outlifs_per_entry == 3)
    {

        *nof_outlifs_per_entry = 4;
    }

    if (rt_has_ll)
    {

        actual_extradata_bits = MDB_DIRECT_BASIC_ENTRY_SIZE - ll_field_info.field_nof_bits;
        if ((entry_size_in_bits > address_granularity) && (entry_size_in_bits % address_granularity))
        {
            if ((entry_size_in_bits % address_granularity) <= actual_extradata_bits)

                *nof_outlifs_per_entry = *nof_outlifs_per_entry - 1;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_info_to_resource_info(
    int unit,
    lif_mngr_local_outlif_info_t * outlif_info,
    dnx_algo_lif_local_outlif_resource_info_t * resource_info)
{
    uint8 address_granularity;
    dnx_algo_local_outlif_logical_phase_e logical_phase;
    SHR_FUNC_INIT_VARS(unit);

    logical_phase = outlif_info->logical_phase;
    if (outlif_info->logical_phase == DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_INVALID)
    {
        int outlif_bank = DNX_ALGO_OUTLIF_LOCAL_LIF_TO_BANK(outlif_info->local_outlif);
        uint8 tmp;
        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.used_logical_phase.get(unit, outlif_bank, &tmp));
        logical_phase = tmp;
    }

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                    address_granularity.get(unit, logical_phase, &address_granularity));

    if (address_granularity == 30 || address_granularity == 60)
    {

        resource_info->use_tag_and_align = TRUE;
    }
    else
    {

        resource_info->nof_outlifs_per_entry = 1;
        resource_info->nof_outlifs_per_alternative_entry = 1;
        resource_info->use_tag_and_align = FALSE;
        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_result_type_and_granularity_to_nof_outlifs(unit,
                                                                                     address_granularity,
                                                                                     outlif_info->dbal_table_id,
                                                                                     outlif_info->dbal_result_type,
                                                                                     &resource_info->nof_outlifs_per_entry));

    if (_SHR_IS_FLAG_SET
        (outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_REPLACE | DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_RESERVE))
    {

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_result_type_and_granularity_to_nof_outlifs(unit,
                                                                                         address_granularity,
                                                                                         outlif_info->dbal_table_id,
                                                                                         outlif_info->alternative_result_type,
                                                                                         &resource_info->nof_outlifs_per_alternative_entry));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_resource_create(
    int unit,
    uint32 node_id,
    void *res_tag_bitmap,
    dnx_algo_res_create_data_t * create_data,
    void *extra_arguments,
    uint32 alloc_flags)
{
    int nof_eedb_banks_per_outlif_bank, nof_outlifs_per_entry;
    dnx_algo_res_create_data_t res_tag_bitmap_create_info;
    resource_tag_bitmap_utils_extra_arg_create_info_t extra_create_info;
    dnx_algo_lif_local_outlif_resource_extra_info_t extra_info = { 0 };
    int outlifs_grain_idx = 0;
    resource_tag_bitmap_t *resource = (resource_tag_bitmap_t *) res_tag_bitmap;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_data_entries_supported))
    {
        outlifs_grain_idx = 1;
    }

    sal_memset(&extra_create_info, 0, sizeof(extra_create_info));

    sal_memset(&res_tag_bitmap_create_info, 0, sizeof(res_tag_bitmap_create_info));
    sal_strncpy(res_tag_bitmap_create_info.name, create_data->name, sizeof(res_tag_bitmap_create_info.name));
    sal_strncpy(res_tag_bitmap_create_info.advanced_algo_name, create_data->advanced_algo_name,
                sizeof(res_tag_bitmap_create_info.advanced_algo_name));
    res_tag_bitmap_create_info.nof_elements = create_data->nof_elements;
    res_tag_bitmap_create_info.first_element = create_data->first_element;
    res_tag_bitmap_create_info.flags = RESOURCE_TAG_BITMAP_CREATE_FLAGS_NONE;
    res_tag_bitmap_create_info.advanced_algorithm = create_data->advanced_algorithm;

    if (create_data->first_element == 1)
    {

        res_tag_bitmap_create_info.nof_elements++;
        res_tag_bitmap_create_info.first_element = 0;
    }

    extra_info = *((dnx_algo_lif_local_outlif_resource_extra_info_t *) extra_arguments);
    nof_outlifs_per_entry = EEDB_MAX_DATA_ENTRY_SIZE / extra_info.granularity;

    if (extra_info.assigned == DNX_ALGO_OUTLIF_BANK_ASSIGNED_TO_EEDB)
    {
        nof_eedb_banks_per_outlif_bank =
            DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit) /
            (dnx_data_mdb.dh.macro_type_info_get(unit, MDB_EEDB_BANK)->nof_rows * nof_outlifs_per_entry);

        extra_create_info.grains_size[outlifs_grain_idx] = nof_eedb_banks_per_outlif_bank;
        extra_create_info.max_tags_value[outlifs_grain_idx] =
            utilex_msb_bit_on(extra_create_info.grains_size[outlifs_grain_idx]);
    }
    else
    {

        extra_create_info.grains_size[outlifs_grain_idx] = nof_outlifs_per_entry;
        extra_create_info.max_tags_value[outlifs_grain_idx] =
            utilex_msb_bit_on(extra_create_info.grains_size[outlifs_grain_idx]);
        if (extra_create_info.grains_size[outlifs_grain_idx] == 1)
        {

            extra_create_info.grains_size[outlifs_grain_idx] = res_tag_bitmap_create_info.nof_elements;
            extra_create_info.max_tags_value[outlifs_grain_idx] = 0;
        }

        if (dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_data_entries_supported))
        {
            extra_create_info.grains_size[0] = dnx_data_lif.out_lif.data_entries_size_get(unit);
            extra_create_info.max_tags_value[0] = 1;
            extra_create_info.nof_tags_levels = 2;
        }
    }

    if (_SHR_IS_FLAG_SET(create_data->flags, RESOURCE_TAG_BITMAP_CREATE_ALLOW_FORCING_TAG))
    {

        res_tag_bitmap_create_info.flags |= RESOURCE_TAG_BITMAP_CREATE_ALLOW_FORCING_TAG;
        extra_create_info.max_tags_value[outlifs_grain_idx] = OUTLIF_RESOURCE_ILLEGAL_TAG;
    }

    SHR_IF_ERR_EXIT(resource_tag_bitmap_create(unit, node_id, resource, &res_tag_bitmap_create_info,
                                               &extra_create_info, alloc_flags));

    if (create_data->first_element == 1)
    {

        resource_tag_bitmap_utils_alloc_info_t alloc_info;
        int element;

        sal_memset(&alloc_info, 0, sizeof(alloc_info));

        alloc_info.flags |= RESOURCE_TAG_BITMAP_ALLOC_WITH_ID;
        alloc_info.tags[outlifs_grain_idx] = 0;
        alloc_info.count = 1;
        element = 0;
        SHR_IF_ERR_EXIT(resource_tag_bitmap_alloc(unit, node_id, *resource, &alloc_info, &element));
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_resource_is_allocated(
    int unit,
    uint32 node_id,
    void *res_tag_bitmap,
    int element,
    uint8 *is_allocated)
{
    uint8 allocation_size;
    resource_tag_bitmap_utils_tag_info_t tag_info;
    int outlifs_grain_idx = 0;

    SHR_FUNC_INIT_VARS(unit);

    if (res_tag_bitmap == NULL)
    {
        *is_allocated = FALSE;
        SHR_EXIT();
    }

    if (dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_data_entries_supported))
    {
        outlifs_grain_idx = 1;
    }

    sal_memset(&tag_info, 0, sizeof(tag_info));
    tag_info.element = element;
    SHR_IF_ERR_EXIT(resource_tag_bitmap_tag_get(unit, node_id, res_tag_bitmap, &tag_info));

    allocation_size = OUTLIF_RESOURCE_TAG_TO_ALLOCATION_SIZE(tag_info.tags[outlifs_grain_idx]);

    if (element % allocation_size == 0)
    {

        SHR_IF_ERR_EXIT(resource_tag_bitmap_is_allocated(unit, node_id, res_tag_bitmap, element, is_allocated));
    }
    else
    {
        *is_allocated = FALSE;
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_resource_allocate(
    int unit,
    uint32 node_id,
    void *res_tag_bitmap,
    uint32 flags,
    void *extra_arguments,
    int *element)
{
    lif_mngr_local_outlif_info_t *outlif_info;
    dnx_algo_lif_local_outlif_resource_info_t resource_info;
    uint32 allocation_size, tag = 0;
    resource_tag_bitmap_utils_alloc_info_t alloc_info;
    resource_tag_bitmap_utils_tag_info_t tag_info;
    uint8 with_id, with_tag, silent_mode;
    int rv, outlifs_grain_idx = 0;
    uint32 is_data_entry;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(&alloc_info, 0, sizeof(alloc_info));
    sal_memset(&resource_info, 0, sizeof(resource_info));
    sal_memset(&tag_info, 0, sizeof(tag_info));

    silent_mode = _SHR_IS_FLAG_SET(flags, DNX_ALGO_RES_ALLOCATE_SILENTLY);

    if (dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_data_entries_supported))
    {
        outlifs_grain_idx = 1;
    }

    with_id =
        _SHR_IS_FLAG_SET(flags,
                         DNX_ALGO_RES_ALLOCATE_WITH_ID | DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_REPLACE |
                         DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_WITH_ID);

    if (with_id)
    {
        alloc_info.flags |= RESOURCE_TAG_BITMAP_ALLOC_WITH_ID;
    }

    with_tag = (_SHR_IS_FLAG_SET(flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_RES_IGNORE_TAG));
    if (with_tag)
    {
        tag_info.element = *element;
        SHR_IF_ERR_EXIT(resource_tag_bitmap_tag_get(unit, node_id, res_tag_bitmap, &tag_info));

        tag = tag_info.tags[outlifs_grain_idx];
        alloc_info.flags |= RESOURCE_TAG_BITMAP_ALLOC_IGNORE_TAG;
    }

    outlif_info = (lif_mngr_local_outlif_info_t *) extra_arguments;

    SHR_IF_ERR_EXIT(dbal_tables_indication_get
                    (unit, outlif_info->dbal_table_id, DBAL_TABLE_IND_RESULT_TYPE_MAPPED_TO_SW, &is_data_entry));

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_info_to_resource_info(unit, outlif_info, &resource_info));

    if (_SHR_IS_FLAG_SET(flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_REPLACE))
    {

        uint8 is_allocated;
        uint32 old_size;

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_resource_is_allocated(unit, node_id, res_tag_bitmap,
                                                                    *element, &is_allocated));

        if (!is_allocated)
        {

            if (silent_mode)
            {

                SHR_SET_CURRENT_ERR(_SHR_E_NOT_FOUND);
                SHR_EXIT();
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "Trying to replace an outlif that doesn't exist, or is too small.");
            }
        }

        sal_memset(&tag_info, 0, sizeof(tag_info));
        tag_info.element = *element;
        SHR_IF_ERR_EXIT(resource_tag_bitmap_tag_get(unit, node_id, res_tag_bitmap, &tag_info));

        old_size = OUTLIF_RESOURCE_TAG_TO_ALLOCATION_SIZE(tag_info.tags[outlifs_grain_idx]);

        if (old_size == resource_info.nof_outlifs_per_entry)
        {

            SHR_EXIT();
        }
        if (old_size < resource_info.nof_outlifs_per_entry)
        {

            if (silent_mode)
            {

                SHR_SET_CURRENT_ERR(_SHR_E_NOT_FOUND);
                SHR_EXIT();
            }
            else
            {
                SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "Trying to replace an existing outlif with a larger outlif size.");
            }
        }

        SHR_IF_ERR_EXIT(resource_tag_bitmap_free_several(unit, node_id, res_tag_bitmap,
                                                         resource_info.nof_outlifs_per_alternative_entry,
                                                         *element, NULL));
    }

    allocation_size = resource_info.nof_outlifs_per_entry;

    if (with_tag)
    {
        tag_info.tags[outlifs_grain_idx] = tag;
    }
    if (dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_data_entries_supported))
    {

        alloc_info.tags[0] = is_data_entry;
    }
    if (resource_info.use_tag_and_align)
    {

        alloc_info.flags |= RESOURCE_TAG_BITMAP_ALLOC_ALIGN;
        alloc_info.align = allocation_size;
        alloc_info.count = allocation_size;
        if (!with_tag)
        {
            alloc_info.tags[outlifs_grain_idx] = OUTLIF_RESOURCE_ALLOCATION_SIZE_TO_TAG(allocation_size);
        }
    }
    else
    {

        alloc_info.count = allocation_size;
    }
    if (_SHR_IS_FLAG_SET(flags, DNX_ALGO_RES_ALLOCATE_SILENTLY))
    {
        alloc_info.flags |= RESOURCE_TAG_BITMAP_ALLOC_SILENTLY;
    }
    rv = resource_tag_bitmap_alloc(unit, node_id, res_tag_bitmap, &alloc_info, element);

    if ((dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_data_entries_supported))
        && (is_data_entry && (rv == _SHR_E_NONE)))
    {

        if (alloc_info.first_references[0])
        {
            outlif_info->local_lif_flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_DATA_ENTRY_HW;
        }
    }

    if (!silent_mode)
    {
        SHR_IF_ERR_EXIT(rv);
    }
    else
    {
        SHR_SET_CURRENT_ERR(rv);
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_resource_free_several(
    int unit,
    uint32 node_id,
    resource_tag_bitmap_t res_tag_bitmap,
    uint32 nof_elements,
    int element,
    void *extra_arguments)
{
    uint8 last_references[RESOURCE_TAG_BITMAP_MAX_NOF_TAGS_LEVELS] = { 0 };

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(resource_tag_bitmap_free_several
                    (unit, node_id, res_tag_bitmap, nof_elements, element, &last_references));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_lif_lib_encap_access_to_logical_phase_convert(
    int unit,
    bcm_encap_access_t encap_access,
    dnx_algo_local_outlif_logical_phase_e * logical_phase)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(logical_phase, _SHR_E_PARAM, "logical_phase");

    switch (encap_access)
    {
        case bcmEncapAccessTunnel1:
            *logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_3;
            break;
        case bcmEncapAccessTunnel2:
            *logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_4;
            break;
        case bcmEncapAccessTunnel3:
            *logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_5;
            break;
        case bcmEncapAccessTunnel4:
            *logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_6;
            break;
        case bcmEncapAccessNativeArp:
            *logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_2;
            break;
        case bcmEncapAccessArp:
            *logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_7;
            break;
        case bcmEncapAccessRif:
            *logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1;
            break;
        case bcmEncapAccessAc:
            *logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_8;
            break;
        case bcmEncapAccessInvalid:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Unhandled bcmEncapAccessInvalid value, shouldn't be used internally");
        case bcmEncapAccessNativeAc:
            SHR_ERR_EXIT(_SHR_E_PARAM, "bcmEncapAccessNativeAc is not supported");
        default:
            SHR_ERR_EXIT(_SHR_E_PARAM, "encap_access value (%d) is not supported", encap_access);
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_lif_lib_logical_phase_to_encap_access_convert(
    int unit,
    dnx_algo_local_outlif_logical_phase_e logical_phase,
    bcm_encap_access_t * encap_access)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_NULL_CHECK(encap_access, _SHR_E_PARAM, "encap_access");

    switch (logical_phase)
    {
        case DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1:
            *encap_access = bcmEncapAccessRif;
            break;
        case DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_2:
            *encap_access = bcmEncapAccessNativeArp;
            break;
        case DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_3:
            *encap_access = bcmEncapAccessTunnel1;
            break;
        case DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_4:
            *encap_access = bcmEncapAccessTunnel2;
            break;
        case DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_5:
            *encap_access = bcmEncapAccessTunnel3;
            break;
        case DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_6:
            *encap_access = bcmEncapAccessTunnel4;
            break;
        case DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_7:
            *encap_access = bcmEncapAccessArp;
            break;
        case DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_8:
            *encap_access = bcmEncapAccessAc;
            break;
        default:
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "logical_phase value (%d) is not supported by bcm_encap_access_t",
                         logical_phase);
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_bank_hw_info_get(
    int unit,
    int local_outlif,
    dnx_algo_local_outlif_hw_info_t * outlif_hw_info)
{
    int outlif_bank;
    uint8 ll_in_use;
    uint8 logical_phase, physical_phase, tmp;
    SHR_FUNC_INIT_VARS(unit);

    outlif_bank = DNX_ALGO_OUTLIF_LOCAL_LIF_TO_BANK(local_outlif);

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.used_logical_phase.get(unit, outlif_bank, &logical_phase));

    outlif_hw_info->logical_phase = logical_phase;

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.physical_phase.get(unit, logical_phase, &physical_phase));

    if (_SHR_IS_FLAG_SET(outlif_hw_info->flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_DATA_BANK))
    {
        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.assigned.get(unit, outlif_bank, &tmp));

        if (tmp == DNX_ALGO_OUTLIF_BANK_ASSIGNED_TO_EEDB)
        {
            int nof_outlifs_per_eedb_bank, eedb_bank_array_index;
            uint8 address_granularity;

            outlif_hw_info->data_bank_info.macro_type = MDB_EEDB_BANK;

            outlif_hw_info->data_bank_info.mdb_eedb_type = MDB_EEDB_MEM_TYPE_DATA_BANK;

            outlif_hw_info->data_bank_info.dbal_physical_table_id =
                EEDB_PHYSICAL_PHASE_TO_PHYSICAL_TABLE(physical_phase);

            SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                            address_granularity.get(unit, logical_phase, &address_granularity));

            if (address_granularity == 0)
            {
                SHR_IF_ERR_EXIT(_SHR_E_INTERNAL);
            }
            nof_outlifs_per_eedb_bank =
                EEDB_MAX_DATA_ENTRY_SIZE / address_granularity * dnx_data_mdb.dh.macro_type_info_get(unit,
                                                                                                     MDB_EEDB_BANK)->nof_rows;

            eedb_bank_array_index = DNX_ALGO_OUTLIF_LOCAL_LIF_TO_OFFSET(local_outlif) / nof_outlifs_per_eedb_bank;

            SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.eedb_data_banks.get(unit,
                                                                                   outlif_bank,
                                                                                   eedb_bank_array_index, &tmp));
            outlif_hw_info->data_bank_info.mdb_eedb_type = MDB_EEDB_MEM_TYPE_DATA_BANK;

            outlif_hw_info->data_bank_info.macro_type = MDB_EEDB_BANK;

            outlif_hw_info->data_bank_info.cluster_idx = tmp;

            outlif_hw_info->data_bank_info.macro_idx = 0;

            outlif_hw_info->data_bank_info.logical_start_address =
                outlif_bank * DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit) + nof_outlifs_per_eedb_bank * eedb_bank_array_index;
        }
        else
        {

        }
    }

    if (_SHR_IS_FLAG_SET(outlif_hw_info->flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_LL_BANK))
    {

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_in_use.get(unit, outlif_bank, &ll_in_use));
        if (ll_in_use)
        {
            uint8 ll_index;

            SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_index.get(unit, outlif_bank, &ll_index));

            outlif_hw_info->ll_bank_info.macro_type = MDB_EEDB_BANK;
            outlif_hw_info->ll_bank_info.macro_idx = 0;
            outlif_hw_info->ll_bank_info.dbal_physical_table_id = EEDB_PHYSICAL_PHASE_TO_PHYSICAL_TABLE(physical_phase);
            outlif_hw_info->ll_bank_info.mdb_eedb_type = MDB_EEDB_MEM_TYPE_LL;

            outlif_hw_info->ll_bank_info.cluster_idx = ll_index;

            outlif_hw_info->ll_bank_info.logical_start_address = outlif_bank * DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit);
        }
        else
        {
            SHR_ERR_EXIT(_SHR_E_INTERNAL, "Something went wrong - outlif %d doesn't have a linked list assigned.",
                         local_outlif);
        }
    }
exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_get_nof_available_ll_banks(
    int unit,
    int logical_phase,
    int *nof_available_banks)
{
    int count;
    uint8 first_ll_bank, last_ll_bank, nof_banks;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.first_ll_bank.get(unit, logical_phase, &first_ll_bank));

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.last_ll_bank.get(unit, logical_phase, &last_ll_bank));

    nof_banks = last_ll_bank - first_ll_bank + 1;

    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                    bank_occupation_bitmap.bit_range_count(unit, first_ll_bank, nof_banks, &count));

    *nof_available_banks = (nof_banks - count);

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_verify_ll_availability(
    int unit,
    int logical_phase,
    int nof_required_banks,
    int *is_available)
{
    int nof_available_banks = 0;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_get_nof_available_ll_banks(unit, logical_phase, &nof_available_banks));

    *is_available = nof_required_banks <= nof_available_banks;

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_eedb_bank_allocate(
    int unit,
    dnx_algo_local_outlif_logical_phase_e logical_phase,
    int *bank)
{
    uint8 first_ll_bank, last_ll_bank, ll_bank_used, current_ll_bank = 0, bank_found;
    int stride, nof_banks;
    SHR_FUNC_INIT_VARS(unit);

    bank_found = FALSE;

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.first_ll_bank.get(unit, logical_phase, &first_ll_bank));

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.last_ll_bank.get(unit, logical_phase, &last_ll_bank));

    nof_banks = last_ll_bank - first_ll_bank + 1;
    stride = nof_banks / 2;

    for (current_ll_bank = first_ll_bank; current_ll_bank <= (first_ll_bank + stride); current_ll_bank++)
    {
        SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                        bank_occupation_bitmap.bit_get(unit, current_ll_bank, &ll_bank_used));
        if (!ll_bank_used)
        {
            bank_found = TRUE;
            break;
        }
        SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                        bank_occupation_bitmap.bit_get(unit, (current_ll_bank + stride), &ll_bank_used));
        if (!ll_bank_used)
        {
            bank_found = TRUE;
            current_ll_bank = current_ll_bank + stride;
            break;
        }
    }

    if (!bank_found)
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL,
                     "Sanity failed: an ll banks is supposed to be available for phase %d, but none was found.",
                     logical_phase);
    }

    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.bank_occupation_bitmap.bit_set(unit, current_ll_bank));

    *bank = current_ll_bank;

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_bank_in_use_set(
    int unit,
    int bank,
    dnx_algo_local_outlif_logical_phase_e logical_phase,
    int ll_required)
{
    SHR_FUNC_INIT_VARS(unit);

    if (ll_required)
    {
        int eedb_bank;
        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_eedb_bank_allocate(unit, logical_phase, &eedb_bank));

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_index.set(unit, bank, eedb_bank));
    }

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.in_use.set(unit, bank, TRUE));

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.used_logical_phase.set(unit, bank, logical_phase));

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_in_use.set(unit, bank, ll_required));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_bank_in_use_unset(
    int unit,
    int bank)
{
    uint8 ll_in_use;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_in_use.get(unit, bank, &ll_in_use));

    if (ll_in_use)
    {
        uint8 used_ll_bank;

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_index.get(unit, bank, &used_ll_bank));

        SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.bank_occupation_bitmap.bit_clear(unit, used_ll_bank));

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_index.set(unit, bank, 0));

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_in_use.set(unit, bank, FALSE));
    }

    if (!dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_per_phase_algo))
    {

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.used_logical_phase.set(unit, bank, 0));
    }

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.in_use.set(unit, bank, FALSE));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_bank_prefix_for_eedb_bank_assign(
    int unit,
    int granularity,
    int nof_eedb_banks_per_outlif_bank,
    int logical_phase,
    uint32 outlif_bank)
{
    int current_outlif_prefix, outlif_prefix_index;
    uint8 tmp;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.
                    assigned.set(unit, outlif_bank, DNX_ALGO_OUTLIF_BANK_ASSIGNED_TO_EEDB));

    current_outlif_prefix =
        MDB_OUTLIF_AND_GRANULARITY_TO_PREFIX(unit, outlif_bank * DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit), granularity);
    for (outlif_prefix_index = 0; outlif_prefix_index < nof_eedb_banks_per_outlif_bank; outlif_prefix_index++)
    {

        SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.outlif_prefix_occupation_bitmap.bit_set(unit,
                                                                                                  current_outlif_prefix
                                                                                                  +
                                                                                                  outlif_prefix_index));
    }

    for (outlif_prefix_index = 0; outlif_prefix_index < MAX_EEDB_BANKS_PER_OUTLIF_BANK; outlif_prefix_index++)
    {

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.eedb_data_banks.set(unit,
                                                                               outlif_bank,
                                                                               outlif_prefix_index,
                                                                               DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK));
    }

    tmp = outlif_bank;
    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                    used_data_bank_per_logical_phase.add_first(unit, logical_phase, &tmp));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_bank_prefix_for_eedb_bank_unassign(
    int unit,
    int granularity,
    int nof_eedb_banks_per_outlif_bank,
    int logical_phase,
    uint32 outlif_bank)
{
    int current_outlif_prefix, outlif_prefix_index;
    uint8 tmp;
    sw_state_ll_node_t current_node;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.
                    assigned.set(unit, outlif_bank, DNX_ALGO_OUTLIF_BANK_UNASSIGNED));

    current_outlif_prefix =
        MDB_OUTLIF_AND_GRANULARITY_TO_PREFIX(unit, outlif_bank * DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit), granularity);
    for (outlif_prefix_index = 0; outlif_prefix_index < nof_eedb_banks_per_outlif_bank; outlif_prefix_index++)
    {

        SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.outlif_prefix_occupation_bitmap.bit_clear(unit,
                                                                                                    current_outlif_prefix
                                                                                                    +
                                                                                                    outlif_prefix_index));
    }

    for (outlif_prefix_index = 0; outlif_prefix_index < MAX_EEDB_BANKS_PER_OUTLIF_BANK; outlif_prefix_index++)
    {

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.eedb_data_banks.set(unit,
                                                                               outlif_bank, outlif_prefix_index, 0));
    }

    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                    used_data_bank_per_logical_phase.get_first(unit, logical_phase, &current_node));

    while (DNX_SW_STATE_LL_IS_NODE_VALID(current_node))
    {
        SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                        used_data_bank_per_logical_phase.node_value(unit, current_node, &tmp));

        if (tmp == outlif_bank)
        {
            break;
        }

        SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                        used_data_bank_per_logical_phase.next_node(unit, logical_phase, current_node, &current_node));
    }

    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                    used_data_bank_per_logical_phase.remove_node(unit, logical_phase, current_node));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_bank_prefix_for_eedb_bank_allocate(
    int unit,
    int granularity,
    int nof_eedb_banks_for_granularity,
    uint32 *outlif_bank)
{
    int current_outlif_bank, current_outlif_prefix, outlif_prefix_index;
    uint8 bank_assigned, prefix_in_use;
    SHR_FUNC_INIT_VARS(unit);

    for (current_outlif_bank = 0; current_outlif_bank < DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit); current_outlif_bank++)
    {
        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.assigned.get(unit, current_outlif_bank, &bank_assigned));

        if (bank_assigned == DNX_ALGO_OUTLIF_BANK_UNASSIGNED)
        {
            current_outlif_prefix =
                MDB_OUTLIF_AND_GRANULARITY_TO_PREFIX(unit, current_outlif_bank * DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit),
                                                     granularity);
            for (outlif_prefix_index = 0; outlif_prefix_index < nof_eedb_banks_for_granularity; outlif_prefix_index++)
            {
                SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.outlif_prefix_occupation_bitmap.bit_get(unit,
                                                                                                          current_outlif_prefix
                                                                                                          +
                                                                                                          outlif_prefix_index,
                                                                                                          &prefix_in_use));

                if (prefix_in_use)
                {

                    break;
                }
            }

            if (outlif_prefix_index == nof_eedb_banks_for_granularity)
            {

                break;
            }
        }
    }

    if (current_outlif_bank == DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit))
    {
        SHR_ERR_EXIT(_SHR_E_RESOURCE, "There are no more outlif banks available for use.");
    }

    *outlif_bank = current_outlif_bank;

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_assign_eedb_bank_to_outlif_bank(
    int unit,
    int outlif_bank,
    int logical_phase,
    int eedb_bank_offset_in_outlif_bank,
    int nof_outlifs_per_eedb_bank)
{
    int eedb_bank;
    resource_tag_bitmap_utils_tag_info_t tag_set_info;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_eedb_bank_allocate(unit, logical_phase, &eedb_bank));

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.eedb_data_banks.set(unit,
                                                                           outlif_bank,
                                                                           eedb_bank_offset_in_outlif_bank, eedb_bank));

    sal_memset(&tag_set_info, 0, sizeof(resource_tag_bitmap_utils_tag_info_t));
    tag_set_info.force_tag = FALSE;
    tag_set_info.tags[0] = 0;
    tag_set_info.nof_elements = nof_outlifs_per_eedb_bank;
    tag_set_info.element = OUTLIF_BANK_FIRST_INDEX(unit, outlif_bank) +
        nof_outlifs_per_eedb_bank * eedb_bank_offset_in_outlif_bank;

    SHR_IF_ERR_EXIT(lif_mngr_db.egress_local_lif.advanced_algorithm_info_set(unit, outlif_bank, &tag_set_info));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_unassign_eedb_bank_to_outlif_bank(
    int unit,
    int outlif_bank,
    int eedb_bank_offset_in_outlif_bank,
    int nof_outlifs_per_eedb_bank)
{
    uint8 eedb_bank;
    resource_tag_bitmap_utils_tag_info_t tag_set_info;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.eedb_data_banks.get(unit,
                                                                           outlif_bank,
                                                                           eedb_bank_offset_in_outlif_bank,
                                                                           &eedb_bank));

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.eedb_data_banks.set(unit,
                                                                           outlif_bank,
                                                                           eedb_bank_offset_in_outlif_bank,
                                                                           DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK));

    sal_memset(&tag_set_info, 0, sizeof(resource_tag_bitmap_utils_tag_info_t));
    tag_set_info.force_tag = TRUE;
    tag_set_info.tags[0] = OUTLIF_RESOURCE_ILLEGAL_TAG;
    tag_set_info.nof_elements = nof_outlifs_per_eedb_bank;
    tag_set_info.element = OUTLIF_BANK_FIRST_INDEX(unit, outlif_bank) +
        nof_outlifs_per_eedb_bank * eedb_bank_offset_in_outlif_bank;

    SHR_IF_ERR_EXIT(lif_mngr_db.egress_local_lif.advanced_algorithm_info_set(unit, outlif_bank, &tag_set_info));

    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.bank_occupation_bitmap.bit_clear(unit, eedb_bank));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_alloc_in_used_bank(
    int unit,
    int bank,
    dnx_algo_local_outlif_logical_phase_e required_logical_phase,
    int ll_required,
    lif_mngr_local_outlif_info_t * outlif_info,
    int *bank_match,
    int *bank_can_be_used)
{
    uint8 bank_logical_phase;
    uint8 ll_in_use;
    int element;
    shr_error_e rv;
    int nof_rifs;
    uint8 is_rif;
    int nof_free_elements;
    int flags = 0;

    SHR_FUNC_INIT_VARS(unit);

    *bank_can_be_used = FALSE;
    *bank_match = FALSE;

    SHR_IF_ERR_EXIT(lif_mngr_db.egress_local_lif.nof_free_elements_get(unit, bank, &nof_free_elements));

    if (!nof_free_elements)
    {

        SHR_EXIT();
    }

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.used_logical_phase.get(unit, bank, &bank_logical_phase));

    if (bank_logical_phase == required_logical_phase)
    {

        if (bank_logical_phase == DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1)
        {
            nof_rifs = dnx_data_l3.rif.nof_rifs_get(unit);
            is_rif = ((outlif_info->logical_phase == DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1)
                      && (outlif_info->dbal_table_id == DBAL_TABLE_EEDB_RIF_BASIC)) ? TRUE : FALSE;

            if (is_rif)
            {
                if ((bank * DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit)) > nof_rifs)
                {
                    SHR_EXIT();
                }
            }
            else
            {

                if ((bank * DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit)) < nof_rifs)
                {
                    SHR_EXIT();
                }
            }
        }

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_in_use.get(unit, bank, &ll_in_use));

        if ((ll_in_use && ll_required) || (!ll_in_use && !ll_required))
        {
            *bank_match = TRUE;
        }
        else
        {

            SHR_EXIT();
        }
    }
    else
    {

        SHR_EXIT();
    }

    if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_RES_IGNORE_TAG))
    {
        flags = DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_RES_IGNORE_TAG;
    }

    flags |= DNX_ALGO_RES_ALLOCATE_SILENTLY;
    if ((_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_WITH_ID)))
    {
        flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_WITH_ID;
    }
    rv = lif_mngr_db.egress_local_lif.allocate_single(unit, bank, flags, (void *) outlif_info, &element);

    if (rv == _SHR_E_NONE)
    {

        *bank_can_be_used = TRUE;
        outlif_info->local_outlif = element;
    }
    else if (rv != _SHR_E_RESOURCE)
    {
        SHR_IF_ERR_EXIT(rv);
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_bank_in_eedb_bank_find(
    int unit,
    uint32 local_lif_flags,
    dnx_algo_local_outlif_logical_phase_e logical_phase,
    int ll_required,
    lif_mngr_local_outlif_info_t * outlif_info,
    uint32 *output_flags,
    uint32 *outlif_bank)
{
    sw_state_ll_node_t current_node;
    uint8 address_granularity, current_outlif_bank, new_eedb_bank_array_index, current_eedb_bank;
    int outlif_bank_match, outlif_bank_can_be_used, nof_eedb_banks_to_allocate, eedb_bank_is_available;
    int nof_outlifs_per_entry, nof_eedb_banks_per_outlif_bank;
    int current_eedb_bank_array_index, extendable_outlif_bank;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                    address_granularity.get(unit, logical_phase, &address_granularity));

    if (address_granularity == 0)
    {
        SHR_IF_ERR_EXIT(_SHR_E_INTERNAL);
    }
    nof_outlifs_per_entry = EEDB_MAX_DATA_ENTRY_SIZE / address_granularity;
    nof_eedb_banks_per_outlif_bank =
        DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit) / (dnx_data_mdb.dh.macro_type_info_get(unit, MDB_EEDB_BANK)->nof_rows *
                                                 nof_outlifs_per_entry);

    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                    used_data_bank_per_logical_phase.get_first(unit, logical_phase, &current_node));
    extendable_outlif_bank = DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK;
    new_eedb_bank_array_index = 0;
    while (DNX_SW_STATE_LL_IS_NODE_VALID(current_node)
           && !_SHR_IS_FLAG_SET(local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_FORCE_NEW_BANK_ALLOCATION))
    {
        SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                        used_data_bank_per_logical_phase.node_value(unit, current_node, &current_outlif_bank));

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_alloc_in_used_bank
                        (unit, current_outlif_bank, logical_phase, ll_required, outlif_info, &outlif_bank_match,
                         &outlif_bank_can_be_used));

        if (outlif_bank_can_be_used)
        {

            *outlif_bank = current_outlif_bank;
            SHR_EXIT();
        }

        if (outlif_bank_match && extendable_outlif_bank == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK)
        {
            for (current_eedb_bank_array_index = 0; current_eedb_bank_array_index < nof_eedb_banks_per_outlif_bank;
                 current_eedb_bank_array_index++)
            {
                SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.
                                eedb_data_banks.get(unit, current_outlif_bank, current_eedb_bank_array_index,
                                                    &current_eedb_bank));

                if (current_eedb_bank == (uint8) DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK)
                {
                    extendable_outlif_bank = current_outlif_bank;
                    new_eedb_bank_array_index = current_eedb_bank_array_index;
                    break;
                }
            }
        }

        SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                        used_data_bank_per_logical_phase.next_node(unit, logical_phase, current_node, &current_node));
    }

    if (_SHR_IS_FLAG_SET(local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_DONT_ALLOCATE_NEW_BANK))
    {

        SHR_EXIT();
    }

    if (extendable_outlif_bank == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK && ll_required)
    {
        nof_eedb_banks_to_allocate = 2;
    }
    else
    {
        nof_eedb_banks_to_allocate = 1;
    }

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_verify_ll_availability
                    (unit, logical_phase, nof_eedb_banks_to_allocate, &eedb_bank_is_available));

    if (!eedb_bank_is_available)
    {

        *outlif_bank = DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK;
        SHR_EXIT();
    }

    if (extendable_outlif_bank == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK)
    {
        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_prefix_for_eedb_bank_allocate
                        (unit, address_granularity, nof_eedb_banks_per_outlif_bank, outlif_bank));

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_prefix_for_eedb_bank_assign
                        (unit, address_granularity, nof_eedb_banks_per_outlif_bank, logical_phase, *outlif_bank));

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_in_use_set(unit, *outlif_bank, logical_phase, ll_required));
    }
    else
    {

        *outlif_bank = extendable_outlif_bank;
    }

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_assign_eedb_bank_to_outlif_bank
                    (unit, *outlif_bank, logical_phase, new_eedb_bank_array_index,
                     DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit) / nof_eedb_banks_per_outlif_bank));

    *output_flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_DATA_BANK;

    if (extendable_outlif_bank == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK)
    {
        *output_flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_POINTERS;
        if (ll_required)
        {
            *output_flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_LL_BANK;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_bank_in_eedb_bank_check_and_unassign(
    int unit,
    int local_outlif,
    dnx_algo_local_outlif_hw_info_t * outlif_hw_info)
{
    uint8 address_granularity, logical_phase;
    int outlif_bank, bank_offset, eedb_bank_array_index;
    int nof_outlifs_per_entry, nof_eedb_banks_per_outlif_bank, nof_outlifs_per_eedb_bank;
    int nof_allocated_elements, nof_free_elements;

    SHR_FUNC_INIT_VARS(unit);

    outlif_bank = DNX_ALGO_OUTLIF_LOCAL_LIF_TO_BANK(local_outlif);
    bank_offset = DNX_ALGO_OUTLIF_LOCAL_LIF_TO_OFFSET(local_outlif);

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.used_logical_phase.get(unit, outlif_bank, &logical_phase));

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                    address_granularity.get(unit, logical_phase, &address_granularity));

    if (address_granularity == 0)
    {
        SHR_IF_ERR_EXIT(_SHR_E_INTERNAL);
    }
    nof_outlifs_per_entry = EEDB_MAX_DATA_ENTRY_SIZE / address_granularity;
    nof_eedb_banks_per_outlif_bank =
        DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit) / (dnx_data_mdb.dh.macro_type_info_get(unit, MDB_EEDB_BANK)->nof_rows *
                                                 nof_outlifs_per_entry);

    nof_outlifs_per_eedb_bank = DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit) / nof_eedb_banks_per_outlif_bank;

    eedb_bank_array_index = bank_offset / nof_outlifs_per_eedb_bank;

    SHR_IF_ERR_EXIT(lif_mngr_db.egress_local_lif.nof_allocated_elements_in_range_get(unit, outlif_bank,
                                                                                     OUTLIF_BANK_FIRST_INDEX(unit,
                                                                                                             outlif_bank)
                                                                                     +
                                                                                     nof_outlifs_per_eedb_bank *
                                                                                     eedb_bank_array_index,
                                                                                     nof_outlifs_per_eedb_bank,
                                                                                     &nof_allocated_elements));

    if (nof_allocated_elements == 0)
    {
        outlif_hw_info->flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_DATA_BANK;

        SHR_IF_ERR_EXIT(lif_mngr_db.egress_local_lif.nof_free_elements_get(unit, outlif_bank, &nof_free_elements));

        if (nof_free_elements == DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit))
        {
            uint8 ll_in_use;

            outlif_hw_info->flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_POINTERS;

            SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_in_use.get(unit, outlif_bank, &ll_in_use));

            if (ll_in_use)
            {
                outlif_hw_info->flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_LL_BANK;
            }

        }

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_hw_info_get(unit, local_outlif, outlif_hw_info));

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_unassign_eedb_bank_to_outlif_bank
                        (unit, outlif_bank, eedb_bank_array_index, nof_outlifs_per_eedb_bank));

        if (nof_free_elements == DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit))
        {

            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_prefix_for_eedb_bank_unassign
                            (unit, address_granularity, nof_eedb_banks_per_outlif_bank, logical_phase, outlif_bank));

            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_in_use_unset(unit, outlif_bank));
        }

    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_allocate_in_bank(
    int unit,
    uint32 local_lif_flags,
    dnx_algo_local_outlif_logical_phase_e logical_phase,
    uint8 ll_required,
    lif_mngr_local_outlif_info_t * outlif_info,
    int first_bank_for_phase,
    int last_bank_for_phase,
    uint32 *outlif_bank,
    uint32 *first_unused_bank_in_mdb_cluster)
{
    int current_bank, bank_can_be_used, bank_match;
    uint8 in_use;

    SHR_FUNC_INIT_VARS(unit);

    for (current_bank = first_bank_for_phase; current_bank <= last_bank_for_phase; current_bank++)
    {

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.in_use.get(unit, current_bank, &in_use));

        if (in_use && !_SHR_IS_FLAG_SET(local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_FORCE_NEW_BANK_ALLOCATION))
        {

            bank_can_be_used = FALSE;
            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_alloc_in_used_bank
                            (unit, current_bank, logical_phase, ll_required, outlif_info, &bank_match,
                             &bank_can_be_used));

            if (bank_can_be_used)
            {

                *outlif_bank = current_bank;
                break;
            }
        }
        else if (*first_unused_bank_in_mdb_cluster == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK)
        {

            *first_unused_bank_in_mdb_cluster = current_bank;
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_allocation_find_existing_bank_to_allocate(
    int unit,
    uint32 local_lif_flags,
    dnx_algo_local_outlif_logical_phase_e logical_phase,
    uint8 ll_required,
    lif_mngr_local_outlif_info_t * outlif_info,
    uint32 *outlif_bank,
    uint32 *first_unused_bank_in_mdb_cluster_p)
{
    uint8 disable_mdb_clusters, disable_eedb_data_banks, is_rif;
    uint32 current_bank, first_bank_for_phase = 0, last_bank_for_phase = 0, first_bank_for_phase_no_ll =
        0, last_bank_for_phase_no_ll = 0;
    uint32 first_unused_bank_in_mdb_cluster;
    int nof_rifs, nof_rif_banks;

    SHR_FUNC_INIT_VARS(unit);

    *outlif_bank = DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK;

    if (_SHR_IS_FLAG_SET(local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_FORCE_DATA_IN_EEDB_BANKS))
    {
        disable_mdb_clusters = TRUE;
    }
    else
    {
        SHR_IF_ERR_EXIT(local_outlif_info.disable_mdb_clusters.get(unit, &disable_mdb_clusters));
    }

    SHR_IF_ERR_EXIT(local_outlif_info.disable_eedb_data_banks.get(unit, &disable_eedb_data_banks));

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.first_bank.get(unit, logical_phase, &first_bank_for_phase));
    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.last_bank.get(unit, logical_phase, &last_bank_for_phase));
    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                    first_no_ll_bank.get(unit, logical_phase, &first_bank_for_phase_no_ll));
    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                    last_no_ll_bank.get(unit, logical_phase, &last_bank_for_phase_no_ll));

    first_unused_bank_in_mdb_cluster = DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK;

    is_rif = ((outlif_info->logical_phase == DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1)
              && (outlif_info->dbal_table_id == DBAL_TABLE_EEDB_RIF_BASIC)) ? TRUE : FALSE;

    if ((logical_phase == DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1)
        && ((outlif_info->logical_phase != DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1)
            || (outlif_info->dbal_table_id != DBAL_TABLE_EEDB_RIF_BASIC)))
    {

        nof_rifs = dnx_data_l3.rif.nof_rifs_get(unit);
        nof_rif_banks = UTILEX_DIV_ROUND_UP(nof_rifs, DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit));
        first_bank_for_phase += nof_rif_banks;
    }

    if (!disable_mdb_clusters)
    {

        if ((!ll_required) && (first_bank_for_phase_no_ll) && (!is_rif))
        {

            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_allocate_in_bank
                            (unit, local_lif_flags, logical_phase, ll_required, outlif_info, first_bank_for_phase_no_ll,
                             last_bank_for_phase_no_ll, outlif_bank, &first_unused_bank_in_mdb_cluster));
        }
        if ((*outlif_bank == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK)
            && (first_unused_bank_in_mdb_cluster == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK))
        {

            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_allocate_in_bank
                            (unit, local_lif_flags, logical_phase, ll_required, outlif_info, first_bank_for_phase,
                             last_bank_for_phase, outlif_bank, &first_unused_bank_in_mdb_cluster));
        }
    }

    if ((!disable_eedb_data_banks) && (*outlif_bank == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK))
    {

        current_bank = DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK;

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_in_eedb_bank_find
                        (unit, local_lif_flags | DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_DONT_ALLOCATE_NEW_BANK,
                         logical_phase, ll_required, outlif_info, NULL, &current_bank));

        *outlif_bank = current_bank;
    }

    if (first_unused_bank_in_mdb_cluster_p)
    {
        *first_unused_bank_in_mdb_cluster_p = first_unused_bank_in_mdb_cluster;
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_allocate(
    int unit,
    lif_mngr_local_outlif_info_t * outlif_info,
    dnx_algo_local_outlif_hw_info_t * outlif_hw_info)
{
    dnx_algo_local_outlif_logical_phase_e logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_INVALID;
    uint8 ll_required = FALSE;
    uint8 rt_has_ll = FALSE;
    uint32 outlif_bank, first_unused_bank_in_mdb_cluster, flags;
    int element, active_result_type, rv;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    sal_memset(outlif_hw_info, 0, sizeof(dnx_algo_local_outlif_hw_info_t));

    if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_REPLACE))
    {
        if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_RESERVE))
        {

            SHR_EXIT();
        }

        element = outlif_info->local_outlif;
        outlif_bank = DNX_ALGO_OUTLIF_LOCAL_LIF_TO_BANK(element);
        flags = DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_REPLACE;
    }
    else
    {
        if (!(_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_WITH_ID)))
        {
            outlif_info->local_outlif = INVALID_LOCAL_OUTLIF;
            flags = 0;
        }
        else
        {
            flags = DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_WITH_ID;
        }

        active_result_type =
            (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_RESERVE)) ?
            outlif_info->alternative_result_type : outlif_info->dbal_result_type;

        SHR_IF_ERR_EXIT(dnx_lif_mngr_eedb_table_rt_has_linked_list(unit,
                                                                   outlif_info->dbal_table_id,
                                                                   active_result_type, &rt_has_ll));
        if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_FORCE_LINKED_LIST))
        {
            ll_required = TRUE;
        }
        else if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_NO_LINKED_LIST))
        {
            ll_required = FALSE;
        }
        else
        {

            ll_required = rt_has_ll;
        }

        logical_phase = outlif_info->logical_phase;

        if ((ll_required == FALSE) && (rt_has_ll))
        {
            dbal_table_field_info_t field_info;
            rv = dbal_tables_field_info_get_no_err(unit, outlif_info->dbal_table_id, DBAL_FIELD_EEDB_LL_EXTRA_DATA, 0,
                                                   outlif_info->dbal_result_type, 0, &field_info);

            if (((rv == _SHR_E_NONE) && (field_info.field_nof_bits < EEDB_LL_DATA_MAX_SIZE))
                || (rv == _SHR_E_NOT_FOUND))
            {
                outlif_info->local_lif_flags &= (~DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_NO_LINKED_LIST);
                outlif_info->local_lif_flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_FORCE_LINKED_LIST;
                ll_required = TRUE;
            }
        }

        if ((ll_required == FALSE) && (!rt_has_ll))
        {
            uint8 found;
            dbal_to_phase_info_t dbal_to_phase_info = { 0 };
            dnx_local_outlif_ll_indication_e ll_indication;
            dbal_to_phase_info.dbal_result_type = outlif_info->dbal_result_type;
            dbal_to_phase_info.dbal_table = outlif_info->dbal_table_id;
            SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                            dbal_valid_combinations.find(unit, outlif_info->logical_phase, &dbal_to_phase_info,
                                                         &ll_indication, &found));
            if (found && ll_indication == DNX_LOCAL_OUTLIF_LL_ALWAYS)
            {
                ll_required = TRUE;
            }
        }

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_allocation_find_existing_bank_to_allocate(unit,
                                                                                        outlif_info->local_lif_flags,
                                                                                        logical_phase, ll_required,
                                                                                        outlif_info, &outlif_bank,
                                                                                        &first_unused_bank_in_mdb_cluster));

        if (outlif_bank == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK
            && first_unused_bank_in_mdb_cluster == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK && !ll_required
            && dnx_data_mdb.feature.feature_get(unit, dnx_data_mdb_feature_eedb_bank_traffic_lock))
        {
            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_allocation_find_existing_bank_to_allocate(unit,
                                                                                            outlif_info->local_lif_flags,
                                                                                            logical_phase, TRUE,
                                                                                            outlif_info, &outlif_bank,
                                                                                            NULL));
        }

        if (outlif_bank == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK)
        {
            if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_DONT_ALLOCATE_NEW_BANK))
            {
                SHR_ERR_EXIT(_SHR_E_RESOURCE,
                             "No room to allocate in existing outlif banks, and DONT_ALLOCATE_NEW_BANK flag set.");
            }

            if (first_unused_bank_in_mdb_cluster != DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK)
            {

                if (ll_required)
                {
                    int is_available = FALSE;
                    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_verify_ll_availability
                                    (unit, logical_phase, 1, &is_available));

                    if (!is_available)
                    {
                        SHR_ERR_EXIT(_SHR_E_RESOURCE, "All banks using linked list on logical phase %d are full.",
                                     logical_phase + 1);
                    }
                }

                if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_WITH_ID))
                {
                    first_unused_bank_in_mdb_cluster =
                        UTILEX_DIV_ROUND_DOWN(outlif_info->local_outlif, DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit));
                }
                SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_in_use_set
                                (unit, first_unused_bank_in_mdb_cluster, logical_phase, ll_required));
                if (ll_required)
                {
                    outlif_hw_info->flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_LL_BANK;
                }
                outlif_hw_info->flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_POINTERS;
                outlif_bank = first_unused_bank_in_mdb_cluster;
            }
            else
            {
                uint8 disable_eedb_data_banks;
                SHR_IF_ERR_EXIT(local_outlif_info.disable_eedb_data_banks.get(unit, &disable_eedb_data_banks));
                if (!disable_eedb_data_banks)
                {

                    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_in_eedb_bank_find
                                    (unit, outlif_info->local_lif_flags, logical_phase, ll_required, outlif_info,
                                     &outlif_hw_info->flags, &outlif_bank));
                }
            }

            if (outlif_bank == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK && !ll_required)
            {
                SHR_IF_ERR_EXIT(dnx_algo_local_outlif_allocation_find_existing_bank_to_allocate(unit,
                                                                                                outlif_info->local_lif_flags,
                                                                                                logical_phase, TRUE,
                                                                                                outlif_info,
                                                                                                &outlif_bank, NULL));
            }

            if (outlif_bank == DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK)
            {
                SHR_ERR_EXIT(_SHR_E_RESOURCE, "No available outlif bank with%s linked list for logical phase %d.",
                             (ll_required) ? "" : "out", logical_phase + 1);
            }
        }
    }

    if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_WITH_ID))
    {
        flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_WITH_ID;
        element = outlif_info->local_outlif;
    }

    if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_RES_IGNORE_TAG))
    {
        flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_RES_IGNORE_TAG;
    }

    if (outlif_info->local_outlif == INVALID_LOCAL_OUTLIF)
    {
        SHR_IF_ERR_EXIT(lif_mngr_db.egress_local_lif.allocate_single
                        (unit, outlif_bank, flags, (void *) outlif_info, &element));
    }
    else
    {

        element = outlif_info->local_outlif;
    }

    if (_SHR_IS_FLAG_SET(outlif_hw_info->flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_HW))
    {

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_hw_info_get(unit, element, outlif_hw_info));
    }

    outlif_info->local_outlif = element;

    if ((DNX_ALGO_OUTLIF_IS_POINTER_BIGGER_THAN_EEDB_RESOURCE) && (ll_required))
    {
        if (element >= (1 << dnx_data_lif.out_lif.outlif_eedb_banks_pointer_size_get(unit)))
        {
            SHR_ERR_EXIT(_SHR_E_FULL, "Can't allocate lif with ll for logical phase %d", logical_phase);
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_free(
    int unit,
    lif_mngr_local_outlif_info_t * outlif_info,
    dnx_algo_local_outlif_hw_info_t * outlif_hw_info)
{
    int outlif_bank, nof_free_elements;
    int deallocation_size;
    uint8 assigned;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    outlif_bank = DNX_ALGO_OUTLIF_LOCAL_LIF_TO_BANK(outlif_info->local_outlif);

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_info_to_nof_outlifs_per_entry(unit, outlif_info, &deallocation_size));

    SHR_IF_ERR_EXIT(lif_mngr_db.
                    egress_local_lif.free_several(unit, outlif_bank, deallocation_size, outlif_info->local_outlif,
                                                  (void *) outlif_info));

    sal_memset(outlif_hw_info, 0, sizeof(dnx_algo_local_outlif_hw_info_t));
    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.assigned.get(unit, outlif_bank, &assigned));

    if (assigned == DNX_ALGO_OUTLIF_BANK_ASSIGNED_TO_EEDB)
    {

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_in_eedb_bank_check_and_unassign
                        (unit, outlif_info->local_outlif, outlif_hw_info));
    }
    else
    {

        SHR_IF_ERR_EXIT(lif_mngr_db.egress_local_lif.nof_free_elements_get(unit, outlif_bank, &nof_free_elements));

        if (nof_free_elements == DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit))
        {
            uint8 ll_in_use;

            outlif_hw_info->flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_POINTERS;

            SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.ll_in_use.get(unit, outlif_bank, &ll_in_use));
            if (ll_in_use)
            {
                outlif_hw_info->flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_LL_BANK;
            }

            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_hw_info_get(unit, outlif_info->local_outlif, outlif_hw_info));

            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_in_use_unset(unit, outlif_bank));
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_ll_match_check(
    int unit,
    lif_mngr_local_outlif_info_t * outlif_info,
    int *ll_match)
{
    uint8 ll_required, alternative_ll_required;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_lif_mngr_outlif_sw_info_get
                    (unit, outlif_info->local_outlif, NULL, NULL, NULL, NULL, &alternative_ll_required, NULL));

    if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_FORCE_LINKED_LIST))
    {
        ll_required = TRUE;
    }
    else if (_SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_NO_LINKED_LIST))
    {
        ll_required = FALSE;
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_lif_mngr_eedb_table_rt_has_linked_list(unit,
                                                                   outlif_info->dbal_table_id,
                                                                   outlif_info->alternative_result_type, &ll_required));
    }

    if (alternative_ll_required || !ll_required)
    {

        *ll_match = TRUE;
    }
    else
    {

        *ll_match = FALSE;
    }

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_can_be_reused(
    int unit,
    lif_mngr_local_outlif_info_t * outlif_info,
    int *can_be_reused)
{
    dnx_algo_lif_local_outlif_resource_info_t resource_info;
    int can_be_reused_tmp, ll_match;
    uint32 original_flags;
    dnx_algo_local_outlif_logical_phase_e logical_phase;
    uint8 address_granularity;
    SHR_FUNC_INIT_VARS(unit);

    logical_phase = outlif_info->logical_phase;
    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                    address_granularity.get(unit, logical_phase, &address_granularity));

    original_flags = outlif_info->local_lif_flags;
    outlif_info->local_lif_flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_REPLACE;
    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_info_to_resource_info(unit, outlif_info, &resource_info));
    outlif_info->local_lif_flags = original_flags;

    if ((resource_info.nof_outlifs_per_alternative_entry < resource_info.nof_outlifs_per_entry)
        && _SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_RESERVE)
        && _SHR_IS_FLAG_SET(outlif_info->local_lif_flags, DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_REPLACE))
    {

        can_be_reused_tmp = TRUE;
    }
    else if (address_granularity == 30 && resource_info.nof_outlifs_per_alternative_entry == 2
             && resource_info.nof_outlifs_per_entry == 1)
    {

        can_be_reused_tmp = FALSE;
    }
    else if (resource_info.nof_outlifs_per_alternative_entry >= resource_info.nof_outlifs_per_entry)
    {

        can_be_reused_tmp = TRUE;
    }
    else
    {

        can_be_reused_tmp = FALSE;
    }

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_ll_match_check(unit, outlif_info, &ll_match));

    *can_be_reused = can_be_reused_tmp && ll_match;

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_ll_banks_init(
    int unit)
{
    int current_logical_phase;
    int nof_valid_clusters, current_cluster;
    mdb_cluster_alloc_info_t clusters[DNX_DATA_MAX_MDB_DH_MAX_NOF_DB_CLUSTERS], *cluster;
    uint8 physical_phase;
    uint8 first_ll_bank, last_ll_bank;
    SHR_FUNC_INIT_VARS(unit);

    for (current_logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_FIRST;
         current_logical_phase < DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_COUNT; current_logical_phase++)
    {

        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                        physical_phase.get(unit, current_logical_phase, &physical_phase));

        SHR_IF_ERR_EXIT(mdb_init_get_table_resources
                        (unit, EEDB_PHYSICAL_PHASE_TO_PHYSICAL_TABLE(physical_phase), clusters, &nof_valid_clusters));

        first_ll_bank = 0xff;
        last_ll_bank = 0;

        for (current_cluster = 0; current_cluster < nof_valid_clusters; current_cluster++)
        {
            cluster = &clusters[current_cluster];
            if (cluster->macro_type == MDB_EEDB_BANK)
            {

                if (cluster->cluster_idx < first_ll_bank)
                {
                    first_ll_bank = cluster->cluster_idx;
                }

                if (cluster->cluster_idx > last_ll_bank)
                {
                    last_ll_bank = cluster->cluster_idx;
                }
            }
        }

        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                        first_ll_bank.set(unit, current_logical_phase, first_ll_bank));

        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                        last_ll_bank.set(unit, current_logical_phase, last_ll_bank));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_phase_set_first_and_last_bank(
    int unit,
    uint8 logical_phase,
    int first_bank,
    int last_bank,
    int first_no_ll_bank,
    int last_no_ll_bank)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.first_bank.set(unit, logical_phase, first_bank));

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.first_no_ll_bank.set(unit, logical_phase, first_no_ll_bank));

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.last_bank.set(unit, logical_phase, last_bank));

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.last_no_ll_bank.set(unit, logical_phase, last_no_ll_bank));

    if (dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_per_phase_algo))
    {
        int outlif_bank;

        for (outlif_bank = first_bank; outlif_bank <= last_bank; outlif_bank++)
        {
            SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.
                            used_logical_phase.set(unit, outlif_bank, logical_phase));
        }

        if (last_no_ll_bank > first_no_ll_bank)
        {
            for (outlif_bank = first_no_ll_bank; outlif_bank <= last_no_ll_bank; outlif_bank++)
            {
                SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.
                                used_logical_phase.set(unit, outlif_bank, logical_phase));
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_resource_init(
    int unit)
{
    dnx_algo_res_create_data_t res_data;
    resource_tag_bitmap_utils_tag_info_t tag_set_info;
    int *bank_address_granularities, current_granularity, minimum_granularity;
    uint32 first_bank, last_bank, first_bank_no_ll, last_bank_no_ll, current_bank;
    uint8 phase_address_granularity;
    uint32 current_outlif_bank;
    dnx_algo_local_outlif_logical_phase_e logical_phase;
    dnx_algo_lif_local_outlif_resource_extra_info_t extra_info = { 0 };
    int outlifs_grain_idx = 0;

    SHR_FUNC_INIT_VARS(unit);

    bank_address_granularities = NULL;
    minimum_granularity = EEDB_MAX_GRANULARITY;
    SHR_ALLOC_SET_ZERO(bank_address_granularities, sizeof(int) * (DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit)),
                       "bank_address_granularities", "%s%s%s\r\n", EMPTY, EMPTY, EMPTY);

    for (logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_FIRST;
         logical_phase < DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_COUNT; logical_phase++)
    {
        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.first_bank.get(unit, logical_phase, &first_bank));
        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.last_bank.get(unit, logical_phase, &last_bank));
        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                        first_no_ll_bank.get(unit, logical_phase, &first_bank_no_ll));
        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                        last_no_ll_bank.get(unit, logical_phase, &last_bank_no_ll));

        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                        address_granularity.get(unit, logical_phase, &phase_address_granularity));

        for (current_bank = first_bank; current_bank <= last_bank; current_bank++)
        {
            bank_address_granularities[current_bank] = phase_address_granularity;
        }

        for (current_bank = first_bank_no_ll; current_bank <= last_bank_no_ll; current_bank++)
        {
            bank_address_granularities[current_bank] = phase_address_granularity;
        }

        if (phase_address_granularity < minimum_granularity)
        {
            minimum_granularity = phase_address_granularity;
        }
    }

    sal_memset(&res_data, 0, sizeof(res_data));

    res_data.flags = DNX_ALGO_RES_CREATE_USE_ADVANCED_ALGORITHM;
    res_data.nof_elements = DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit);
    res_data.advanced_algorithm = DNX_ALGO_RESOURCE_ADVANCED_ALGORITHM_LIF_LOCAL_OUTLIF;
    sal_strncpy(res_data.name, "lif_local_outlif 2", DNX_ALGO_RES_MNGR_MAX_NAME_LENGTH - 1);

    if (dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_data_entries_supported))
    {
        outlifs_grain_idx = 1;
    }
    sal_memset(&tag_set_info, 0, sizeof(resource_tag_bitmap_utils_tag_info_t));
    tag_set_info.force_tag = TRUE;
    tag_set_info.tags[outlifs_grain_idx] = OUTLIF_RESOURCE_ILLEGAL_TAG;
    tag_set_info.nof_elements = res_data.nof_elements;

    SHR_IF_ERR_EXIT(lif_mngr_db.egress_local_lif.alloc(unit, DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit)));
    for (current_outlif_bank = 0; current_outlif_bank < DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit); current_outlif_bank++)
    {
        if (bank_address_granularities[current_outlif_bank] == 0)
        {

            if (dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_per_phase_algo))
            {
                continue;
            }

            current_granularity = minimum_granularity;
            res_data.flags |= RESOURCE_TAG_BITMAP_CREATE_ALLOW_FORCING_TAG;
        }
        else
        {
            current_granularity = bank_address_granularities[current_outlif_bank];
        }
        res_data.first_element = OUTLIF_BANK_FIRST_INDEX(unit, current_outlif_bank);
        extra_info.granularity = current_granularity;
        extra_info.assigned =
            (bank_address_granularities[current_outlif_bank] ==
             0) ? DNX_ALGO_OUTLIF_BANK_ASSIGNED_TO_EEDB : DNX_ALGO_OUTLIF_BANK_ASSIGNED_TO_MDB;
        SHR_IF_ERR_EXIT(lif_mngr_db.
                        egress_local_lif.create(unit, current_outlif_bank, &res_data, (void *) &extra_info));

        if (bank_address_granularities[current_outlif_bank] == 0)
        {
            res_data.flags &= ~RESOURCE_TAG_BITMAP_CREATE_ALLOW_FORCING_TAG;

            tag_set_info.element = res_data.first_element;
            SHR_IF_ERR_EXIT(lif_mngr_db.egress_local_lif.advanced_algorithm_info_set(unit,
                                                                                     current_outlif_bank,
                                                                                     &tag_set_info));
        }
    }

exit:
    SHR_FREE(bank_address_granularities);
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_calc_required_cluster_outlif_banks(
    int unit,
    mdb_cluster_alloc_info_t * init_clusters_info,
    int nof_required_outlif_banks[DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES])
{
    int current_cluster, current_bank_in_cluster, nof_banks_per_cluster, current_bank;
    uint32 nof_entries_in_cluster;
    mdb_cluster_alloc_info_t *current_cluster_info;
    mdb_macro_types_e current_macro_type, first_macro_type, last_macro_type;
    mdb_cluster_alloc_info_t clusters[DNX_DATA_MAX_MDB_DH_MAX_NOF_DB_CLUSTERS];
    int nof_valid_clusters;
    int current_physical_phase;
    dbal_physical_tables_e physical_table;
    int physical_phase;
    int total_outlif_banks = 0;
    int max_phase;

    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_per_phase_algo))
    {
        max_phase = NOF_EEDB_PHASE_PAIRS;
    }
    else
    {
        max_phase = DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES;
    }

    for (current_physical_phase = 0; current_physical_phase < max_phase; current_physical_phase++)
    {
        if (!dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_per_phase_algo))
        {
            physical_phase = EEDB_PHYSICAL_TABLE_PHASE_PAIR_TO_FIRST_PHYSICAL_PHASE(current_physical_phase);
        }
        else
        {
            physical_phase = current_physical_phase;
        }

        physical_table = EEDB_PHYSICAL_PHASE_TO_PHYSICAL_TABLE(physical_phase);

        SHR_IF_ERR_EXIT(mdb_init_get_table_resources(unit, physical_table, clusters, &nof_valid_clusters));

        first_macro_type = MDB_MACRO_A;
        last_macro_type = MDB_MACRO_B;
        current_bank = 0;

        for (current_macro_type = first_macro_type; current_macro_type <= last_macro_type; current_macro_type++)
        {

            SHR_IF_ERR_EXIT(mdb_eedb_table_nof_entries_per_cluster_type_get
                            (unit, physical_table, current_macro_type, &nof_entries_in_cluster));

            nof_banks_per_cluster = UTILEX_DIV_ROUND_UP(nof_entries_in_cluster, DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit));

            if (UTILEX_ALIGN_UP(total_outlif_banks, nof_banks_per_cluster) > total_outlif_banks)
            {
                total_outlif_banks++;
                nof_required_outlif_banks[current_physical_phase]++;
            }
            nof_required_outlif_banks[current_physical_phase] = UTILEX_ALIGN_UP(current_bank, nof_banks_per_cluster);

            for (current_cluster = 0; current_cluster < nof_valid_clusters; current_cluster++)
            {
                current_cluster_info = &clusters[current_cluster];
                if (current_cluster_info->dbal_physical_table_id == physical_table
                    && current_cluster_info->macro_type == current_macro_type)
                {
                    if (current_bank == DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit))
                    {
                        SHR_ERR_EXIT(_SHR_E_FULL,
                                     "The input to the outlif bank allocation algorithm resulted in assigning more banks than the system supports."
                                     "See comment in code for possible solutions.");
                    }

                    for (current_bank_in_cluster = 0; current_bank_in_cluster < nof_banks_per_cluster;
                         current_bank_in_cluster++, current_bank++)
                    {
                        nof_required_outlif_banks[current_physical_phase]++;
                        total_outlif_banks++;
                    }
                }
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_perform_bank_assignment(
    int unit,
    int starting_outlif_bank,
    int starting_no_ll_outlif_bank,
    dbal_physical_tables_e physical_table,
    int *first_outlif_bank,
    int *last_outlif_bank,
    int *first_no_ll_outlif_bank,
    int *last_no_ll_outlif_bank,
    mdb_cluster_alloc_info_t * init_clusters_info,
    int *nof_init_clusters,
    uint8 optimize_cluster_outlif_banks,
    int nof_allowed_ll_outlif_banks)
{
    int current_cluster, current_bank_in_cluster, nof_banks_per_cluster, current_bank, current_no_ll_bank;
    uint32 nof_entries_in_cluster;
    mdb_cluster_alloc_info_t *current_cluster_info, *current_init_cluster;
    mdb_macro_types_e current_macro_type, first_macro_type, last_macro_type;
    mdb_cluster_alloc_info_t clusters[DNX_DATA_MAX_MDB_DH_MAX_NOF_DB_CLUSTERS];
    int nof_valid_clusters;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(mdb_init_get_table_resources(unit, physical_table, clusters, &nof_valid_clusters));

    first_macro_type = MDB_MACRO_A;
    last_macro_type = MDB_MACRO_B;
    current_bank = starting_outlif_bank;
    current_no_ll_bank = starting_no_ll_outlif_bank;
    *first_outlif_bank = DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit);
    *first_no_ll_outlif_bank = DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit);

    for (current_macro_type = first_macro_type; current_macro_type <= last_macro_type; current_macro_type++)
    {

        SHR_IF_ERR_EXIT(mdb_eedb_table_nof_entries_per_cluster_type_get
                        (unit, physical_table, current_macro_type, &nof_entries_in_cluster));

        nof_banks_per_cluster = UTILEX_DIV_ROUND_UP(nof_entries_in_cluster, DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit));

        current_bank = UTILEX_ALIGN_UP(current_bank, nof_banks_per_cluster);
        current_no_ll_bank = UTILEX_ALIGN_UP(current_no_ll_bank, nof_banks_per_cluster);

        for (current_cluster = 0; current_cluster < nof_valid_clusters; current_cluster++)
        {
            current_cluster_info = &clusters[current_cluster];
            if (current_cluster_info->dbal_physical_table_id == physical_table
                && current_cluster_info->macro_type == current_macro_type)
            {
                if (current_bank == DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit))
                {

                    SHR_ERR_EXIT(_SHR_E_FULL,
                                 "The input to the outlif bank allocation algorithm resulted in assigning more banks than the system supports."
                                 "See comment in code for possible solutions.");
                }

                if (current_bank < *first_outlif_bank)
                {

                    *first_outlif_bank = current_bank;
                }

                current_init_cluster = &init_clusters_info[*nof_init_clusters];

                sal_memcpy(current_init_cluster, current_cluster_info, sizeof(mdb_cluster_alloc_info_t));

                if (DNX_ALGO_OUTLIF_IS_POINTER_BIGGER_THAN_EEDB_RESOURCE)
                {
                    if (optimize_cluster_outlif_banks)
                    {
                        if ((current_bank - starting_outlif_bank + nof_banks_per_cluster) > nof_allowed_ll_outlif_banks)
                        {
                            if (current_no_ll_bank < *first_no_ll_outlif_bank)
                            {

                                *first_no_ll_outlif_bank = current_no_ll_bank;
                            }

                            current_init_cluster->logical_start_address =
                                current_no_ll_bank * DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit);

                            for (current_bank_in_cluster = 0; current_bank_in_cluster < nof_banks_per_cluster;
                                 current_bank_in_cluster++, current_no_ll_bank++)
                            {

                                SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.
                                                assigned.set(unit, current_no_ll_bank,
                                                             DNX_ALGO_OUTLIF_BANK_ASSIGNED_TO_MDB));
                            }
                            (*nof_init_clusters)++;
                            continue;
                        }
                    }
                }

                current_init_cluster->logical_start_address = current_bank * DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit);

                for (current_bank_in_cluster = 0; current_bank_in_cluster < nof_banks_per_cluster;
                     current_bank_in_cluster++, current_bank++)
                {

                    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.assigned.set(unit, current_bank,
                                                                                    DNX_ALGO_OUTLIF_BANK_ASSIGNED_TO_MDB));
                }

                (*nof_init_clusters)++;
            }
        }
    }

    if (*first_outlif_bank == DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit))
    {

        *first_outlif_bank = 1;
        *last_outlif_bank = 0;
    }
    else
    {
        *last_outlif_bank = current_bank - 1;
    }

    if (*first_no_ll_outlif_bank == DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit))
    {

        *first_no_ll_outlif_bank = 1;
        *last_no_ll_outlif_bank = 0;
    }
    else
    {
        *last_no_ll_outlif_bank = current_no_ll_bank - 1;
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_bank_assign_range_to_eedb_phy_table(
    int unit,
    int phase,
    int current_outlif_bank,
    int current_no_ll_outlif_bank,
    int *next_outlif_bank,
    int *next_no_ll_outlif_bank,
    mdb_cluster_alloc_info_t * init_clusters_info,
    int *nof_init_clusters,
    uint8 optimize_cluster_outlif_banks,
    int nof_allowed_ll_outlif_banks)
{
    int physical_phase = phase;
    dbal_physical_tables_e physical_table;
    int first_outlif_bank = 0, last_outlif_bank = 0, first_no_ll_outlif_bank = 0, last_no_ll_outlif_bank = 0;
    uint8 first_logical_phase, second_logical_phase;
    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_per_phase_algo))
    {
        physical_phase = EEDB_PHYSICAL_TABLE_PHASE_PAIR_TO_FIRST_PHYSICAL_PHASE(phase);
    }
    else
    {
        physical_phase = phase;
    }

    physical_table = EEDB_PHYSICAL_PHASE_TO_PHYSICAL_TABLE(physical_phase);

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_perform_bank_assignment
                    (unit, current_outlif_bank, current_no_ll_outlif_bank, physical_table,
                     &first_outlif_bank, &last_outlif_bank, &first_no_ll_outlif_bank, &last_no_ll_outlif_bank,
                     init_clusters_info, nof_init_clusters, optimize_cluster_outlif_banks,
                     nof_allowed_ll_outlif_banks));

    SHR_IF_ERR_EXIT(local_outlif_info.
                    physical_phase_to_logical_phase_map.get(unit, physical_phase, &first_logical_phase));

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_phase_set_first_and_last_bank
                    (unit, first_logical_phase, first_outlif_bank, last_outlif_bank, first_no_ll_outlif_bank,
                     last_no_ll_outlif_bank));

    SHR_IF_ERR_EXIT(local_outlif_info.physical_phase_to_logical_phase_map.get(unit,
                                                                              EEDB_PHYSICAL_PHASE_TO_PARTNER_PHASE
                                                                              (physical_phase), &second_logical_phase));

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_phase_set_first_and_last_bank
                    (unit, second_logical_phase, first_outlif_bank, last_outlif_bank, first_no_ll_outlif_bank,
                     last_no_ll_outlif_bank));

    if (last_outlif_bank >= first_outlif_bank)
    {
        *next_outlif_bank = last_outlif_bank + 1;
    }

    if (last_no_ll_outlif_bank >= first_no_ll_outlif_bank)
    {
        *next_no_ll_outlif_bank = last_no_ll_outlif_bank + 1;
    }

exit:
    SHR_FUNC_EXIT;
}

void
dnx_algo_local_outlif_sort_required_ll_outlif_banks(
    int unit,
    int nof_required_outlif_banks[DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES],
    int nof_allowed_ll_outlif_banks[DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES],
    uint8 phase_pair_mode)
{
    int tmp_count =
        0, idx, idx2, pos, min, nof_phase_required_outlif_banks, nof_required_outlif_banks_idx, current_physical_phase;
    int fair_nof_outlif_banks_per_phase = DNX_ALGO_LOCAL_OUTLIF_LL_CAPABLE_NOF_BANKS(unit) / NOF_EEDB_PHASE_PAIRS;
    int nof_required_outlif_banks_sorted[DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES] = { 0 };
    int nof_required_outlif_banks_idx_sorted[DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES] = { 0 };
    int end_idx;

    if (phase_pair_mode)
    {
        end_idx = NOF_EEDB_PHASE_PAIRS;
    }
    else
    {
        end_idx = DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES;
        fair_nof_outlif_banks_per_phase =
            DNX_ALGO_LOCAL_OUTLIF_LL_CAPABLE_NOF_BANKS(unit) / (DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES);
    }

    for (idx = 0; idx < end_idx; idx++)
    {
        pos = 0;
        min = nof_required_outlif_banks[pos];

        for (idx2 = 0; idx2 < end_idx; idx2++)
        {
            if (((nof_required_outlif_banks[idx2] > 0) && (nof_required_outlif_banks[idx2] < min)) || (min == 0))
            {
                min = nof_required_outlif_banks[idx2];
                pos = idx2;
            }
        }
        nof_required_outlif_banks[pos] = 0;
        nof_required_outlif_banks_sorted[idx] = min;
        nof_required_outlif_banks_idx_sorted[idx] = pos;
    }

    for (current_physical_phase = 0; current_physical_phase < end_idx; current_physical_phase++)
    {
        nof_phase_required_outlif_banks = nof_required_outlif_banks_sorted[current_physical_phase];
        nof_required_outlif_banks_idx = nof_required_outlif_banks_idx_sorted[current_physical_phase];
        if (nof_phase_required_outlif_banks <= fair_nof_outlif_banks_per_phase)
        {
            nof_allowed_ll_outlif_banks[nof_required_outlif_banks_idx] = nof_phase_required_outlif_banks;
        }
        else if ((tmp_count + nof_phase_required_outlif_banks) <=
                 ((current_physical_phase + 1) * fair_nof_outlif_banks_per_phase))
        {
            nof_allowed_ll_outlif_banks[nof_required_outlif_banks_idx] = nof_phase_required_outlif_banks;
        }
        else
        {
            int phase_idx = current_physical_phase + 1;
            nof_allowed_ll_outlif_banks[nof_required_outlif_banks_idx] =
                (phase_idx * fair_nof_outlif_banks_per_phase) - tmp_count;
        }
        tmp_count += nof_allowed_ll_outlif_banks[nof_required_outlif_banks_idx];
    }
}

static shr_error_e
dnx_algo_local_outlif_mdb_bank_database_init(
    int unit,
    mdb_cluster_alloc_info_t * init_clusters_info,
    int *nof_init_clusters)
{
    uint32 eedb_pair_granularities[NOF_EEDB_PHASE_PAIRS];
    int current_eedb_data_bank, current_eedb_no_ll_data_bank, current_granularity;
    dnx_algo_local_outlif_logical_phase_e rif_logical_phase;
    uint8 rif_physical_phase;
    int current_physical_phase_pair, rif_phase_pair;
    int nof_rifs, nof_rif_banks;
    int nof_required_outlif_banks[DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES] = { 0 };
    int nof_allowed_ll_outlif_banks[DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES] = { 0 };
    int total_required_outlif_banks = 0;
    uint8 optimize_cluster_outlif_banks = FALSE;

    SHR_FUNC_INIT_VARS(unit);

    for (current_physical_phase_pair = 0;
         current_physical_phase_pair < NOF_EEDB_PHASE_PAIRS; current_physical_phase_pair++)
    {
        SHR_IF_ERR_EXIT(mdb_eedb_table_data_granularity_get
                        (unit,
                         EEDB_PHYSICAL_PHASE_TO_PHYSICAL_TABLE(EEDB_PHYSICAL_TABLE_PHASE_PAIR_TO_FIRST_PHYSICAL_PHASE
                                                               (current_physical_phase_pair)),
                         &eedb_pair_granularities[current_physical_phase_pair]));
    }

    if (DNX_ALGO_OUTLIF_IS_POINTER_BIGGER_THAN_EEDB_RESOURCE)
    {
        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_calc_required_cluster_outlif_banks
                        (unit, init_clusters_info, nof_required_outlif_banks));
        for (current_physical_phase_pair = 0; current_physical_phase_pair < NOF_EEDB_PHASE_PAIRS;
             current_physical_phase_pair++)
        {
            total_required_outlif_banks += nof_required_outlif_banks[current_physical_phase_pair];
        }

        if (total_required_outlif_banks > DNX_ALGO_LOCAL_OUTLIF_LL_CAPABLE_NOF_BANKS(unit))
        {
            optimize_cluster_outlif_banks = TRUE;

            dnx_algo_local_outlif_sort_required_ll_outlif_banks(unit, nof_required_outlif_banks,
                                                                nof_allowed_ll_outlif_banks, TRUE);
        }
    }

    rif_logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1;
    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                    physical_phase.get(unit, rif_logical_phase, &rif_physical_phase));
    rif_phase_pair = EEDB_PHYSICAL_TABLE_PHYSICAL_PHASE_TO_PHASE_PAIR(rif_physical_phase);
    current_eedb_data_bank = 0;
    current_eedb_no_ll_data_bank = DNX_ALGO_LOCAL_OUTLIF_LL_CAPABLE_NOF_BANKS(unit);
    *nof_init_clusters = 0;

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_assign_range_to_eedb_phy_table
                    (unit, rif_phase_pair, current_eedb_data_bank, current_eedb_no_ll_data_bank,
                     &current_eedb_data_bank, &current_eedb_no_ll_data_bank, init_clusters_info, nof_init_clusters,
                     optimize_cluster_outlif_banks, nof_allowed_ll_outlif_banks[rif_phase_pair]));

    nof_rifs = dnx_data_l3.rif.nof_rifs_get(unit);
    nof_rif_banks = UTILEX_DIV_ROUND_UP(nof_rifs, DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit));

    if (current_eedb_data_bank < nof_rif_banks)
    {
        current_eedb_data_bank = nof_rif_banks;
    }

    for (current_granularity = EEDB_GRANULARITY_UNIT; current_granularity <= EEDB_MAX_GRANULARITY;
         current_granularity += EEDB_GRANULARITY_UNIT)
    {
        for (current_physical_phase_pair = 0;
             current_physical_phase_pair < NOF_EEDB_PHASE_PAIRS; current_physical_phase_pair++)
        {
            if ((current_physical_phase_pair != rif_phase_pair) &&
                (eedb_pair_granularities[current_physical_phase_pair] == current_granularity))

            {
                SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_assign_range_to_eedb_phy_table
                                (unit, current_physical_phase_pair, current_eedb_data_bank,
                                 current_eedb_no_ll_data_bank, &current_eedb_data_bank, &current_eedb_no_ll_data_bank,
                                 init_clusters_info, nof_init_clusters, optimize_cluster_outlif_banks,
                                 nof_allowed_ll_outlif_banks[current_physical_phase_pair]));
            }
        }
    }

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_resource_init(unit));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_per_phase_db_bank_to_eedb_phy_assign(
    int unit,
    int physical_phase,
    int current_outlif_bank,
    int current_no_ll_outlif_bank,
    int *next_outlif_bank,
    int *next_no_ll_outlif_bank,
    mdb_cluster_alloc_info_t * init_clusters_info,
    int *nof_init_clusters,
    uint8 optimize_cluster_outlif_banks,
    int nof_allowed_ll_outlif_banks)
{
    dbal_physical_tables_e physical_table;
    int first_outlif_bank = 0, last_outlif_bank = 0, first_no_ll_outlif_bank = 0, last_no_ll_outlif_bank = 0;
    uint8 logical_phase;

    SHR_FUNC_INIT_VARS(unit);

    physical_table = EEDB_PHYSICAL_PHASE_TO_PHYSICAL_TABLE(physical_phase);

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_perform_bank_assignment
                    (unit, current_outlif_bank, current_no_ll_outlif_bank, physical_table,
                     &first_outlif_bank, &last_outlif_bank, &first_no_ll_outlif_bank, &last_no_ll_outlif_bank,
                     init_clusters_info, nof_init_clusters, optimize_cluster_outlif_banks,
                     nof_allowed_ll_outlif_banks));

    SHR_IF_ERR_EXIT(local_outlif_info.physical_phase_to_logical_phase_map.get(unit, physical_phase, &logical_phase));

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_phase_set_first_and_last_bank
                    (unit, logical_phase, first_outlif_bank, last_outlif_bank, first_no_ll_outlif_bank,
                     last_no_ll_outlif_bank));

    if (last_outlif_bank >= first_outlif_bank)
    {
        *next_outlif_bank = last_outlif_bank + 1;
    }

    if (last_no_ll_outlif_bank >= first_no_ll_outlif_bank)
    {
        *next_no_ll_outlif_bank = last_no_ll_outlif_bank + 1;
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_per_phase_db_init(
    int unit,
    mdb_cluster_alloc_info_t * init_clusters_info,
    int *nof_init_clusters)
{
    uint32 eedb_phase_granularities[DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES];
    int current_eedb_data_bank, current_eedb_no_ll_data_bank, current_granularity;
    dnx_algo_local_outlif_logical_phase_e rif_logical_phase;
    uint8 rif_physical_phase;
    int current_phase;
    int nof_required_outlif_banks[DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES] = { 0 };
    int nof_allowed_ll_outlif_banks[DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES] = { 0 };
    int total_required_outlif_banks = 0;
    uint8 optimize_cluster_outlif_banks = FALSE;
    int current_physical_phase;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_calc_required_cluster_outlif_banks
                    (unit, init_clusters_info, nof_required_outlif_banks));

    LOG_DEBUG(BSL_LOG_MODULE,
              (BSL_META_U(unit, "Number of required ll outlif banks per phase: {%d, %d, %d, %d, %d, %d, %d, %d} \n"),
               nof_required_outlif_banks[0], nof_required_outlif_banks[1], nof_required_outlif_banks[2],
               nof_required_outlif_banks[3], nof_required_outlif_banks[4], nof_required_outlif_banks[5],
               nof_required_outlif_banks[6], nof_required_outlif_banks[7]));

    for (current_phase = 0; current_phase < DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES; current_phase++)
    {
        SHR_IF_ERR_EXIT(mdb_eedb_table_data_granularity_get
                        (unit,
                         EEDB_PHYSICAL_PHASE_TO_PHYSICAL_TABLE(current_phase),
                         &eedb_phase_granularities[current_phase]));

        total_required_outlif_banks += nof_required_outlif_banks[current_phase];
    }

    if (total_required_outlif_banks > DNX_ALGO_LOCAL_OUTLIF_LL_CAPABLE_NOF_BANKS(unit))
    {
        optimize_cluster_outlif_banks = TRUE;

        dnx_algo_local_outlif_sort_required_ll_outlif_banks(unit, nof_required_outlif_banks,
                                                            nof_allowed_ll_outlif_banks, FALSE);

        LOG_DEBUG(BSL_LOG_MODULE,
                  (BSL_META_U
                   (unit,
                    "Number of allowed (after sorting) ll outlif banks per phase: {%d, %d, %d, %d, %d, %d, %d, %d} \n"),
                   nof_allowed_ll_outlif_banks[0], nof_allowed_ll_outlif_banks[1], nof_allowed_ll_outlif_banks[2],
                   nof_allowed_ll_outlif_banks[3], nof_allowed_ll_outlif_banks[4], nof_allowed_ll_outlif_banks[5],
                   nof_allowed_ll_outlif_banks[6], nof_allowed_ll_outlif_banks[7]));
    }

    rif_logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1;
    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                    physical_phase.get(unit, rif_logical_phase, &rif_physical_phase));

    current_eedb_data_bank = 0;
    *nof_init_clusters = 0;

    current_eedb_no_ll_data_bank = DNX_ALGO_LOCAL_OUTLIF_LL_CAPABLE_NOF_BANKS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_per_phase_db_bank_to_eedb_phy_assign
                    (unit, rif_physical_phase, current_eedb_data_bank, current_eedb_no_ll_data_bank,
                     &current_eedb_data_bank, &current_eedb_no_ll_data_bank, init_clusters_info, nof_init_clusters,
                     optimize_cluster_outlif_banks, nof_allowed_ll_outlif_banks[rif_physical_phase]));

    for (current_granularity = EEDB_GRANULARITY_UNIT; current_granularity <= EEDB_MAX_GRANULARITY;
         current_granularity += EEDB_GRANULARITY_UNIT)
    {
        for (current_physical_phase = 0;
             current_physical_phase < DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES; current_physical_phase++)
        {
            if ((current_physical_phase != rif_physical_phase) &&
                (eedb_phase_granularities[current_physical_phase] == current_granularity))
            {
                SHR_IF_ERR_EXIT(dnx_algo_local_outlif_per_phase_db_bank_to_eedb_phy_assign
                                (unit, current_physical_phase, current_eedb_data_bank,
                                 current_eedb_no_ll_data_bank, &current_eedb_data_bank, &current_eedb_no_ll_data_bank,
                                 init_clusters_info, nof_init_clusters, optimize_cluster_outlif_banks,
                                 nof_allowed_ll_outlif_banks[current_physical_phase]));
            }
        }
    }

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_resource_init(unit));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_db_init(
    int unit,
    mdb_cluster_alloc_info_t * init_clusters_info,
    int *nof_init_clusters)
{
    SHR_FUNC_INIT_VARS(unit);

    if (!dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_per_phase_algo))
    {
        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_mdb_bank_database_init(unit, init_clusters_info, nof_init_clusters));
    }
    else
    {
        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_per_phase_db_init(unit, init_clusters_info, nof_init_clusters));
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_ll_indication_get_by_name(
    int unit,
    char *ll_indicaiton_name_str,
    dnx_local_outlif_ll_indication_e * ll_indication)
{
    SHR_FUNC_INIT_VARS(unit);

    if (sal_strncasecmp(ll_indicaiton_name_str, "Mandatory", SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH) == 0)
    {
        *ll_indication = DNX_LOCAL_OUTLIF_LL_ALWAYS;
    }
    else if (sal_strncasecmp(ll_indicaiton_name_str, "Optional", SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH) == 0)
    {
        *ll_indication = DNX_LOCAL_OUTLIF_LL_OPTIONAL;
    }
    else if (sal_strncasecmp(ll_indicaiton_name_str, "Never", SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH) == 0)
    {
        *ll_indication = DNX_LOCAL_OUTLIF_LL_NEVER;
    }
    else if (sal_strncasecmp(ll_indicaiton_name_str, "NA", SHR_SAND_DEFAULT_MAX_STRING_OPERATION_LENGTH) == 0)
    {
        *ll_indication = DNX_LOCAL_OUTLIF_LL_OPTIONAL;
    }
    else
    {
        SHR_ERR_EXIT(_SHR_E_INTERNAL, "Unrecognized LL_Allocation token: %s", ll_indicaiton_name_str);
    }

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_phases_info_init(
    int unit)
{
    char etps_to_phases_xml_path[RHFILE_MAX_SIZE];
    void *curTop = NULL, *curPhase;
    char *image_name = NULL;
    uint8 success;
    uint8 is_standard_image = FALSE;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_pp_prgm_device_image_name_get(unit, &image_name));
    SHR_IF_ERR_EXIT(dnx_pp_prgm_default_image_check(unit, &is_standard_image));

    if (is_standard_image)
    {
        sal_strncpy(etps_to_phases_xml_path, "mdb/auto_generated/", RHFILE_MAX_SIZE - 1);
    }
    else
    {
        sal_strncpy(etps_to_phases_xml_path, "bare_metal/mdb/auto_generated/", RHFILE_MAX_SIZE - 1);
    }
    sal_strncat_s(etps_to_phases_xml_path, image_name, sizeof(etps_to_phases_xml_path));
    sal_strncat_s(etps_to_phases_xml_path, "/", sizeof(etps_to_phases_xml_path));
    sal_strncat_s(etps_to_phases_xml_path, image_name, sizeof(etps_to_phases_xml_path));
    sal_strncat_s(etps_to_phases_xml_path, "_etps_in_eedb_phases.xml", sizeof(etps_to_phases_xml_path));

    if (is_standard_image)
    {
        curTop =
            dbx_pre_compiled_lif_phases_top_get(unit, etps_to_phases_xml_path, "PhasesEedbCatalog",
                                                CONF_OPEN_PER_DEVICE);
    }
    else
    {
        curTop = dbx_pre_compiled_lif_phases_top_get(unit, etps_to_phases_xml_path, "PhasesEedbCatalog", 0);
    }
    if (curTop == NULL)
    {
        SHR_ERR_EXIT(_SHR_E_NOT_FOUND, "Cannot find etps to phase XML file: %s\n", etps_to_phases_xml_path);
    }

    RHDATA_ITERATOR(curPhase, curTop, "EedbPhase")
    {
        int logical_phase = 0;
        int nof_mappings = 0;
        char phase_name[10];
        void *curElement;
        sw_state_htbl_init_info_t hash_tbl_init_info;

        RHDATA_GET_XSTR_STOP(curPhase, "Name", phase_name, 10);
        RHDATA_GET_INT_STOP(curPhase, "NumOfMappings", nof_mappings);

        logical_phase = phase_name[5] - 'A';

        sal_memset(&hash_tbl_init_info, 0, sizeof(sw_state_htbl_init_info_t));

        hash_tbl_init_info.max_nof_elements = nof_mappings;
        hash_tbl_init_info.expected_nof_elements = hash_tbl_init_info.max_nof_elements;
        hash_tbl_init_info.print_cb_name = "dnx_algo_lif_local_outlif_valid_combinations_print_cb";

        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                        dbal_valid_combinations.create(unit, logical_phase, &hash_tbl_init_info));

        RHDATA_ITERATOR(curElement, curPhase, "Element")
        {

            char dbal_table_name[DBAL_MAX_STRING_LENGTH], dbal_result_type_name[DBAL_MAX_STRING_LENGTH],
                ll_indication_name[DBAL_MAX_STRING_LENGTH] = { 0 };
            dbal_tables_e dbal_table_id;
            int is_table_active;
            int result_type;
            dbal_to_phase_info_t dbal_to_phase_info;
            dnx_local_outlif_ll_indication_e ll_indication = DNX_LOCAL_OUTLIF_LL_OPTIONAL;

            RHDATA_GET_XSTR_STOP(curElement, "AppDb", dbal_table_name, DBAL_MAX_STRING_LENGTH);
            RHDATA_GET_XSTR_STOP(curElement, "ResultType", dbal_result_type_name, DBAL_MAX_STRING_LENGTH);
            RHDATA_GET_XSTR_STOP(curElement, "LL_Allocation", ll_indication_name, DBAL_MAX_STRING_LENGTH);

            SHR_IF_ERR_EXIT(dbal_logical_table_string_to_id(unit, dbal_table_name, &dbal_table_id));
            SHR_IF_ERR_EXIT(dbal_tables_is_table_active(unit, dbal_table_id, &is_table_active));
            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_ll_indication_get_by_name(unit, ll_indication_name, &ll_indication));
            if (!is_table_active)
            {
                continue;
            }

            if (sal_strncmp(dbal_result_type_name, "", DBAL_MAX_STRING_LENGTH) == 0)
            {
                result_type = -1;
            }
            else
            {
                SHR_IF_ERR_EXIT(dbal_tables_result_type_by_name_get
                                (unit, dbal_table_id, dbal_result_type_name, &result_type));
            }
            sal_memset(&dbal_to_phase_info, 0, sizeof(dbal_to_phase_info));
            dbal_to_phase_info.dbal_result_type = result_type;
            dbal_to_phase_info.dbal_table = dbal_table_id;
            SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                            dbal_valid_combinations.insert(unit, logical_phase, &dbal_to_phase_info, &ll_indication,
                                                           &success));
            if (success == 0)
            {
                SHR_ERR_EXIT(_SHR_E_INTERNAL,
                             "Internal error - failed to add phase combinations entry to hash table: logical phase %d, dbal table %s, result type %s",
                             logical_phase, dbal_table_name, dbal_result_type_name);
            }
        }
    }

exit:
    dbx_xml_top_close(curTop);
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_phase_data_init(
    int unit)
{
    dnx_algo_local_outlif_logical_phase_e logical_phase;
    uint32 address_granularity;
    int physical_phase;
    int mapped_physical_phase[DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_COUNT] = { 0 };
    SHR_FUNC_INIT_VARS(unit);

    for (logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_FIRST;
         logical_phase < DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_COUNT; logical_phase++)
    {
        physical_phase =
            (dnx_data_lif.out_lif.logical_to_physical_phase_map_get(unit, logical_phase + 1))->physical_phase;

        if (physical_phase == -1)
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Soc property outlif_logical_to_physical_phase_map must have a valid value "
                         "for phases 1-%d. Phase %d didn't have any.", DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_COUNT,
                         logical_phase + 1);
        }

        if (mapped_physical_phase[physical_phase])
        {
            SHR_ERR_EXIT(_SHR_E_CONFIG, "Two logical phases were set with the same physical phase %d.", physical_phase);
        }

        mapped_physical_phase[physical_phase] = TRUE;

        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.physical_phase.set(unit, logical_phase, physical_phase));

        SHR_IF_ERR_EXIT(local_outlif_info.physical_phase_to_logical_phase_map.set(unit, physical_phase, logical_phase));

        SHR_IF_ERR_EXIT(mdb_eedb_table_data_granularity_get
                        (unit, EEDB_PHYSICAL_PHASE_TO_PHYSICAL_TABLE(physical_phase), &address_granularity));

        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                        address_granularity.set(unit, logical_phase, address_granularity));
    }

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_phases_info_init(unit));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_databases_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_phase_data_init(unit));

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_ll_banks_init(unit));

exit:
    SHR_FUNC_EXIT;
}

static shr_error_e
dnx_algo_local_outlif_databases_allocate(
    int unit)
{
    sw_state_ll_init_info_t used_data_banks_list_init_info;
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.init(unit));

    SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.alloc(unit, DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit)));

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.alloc(unit, DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_COUNT));

    SHR_IF_ERR_EXIT(local_outlif_info.
                    physical_phase_to_logical_phase_map.alloc(unit, DBAL_NOF_ENUM_MDB_EEDB_PHASE_VALUES));

    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                    bank_occupation_bitmap.alloc_bitmap(unit, dnx_data_mdb.eedb.nof_eedb_banks_get(unit)));

    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                    outlif_prefix_occupation_bitmap.alloc_bitmap(unit, 1 << dnx_data_mdb.eedb.bank_id_bits_get(unit)));

    sal_memset(&used_data_banks_list_init_info, 0, sizeof(sw_state_ll_init_info_t));
    used_data_banks_list_init_info.max_nof_elements = dnx_data_mdb.eedb.nof_eedb_banks_get(unit);
    used_data_banks_list_init_info.nof_heads = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_COUNT;

    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                    used_data_bank_per_logical_phase.create_empty(unit, &used_data_banks_list_init_info));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_rif_init(
    int unit)
{
    int current_rif_bank, nof_rif_banks;
    dnx_algo_local_outlif_logical_phase_e rif_logical_phase;
    int nof_rifs;
    uint8 rif_physical_phase, partner_logical_phase;
    uint32 first_rif_bank, last_rif_bank, nof_rif_banks_in_mdb_cluster;

    uint8 address_granularity = 0;
    int nof_outlifs_per_entry = 0, nof_eedb_banks_per_outlif_bank = 0;

    SHR_FUNC_INIT_VARS(unit);

    if (dnx_data_lif.out_lif.feature_get(unit, dnx_data_lif_out_lif_per_phase_algo))
    {

        SHR_EXIT();
    }

    nof_rifs = dnx_data_l3.rif.nof_rifs_get(unit);
    nof_rif_banks = UTILEX_DIV_ROUND_UP(nof_rifs, DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit));

    if (nof_rif_banks > 0)
    {
        rif_logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1;

        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.last_bank.get(unit, rif_logical_phase, &last_rif_bank));
        SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.first_bank.get(unit, rif_logical_phase, &first_rif_bank));

        nof_rif_banks_in_mdb_cluster = (last_rif_bank >= first_rif_bank) ? last_rif_bank - first_rif_bank + 1 : 0;

        if (nof_rif_banks_in_mdb_cluster < nof_rif_banks)
        {
            int nof_required_eedb_banks, is_available;

            SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                            address_granularity.get(unit, rif_logical_phase, &address_granularity));

            if (address_granularity == 0)
            {
                SHR_IF_ERR_EXIT(_SHR_E_INTERNAL);
            }
            nof_outlifs_per_entry = EEDB_MAX_DATA_ENTRY_SIZE / address_granularity;
            nof_eedb_banks_per_outlif_bank =
                DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit) /
                (dnx_data_mdb.dh.macro_type_info_get(unit, MDB_EEDB_BANK)->nof_rows * nof_outlifs_per_entry);

            nof_required_eedb_banks = (nof_rif_banks - nof_rif_banks_in_mdb_cluster) * nof_eedb_banks_per_outlif_bank;

            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_verify_ll_availability
                            (unit, rif_logical_phase, nof_required_eedb_banks, &is_available));

            if (!is_available)
            {
                SHR_ERR_EXIT(_SHR_E_INTERNAL,
                             "There are not enough MDB clusters or eedb banks available for the number of "
                             "rifs declared in soc property rif_id_max.\n" "rif_id_max=0x%08x rifs.", nof_rifs);
            }

            for (current_rif_bank = nof_rif_banks_in_mdb_cluster; current_rif_bank < nof_rif_banks; current_rif_bank++)
            {
                SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_prefix_for_eedb_bank_assign
                                (unit, address_granularity, nof_eedb_banks_per_outlif_bank, rif_logical_phase,
                                 current_rif_bank));
            }
        }

        for (current_rif_bank = 0; current_rif_bank < nof_rif_banks; current_rif_bank++)
        {

            SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_in_use_set(unit, current_rif_bank, rif_logical_phase, FALSE));

            if (current_rif_bank >= nof_rif_banks_in_mdb_cluster)
            {

                int current_eedb_bank_index;

                for (current_eedb_bank_index = 0; current_eedb_bank_index < nof_eedb_banks_per_outlif_bank;
                     current_eedb_bank_index++)
                {

                    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_assign_eedb_bank_to_outlif_bank
                                    (unit, current_rif_bank, rif_logical_phase, current_eedb_bank_index,
                                     DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit) / nof_eedb_banks_per_outlif_bank));
                }
            }
        }

        if (nof_rif_banks_in_mdb_cluster > 0)
        {
            SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                            physical_phase.get(unit, rif_logical_phase, &rif_physical_phase));

            SHR_IF_ERR_EXIT(local_outlif_info.physical_phase_to_logical_phase_map.get(unit,
                                                                                      EEDB_PHYSICAL_PHASE_TO_PARTNER_PHASE
                                                                                      (rif_physical_phase),
                                                                                      &partner_logical_phase));

            SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                            first_bank.set(unit, partner_logical_phase, nof_rif_banks));
        }
    }
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_allocation_init(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_databases_allocate(unit));

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_databases_init(unit));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_allocation_deinit(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);
    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_logical_phase_to_physical_phase(
    int unit,
    dnx_algo_local_outlif_logical_phase_e logical_phase,
    uint8 *physical_phase)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.physical_phase.get(unit, logical_phase, physical_phase));
exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_info_to_nof_outlifs_per_entry(
    int unit,
    lif_mngr_local_outlif_info_t * outlif_info,
    int *nof_outlifs_per_entry)
{
    dnx_algo_lif_local_outlif_resource_info_t resource_info;

    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_info_to_resource_info(unit, outlif_info, &resource_info));

    *nof_outlifs_per_entry = resource_info.nof_outlifs_per_entry;

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_get_potential_nof_mdb_outlifs_for_entry(
    int unit,
    lif_mngr_local_outlif_info_t * outlif_info,
    int *nof_potential_outlifs)
{
    dnx_algo_local_outlif_logical_phase_e logical_phase;
    uint32 first_bank_for_phase, last_bank_for_phase, current_bank;
    uint8 in_use, used_logical_phase;
    int nof_free_elements;
    int nof_outlifs_per_entry;
    int nof_free_outlifs;

    SHR_FUNC_INIT_VARS(unit);

    logical_phase = outlif_info->logical_phase;
    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.first_bank.get(unit, logical_phase, &first_bank_for_phase));
    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.last_bank.get(unit, logical_phase, &last_bank_for_phase));

    nof_free_outlifs = 0;
    for (current_bank = first_bank_for_phase; current_bank < last_bank_for_phase; current_bank++)
    {

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.in_use.get(unit, current_bank, &in_use));

        if (in_use)
        {
            SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.
                            used_logical_phase.get(unit, current_bank, &used_logical_phase));

            if (used_logical_phase == logical_phase)
            {
                SHR_IF_ERR_EXIT(lif_mngr_db.
                                egress_local_lif.nof_free_elements_get(unit, current_bank, &nof_free_elements));

                nof_free_outlifs += nof_free_elements;
            }
        }
        else
        {
            nof_free_outlifs += DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit);
        }
    }

    SHR_IF_ERR_EXIT(dnx_algo_local_outlif_info_to_nof_outlifs_per_entry(unit, outlif_info, &nof_outlifs_per_entry));

    if (nof_outlifs_per_entry == 0)
    {
        SHR_IF_ERR_EXIT(_SHR_E_INTERNAL);
    }
    *nof_potential_outlifs = nof_free_outlifs / nof_outlifs_per_entry;

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_stats_get(
    int unit,
    dnx_algo_local_outlif_stats_t * outlif_stats)
{
    int current_bank, count;
    uint8 assigned, in_use;
    int nof_glem_lines;
    SHR_FUNC_INIT_VARS(unit);

    sal_memset(outlif_stats, 0, sizeof(dnx_algo_local_outlif_stats_t));

    for (current_bank = 0; current_bank < DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit); current_bank++)
    {
        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.assigned.get(unit, current_bank, &assigned));

        if (assigned == DNX_ALGO_OUTLIF_BANK_ASSIGNED_TO_MDB)
        {
            outlif_stats->nof_outlif_banks_in_external_memory++;
            SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.in_use.get(unit, current_bank, &in_use));

            if (in_use)
            {
                outlif_stats->nof_used_outlif_banks_in_external_memory++;
            }
        }
    }

    outlif_stats->nof_eedb_banks = dnx_data_mdb.eedb.nof_eedb_banks_get(unit);
    SHR_IF_ERR_EXIT(local_outlif_info.eedb_banks_info.
                    bank_occupation_bitmap.bit_range_count(unit, 0, dnx_data_mdb.eedb.nof_eedb_banks_get(unit),
                                                           &count));
    outlif_stats->nof_used_eedb_banks = count;

    SHR_IF_ERR_EXIT(dnx_algo_lif_mngr_nof_glem_lines_get(unit, &nof_glem_lines));
    outlif_stats->nof_glem_entries = nof_glem_lines;

    SHR_IF_ERR_EXIT(lif_mngr_db.global_lif_allocation.egress_global_lif_counter.get(unit, &count));

    outlif_stats->nof_used_glem_entries = count;

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_next_bank_get(
    int unit,
    uint32 *next_bank)
{
    uint8 in_use;
    uint32 current_bank;
    SHR_FUNC_INIT_VARS(unit);

    current_bank = *next_bank;
    while (current_bank < DNX_ALGO_LOCAL_OUTLIF_NOF_BANKS(unit))
    {
        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.in_use.get(unit, current_bank, &in_use));

        if (in_use)
        {
            *next_bank = current_bank;
            SHR_EXIT();
        }
        current_bank++;
    };

    *next_bank = DNX_ALGO_LOCAL_OUTLIF_INVALID_BANK;

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_outrif_physical_bank_hw_info_get(
    int unit,
    int *outrif_bank_starts,
    dnx_algo_local_outlif_hw_info_t * outlif_hw_infos,
    int *nof_outrifs_info)
{
    int current_outrif_physical_bank_start, current_outrif_info, current_outlif_bank;
    uint8 assigned, is_eedb_bank;
    uint8 logical_phase;
    SHR_FUNC_INIT_VARS(unit);

    current_outrif_physical_bank_start = 0;
    current_outrif_info = 0;

    while (current_outrif_physical_bank_start < dnx_data_l3.rif.nof_rifs_get(unit))
    {
        sal_memset(&outlif_hw_infos[current_outrif_info], 0, sizeof(dnx_algo_local_outlif_hw_info_t));

        outrif_bank_starts[current_outrif_info] = current_outrif_physical_bank_start;

        if (current_outrif_physical_bank_start % DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit) == 0)
        {
            outlif_hw_infos[current_outrif_info].flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_POINTERS;

        }

        current_outlif_bank = DNX_ALGO_OUTLIF_LOCAL_LIF_TO_BANK(current_outrif_physical_bank_start);

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.
                        used_logical_phase.get(unit, current_outlif_bank, &logical_phase));

        SHR_IF_ERR_EXIT(local_outlif_info.outlif_bank_info.assigned.get(unit, current_outlif_bank, &assigned));

        is_eedb_bank = assigned == DNX_ALGO_OUTLIF_BANK_ASSIGNED_TO_EEDB;

        if (is_eedb_bank)
        {
            outlif_hw_infos[current_outrif_info].flags |= DNX_ALGO_LIF_MNGR_LOCAL_OUTLIF_UPDATE_DATA_BANK;
        }

        SHR_IF_ERR_EXIT(dnx_algo_local_outlif_bank_hw_info_get(unit,
                                                               current_outrif_physical_bank_start,
                                                               &outlif_hw_infos[current_outrif_info]));

        if (is_eedb_bank)
        {

            int nof_outlifs_per_eedb_bank;
            uint8 address_granularity;

            SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                            address_granularity.get(unit, logical_phase, &address_granularity));

            if (address_granularity == 0)
            {
                SHR_IF_ERR_EXIT(_SHR_E_INTERNAL);
            }
            nof_outlifs_per_eedb_bank =
                EEDB_MAX_DATA_ENTRY_SIZE / address_granularity * dnx_data_mdb.dh.macro_type_info_get(unit,
                                                                                                     MDB_EEDB_BANK)->nof_rows;

            current_outrif_physical_bank_start += nof_outlifs_per_eedb_bank;
        }
        else
        {
            current_outrif_physical_bank_start += DNX_ALGO_LOCAL_OUTLIF_BANK_SIZE(unit);
        }

        current_outrif_info++;
    }

    *nof_outrifs_info = current_outrif_info;

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_mdb_clusters_disable_set(
    int unit,
    uint8 value)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.disable_mdb_clusters.set(unit, value));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_eedb_data_banks_disable_set(
    int unit,
    uint8 value)
{
    SHR_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(local_outlif_info.disable_eedb_data_banks.set(unit, value));

exit:
    SHR_FUNC_EXIT;
}

shr_error_e
dnx_algo_local_outlif_rif_init_info_get(
    int unit,
    dnx_algo_lif_local_outlif_resource_extra_info_t * init_info)
{
    dnx_algo_local_outlif_logical_phase_e rif_logical_phase;
    uint8 phase_address_granularity;
    SHR_FUNC_INIT_VARS(unit);

    rif_logical_phase = DNX_ALGO_LOCAL_OUTLIF_LOGICAL_PHASE_1;
    SHR_IF_ERR_EXIT(local_outlif_info.logical_phase_info.
                    address_granularity.get(unit, rif_logical_phase, &phase_address_granularity));

    init_info->granularity = phase_address_granularity;

exit:
    SHR_FUNC_EXIT;
}
