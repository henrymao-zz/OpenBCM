/***********************************************************************************
 *                                                                                 *
 * Copyright: (c) 2021 Broadcom.                                                   *
 * Broadcom Proprietary and Confidential. All rights reserved.                     *
 *                                                                                 *
 *  Revision      :                                                            *
 *                                                                                 *
 *  Description   :  This is an auto generated diagnostic dump tool file           *
 *                                                                                 *
 **********************************************************************************/

/* THIS FILE IS GENERATED USING AN AUTOMATED SCRIPT.DO NOT EDIT THIS FILE DIRECTLY! */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSPREY7_V2L8P1_API_COLLECT_CUSTOM_FIELDS_H
#define OSPREY7_V2L8P1_API_COLLECT_CUSTOM_FIELDS_H
#include "osprey7_v2l8p1_ipconfig.h"
#include "osprey7_v2l8p1_usr_includes.h"
#include "common/srds_api_err_code.h"
#include "common/srds_api_types.h"

/*! @file
 *  @brief Auto generated tool for updating struct member fields
 */

/*! @addtogroup APITag
 * @{
 */

/*! @defgroup SerdesApiCollectCustomFieldsTag Struct Collection APIs
 * Serdes API functions used for updating structs.
 */

/*! @addtogroup SerdesApiCollectCustomFieldsTag
 * @{
 */

 #ifndef SMALL_FOOTPRINT

#include "osprey7_v2l8p1_lane_detailed_status.h"

/** osprey7_v2l8p1_collect_custom_fields_osprey7_v2l8p1_detailed_lane_status_st_pre
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] st struct pointer which will have its custom fields updated
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_collect_custom_fields_osprey7_v2l8p1_detailed_lane_status_st_pre(srds_access_t *sa__, osprey7_v2l8p1_detailed_lane_status_st_t *st);

/** osprey7_v2l8p1_collect_custom_fields_osprey7_v2l8p1_detailed_lane_status_st_post
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] st struct pointer which will have its custom fields updated
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_collect_custom_fields_osprey7_v2l8p1_detailed_lane_status_st_post(srds_access_t *sa__, osprey7_v2l8p1_detailed_lane_status_st_t *st);

#include "osprey7_v2l8p1_lane_state.h"

/** osprey7_v2l8p1_collect_custom_fields_osprey7_v2l8p1_lane_state_st_pre
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] st struct pointer which will have its custom fields updated
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_collect_custom_fields_osprey7_v2l8p1_lane_state_st_pre(srds_access_t *sa__, osprey7_v2l8p1_lane_state_st_t *st);

/** osprey7_v2l8p1_collect_custom_fields_osprey7_v2l8p1_lane_state_st_post
 * @param[in] sa__ is an opaque state vector passed through to device access functions.
 * @param[out] st struct pointer which will have its custom fields updated
 * @return Error Code generated by API (returns ERR_CODE_NONE if no errors).
 */
err_code_t osprey7_v2l8p1_collect_custom_fields_osprey7_v2l8p1_lane_state_st_post(srds_access_t *sa__, osprey7_v2l8p1_lane_state_st_t *st);


#endif /* !SMALL_FOOTPRINT */
/*! @} SerdesApiCollectCustomFieldsTag */
/*! @} APITag */
#endif /* SERDES_API_COLLECT_CUSTOM_FIELDS_H */
#ifdef __cplusplus
}
#endif
