/** \file l2_traverse.c
 * 
 *
 * L2 procedures for DNX.
 *
 * This file contains functions for using the traverse machine.
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
#ifdef BSL_LOG_MODULE
#error "BSL_LOG_MODULE redefined"
#endif
#define BSL_LOG_MODULE BSL_LS_BCMDNX_L2

/*
 * Include files.
 * {
 */

#include <soc/sand/shrextend/shrextend_debug.h>
#include <soc/register.h>

#include <soc/dnx/dbal/dbal.h>
#include <soc/dnx/dnx_err_recovery_manager.h>
#include <soc/dnx/dnx_er_threading.h>
#include <bcm_int/dnx/l2/l2.h>
#include <bcm_int/dnx/l2/l2_addr.h>
#include <bcm_int/dnx/l2/l2_traverse.h>
#include <bcm/l2.h>
#include <bcm/switch.h>
#include <soc/dnx/dnx_fifodma.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_l2.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_trunk.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_headers.h>
#include <soc/dnx/dnx_data/auto_generated/dnx_data_field.h>
#include <soc/dnx/dbal/auto_generated/dbal_defines_tables.h>
#include <src/soc/dnx/flush/flush_internal.h>
#include <soc/dnx/swstate/auto_generated/access/l2_access.h>
#include <src/bcm/dnx/trunk/trunk_verify.h>
#include <soc/dnxc/swstate/dnxc_sw_state_utils.h>
#include <shared/utilex/utilex_bitstream.h>
#include <shared/shr_thread_manager.h>

/*
 * }
 */
/*
 * Function Declaration.
 * {
 */

/*
 * }
 */
/*
 * Defines.
 * {
 */
#define DNX_L2_MATCH_STATIC                 SAL_BIT(0)  /* Match L2 static entries, all the strength values that are *
                                                         * considered static. */
#define DNX_L2_MATCH_DYNAMIC                SAL_BIT(1)  /* Match L2 dynamic entries, all the strength values that are * 
                                                         * considered dynamic. */
#define DNX_L2_MATCH_MAC                    SAL_BIT(2)  /* Match L2 entries with given MAC address */
#define DNX_L2_MATCH_VSI                    SAL_BIT(3)  /* Match L2 entries with given VSI */
#define DNX_L2_MATCH_DEST                   SAL_BIT(4)  /* Match L2 entries with given modid port/tgid */
#define DNX_L2_MATCH_HIT                    SAL_BIT(5)  /* Match entries according to the hit-bit indication */
#define DNX_L2_MATCH_AGE                    SAL_BIT(6)  /* Match entries of a given age */
#define DNX_L2_REPLACE_DELETE               SAL_BIT(7)  /* Delete the matching entries */
#define DNX_L2_MATCH_GROUP                  SAL_BIT(8)  /* Match entries according to group field */
#define DNX_L2_MATCH_IVL                    SAL_BIT(9)  /* Match entries from the IVL table */
#define DNX_L2_MATCH_STATIC_TRANSPLANTABLE  SAL_BIT(10) /* Match static entries that can change their destination with
                                                         * * transplant */
#define DNX_L2_MATCH_DYNAMIC_NON_TRANSPLANT SAL_BIT(11) /* Match dynamic entries that cannot change their destination
                                                         * with transplant */
#define DNX_L2_MATCH_GET_NON_BLOCKING       SAL_BIT(12) /* Perform GET action on the matched entries in non-blocking *
                                                         * mode */

#define DNX_L2_REPLACE_DES_HIT_CLEAR        SAL_BIT(13) /* Clear Hit-bit of matched entries. */
#define DNX_L2_REPLACE_DYNAMIC_SET          SAL_BIT(14) /* Change the matched entries to be dynamic */
#define DNX_L2_REPLACE_STATIC_SET           SAL_BIT(15) /* Change the matched entries to be static */
#define DNX_L2_REPLACE_DESTINATION          SAL_BIT(16) /* Change the destination of the matched entries */
#define DNX_L2_NO_CALLBACKS                 SAL_BIT(17) /* Don't call user callback for returned entries */
#define DNX_L2_REPLACE_NON_BLOCKING         SAL_BIT(18) /* Start the flush machine without waiting for it to finish */

/**
 * L2 traverse flag for internal use, in case of separated learning/forwarding MACT indicates whether the learning MACT
 * should be traversed or not
 */
#define DNX_L2_TRAVERSE_LRN           SAL_BIT(19)

/** Define currently supported replace flags */
#define L2_REPLACE_SUPPORTED_BCM_FLAGS  (BCM_L2_REPLACE_MATCH_STATIC | BCM_L2_REPLACE_MATCH_MAC | BCM_L2_REPLACE_MATCH_VLAN | \
                                          BCM_L2_REPLACE_MATCH_DEST | BCM_L2_REPLACE_IGNORE_DES_HIT | \
                                          BCM_L2_REPLACE_DELETE | BCM_L2_REPLACE_DES_HIT_CLEAR | BCM_L2_REPLACE_DYNAMIC_SET | \
                                          BCM_L2_REPLACE_DYNAMIC_CLEAR | BCM_L2_REPLACE_MIGRATE_PORT | BCM_L2_REPLACE_NEW_TRUNK | \
                                          BCM_L2_REPLACE_PROTECTION_RING | BCM_L2_REPLACE_NO_CALLBACKS | BCM_L2_REPLACE_MATCH_GROUP | \
                                          BCM_L2_REPLACE_VLAN_AND_VPN_TYPE | BCM_L2_REPLACE_IGNORE_PENDING)

#define FLUSH_INVALID_OPERATION -1

/*
 * }
 */

/*
* DB holding information for running flush traverse in non-blocking mode.
* See:
*   - dnx_l2_traverse_thread
*   - dnx_l2_traverse_thread_start
*   - dnx_l2_traverse_thread_stop
*   - dnx_l2_traverse_thread_awake
*/
l2_flush_traverse_non_blocking_t l2_traverse_db[BCM_MAX_NUM_UNITS];

/*
  * Internal functions.
  * {
  */
static shr_error_e dnx_l2_traverse_thread_awake(
    int unit,
    bcm_l2_traverse_cb trav_fn,
    void *user_data,
    uint32 table_id);

/**
 * \brief - Init the DMA channel of the flush machine
 *
 * \param [in] unit - unit id
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_l2_flush_dma_init(
    int unit)
{
    int flush_channel;
    soc_dnx_fifodma_config_t fifodma_info;
    int is_started;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * if we are during warmboot the is_started may be incorrect, it
     * may have been turned off during init, but this information
     * was not synced to the external storage and this info was
     * overriten with incorrect info during warmboot recovery
     */
    if (!sw_state_is_warm_boot(unit))
    {
        /** Stop and free the channel if it is already started */
        SHR_IF_ERR_EXIT(soc_dnx_fifodma_channel_is_started(unit, soc_dnx_fifodma_src_event_fifo, &is_started));

        if (is_started)
        {
            SHR_IF_ERR_EXIT(soc_dnx_fifodma_channel_get(unit, soc_dnx_fifodma_src_event_fifo, &flush_channel));
            SHR_IF_ERR_EXIT(soc_dnx_fifodma_channel_stop(unit, flush_channel));
            SHR_IF_ERR_EXIT(soc_dnx_fifodma_channel_free(unit, flush_channel));
        }
    }

    SHR_IF_ERR_EXIT(soc_dnx_fifodma_channel_alloc(unit, soc_dnx_fifodma_src_event_fifo, &flush_channel));
    /*
     * Set initial values into 'fifodma_info' before loading new meaningful
     * data in some of the elements.
     */
    SHR_IF_ERR_EXIT(soc_dnx_fifodma_config_t_init(unit, &fifodma_info));
    fifodma_info.copyno = REG_PORT_ANY;
    fifodma_info.force_entry_size = 0;
    fifodma_info.is_mem = 0;
    fifodma_info.is_poll = 1;
    fifodma_info.max_entries = dnx_data_l2.dma.flush_nof_dma_entries_get(unit);;
    fifodma_info.reg = MACT_LARGE_EM_REPLYr;
    fifodma_info.threshold = 0;
    fifodma_info.timeout = 0;

    SHR_IF_ERR_EXIT(soc_dnx_fifodma_channel_start(unit, flush_channel, &fifodma_info, NULL));

    /** Pause the flush DMA */
    SHR_IF_ERR_EXIT(soc_dnx_fifodma_channel_pause(unit, flush_channel));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Stop and free the dma channel of the flush
 *
 * \param [in] unit - unit id
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_l2_flush_dma_deinit(
    int unit)
{
    int olp_channel;
    shr_error_e rv;

    SHR_FUNC_INIT_VARS(unit);

    rv = soc_dnx_fifodma_channel_get(unit, soc_dnx_fifodma_src_event_fifo, &olp_channel);

    if (rv == _SHR_E_NONE)
    {
        SHR_IF_ERR_EXIT(soc_dnx_fifodma_channel_free(unit, olp_channel));
    }

exit:
    SHR_FUNC_EXIT;
}

/** Set the flags in the bcm_l2_addr_t structs according to the replace flags */
static shr_error_e
dnx_l2_traverse_format_addresses(
    int unit,
    uint32 flags,
    bcm_l2_addr_t * match_addr,
    bcm_l2_addr_t * mask_addr,
    bcm_l2_addr_t * replace_l2addr,
    bcm_l2_addr_t * replace_mask_l2addr)
{
    SHR_FUNC_INIT_VARS(unit);

    if (flags & BCM_L2_REPLACE_NEW_TRUNK)
    {
        match_addr->flags |= BCM_L2_TRUNK_MEMBER;
        mask_addr->flags |= BCM_L2_TRUNK_MEMBER;
        replace_l2addr->flags |= BCM_L2_TRUNK_MEMBER;
        replace_mask_l2addr->flags |= BCM_L2_TRUNK_MEMBER;

        /** Make sure that trunk and multicast flags are not set in the same time */
        if (match_addr->flags & BCM_L2_MCAST || mask_addr->flags & BCM_L2_MCAST ||
            replace_l2addr->flags & BCM_L2_MCAST || replace_mask_l2addr->flags & BCM_L2_MCAST)
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "bcm_l2_addr_t flags are not in synch with the replace flags. BCM_L2_REPLACE_NEW_TRUNK can't be used with BCM_L2_MCAST in bcm_l2_addr_t.");
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Verify that the traverse flags used are supported
 *
 * \param [in] unit - unit id
 * \param [in] traverse_flags - flags to verify
 *
 * \return
 *   int
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static int
dnx_l2_traverse_flags_verify(
    int unit,
    uint32 traverse_flags)
{
    uint32 supported_traverse_flags;
    SHR_FUNC_INIT_VARS(unit);

    supported_traverse_flags = dnx_data_l2.general.l2_traverse_api_supported_flags_get(unit);
    if (_SHR_IS_FLAG_SET(traverse_flags, ~supported_traverse_flags))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal traverse flags are used. traverse_flags = 0x%08X, supported_flags = 0x%08X",
                     traverse_flags, supported_traverse_flags);
    }

    /*
     * Verify BCM_L2_TRAVERSE_IGNORE_PENDING flag:
     *   - not supported in simulation mode
     */
#ifdef ADAPTER_SERVER_MODE
    if (_SHR_IS_FLAG_SET(traverse_flags, BCM_L2_TRAVERSE_IGNORE_PENDING))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Flag BCM_L2_TRAVERSE_IGNORE_PENDING (0x%08X) is not supported in simulation mode. traverse_flags = 0x%08X",
                     BCM_L2_TRAVERSE_IGNORE_PENDING, traverse_flags);
    }
#endif

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Verify that the replace flags used are supported
 *
 * \param [in] unit - unit id
 * \param [in] replace_flags - flags to verify
 *
 * \return
 *   int
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static int
dnx_l2_replace_flags_verify(
    int unit,
    uint32 replace_flags)
{
    SHR_FUNC_INIT_VARS(unit);

    if (_SHR_IS_FLAG_SET(replace_flags, ~L2_REPLACE_SUPPORTED_BCM_FLAGS))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal replace flags are used. replace_flags = 0x%08X, supported_flags = 0x%08X",
                     replace_flags, L2_REPLACE_SUPPORTED_BCM_FLAGS);
    }

    /** Make sure that replace and delete are not set together */
    if ((replace_flags & BCM_L2_REPLACE_DELETE) &&
        (replace_flags & (BCM_L2_REPLACE_DYNAMIC_CLEAR | BCM_L2_REPLACE_DYNAMIC_SET | BCM_L2_REPLACE_NEW_TRUNK |
                          BCM_L2_REPLACE_DES_HIT_CLEAR | BCM_L2_REPLACE_MIGRATE_PORT | BCM_L2_REPLACE_PROTECTION_RING)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Illegal replace flags are used. Replcae and delete can't be set together.");
    }

    /** Make sure that dynamic set and dynamic clear are not set together */
    if ((replace_flags & BCM_L2_REPLACE_DYNAMIC_SET) && (replace_flags & BCM_L2_REPLACE_DYNAMIC_CLEAR))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Illegal replace flags are used. BCM_L2_REPLACE_DYNAMIC_CLEAR and BCM_L2_REPLACE_DYNAMIC_SET can't be set together.");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - verify traverse parameters
 *
 * \param [in] unit - unit id
 * \param [in] flags - traverse flags
 * \param [in] match_l2addr - l2 address for filter rule
 * \param [in] match_mask_l2addr - l2 address used as a mask for the filter
 * \param [in] replace_l2addr - l2 address for replace data
 * \param [in] replace_mask_l2addr - l2 address for mast to the replace data
 * \param [in] trav_fn - user callback
 * \param [in] user_data - context sent to the callback
 *
 * \return
 *   int
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static int
dnx_l2_traverse_verify(
    int unit,
    uint32 flags,
    bcm_l2_addr_t * match_l2addr,
    bcm_l2_addr_t * match_mask_l2addr,
    bcm_l2_addr_t * replace_l2addr,
    bcm_l2_addr_t * replace_mask_l2addr,
    bcm_l2_traverse_cb trav_fn,
    void *user_data)
{
    uint8 is_ivl;
    uint32 entry_strength = 0;
    uint32 learn_res_optmize = 0;

    SHR_FUNC_INIT_VARS(unit);

    /** match_l2addr can't be NULL */
    SHR_NULL_CHECK(match_l2addr, _SHR_E_PARAM, "match_l2addr");

    /** Verify traverse flags */
    SHR_INVOKE_VERIFY_DNXC(dnx_l2_traverse_flags_verify(unit, flags));
    is_ivl = L2_ADDR_IS_MACT_IVL(match_l2addr->modid);
    if (is_ivl)
    {
        if (!dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_ivl_feature_support))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "No support ivl on current device");
        }
        if (!_SHR_IS_FLAG_SET(flags, BCM_L2_TRAVERSE_MATCH_IVL))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "modid!=0 requires the use of BCM_L2_TRAVERSE_MATCH_IVL.");
        }
    }

    learn_res_optmize = dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_learn_payload_res_optimize);
    if (learn_res_optmize)
    {
        if (match_l2addr)
        {
            entry_strength = MACT_ENTRY_STRENGTH_ENCODE_SET(match_l2addr->learn_strength, match_l2addr->age_profile);
            if ((entry_strength != CONFIGURED_MACT_ENTRY_STRENGTH) &&
                (entry_strength != CONFIGURED_MACT_ENTRY_STRENGTH_2) && (entry_strength != 0))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "This device only support learn_strength = 2,3 and age_profile = 0");
            }
        }

        if (replace_l2addr)
        {
            entry_strength =
                MACT_ENTRY_STRENGTH_ENCODE_SET(replace_l2addr->learn_strength, replace_l2addr->age_profile);
            if ((entry_strength != CONFIGURED_MACT_ENTRY_STRENGTH)
                && (entry_strength != CONFIGURED_MACT_ENTRY_STRENGTH_2) && (entry_strength != 0))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "This device only support learn_strength = 2,3 and age_profile = 0");
            }
        }
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - verify replace parameters
 *
 * \param [in] unit - unit id
 * \param [in] flags - traverse flags
 * \param [in] match_l2addr - l2 address for filter rule
 * \param [in] match_mask_l2addr - l2 address used as a mask for the filter
 * \param [in] replace_l2addr - l2 address for replace data
 * \param [in] replace_mask_l2addr - l2 address for mast to the replace data
 * \param [in] trav_fn - user callback
 * \param [in] user_data - context sent to the callback
 *
 * \return
 *   int
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static int
dnx_l2_replace_verify(
    int unit,
    uint32 flags,
    bcm_l2_addr_t * match_l2addr,
    bcm_l2_addr_t * match_mask_l2addr,
    bcm_l2_addr_t * replace_l2addr,
    bcm_l2_addr_t * replace_mask_l2addr,
    bcm_l2_traverse_cb trav_fn,
    void *user_data)
{
    uint8 is_ivl;
    uint32 entry_strength = 0;
    uint32 learn_res_optmize = 0;

    SHR_FUNC_INIT_VARS(unit);

    /** match_l2addr can't be NULL */
    SHR_NULL_CHECK(match_l2addr, _SHR_E_PARAM, "match_l2addr");

    if ((flags & BCM_L2_REPLACE_NO_CALLBACKS) && trav_fn)
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "BCM_L2_REPLACE_NO_CALLBACKS can't be added when a callback is set.");
    }

    if (flags & (BCM_L2_REPLACE_PROTECTION_RING | BCM_L2_REPLACE_NEW_TRUNK | BCM_L2_REPLACE_MIGRATE_PORT))
    {
        SHR_NULL_CHECK(replace_l2addr, _SHR_E_PARAM, "replace_l2addr");
    }

    /*
     * Verify BCM_L2_REPLACE_IGNORE_PENDING flag:
     *   - can be used only on dynamic entries
     *   - must be set together with "no callback" flag
     */
    if (_SHR_IS_FLAG_SET(flags, BCM_L2_REPLACE_IGNORE_PENDING))
    {
        if (_SHR_IS_FLAG_SET(flags, BCM_L2_REPLACE_MATCH_STATIC)
            || _SHR_IS_FLAG_SET(match_l2addr->flags, BCM_L2_STATIC))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM, "BCM_L2_REPLACE_IGNORE_PENDING can be set only on dynamic entries.");
        }

        if (!_SHR_IS_FLAG_SET(flags, BCM_L2_REPLACE_NO_CALLBACKS))
        {
            SHR_ERR_EXIT(_SHR_E_PARAM,
                         "Flag BCM_L2_REPLACE_IGNORE_PENDING (0x%08X) must be set with flag BCM_L2_REPLACE_NO_CALLBACKS (0x%08X)! flags = 0x%08X \n",
                         BCM_L2_REPLACE_IGNORE_PENDING, BCM_L2_REPLACE_NO_CALLBACKS, flags);
        }
    }

    /** Verify replace flags */
    SHR_INVOKE_VERIFY_DNXC(dnx_l2_replace_flags_verify(unit, flags));

    /**IVL full functionality is not support in JR2 A0 */
    is_ivl = L2_ADDR_IS_MACT_IVL(match_l2addr->modid);
    if (!dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_ivl_feature_support) && (is_ivl
                                                                                            || (flags &
                                                                                                BCM_L2_REPLACE_VLAN_AND_VPN_TYPE)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "No support ivl on current device");
    }

    if (is_ivl && (!_SHR_IS_FLAG_SET(flags, BCM_L2_REPLACE_VLAN_AND_VPN_TYPE)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "modid!=0 requires the use of BCM_L2_REPLACE_VLAN_AND_VPN_TYPE.");
    }

    learn_res_optmize = dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_learn_payload_res_optimize);
    if (learn_res_optmize)
    {
        if (match_l2addr)
        {
            entry_strength = MACT_ENTRY_STRENGTH_ENCODE_SET(match_l2addr->learn_strength, match_l2addr->age_profile);
            if ((entry_strength != CONFIGURED_MACT_ENTRY_STRENGTH) &&
                (entry_strength != CONFIGURED_MACT_ENTRY_STRENGTH_2) && (entry_strength != 0))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "This device only support learn_strength = 2,3 and age_profile = 0");
            }
        }

        if (replace_l2addr)
        {
            entry_strength =
                MACT_ENTRY_STRENGTH_ENCODE_SET(replace_l2addr->learn_strength, replace_l2addr->age_profile);
            if ((entry_strength != CONFIGURED_MACT_ENTRY_STRENGTH)
                && (entry_strength != CONFIGURED_MACT_ENTRY_STRENGTH_2) && (entry_strength != 0))
            {
                SHR_ERR_EXIT(_SHR_E_PARAM, "This device only support learn_strength = 2,3 and age_profile = 0");
            }
        }
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

static int
dnx_l2_delete_verify(
    int unit,
    uint32 flags)
{
    SHR_FUNC_INIT_VARS(unit);

    if (_SHR_IS_FLAG_SET(flags, ~(dnx_data_l2.general.l2_delete_api_supported_flags_get(unit))))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM,
                     "Illegal flags are used. Only BCM_L2_DELETE_NO_CALLBACKS, BCM_L2_DELETE_STATIC and BCM_L2_DELETE_IVL are supported.");
    }

    /**IVL full functionality is not support in JR2 A0 */
    if ((dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_ivl_feature_support) == 0)
        && (_SHR_IS_FLAG_SET(flags, BCM_L2_DELETE_IVL)))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "No support ivl on current device");
    }

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - transalte from BCM_L2_TRAVERSE_* flags to local traverse flags.
 *
 * \param [in] unit - unit id
 * \param [in] match_addr - use the match address in order to decide about the dynamic/static rule
 * \param [in] traverse_flags - BCM_L2_TRAVERSE_* flags used as an input for the translation.
 * \param [in,out] local_flags - set the bits of local_flags that coresponds to traverse_flags. Don't set the param to 0 in the beginning.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_l2_traverse_flags_to_local_flags(
    int unit,
    bcm_l2_addr_t * match_addr,
    uint32 traverse_flags,
    uint32 *local_flags)
{
    uint8 set_static = 0;
    uint8 set_static_transplantable = 0;
    uint8 set_dynamic = 0;
    uint8 set_dynamic_non_transplantable = 0;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Configure the dynamic and static rule dynamic logic:
     * flags & BCM_L2_TRAVERSE_MATCH_STATIC == 0 &&match_addr->flags & BCM_L2_STATIC == 0 --> match dynamic entry only
     * flags & BCM_L2_TRAVERSE_MATCH_STATIC == 0 && match_addr->flags & BCM_L2_STATIC == 1 --> match static entry only
     * flags & BCM_L2_TRAVERSE_MATCH_STATIC == 1 -->match both static and dynamic entries
     */
    if ((traverse_flags & BCM_L2_TRAVERSE_MATCH_STATIC) || match_addr == NULL)
    {
        set_static = 1;
        set_dynamic = 1;
    }
    else
    {
        if (match_addr->flags & BCM_L2_STATIC)
        {
            if (match_addr->flags & BCM_L2_MOVE_PORT)
            {
                set_static_transplantable = 1;
            }
            else
            {
                set_static = 1;
            }
        }
        else
        {
            if (match_addr->flags2 & BCM_L2_FLAGS2_NO_MOVE)
            {
                set_dynamic_non_transplantable = 1;
            }
            else
            {
                set_dynamic = 1;
            }
        }
    }

    *local_flags |= (set_static_transplantable ? DNX_L2_MATCH_STATIC_TRANSPLANTABLE : 0);
    *local_flags |= (set_static ? DNX_L2_MATCH_STATIC : 0);
    *local_flags |= (set_dynamic ? DNX_L2_MATCH_DYNAMIC : 0);
    *local_flags |= (set_dynamic_non_transplantable ? DNX_L2_MATCH_DYNAMIC_NON_TRANSPLANT : 0);
    *local_flags |= ((traverse_flags & BCM_L2_TRAVERSE_MATCH_MAC) ? DNX_L2_MATCH_MAC : 0);
    *local_flags |= ((traverse_flags & BCM_L2_TRAVERSE_MATCH_VLAN) ? DNX_L2_MATCH_VSI : 0);
    *local_flags |= ((traverse_flags & BCM_L2_TRAVERSE_MATCH_DEST) ? DNX_L2_MATCH_DEST : 0);
    *local_flags |= ((traverse_flags & BCM_L2_TRAVERSE_MATCH_GROUP) ? DNX_L2_MATCH_GROUP : 0);
    *local_flags |= ((traverse_flags & BCM_L2_TRAVERSE_MATCH_IVL) ? DNX_L2_MATCH_IVL : 0);
    *local_flags |= ((traverse_flags & BCM_L2_TRAVERSE_IGNORE_PENDING) ? DNX_L2_MATCH_GET_NON_BLOCKING : 0);

    /** Hit bit is not supported in adapter mode */
#ifndef ADAPTER_SERVER_MODE
    *local_flags |= ((traverse_flags & BCM_L2_TRAVERSE_IGNORE_DES_HIT) ? 0 : DNX_L2_MATCH_HIT);
#endif

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - transalte from BCM_L2_REPLACE_* flags to local traverse flags.
 *
 * \param [in] unit - unit id
 * \param [in] match_addr - use the match address in order to decide about the dynamic/static rule
 * \param [in] replace_flags - BCM_L2_REPLACE_* flags used as an input for the translation.
 * \param [in,out] local_flags - set the bits of local_flags that coresponds to replace_flags. Don't set the param to 0 in the beginning.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_l2_replace_flags_to_local_flags(
    int unit,
    bcm_l2_addr_t * match_addr,
    uint32 replace_flags,
    uint32 *local_flags)
{
    uint8 set_static = 0;
    uint8 set_static_transplantable = 0;
    uint8 set_dynamic = 0;
    uint8 set_dynamic_non_transplantable = 0;

    SHR_FUNC_INIT_VARS(unit);

    /*
     * Configure the dynamic and static rule dynamic logic:
     * flags & BCM_L2_REPLACE_MATCH_STATIC == 0 && match_addr->flags & BCM_L2_STATIC == 0 --> match dynamic entry only
     * flags & BCM_L2_REPLACE_MATCH_STATIC == 0 && match_addr->flags & BCM_L2_STATIC == 1 -->match static entry only
     * flags & BCM_L2_REPLACE_MATCH_STATIC == 1 -->match both static and dynamic entries
     */
    if ((replace_flags & BCM_L2_REPLACE_MATCH_STATIC) || match_addr == NULL)
    {
        set_static = 1;
        set_dynamic = 1;
    }
    else
    {
        if (match_addr->flags & BCM_L2_STATIC)
        {
            if (match_addr->flags & BCM_L2_MOVE_PORT)
            {
                set_static_transplantable = 1;
            }
            else
            {
                set_static = 1;
            }
        }
        else
        {
            if (match_addr->flags2 & BCM_L2_FLAGS2_NO_MOVE)
            {
                set_dynamic_non_transplantable = 1;
            }
            else
            {
                set_dynamic = 1;
            }
        }
    }

    *local_flags |= (set_static_transplantable ? DNX_L2_MATCH_STATIC_TRANSPLANTABLE : 0);
    *local_flags |= (set_static ? DNX_L2_MATCH_STATIC : 0);
    *local_flags |= (set_dynamic ? DNX_L2_MATCH_DYNAMIC : 0);
    *local_flags |= (set_dynamic_non_transplantable ? DNX_L2_MATCH_DYNAMIC_NON_TRANSPLANT : 0);
    *local_flags |= ((replace_flags & BCM_L2_REPLACE_MATCH_MAC) ? DNX_L2_MATCH_MAC : 0);
    *local_flags |= ((replace_flags & BCM_L2_REPLACE_MATCH_VLAN) ? DNX_L2_MATCH_VSI : 0);
    *local_flags |= ((replace_flags & BCM_L2_REPLACE_MATCH_DEST) ? DNX_L2_MATCH_DEST : 0);
    *local_flags |= ((replace_flags & BCM_L2_REPLACE_MATCH_GROUP) ? DNX_L2_MATCH_GROUP : 0);
    *local_flags |= ((replace_flags & BCM_L2_REPLACE_VLAN_AND_VPN_TYPE) ? DNX_L2_MATCH_IVL : 0);

    /** Hit bit is not supported in adapter mode */
#ifndef ADAPTER_SERVER_MODE
    *local_flags |= ((replace_flags & BCM_L2_REPLACE_IGNORE_DES_HIT) ? 0 : DNX_L2_MATCH_HIT);

    *local_flags |= ((replace_flags & BCM_L2_REPLACE_DES_HIT_CLEAR) ? DNX_L2_REPLACE_DES_HIT_CLEAR : 0);
#endif

    *local_flags |= ((replace_flags & BCM_L2_REPLACE_DELETE) ? DNX_L2_REPLACE_DELETE : 0);
    *local_flags |= ((replace_flags & BCM_L2_REPLACE_DYNAMIC_SET) ? DNX_L2_REPLACE_DYNAMIC_SET : 0);
    *local_flags |= ((replace_flags & BCM_L2_REPLACE_DYNAMIC_CLEAR) ? DNX_L2_REPLACE_STATIC_SET : 0);
    *local_flags |=
        ((replace_flags & (BCM_L2_REPLACE_MIGRATE_PORT | BCM_L2_REPLACE_NEW_TRUNK | BCM_L2_REPLACE_PROTECTION_RING)) ?
         DNX_L2_REPLACE_DESTINATION : 0);
    *local_flags |= ((replace_flags & BCM_L2_REPLACE_NO_CALLBACKS) ? DNX_L2_NO_CALLBACKS : 0);
    *local_flags |= ((replace_flags & BCM_L2_REPLACE_IGNORE_PENDING) ? DNX_L2_REPLACE_NON_BLOCKING : 0);

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - get destination mask when system mode is jericho and destination is FEC.
 * \param [in] unit - unit id
 * \param [in] flags - flags defining which values are relevant for the traverse filter. (DNX_L2_MATCH_XX)
 * \param [in] destination - destination to flush db filter
 * \param [in, out] dest_mask - destination mask
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_l2_dest_fec_mask_get(
    int unit,
    uint32 flags,
    uint32 destination,
    uint32 *dest_mask)
{
    int system_headers_mode;
    uint32 jr_mode_nof_fec_bits = 0;
    uint32 arad_plus_mode_nof_fec_bits = 0;
    dbal_fields_e dbal_dest_type = 0;
    uint32 dest_val = 0;
    uint32 fec_mask_bits = 0;

    SHR_FUNC_INIT_VARS(unit);
    /*
     * For IOP mode at J2C and above device,
     * Use arad+ payload format at OLP learning message, FEC_ID will take 15 bits at L2 payload;
     * Use Jericho payload format when add entry by CPU, FEC_ID will take 17 bits at L2 payload.
     * So delete all entries which 15 LSB FEC_ID is equel to destination(FEC[14:0])
     */
    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);
    if (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE &&
        !dnx_data_field.init.j1_learning_get(unit) && (flags & DNX_L2_MATCH_DEST) && (flags & DNX_L2_REPLACE_DELETE))
    {
        SHR_IF_ERR_EXIT(dbal_fields_uint32_sub_field_info_get
                        (unit, DBAL_FIELD_DESTINATION, destination, &dbal_dest_type, &dest_val));
        if (dbal_dest_type == DBAL_FIELD_FEC)
        {
            jr_mode_nof_fec_bits = dnx_data_l2.general.jr_mode_nof_fec_bits_get(unit);
            arad_plus_mode_nof_fec_bits = dnx_data_l2.general.arad_plus_mode_nof_fec_bits_get(unit);
            fec_mask_bits = jr_mode_nof_fec_bits - arad_plus_mode_nof_fec_bits;
            *dest_mask &= (~(((1 << fec_mask_bits) - 1) << arad_plus_mode_nof_fec_bits));
        }
    }

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Set actions to the rule handle according to the replace structs and flags.
 *
 * \param [in] unit - unit id
 * \param [in] flags - flags defining which actions should be performed. (DNX_L2_REPLACE_XX)
 * \param [in] replace_l2addr - data for the replace actions.
 * \param [in] replace_mask_l2addr - mask for the replace data.
 * \param [in] rules_handle_id - iterator handle which will be configured with the actions
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_l2_traverse_set_actions(
    int unit,
    uint32 flags,
    bcm_l2_addr_t * replace_l2addr,
    bcm_l2_addr_t * replace_mask_l2addr,
    uint32 *rules_handle_id)
{
    uint32 destination, destination_mask;
    uint32 outlif = 0;
    uint32 outlif_mask = 0;
    uint32 result_type_dummy, result_type_mask_dummy;
    uint32 entry_strength, age_profile;
    uint32 entry_strength_mask = 0xffffffff, age_profile_mask = 0xffffffff;
    uint8 no_mask = 0;
    uint32 group_mask;
    uint32 group;
    uint32 eei = 0;
    uint32 field_flags_dummy;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Configure actions according to the flags */

    /** Add delete action */
    if (flags & DNX_L2_REPLACE_DELETE)
    {
        SHR_IF_ERR_EXIT(dbal_iterator_entry_action_add(unit, *rules_handle_id, DBAL_ITER_ACTION_DELETE));
    }

    if (!replace_mask_l2addr)
    {
        no_mask = 1;
        group_mask = 0;
    }
    else
    {
        group_mask = replace_mask_l2addr->group;
    }

    /** Update destination */
    if (flags & DNX_L2_REPLACE_DESTINATION)
    {
        SHR_IF_ERR_EXIT(dnx_convert_l2_addr_to_dest
                        (unit, 0, replace_l2addr, &destination, &outlif, &result_type_dummy, &eei, &field_flags_dummy));

        if (no_mask)
        {
            destination_mask = 0x1FFFFF;
            outlif_mask = 0x3FFFFF;
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_convert_l2_addr_to_dest
                            (unit, 0, replace_mask_l2addr, &destination_mask, &outlif_mask, &result_type_mask_dummy,
                             &eei, &field_flags_dummy));
        }

        SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                        (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_DESTINATION, INST_SINGLE,
                         &destination, &destination_mask));

        if (outlif_mask != 0)
        {
            /** Update outlif  */
            SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                            (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_GLOB_OUT_LIF, INST_SINGLE,
                             &outlif, &outlif_mask));
        }
    }

    /** Clear hit bit */
    if (flags & DNX_L2_REPLACE_DES_HIT_CLEAR)
    {
        SHR_IF_ERR_EXIT(dbal_iterator_entry_action_add(unit, *rules_handle_id, DBAL_ITER_ACTION_HIT_CLEAR));
    }

    /** Set dynamic */
    if (flags & DNX_L2_REPLACE_DYNAMIC_SET)
    {
        if (dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_learn_payload_res_optimize))
        {
            entry_strength = MACT_ENTRY_STRENGTH_ENCODE_STRENGTH_GET(DYNAMIC_MACT_ENTRY_STRENGTH);
            SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                            (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_MAC_STRENGTH, INST_SINGLE,
                             &entry_strength, &entry_strength_mask));

            age_profile = MACT_ENTRY_STRENGTH_ENCODE_AGE_PROFILE_GET(DYNAMIC_MACT_ENTRY_STRENGTH);
            SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                            (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_MACT_ENTRY_AGE_PROFILE,
                             INST_SINGLE, &age_profile, &age_profile_mask));

        }
        else
        {
            entry_strength = DYNAMIC_MACT_ENTRY_STRENGTH;
            SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                            (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_MAC_STRENGTH, INST_SINGLE,
                             &entry_strength, &entry_strength_mask));
        }
    }

    /** Set static */
    if (flags & DNX_L2_REPLACE_STATIC_SET)
    {
        if (dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_learn_payload_res_optimize))
        {
            if (replace_l2addr
                && MACT_ENTRY_STRENGTH_ENCODE_SET(replace_l2addr->learn_strength, replace_l2addr->age_profile))
            {
                entry_strength = replace_l2addr->learn_strength;
                SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                                (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_MAC_STRENGTH, INST_SINGLE,
                                 &entry_strength, &entry_strength_mask));

                age_profile = replace_l2addr->age_profile;
                SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                                (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_MACT_ENTRY_AGE_PROFILE,
                                 INST_SINGLE, &age_profile, &age_profile_mask));
            }
            else
            {
                entry_strength = MACT_ENTRY_STRENGTH_ENCODE_STRENGTH_GET(STATIC_MACT_ENTRY_STRENGTH);
                SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                                (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_MAC_STRENGTH, INST_SINGLE,
                                 &entry_strength, &entry_strength_mask));

                age_profile = MACT_ENTRY_STRENGTH_ENCODE_AGE_PROFILE_GET(STATIC_MACT_ENTRY_STRENGTH);
                SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                                (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_MACT_ENTRY_AGE_PROFILE,
                                 INST_SINGLE, &age_profile, &age_profile_mask));
            }
        }
        else
        {
            entry_strength = STATIC_MACT_ENTRY_STRENGTH;
            SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                            (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_MAC_STRENGTH, INST_SINGLE,
                             &entry_strength, &entry_strength_mask));
        }
    }

    if (replace_l2addr && (group_mask != 0))
    {
        group = (uint32) replace_l2addr->group;
        SHR_IF_ERR_EXIT(dbal_iterator_field_arr32_action_add
                        (unit, *rules_handle_id, DBAL_ITER_ACTION_UPDATE, DBAL_FIELD_ENTRY_GROUPING, INST_SINGLE,
                         &group, &group_mask));
    }

    /** For non-blocking traverse - need to trigger DMA */
    if (flags & DNX_L2_MATCH_GET_NON_BLOCKING)
    {
        SHR_IF_ERR_EXIT(dbal_iterator_entry_action_add(unit, *rules_handle_id, DBAL_ITER_ACTION_READ_TO_DMA));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get the number of bits in the trunk's group encoding.
 *
 * \param [in] unit - unit id
 * \param [in] trunk_id - encoding of a trunk id
 * \param [out] group_nof_bits - number of bits in the trunk group id encoding
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static void
dnx_l2_traverse_trunk_nof_bits_get(
    int unit,
    uint32 trunk_id,
    uint32 *group_nof_bits)
{
    int pool;
    int max_nof_groups_in_pool;

    *group_nof_bits = 0;

    /** get pool from trunk id */
    BCM_TRUNK_ID_POOL_GET(pool, trunk_id);

    max_nof_groups_in_pool = dnx_data_trunk.parameters.pool_info_get(unit, pool)->max_nof_groups_in_pool;

    if (max_nof_groups_in_pool > 0)
    {
        *group_nof_bits = utilex_log2_round_up(max_nof_groups_in_pool);
    }
}

/**
 * \brief - Get mask and values for traverse inside bcm_l2_addr_t struct and configure the iterator handle with the rules.
 *
 * \param [in] unit - unit id
 * \param [in] flags - flags defining which values are relevant for the traverse filter. (DNX_L2_MATCH_XX)
 * \param [in] match_l2addr - filter rules
 * \param [in] match_mask_l2addr - mask for the filter rules
 * \param [in] rules_handle_id - iterator handle which will be configured with the rules
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_l2_traverse_set_rules(
    int unit,
    uint32 flags,
    bcm_l2_addr_t * match_l2addr,
    bcm_l2_addr_t * match_mask_l2addr,
    uint32 *rules_handle_id)
{
    uint32 key_rule_value;
    uint32 key_rule_mask;
    bcm_mac_t mac_rule_value;
    bcm_mac_t mac_rule_mask;
    uint32 destination, destination_mask;
    uint32 outlif = 0;
    uint32 outlif_mask = 0;
    uint32 result_type_dummy, result_type_mask_dummy;
    uint8 hit_value = 0;
    /** Use this struct in case the function's argument is null */
    bcm_l2_addr_t match_mask_l2addr_local;
    uint8 no_mask = 0;
    uint32 eei = 0;
    uint32 group_nof_bits;
    uint32 trunk_mask;
    uint32 trunk_prefix_shift;
    uint32 tgid;
    int system_headers_mode;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /** Configure rules according to the flags */
    system_headers_mode = dnx_data_headers.system_headers.system_headers_mode_get(unit);
    key_rule_value = 0;
    key_rule_mask = 0;

    if (!match_mask_l2addr)
    {
        sal_memset((void *) &match_mask_l2addr_local, 0xFF, sizeof(bcm_l2_addr_t));
        match_mask_l2addr = &match_mask_l2addr_local;
        no_mask = 1;
    }

    if (dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_learn_payload_res_optimize))
    {
        /** Configure the dynamic and static rule */
        if (flags & DNX_L2_MATCH_STATIC)
        {
            if (flags & DNX_L2_MATCH_DYNAMIC)
            {
                /** Return dynamic and static entries. Strength = 0..3 */
                key_rule_value = 0;
                key_rule_mask = 0;
            }
            else
            {
                /** Return only static entries (strength 2 or 3 == 01X)   */
                key_rule_value = STATIC_MACT_ENTRY_STRENGTH;
                key_rule_mask = 7;
            }
        }
        else
        {
            /** Only dynamic entries return (strength == 1) */
            key_rule_value = DYNAMIC_MACT_ENTRY_STRENGTH;
            key_rule_mask = 7;
        }

        /** static transplantable entries (strength == 0 only)   */
        if (flags & DNX_L2_MATCH_STATIC_TRANSPLANTABLE)
        {
            key_rule_value = STATIC_TRANSPLANTABLE_MACT_ENTRY_STRENGTH;
            key_rule_mask = 7;
        }

        /** Synamic non transplantable entries (strength == 3 only)   */
        if (flags & DNX_L2_MATCH_DYNAMIC_NON_TRANSPLANT)
        {
            key_rule_value = DYNAMIC_NON_TRANSPLANTABLE_MACT_ENTRY_STRENGTH;
            key_rule_mask = 7;
        }

        /** New APIs usage, configured entries (strength = 4 or 6 only )*/
        if (MACT_ENTRY_STRENGTH_ENCODE_SET(match_l2addr->learn_strength, match_l2addr->age_profile))
        {
            key_rule_value = MACT_ENTRY_STRENGTH_ENCODE_SET(match_l2addr->learn_strength, match_l2addr->age_profile);
            key_rule_mask = 7;
        }
    }
    else
    {
        /** Configure the dynamic and static rule */
        if (flags & DNX_L2_MATCH_STATIC)
        {
            if (flags & DNX_L2_MATCH_DYNAMIC)
            {
                /** Return dynamic and static entries. Strength = 0..3 */
                key_rule_value = 0;
                key_rule_mask = 0;
            }
            else
            {
                /** Return only static entries (strength 2 or 3 == 1X)   */
                key_rule_value = STATIC_MACT_ENTRY_STRENGTH;
                key_rule_mask = 3;
            }
        }
        else
        {
            /** Only dynamic entries return (strength == 1) */
            key_rule_value = 1;
            key_rule_mask = 3;
        }

        /** static transplantable entries (strength == 0 only)   */
        if (flags & DNX_L2_MATCH_STATIC_TRANSPLANTABLE)
        {
            key_rule_value = STATIC_TRANSPLANTABLE_MACT_ENTRY_STRENGTH;
            key_rule_mask = 3;
        }

        /** Synamic non transplantable entries (strength == 3 only)   */
        if (flags & DNX_L2_MATCH_DYNAMIC_NON_TRANSPLANT)
        {
            key_rule_value = DYNAMIC_NON_TRANSPLANTABLE_MACT_ENTRY_STRENGTH;
            key_rule_mask = 3;
        }
    }

    if (key_rule_mask)
    {
        if (dnx_data_l2.general.feature_get(unit, dnx_data_l2_general_learn_payload_res_optimize))
        {
            uint32 age_profile_rule_value = MACT_ENTRY_STRENGTH_ENCODE_AGE_PROFILE_GET(key_rule_value);
            uint32 age_profile_rule_mask = MACT_ENTRY_STRENGTH_ENCODE_AGE_PROFILE_GET(key_rule_mask);
            uint32 strength_rule_value = MACT_ENTRY_STRENGTH_ENCODE_STRENGTH_GET(key_rule_value);
            uint32 strength_rule_mask = MACT_ENTRY_STRENGTH_ENCODE_STRENGTH_GET(key_rule_mask);

            SHR_IF_ERR_EXIT(dbal_iterator_value_field32_rule_add
                            (unit, *rules_handle_id, DBAL_FIELD_MACT_ENTRY_AGE_PROFILE, INST_SINGLE,
                             DBAL_CONDITION_EQUAL_TO, age_profile_rule_value, age_profile_rule_mask));
            SHR_IF_ERR_EXIT(dbal_iterator_value_field32_rule_add
                            (unit, *rules_handle_id, DBAL_FIELD_MAC_STRENGTH, INST_SINGLE, DBAL_CONDITION_EQUAL_TO,
                             strength_rule_value, strength_rule_mask));
        }
        else
        {
            SHR_IF_ERR_EXIT(dbal_iterator_value_field32_rule_add
                            (unit, *rules_handle_id, DBAL_FIELD_MAC_STRENGTH, INST_SINGLE, DBAL_CONDITION_EQUAL_TO,
                             key_rule_value, key_rule_mask));
        }
    }

    /** Compare the mac address if needed */
    if (flags & DNX_L2_MATCH_MAC)
    {
        sal_memcpy((void *) &mac_rule_value, &(match_l2addr->mac), sizeof(bcm_mac_t));
        sal_memcpy((void *) &mac_rule_mask, &(match_mask_l2addr->mac), sizeof(bcm_mac_t));

        SHR_IF_ERR_EXIT(dbal_iterator_key_field_arr8_rule_add
                        (unit, *rules_handle_id, DBAL_FIELD_L2_MAC, DBAL_CONDITION_EQUAL_TO, (uint8 *) &mac_rule_value,
                         (uint8 *) &mac_rule_mask));
    }

    /** Compare vsi */
    if (flags & DNX_L2_MATCH_VSI)
    {
        key_rule_value = match_l2addr->vid;
        key_rule_mask = match_mask_l2addr->vid;
         /* coverity[callee_ptr_arith:FALSE]  */
        SHR_IF_ERR_EXIT(dbal_iterator_key_field_arr32_rule_add
                        (unit, *rules_handle_id, DBAL_FIELD_VSI, DBAL_CONDITION_EQUAL_TO, &key_rule_value,
                         &key_rule_mask));
    }

    if (flags & DNX_L2_MATCH_GROUP && match_mask_l2addr->group)
    {
        /** Compare group */
         /* coverity[callee_ptr_arith:FALSE]  */
        SHR_IF_ERR_EXIT(dbal_iterator_value_field32_rule_add
                        (unit, *rules_handle_id, DBAL_FIELD_ENTRY_GROUPING, INST_SINGLE, DBAL_CONDITION_EQUAL_TO,
                         match_l2addr->group, match_mask_l2addr->group));
    }

    if ((flags & DNX_L2_MATCH_IVL) && (match_l2addr->modid != 0))
    {
        /** Compare vlan (modid) */
         /* coverity[callee_ptr_arith:FALSE]  */
        SHR_IF_ERR_EXIT(dbal_iterator_key_field_arr32_rule_add
                        (unit, *rules_handle_id, DBAL_FIELD_VID, DBAL_CONDITION_EQUAL_TO,
                         (uint32 *) &match_l2addr->modid, (uint32 *) &match_mask_l2addr->modid));
    }

    /** Compare destination */
    if (flags & DNX_L2_MATCH_DEST)
    {
        uint32 field_flags;
        SHR_IF_ERR_EXIT(dnx_convert_l2_addr_to_dest
                        (unit, 0, match_l2addr, &destination, &outlif, &result_type_dummy, &eei, &field_flags));
        if (no_mask)
        {
            destination_mask = 0xFFFFFFFF;
            if ((system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE) && (outlif == 0))
            {
                /** JR1 IOP and outlif is not set. */
                outlif_mask = 0;
            }
            else
            {
                outlif_mask = 0xFFFFFFFF;
            }
        }
        else
        {
            SHR_IF_ERR_EXIT(dnx_convert_l2_addr_to_dest
                            (unit, 0, match_mask_l2addr, &destination_mask, &outlif_mask, &result_type_mask_dummy, &eei,
                             &field_flags));
        }

        /** Fast flush by dest only at JR1 system mode. */
        if ((flags & DNX_L2_MATCH_GROUP) && (match_mask_l2addr->group == 0) &&
            (system_headers_mode == DBAL_ENUM_FVAL_SYSTEM_HEADERS_MODE_JERICHO_MODE))
        {
            destination_mask = 0x1FFFF;
            outlif_mask = 0;
        }

        if (_SHR_IS_FLAG_SET(match_l2addr->flags, BCM_L2_TRUNK_MEMBER) || BCM_GPORT_IS_TRUNK(match_l2addr->port))
        {
            tgid = match_l2addr->tgid;

            if (BCM_GPORT_IS_TRUNK(match_l2addr->port))
            {
                tgid = BCM_GPORT_TRUNK_GET(match_l2addr->port);
            }

            SHR_IF_ERR_EXIT(dnx_trunk_t_verify(unit, tgid));

            trunk_prefix_shift = dnx_data_trunk.parameters.spa_type_shift_get(unit);
            dnx_l2_traverse_trunk_nof_bits_get(unit, match_l2addr->tgid, &group_nof_bits);

            /** Compare only the trunk group bits (LSBs) and the trunk prefix. Mask out the member bits and the pool bit. */
            trunk_mask = ((1 << group_nof_bits) - 1) | (1 << trunk_prefix_shift);

            /** Mask out the LAG member bits. */
            destination_mask &= trunk_mask;
        }

        SHR_IF_ERR_EXIT(dnx_l2_dest_fec_mask_get(unit, flags, destination, &destination_mask));

        if (destination_mask)
        {
            SHR_IF_ERR_EXIT(dbal_iterator_value_field32_rule_add
                            (unit, *rules_handle_id, DBAL_FIELD_DESTINATION, INST_SINGLE, DBAL_CONDITION_EQUAL_TO,
                             destination, destination_mask));
        }

        if ((outlif_mask != 0) && (_SHR_IS_FLAG_SET(field_flags, L2_ADDR_DBAL_FIELD_GLOB_OUT_LIF)))
        {
            /** Compare outlif if needed */
            SHR_IF_ERR_EXIT(dbal_iterator_value_field32_rule_add
                            (unit, *rules_handle_id, DBAL_FIELD_GLOB_OUT_LIF, INST_SINGLE, DBAL_CONDITION_EQUAL_TO,
                             outlif, outlif_mask));
        }
    }

    /** Compare hit bit if needed */
    if ((flags & DNX_L2_MATCH_HIT) && (match_mask_l2addr->flags & BCM_L2_HIT))
    {
        if (match_l2addr->flags & BCM_L2_HIT)
        {
            hit_value = 1;
        }
        SHR_IF_ERR_EXIT(dbal_iterator_attribute_rule_add(unit, *rules_handle_id,
                                                         (DBAL_ENTRY_ATTR_HIT_PRIMARY | DBAL_ENTRY_ATTR_HIT_SECONDARY |
                                                          DBAL_ENTRY_ATTR_HIT_GET), hit_value));
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Get the state of the flush machine.
 *
 * \param [in] unit - unit id
 * \param [out] flush_machine_is_done - 1 in case the flush is idle. o otherwise.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
dnx_l2_traverse_commit_done_get(
    int unit,
    int32 *flush_machine_is_done)
{
    uint32 field_value;
    uint32 entry_handle_id;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    *flush_machine_is_done = 0;
    field_value = 0;

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, DBAL_TABLE_FLUSH_MACHINE_GENERAL_PARAMS, &entry_handle_id));
    /** Get the state of the flush machine */
    dbal_value_field32_request(unit, entry_handle_id, DBAL_FIELD_MACHINE_STATUS, INST_SINGLE, &field_value);

    SHR_IF_ERR_EXIT(dbal_entry_get(unit, entry_handle_id, DBAL_COMMIT));

    if (field_value == FLUSH_MACHINE_STATUS_IDLE)
    {
        *flush_machine_is_done = 1;
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - Call user callbacks. Call the callback given in the traverse/replace APIs and to the callbacks registered
 * using bcm_l2_addr_register
 *
 * \param [in] unit - unit id
 * \param [in] l2addr - fetched MAC entry for the user's callback
 * \param [in] registered_callback_operation- the operation for the registered callback
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_traverse_registered_callbacks_invoke(
    int unit,
    bcm_l2_addr_t * l2addr,
    int registered_callback_operation)
{
    int cb_index;

    SHR_FUNC_INIT_VARS(unit);
    /** Call other user callbacks */
    for (cb_index = 0; cb_index < DNX_L2_CB_MAX; cb_index++)
    {
        if (dnx_l2_cbs[unit].entry[cb_index].callback != NULL)
        {
            void *userdata = dnx_l2_cbs[unit].entry[cb_index].userdata;
            dnx_l2_cbs[unit].entry[cb_index].callback(unit, l2addr, registered_callback_operation, userdata);
        }
    }
    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - This function return the operation to perform using registered callbacks, if no operation is set returns
 *          FLUSH_INVALID_OPERATION
 *
 * \param [in] unit - unit id
 * \param [in] flags - DNX_L2_REPLACE_* flags
 * \param [in] trav_fn - traverse callback function
 * \param [out] operation- the operation for the registered callback
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_traverse_get_registered_callbacks_operation(
    int unit,
    uint32 flags,
    bcm_l2_traverse_cb trav_fn,
    int *operation)
{
    SHR_FUNC_INIT_VARS(unit);
    *operation = FLUSH_INVALID_OPERATION;
    if (trav_fn == NULL)
    {
        if (flags & DNX_L2_REPLACE_DELETE)
        {
            *operation = BCM_L2_CALLBACK_DELETE;
        }
        else if (flags &
                 (DNX_L2_REPLACE_DES_HIT_CLEAR | DNX_L2_REPLACE_DYNAMIC_SET | DNX_L2_REPLACE_STATIC_SET |
                  DNX_L2_REPLACE_DESTINATION))
        {
            *operation = BCM_L2_CALLBACK_MOVE_EVENT;
        }
    }
    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - implement traverse and replace logic according to match filters and flags.
 *
 * \param [in] unit - unit id
 * \param [in] l2_action_type - Indicates the L2 action type (fwd/learn), in order to determine the relevant MACT
 * \param [in] flags - DNX_L2_MATCH_... and DNX_L2_REPLAC_... see more details in the flags definitions.
 * \param [in] match_l2addr - details for the filter rules. Use fields according to the flags parameter.
 * \param [in] match_mask_l2addr - mask for the filter rules.
 * \param [in] replace_l2addr - new values for transplant operation. Transplant the parameters according to the flags param.
 * \param [in] replace_mask_l2addr - mask for the replace_l2addr parameter.
 * \param [in] trav_fn - user callback to apply on all the matched entries.
 * \param [in] user_data - context passed to the user's callback.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_l2_addr_traverse_by_rule(
    int unit,
    dnx_l2_action_type_t l2_action_type,
    uint32 flags,
    bcm_l2_addr_t * match_l2addr,
    bcm_l2_addr_t * match_mask_l2addr,
    bcm_l2_addr_t * replace_l2addr,
    bcm_l2_addr_t * replace_mask_l2addr,
    bcm_l2_traverse_cb trav_fn,
    void *user_data)
{
    uint32 entry_handle_id;
    int is_end = 0;
    bcm_l2_addr_t l2addr;
    shr_error_e return_val = _SHR_E_NONE;
    dbal_tables_e table_id;
    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    /**
     * This wait is placed in order to prevent multiple thread access to the overflow buffer
     */
    SHR_IF_ERR_EXIT(shr_thread_manager_wait(l2_traverse_db[unit].l2_traverse_tid, SHR_THREAD_MANAGER_MAX_TIMEOUT));
    table_id = dnx_data_l2.general.fwd_mact_info_get(unit, l2_action_type,
                                                     _SHR_IS_FLAG_SET(flags, DNX_L2_MATCH_IVL))->logical_data_base;
    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    if ((flags & DNX_L2_REPLACE_NON_BLOCKING) || (flags & DNX_L2_MATCH_GET_NON_BLOCKING))
    {
        SHR_IF_ERR_EXIT(dbal_iterator_init(unit, entry_handle_id, DBAL_ITER_MODE_ACTION_NON_BLOCKING));

    }
    else
    {
        SHR_IF_ERR_EXIT(dbal_iterator_init(unit, entry_handle_id, DBAL_ITER_MODE_GET_ALL_EXCEPT_DEFAULT));

    }

    /** Configure rules according to the flags */
    SHR_IF_ERR_EXIT(dnx_l2_traverse_set_rules(unit, flags, match_l2addr, match_mask_l2addr, &entry_handle_id));

    /** Configure actions according to the flags */
    SHR_IF_ERR_EXIT(dnx_l2_traverse_set_actions(unit, flags, replace_l2addr, replace_mask_l2addr, &entry_handle_id));

    /*
     * When DNX_L2_NO_CALLBACKS is set no iteration over the entries is needed.
     * Action commit is used only when no iteration done. Commit is performed in the first call to dbal_iterator_get_next
     */
    if ((flags & DNX_L2_NO_CALLBACKS) || (flags & DNX_L2_MATCH_GET_NON_BLOCKING))
    {
        SHR_IF_ERR_EXIT(dbal_iterator_action_commit(unit, entry_handle_id));
        /** Trigger the low priority thread for non-blocking traverse */
        if (flags & DNX_L2_MATCH_GET_NON_BLOCKING)
        {
            /**
             * Waking the traverse thread to perform the action required.
             */
            SHR_IF_ERR_EXIT(dnx_l2_traverse_thread_awake(unit, trav_fn, user_data, table_id));
        }
    }
    else
    {
        int registered_callbacks_operation;
        SHR_IF_ERR_EXIT(dnx_traverse_get_registered_callbacks_operation
                        (unit, flags, trav_fn, &registered_callbacks_operation));

        SHR_IF_ERR_EXIT(dbal_iterator_get_next(unit, entry_handle_id, &is_end));

        while (!is_end)
        {
            /** Fetch l2 address fields */
            SHR_IF_ERR_EXIT(dnx_l2_addr_from_dbal_to_struct(unit, entry_handle_id, table_id, &l2addr));

            /** Call user callbacks */
            if (trav_fn != NULL)
            {
                return_val = trav_fn(unit, &l2addr, user_data);
            }
            else if (registered_callbacks_operation != FLUSH_INVALID_OPERATION)
            {
                dnx_traverse_registered_callbacks_invoke(unit, &l2addr, registered_callbacks_operation);
            }
            if (return_val)
            {
                char str[20];
                sal_snprintf(str, 20, "%02x:%02x:%02x:%02x:%02x:%02x", l2addr.mac[0], l2addr.mac[1],
                             l2addr.mac[2], l2addr.mac[3], l2addr.mac[4], l2addr.mac[5]);
                LOG_ERROR_EX(BSL_LOG_MODULE, "Callback returned an error %d for address mac - %s vsi - %d %s\n",
                             return_val, str, l2addr.vid, EMPTY);

                /** Clear the buffer that the flush uses for coping the entries */
                dbal_flush_reset_flush_work_buffers(unit, l2_action_type);

                /** Clear flush rules */
                SHR_IF_ERR_EXIT(dbal_flush_db_clear(unit, l2_action_type));

                /** Call flush end to unpause the age-machine */
                SHR_IF_ERR_EXIT(dbal_flush_end(unit, l2_action_type));
                SHR_EXIT();
            }
            SHR_IF_ERR_EXIT(dbal_iterator_get_next(unit, entry_handle_id, &is_end));
        }
    }

exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/**
 * \brief - wrapper function that calls dnx_l2_traverse_traverse_by_rule with the suitable table id
 *
 * \param [in] unit - unit id
 * \param [in] flags - DNX_L2_MATCH_... and DNX_L2_REPLAC_... see more details in the flags definitions.
 * \param [in] match_l2addr - details for the filter rules. Use fields according to the flags parameter.
 * \param [in] match_mask_l2addr - mask for the filter rules.
 * \param [in] replace_l2addr - new values for transplant operation. Transplant the parameters according to the flags param.
 * \param [in] replace_mask_l2addr - mask for the replace_l2addr parameter.
 * \param [in] trav_fn - user callback to apply on all the matched entries.
 * \param [in] user_data - context passed to the user's callback.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_l2_traverse_run_traverse_by_rule(
    int unit,
    uint32 flags,
    bcm_l2_addr_t * match_l2addr,
    bcm_l2_addr_t * match_mask_l2addr,
    bcm_l2_addr_t * replace_l2addr,
    bcm_l2_addr_t * replace_mask_l2addr,
    bcm_l2_traverse_cb trav_fn,
    void *user_data)
{
    SHR_FUNC_INIT_VARS(unit);


    SHR_IF_ERR_EXIT(dnx_l2_addr_traverse_by_rule
                    (unit, l2ActionTypeFwdAndNA, flags, match_l2addr, match_mask_l2addr, replace_l2addr,
                     replace_mask_l2addr, trav_fn, user_data));

exit:
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *      dnx_l2_traverse_thread_pull_results
 * Purpose:
 *      Read the L2 Flash Traverse results from Host memory and call user callback.
 * Parameters:
 *      param - Unit -  number for this thread
 *      param - table_id - The MACT table id (FWD_MACT or FWD_MACT_IVL)
 *      param - trav_fn - user callback function
 *      param - user_data -user callback function parameters
 */
static shr_error_e
dnx_l2_traverse_thread_pull_results(
    int unit,
    uint32 table_id,
    bcm_l2_traverse_cb trav_fn,
    void *user_data)
{
    uint32 entry_handle_id;
    int is_end = 0;
    bcm_l2_addr_t l2addr;
    shr_error_e return_val;
    dnx_l2_action_type_t l2_action_type;

    SHR_FUNC_INIT_VARS(unit);
    DBAL_FUNC_INIT_VARS(unit);

    SHR_IF_ERR_EXIT(DBAL_HANDLE_ALLOC(unit, table_id, &entry_handle_id));

    SHR_IF_ERR_EXIT(dbal_iterator_init(unit, entry_handle_id, DBAL_ITER_MODE_GET_ENTRIES_FROM_DMA_NO_TRIGGER));

    SHR_IF_ERR_EXIT(dbal_iterator_get_next(unit, entry_handle_id, &is_end));
    l2_action_type = dnx_data_l2.general.lem_table_map_l2_action_get(unit, table_id)->l2_action_type;
    while (!is_end)
    {
        /** Fetch l2 address fields */
        SHR_IF_ERR_EXIT(dnx_l2_addr_from_dbal_to_struct(unit, entry_handle_id, table_id, &l2addr));

        /** Call user callbacks */
        return_val = trav_fn(unit, &l2addr, user_data);
        if (return_val)
        {
            char str[20];
            sal_snprintf(str, 20, "%02x:%02x:%02x:%02x:%02x:%02x", l2addr.mac[0], l2addr.mac[1],
                         l2addr.mac[2], l2addr.mac[3], l2addr.mac[4], l2addr.mac[5]);
            LOG_ERROR_EX(BSL_LOG_MODULE, "Callback returned an error %d for address mac - %s vsi - %d %s\n",
                         return_val, str, l2addr.vid, EMPTY);
            /** Clear the buffer that the flush uses for coping the entries */
            dbal_flush_reset_flush_work_buffers(unit, l2_action_type);

            /** Clear flush rules */
            SHR_IF_ERR_EXIT(dbal_flush_db_clear(unit, l2_action_type));

            /** Call flush end to unpause the age-machine */
            SHR_IF_ERR_EXIT(dbal_flush_end(unit, l2_action_type));
            SHR_EXIT();
        }

        SHR_IF_ERR_EXIT(dbal_iterator_get_next(unit, entry_handle_id, &is_end));
    }

    /*
     * No more data, call user callback with NULL data pointer to signal end of data.
     */
    trav_fn(unit, NULL, user_data);
exit:
    DBAL_FUNC_FREE_VARS;
    SHR_FUNC_EXIT;
}

/*
 * Function:
 *      l2_traverse_thread
 * Purpose:
 *      Low priority thread that handles L2 flush traverse operation in non-blocking mode.
 * Parameters:
 *      input    - User input
 * Notes:
 *      This thread can get awoken on by the following reasons:
 *      1.  L2 Flush traverse, in non-blocking mode, has been triggered.
 *      2.  Deinit process triggered - the thread is triggered to "kill" itself and exit.
 */
static shr_error_e
dnx_l2_traverse_thread(
    int unit,
    void *input)
{
    SHR_FUNC_INIT_VARS(unit);

    /*
     * Pull on the DMA results:
     */
    SHR_IF_ERR_EXIT(dnx_l2_traverse_thread_pull_results
                    (unit, l2_traverse_db[unit].table_id, l2_traverse_db[unit].trav_fn,
                     l2_traverse_db[unit].user_data));

exit:
    SHR_FUNC_EXIT;
}

/*
* See header file for description
*/
shr_error_e
dnx_l2_traverse_thread_start(
    int unit)
{
    int priority;
    shr_thread_manager_config_t thread_config_info;

    SHR_FUNC_INIT_VARS(unit);

    LOG_VERBOSE(BSL_LOG_MODULE,
                (BSL_META_U(unit, "dnx_l2_traverse_thread_start: Creating L2 Flush Traverse thread.\n")));

    /** Clear L2 Flush traverse DB */
    sal_memset(&l2_traverse_db[unit], 0, sizeof(l2_flush_traverse_non_blocking_t));

    /*
     * Use SOC property for thread priority
     */
    priority = dnx_data_l2.age_and_flush_machine.traverse_thread_priority_get(unit);

    /*
     * Start L2 Flush Traverse thread.
     */
    shr_thread_manager_config_t_init(&thread_config_info);
    thread_config_info.name = "bcmL2Flush";
    thread_config_info.bsl_module = BSL_LOG_MODULE;
    thread_config_info.interval = sal_sem_FOREVER;
    thread_config_info.type = SHR_THREAD_MANAGER_TYPE_EVENT;
    thread_config_info.callback = dnx_l2_traverse_thread;
    thread_config_info.user_data = NULL;
    thread_config_info.thread_priority = priority;
    thread_config_info.stop_timeout_usec = SHR_THREAD_MANAGER_MAX_TIMEOUT;
    SHR_IF_ERR_EXIT(shr_thread_manager_create(unit, &thread_config_info, &(l2_traverse_db[unit].l2_traverse_tid)));

exit:
    SHR_FUNC_EXIT;
}

/*
* See header file for description
*/
shr_error_e
dnx_l2_traverse_thread_stop(
    int unit)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "dnx_l2_traverse_thread_stop: Destroy L2 Flush Traverse thread.\n")));

    if (l2_traverse_db[unit].l2_traverse_tid != NULL)
    {
        SHR_IF_ERR_EXIT(shr_thread_manager_destroy(&(l2_traverse_db[unit].l2_traverse_tid)));
    }

    SHR_EXIT();

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Awake (trigger) the L2 Flush Traverse Thread (non-blocking mode).
 *
 * \param [in] unit - unit id
 * \param [in] trav_fn - user callback that is called for every filtered MAC entry.
 * \param [in] user_data - context to add to the user callback.
 * \param [in] table_id - The MACT table id (FWD_MACT or FWD_MACT_IVL)
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
static shr_error_e
dnx_l2_traverse_thread_awake(
    int unit,
    bcm_l2_traverse_cb trav_fn,
    void *user_data,
    uint32 table_id)
{
    SHR_FUNC_INIT_VARS(unit);

    LOG_VERBOSE(BSL_LOG_MODULE, (BSL_META_U(unit, "dnx_l2_traverse_thread_awake: trigger the thread.\n")));

    /** Save table_id, so data can be parsed correctly */
    l2_traverse_db[unit].table_id = table_id;

    /** Update calback parameters */
    l2_traverse_db[unit].trav_fn = trav_fn;
    l2_traverse_db[unit].user_data = user_data;

    /** trigger the low priority thread */
    SHR_IF_ERR_EXIT(shr_thread_manager_trigger(l2_traverse_db[unit].l2_traverse_tid));

    SHR_EXIT();
exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Call trav_fn for all the entries in FWD_MACT.
 *
 * \param [in] unit - unit id.
 * \param [in] trav_fn - user callback.
 * \param [in] user_data - context to add to the user callback.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_traverse(
    int unit,
    bcm_l2_traverse_cb trav_fn,
    void *user_data)
{
    uint32 traverse_flags;
    uint32 local_flags = 0;
    bcm_l2_addr_t match_addr;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    sal_memset((void *) &match_addr, 0, sizeof(bcm_l2_addr_t));

    /** Return all the entries in FWD_MACT table only regardless of the hit bit. Static and dynamic entries. */
    traverse_flags = BCM_L2_TRAVERSE_IGNORE_DES_HIT | BCM_L2_TRAVERSE_MATCH_STATIC;

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_traverse_verify
                           (unit, traverse_flags, &match_addr, NULL, NULL, NULL, trav_fn, user_data));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_flags_to_local_flags(unit, &match_addr, traverse_flags, &local_flags));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags, &match_addr, NULL, NULL, NULL, trav_fn, user_data));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Traverse the MAC table according to filter rules and call a callback for each entry.
 *
 * \param [in] unit - unit id
 * \param [in] flags - rules for the traverse filter. \n
 * BCM_L2_TRAVERSE_MATCH_STATIC - traverse static and dynamic entries, otherwise traverse only static or dynamic entries according to
 * match_addr.flags. \n
 * BCM_L2_TRAVERSE_MATCH_MAC - filter by a given mac address taken from match_addr. \n
 * BCM_L2_TRAVERSE_MATCH_VLAN - filter by a given VSI taken from match_addr. \n
 * BCM_L2_TRAVERSE_MATCH_DEST - filter by a given port and encap_id taken from match_addr. \n
 * BCM_L2_TRAVERSE_MATCH_GROUP - filter by a given group taken from match_addr. \n
 * BCM_L2_TRAVERSE_IGNORE_DES_HIT - If present, ignore hit status in compare. Otherwise traverse only entries with hit status that matches
 * match_addr.flags. \n
 * \param [in] match_addr - filter rules for the traverse.  \n
 * [in] match_addr.flags - configures which fields to use. \n
 * [in] match_addr.mac - mac address to filter. \n
 * [in] match_addr.vid - VSI to filter. \n
 * [in] match_addr.port - port param fot destination filtering. \n
 * [in] match_addr.tgid - trunk id for filtering according to destination. \n
 * [in] match_addr.group - filter according to group field. \n
 * \param [in] trav_fn - user callback that is called for every filtered MAC entry.
 * \param [in] user_data - context to add to the user callback.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_matched_traverse(
    int unit,
    uint32 flags,
    bcm_l2_addr_t * match_addr,
    bcm_l2_traverse_cb trav_fn,
    void *user_data)
{
    uint32 local_flags = 0;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_traverse_verify(unit, flags, match_addr, NULL, NULL, NULL, trav_fn, user_data));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_flags_to_local_flags(unit, match_addr, flags, &local_flags));

    /** Return MAC table entries according to the flags and filter rules */
    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags, match_addr, NULL, NULL, NULL, trav_fn, user_data));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Traverse the MAC table according to filter rules and mask, call a callback for each entry.
 *
 * \param [in] unit - unit id
 * \param [in] flags - rules for the traverse filter. \n
 * BCM_L2_TRAVERSE_MATCH_STATIC - traverse static and dynamic entries, otherwise traverse only static or dynamic entries according to
 * match_addr.flags. \n
 * BCM_L2_TRAVERSE_MATCH_MAC - filter by a given mac address taken from match_addr. \n
 * BCM_L2_TRAVERSE_MATCH_VLAN - filter by a given VSI taken from match_addr. \n
 * BCM_L2_TRAVERSE_MATCH_DEST - filter by a given port and encap_id taken from match_addr. \n
 * BCM_L2_TRAVERSE_MATCH_GROUP - filter by a given group taken from match_addr. \n
 * BCM_L2_TRAVERSE_IGNORE_DES_HIT - If present, ignore hit status in compare. Otherwise traverse only entries with hit status that matches
 * match_addr.flags. \n
 * \param [in] match_addr - data for filter rules. \n
 * [in] match_addr.flags - configures which fields to use. \n
 * [in] match_addr.mac - mac address to filter. \n
 * [in] match_addr.vid - VSI to filter. \n
 * [in] match_addr.port - port param fot destination filtering. \n
 * [in] match_addr.tgid - trunk id for filtering according to destination. \n
 * [in] match_addr.group - filter according to group field. \n
 * \param [in] mask_addr - mask for filter rules. Same field description like match_addr. Only set bits are compared.
 * \param [in] trav_fn - user callback that is called for every filtered MAC entry.
 * \param [in] user_data - context to add to the user callback.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_match_masked_traverse(
    int unit,
    uint32 flags,
    bcm_l2_addr_t * match_addr,
    bcm_l2_addr_t * mask_addr,
    bcm_l2_traverse_cb trav_fn,
    void *user_data)
{
    uint32 local_flags = 0;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_traverse_verify(unit, flags, match_addr, mask_addr, NULL, NULL, trav_fn, user_data));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_flags_to_local_flags(unit, match_addr, flags, &local_flags));

    /** Return MAC table entries according to the flags and filter rules */
    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags, match_addr, mask_addr, NULL, NULL, trav_fn, user_data));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Replace destination or delete multiple/all L2 entries.
 *
 * \param [in] unit - Relevant unit
 * \param [in] flags - Replace/delete flags BCM_L2_REPLACE_* \n
 * Supported flags: \n
 * BCM_L2_REPLACE_MATCH_STATIC - Replace static and dynamic entries \n
 * BCM_L2_REPLACE_MATCH_MAC - Replace entries with a given MAC address \n
 * BCM_L2_REPLACE_MATCH_VLAN - Replace entries with a given VSI \n
 * BCM_L2_REPLACE_MATCH_DEST - Replace entries having a given destination \n
 * BCM_L2_REPLACE_IGNORE_DES_HIT - Ignore the hit bit in the filter rule \n
 * BCM_L2_REPLACE_DELETE - Delete the entries according to the filters \n
 * BCM_L2_REPLACE_DES_HIT_CLEAR - Clear hit bit \n
 * BCM_L2_REPLACE_DYNAMIC_SET - Change the entry to be dynamic \n
 * BCM_L2_REPLACE_DYNAMIC_CLEAR - Change the entry to be static \n
 * BCM_L2_REPLACE_MIGRATE_PORT - Update destination port \n
 * BCM_L2_REPLACE_NEW_TRUNK - Update trunk destination \n
 * BCM_L2_REPLACE_PROTECTION_RING - Update protection ring desstination \n
 * BCM_L2_REPLACE_MATCH_GROUP - Replace entries with a given group \n
 * BCM_L2_REPLACE_NO_CALLBACKS - Do not call user callbacks for every entry replaced \n
 * \param [in] match_addr - L2 parameters to match on delete/replace \n
 * [in] match_addr.flags - configures which fields to use. \n
 * [in] match_addr.mac - mac address to filter. \n
 * [in] match_addr.vid - VSI to filter. \n
 * [in] match_addr.port - port param fot destination filtering. \n
 * [in] match_addr.tgid - trunk id for filtering according to destination. \n
 * [in] match_addr.group - filter according to group field. \n
 * \param [in] new_module - not used
 * \param [in] new_port - New port for a replace
 * \param [in] new_trunk - New trunk ID for a replace
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_replace(
    int unit,
    uint32 flags,
    bcm_l2_addr_t * match_addr,
    bcm_module_t new_module,
    bcm_port_t new_port,
    bcm_trunk_t new_trunk)
{
    uint32 local_flags = 0;
    bcm_l2_addr_t replace_addr;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    sal_memset(&replace_addr, 0x0, sizeof(replace_addr));
    replace_addr.modid = new_module;
    replace_addr.port = new_port;
    replace_addr.tgid = new_trunk;

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_replace_verify
                           (unit, flags, match_addr, match_addr, &replace_addr, &replace_addr, NULL, NULL));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_format_addresses
                    (unit, flags, match_addr, match_addr, &replace_addr, &replace_addr));

    SHR_IF_ERR_EXIT(dnx_l2_replace_flags_to_local_flags(unit, match_addr, flags, &local_flags));

    /** Update MAC entries according to the flags */
    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, (local_flags | DNX_L2_TRAVERSE_LRN), match_addr, NULL, &replace_addr, NULL, NULL, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief -
 *
 * \param [in] unit - unit id
 * \param [in] flags - Replace/delete flags BCM_L2_REPLACE_* \n
 * Supported replace flags: \n
 * BCM_L2_REPLACE_MATCH_STATIC - Replace static and dynamic entries \n
 * BCM_L2_REPLACE_MATCH_MAC - Replace entries with a given MAC address \n
 * BCM_L2_REPLACE_MATCH_VLAN - Replace entries with a given VSI \n
 * BCM_L2_REPLACE_MATCH_DEST - Replace entries having a given destination \n
 * BCM_L2_REPLACE_IGNORE_DES_HIT - Ignore the hit bit in the filter rule \n
 * BCM_L2_REPLACE_DELETE - Delete the entries according to the filters \n
 * BCM_L2_REPLACE_DES_HIT_CLEAR - Clear hit bit \n
 * BCM_L2_REPLACE_DYNAMIC_SET - Change the entry to be dynamic \n
 * BCM_L2_REPLACE_DYNAMIC_CLEAR - Change the entry to be static \n
 * BCM_L2_REPLACE_MIGRATE_PORT - Update destination port \n
 * BCM_L2_REPLACE_NEW_TRUNK - Update trunk destination \n
 * BCM_L2_REPLACE_PROTECTION_RING - Update protection ring desstination \n
 * BCM_L2_REPLACE_MATCH_GROUP - Replace entries with a given group \n
 * BCM_L2_REPLACE_NO_CALLBACKS - Do not call user callbacks for every entry replaced \n
 * \param [in] match_addr - L2 parameters to match on delete/replace \n
 * [in] match_addr.flags - configures which fields to use. \n
 * [in] match_addr.mac - mac address to filter. \n
 * [in] match_addr.vid - VSI to filter. \n
 * [in] match_addr.port - port param fot destination filtering. \n
 * [in] match_addr.tgid - trunk id for filtering according to destination. \n
 * [in] match_addr.group - filter according to group field.
 * \param [in] mask_addr - mask for the filter rules. Only set bits are compared. See match_addr for fields description.
 * \param [in] replace_addr - new data to be replaced in the entries
 * \param [in] replace_mask_addr - mask to the new data. Only set bits are updated.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_replace_match(
    int unit,
    uint32 flags,
    bcm_l2_addr_t * match_addr,
    bcm_l2_addr_t * mask_addr,
    bcm_l2_addr_t * replace_addr,
    bcm_l2_addr_t * replace_mask_addr)
{
    uint32 local_flags = 0;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_replace_verify
                           (unit, flags, match_addr, mask_addr, replace_addr, replace_mask_addr, NULL, NULL));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_format_addresses
                    (unit, flags, match_addr, mask_addr, replace_addr, replace_mask_addr));

    SHR_IF_ERR_EXIT(dnx_l2_replace_flags_to_local_flags(unit, match_addr, flags, &local_flags));

    /** Update MAC entries according to the flags */
    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags | DNX_L2_TRAVERSE_LRN, match_addr, mask_addr, replace_addr, replace_mask_addr,
                     NULL, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Delete MAC entries (static and dynamic) according to a given port.
 *
 * \param [in] unit - unit id
 * \param [in] mod - not used
 * \param [in] port - port for filtering which entries to delete
 * \param [in] flags - Only BCM_L2_DELETE_NO_CALLBACKS, BCM_L2_DELETE_STATIC and BCM_L2_DELETE_IVL are handled in the function.
 * When no callbacks flag exists the API will not call user callbacks.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_addr_delete_by_port(
    int unit,
    bcm_module_t mod,
    bcm_port_t port,
    uint32 flags)
{
    uint32 replace_flags = 0;
    uint32 local_flags = 0;
    bcm_l2_addr_t match_addr;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_IF_ERR_EXIT(dnx_l2_delete_verify(unit, flags));

    if (flags & BCM_L2_DELETE_NO_CALLBACKS)
    {
        replace_flags |= BCM_L2_REPLACE_NO_CALLBACKS;
    }

    if (flags & BCM_L2_DELETE_STATIC)
    {
        replace_flags |= BCM_L2_REPLACE_MATCH_STATIC;
    }

    if (flags & BCM_L2_DELETE_IVL)
    {
        replace_flags |= BCM_L2_REPLACE_VLAN_AND_VPN_TYPE;
    }

    sal_memset((void *) &match_addr, 0, sizeof(bcm_l2_addr_t));

    match_addr.port = port;

    /** Delete all the MAC table entries regardless of the hit bit. Static and dynacmic entries according to port. */
    replace_flags |= BCM_L2_REPLACE_IGNORE_DES_HIT | BCM_L2_REPLACE_MATCH_DEST | BCM_L2_REPLACE_DELETE;

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_replace_verify(unit, replace_flags, &match_addr, NULL, NULL, NULL, NULL, NULL));

    SHR_IF_ERR_EXIT(dnx_l2_replace_flags_to_local_flags(unit, &match_addr, replace_flags, &local_flags));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags | DNX_L2_TRAVERSE_LRN, &match_addr, NULL, NULL, NULL, NULL, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Delete MAC entries (static and dynamic) according to a given MAC address.
 *
 * \param [in] unit - unit id
 * \param [in] mac - mac for filtering which entries to delete
 * \param [in] flags - Only BCM_L2_DELETE_NO_CALLBACKS, BCM_L2_DELETE_STATIC and BCM_L2_DELETE_IVL are handled in the function.
 * When no callbacks flag exists the API will not call user callbacks.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_addr_delete_by_mac(
    int unit,
    bcm_mac_t mac,
    uint32 flags)
{
    uint32 replace_flags = 0;
    uint32 local_flags = 0;
    bcm_l2_addr_t match_addr;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_IF_ERR_EXIT(dnx_l2_delete_verify(unit, flags));

    if (flags & BCM_L2_DELETE_NO_CALLBACKS)
    {
        replace_flags |= BCM_L2_REPLACE_NO_CALLBACKS;
    }

    if (flags & BCM_L2_DELETE_STATIC)
    {
        replace_flags |= BCM_L2_REPLACE_MATCH_STATIC;
    }

    if (flags & BCM_L2_DELETE_IVL)
    {
        replace_flags |= BCM_L2_REPLACE_VLAN_AND_VPN_TYPE;
    }

    bcm_l2_addr_t_init(&match_addr, mac, 0);

    /** Delete all the MAC table entries regardless of the hit bit. Static and dynacmic entries according to port. */
    replace_flags |= BCM_L2_REPLACE_IGNORE_DES_HIT | BCM_L2_REPLACE_MATCH_MAC | BCM_L2_REPLACE_DELETE;

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_replace_verify(unit, replace_flags, &match_addr, NULL, NULL, NULL, NULL, NULL));

    SHR_IF_ERR_EXIT(dnx_l2_replace_flags_to_local_flags(unit, &match_addr, replace_flags, &local_flags));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags | DNX_L2_TRAVERSE_LRN, &match_addr, NULL, NULL, NULL, NULL, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Delete MAC entries (static and dynamic) according to a given VSI.
 *
 * \param [in] unit - unit id
 * \param [in] vid - vsi for filtering which entries to delete
 * \param [in] flags - Only BCM_L2_DELETE_NO_CALLBACKS, BCM_L2_DELETE_STATIC and BCM_L2_DELETE_IVL are handled in the function.
  * When no callbacks flag exists the API will not call user callbacks.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_addr_delete_by_vlan(
    int unit,
    bcm_vlan_t vid,
    uint32 flags)
{
    uint32 replace_flags = 0;
    uint32 local_flags = 0;
    bcm_l2_addr_t match_addr;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_IF_ERR_EXIT(dnx_l2_delete_verify(unit, flags));

    if (flags & BCM_L2_DELETE_NO_CALLBACKS)
    {
        replace_flags |= BCM_L2_REPLACE_NO_CALLBACKS;
    }

    if (flags & BCM_L2_DELETE_STATIC)
    {
        replace_flags |= BCM_L2_REPLACE_MATCH_STATIC;
    }

    if (flags & BCM_L2_DELETE_IVL)
    {
        replace_flags |= BCM_L2_REPLACE_VLAN_AND_VPN_TYPE;
    }

    sal_memset((void *) &match_addr, 0, sizeof(bcm_l2_addr_t));

    match_addr.vid = vid;

    /** Delete all the MAC table entries regardless of the hit bit. Static and dynamic entries according to port. */
    replace_flags |= BCM_L2_REPLACE_IGNORE_DES_HIT | BCM_L2_REPLACE_MATCH_VLAN | BCM_L2_REPLACE_DELETE;

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_replace_verify(unit, replace_flags, &match_addr, NULL, NULL, NULL, NULL, NULL));

    SHR_IF_ERR_EXIT(dnx_l2_replace_flags_to_local_flags(unit, &match_addr, replace_flags, &local_flags));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags | DNX_L2_TRAVERSE_LRN, &match_addr, NULL, NULL, NULL, NULL, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Delete MAC entries (static and dynamic) according to a given trunk id.
 *
 * \param [in] unit - unit id
 * \param [in] tid - trunk id for filtering which entries to delete
 * \param [in] flags - Only BCM_L2_DELETE_NO_CALLBACKS, BCM_L2_DELETE_STATIC and BCM_L2_DELETE_IVL are handled in the function.
 * When no callbacks flag exists the API will not call user callbacks.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_addr_delete_by_trunk(
    int unit,
    bcm_trunk_t tid,
    uint32 flags)
{
    uint32 replace_flags = 0;
    uint32 local_flags = 0;
    bcm_l2_addr_t match_addr;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_IF_ERR_EXIT(dnx_l2_delete_verify(unit, flags));

    if (flags & BCM_L2_DELETE_NO_CALLBACKS)
    {
        replace_flags |= BCM_L2_REPLACE_NO_CALLBACKS;
    }

    if (flags & BCM_L2_DELETE_STATIC)
    {
        replace_flags |= BCM_L2_REPLACE_MATCH_STATIC;
    }

    if (flags & BCM_L2_DELETE_IVL)
    {
        replace_flags |= BCM_L2_REPLACE_VLAN_AND_VPN_TYPE;
    }

    sal_memset((void *) &match_addr, 0, sizeof(bcm_l2_addr_t));

    match_addr.tgid = tid;
    match_addr.flags |= BCM_L2_TRUNK_MEMBER;
    BCM_GPORT_TRUNK_SET(match_addr.port, match_addr.tgid);
    match_addr.encap_id = BCM_FORWARD_ENCAP_ID_INVALID;

    /** Delete all the MAC table entries regardless of the hit bit. Static and dynacmic entries according to port. */
    replace_flags |= BCM_L2_REPLACE_IGNORE_DES_HIT | BCM_L2_REPLACE_MATCH_DEST | BCM_L2_REPLACE_DELETE;

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_replace_verify(unit, replace_flags, &match_addr, NULL, NULL, NULL, NULL, NULL));

    SHR_IF_ERR_EXIT(dnx_l2_replace_flags_to_local_flags(unit, &match_addr, replace_flags, &local_flags));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags | DNX_L2_TRAVERSE_LRN, &match_addr, NULL, NULL, NULL, NULL, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Delete MAC entries (static and dynamic) according to a given MAC address and port.
 *
 * \param [in] unit - unit id
 * \param [in] mac - mac for filtering which entries to delete
 * \param [in] mod - not used
 * \param [in] port - port for filtering the MAC entries
 * \param [in] flags - Only BCM_L2_DELETE_NO_CALLBACKS, BCM_L2_DELETE_STATIC and BCM_L2_DELETE_IVL are handled in the function.
 *    When no callbacks flag exists the API will not call user callbacks.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_addr_delete_by_mac_port(
    int unit,
    bcm_mac_t mac,
    bcm_module_t mod,
    bcm_port_t port,
    uint32 flags)
{
    uint32 replace_flags = 0;
    uint32 local_flags = 0;
    bcm_l2_addr_t match_addr;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_IF_ERR_EXIT(dnx_l2_delete_verify(unit, flags));

    if (flags & BCM_L2_DELETE_NO_CALLBACKS)
    {
        replace_flags |= BCM_L2_REPLACE_NO_CALLBACKS;
    }

    if (flags & BCM_L2_DELETE_STATIC)
    {
        replace_flags |= BCM_L2_REPLACE_MATCH_STATIC;
    }

    if (flags & BCM_L2_DELETE_IVL)
    {
        replace_flags |= BCM_L2_REPLACE_VLAN_AND_VPN_TYPE;
    }

    bcm_l2_addr_t_init(&match_addr, mac, 0);

    match_addr.port = port;

    /** Delete all the MAC table entries regardless of the hit bit. Static and dynacmic entries according to port. */
    replace_flags |=
        BCM_L2_REPLACE_IGNORE_DES_HIT | BCM_L2_REPLACE_MATCH_MAC | BCM_L2_REPLACE_MATCH_DEST | BCM_L2_REPLACE_DELETE;

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_replace_verify(unit, replace_flags, &match_addr, NULL, NULL, NULL, NULL, NULL));

    SHR_IF_ERR_EXIT(dnx_l2_replace_flags_to_local_flags(unit, &match_addr, replace_flags, &local_flags));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags | DNX_L2_TRAVERSE_LRN, &match_addr, NULL, NULL, NULL, NULL, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Delete MAC entries (static and dynamic) according to a given trunk id and VSI.
 *
 * \param [in] unit - unit id
 * \param [in] vid - VSI for filtering which entries to delete
 * \param [in] tid - trunk id for filtering which entries to delete
 * \param [in] flags - Only BCM_L2_DELETE_NO_CALLBACKS, BCM_L2_DELETE_STATIC and BCM_L2_DELETE_IVL are handled in the function.
 * When no callbacks flag exists the API will not call user callbacks.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_addr_delete_by_vlan_trunk(
    int unit,
    bcm_vlan_t vid,
    bcm_trunk_t tid,
    uint32 flags)
{
    uint32 replace_flags = 0;
    uint32 local_flags = 0;
    bcm_l2_addr_t match_addr;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_IF_ERR_EXIT(dnx_l2_delete_verify(unit, flags));

    if (flags & BCM_L2_DELETE_NO_CALLBACKS)
    {
        replace_flags |= BCM_L2_REPLACE_NO_CALLBACKS;
    }

    if (flags & BCM_L2_DELETE_STATIC)
    {
        replace_flags |= BCM_L2_REPLACE_MATCH_STATIC;
    }

    if (flags & BCM_L2_DELETE_IVL)
    {
        replace_flags |= BCM_L2_REPLACE_VLAN_AND_VPN_TYPE;
    }

    if ((dnx_trunk_t_verify(unit, tid) != _SHR_E_NONE))
    {
        SHR_ERR_EXIT(_SHR_E_PARAM, "Invalid trunk ID: %d!", tid);
    }
    sal_memset((void *) &match_addr, 0, sizeof(bcm_l2_addr_t));

    match_addr.vid = vid;
    match_addr.tgid = tid;
    match_addr.flags |= BCM_L2_TRUNK_MEMBER;
    match_addr.encap_id = BCM_FORWARD_ENCAP_ID_INVALID;

    /** Delete all the MAC table entries regardless of the hit bit. Static and dynacmic entries according to port. */
    replace_flags |=
        BCM_L2_REPLACE_IGNORE_DES_HIT | BCM_L2_REPLACE_MATCH_DEST | BCM_L2_REPLACE_DELETE | BCM_L2_REPLACE_MATCH_VLAN;

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_replace_verify(unit, replace_flags, &match_addr, NULL, NULL, NULL, NULL, NULL));

    SHR_IF_ERR_EXIT(dnx_l2_replace_flags_to_local_flags(unit, &match_addr, replace_flags, &local_flags));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags | DNX_L2_TRAVERSE_LRN, &match_addr, NULL, NULL, NULL, NULL, NULL));

exit:
    SHR_FUNC_EXIT;
}

/**
 * \brief - Delete MAC entries (static and dynamic) according to a given MAC address and port.
 *
 * \param [in] unit - unit id
 * \param [in] vid - VSI for filtering which entries to delete
 * \param [in] mod - not used
 * \param [in] port - port for filtering the MAC entries
 * \param [in] flags - Only BCM_L2_DELETE_NO_CALLBACKS, BCM_L2_DELETE_STATIC and BCM_L2_DELETE_IVL are handled in the function.
 * When no callbacks flag exists the API will not call user callbacks.
 *
 * \return
 *   shr_error_e
 *
 * \remark
 *   * None
 * \see
 *   * None
 */
shr_error_e
bcm_dnx_l2_addr_delete_by_vlan_port(
    int unit,
    bcm_vlan_t vid,
    bcm_module_t mod,
    bcm_port_t port,
    uint32 flags)
{
    uint32 replace_flags = 0;
    uint32 local_flags = 0;
    bcm_l2_addr_t match_addr;

    SHR_FUNC_INIT_VARS(unit);
    DNX_ERR_RECOVERY_NOT_NEEDED(unit);

    SHR_IF_ERR_EXIT(dnx_l2_delete_verify(unit, flags));

    if (flags & BCM_L2_DELETE_NO_CALLBACKS)
    {
        replace_flags |= BCM_L2_REPLACE_NO_CALLBACKS;
    }

    if (flags & BCM_L2_DELETE_STATIC)
    {
        replace_flags |= BCM_L2_REPLACE_MATCH_STATIC;
    }

    if (flags & BCM_L2_DELETE_IVL)
    {
        replace_flags |= BCM_L2_REPLACE_VLAN_AND_VPN_TYPE;
    }

    sal_memset((void *) &match_addr, 0, sizeof(bcm_l2_addr_t));

    match_addr.vid = vid;
    match_addr.port = port;

    /** Delete all the MAC table entries regardless of the hit bit. Static and dynacmic entries according to port. */
    replace_flags |=
        BCM_L2_REPLACE_IGNORE_DES_HIT | BCM_L2_REPLACE_MATCH_VLAN | BCM_L2_REPLACE_MATCH_DEST | BCM_L2_REPLACE_DELETE;

    SHR_INVOKE_VERIFY_DNXC(dnx_l2_replace_verify(unit, replace_flags, &match_addr, NULL, NULL, NULL, NULL, NULL));

    SHR_IF_ERR_EXIT(dnx_l2_replace_flags_to_local_flags(unit, &match_addr, replace_flags, &local_flags));

    SHR_IF_ERR_EXIT(dnx_l2_traverse_run_traverse_by_rule
                    (unit, local_flags | DNX_L2_TRAVERSE_LRN, &match_addr, NULL, NULL, NULL, NULL, NULL));

exit:
    SHR_FUNC_EXIT;
}

 /*
  * }
  */
