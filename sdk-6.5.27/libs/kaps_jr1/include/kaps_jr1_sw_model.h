

#ifndef INCLUDED_KAPS_JR1_MODEL_H
#define INCLUDED_KAPS_JR1_MODEL_H

#include <stdint.h>

#include "kaps_jr1_device.h"
#include "kaps_jr1_errors.h"
#include "kaps_jr1_init.h"

#ifdef __cplusplus
extern "C" {
#endif


enum kaps_jr1_sw_model_property
{
    KAPS_JR1_SW_MODEL_DUMP,    
    KAPS_JR1_SW_MODEL_UNROLL_COMPLEX_INST, 
    KAPS_JR1_SW_MODEL_TRACE,   
    KAPS_JR1_SW_MODEL_TRIG_EVENTS,  


    KAPS_JR1_SW_MODEL_INVALID  
    
};


enum kaps_jr1_model_tcam_format
{
    KAPS_JR1_MODEL_TCAM_FORMAT_1,
    KAPS_JR1_MODEL_TCAM_FORMAT_2,
    KAPS_JR1_MODEL_TCAM_FORMAT_3
};



enum kaps_jr1_model_xpt_version
{
    KAPS_JR1_MODEL_XPT_VERSION_1,
    KAPS_JR1_MODEL_XPT_VERSION_2
};








struct kaps_jr1_sw_model_config
{
    uint8_t id; 
    uint8_t sub_type;   
    uint16_t profile;   
    
    uint16_t total_num_rpb; 
    uint16_t total_num_ads; 
    uint16_t is_small_bb_present; 
    uint16_t total_num_small_bb; 
    uint16_t total_num_ads2_blks; 
    uint16_t total_num_bb;  
    uint16_t num_rows_in_rpb[KAPS_JR1_HW_MAX_NUM_RPB_BLOCKS]; 
    uint16_t num_rows_in_small_bb; 
    uint16_t num_rows_in_bb; 

    uint32_t num_dbs_per_group; 
    uint32_t num_db_groups; 
    

    uint16_t small_bb_start; 
    uint16_t small_bb_end;   
    uint16_t large_bb_start; 
    uint16_t large_bb_end;   

    uint16_t num_bb_in_one_bb_cascade;  

    uint16_t is_x_y_valid_bit_common; 

    uint16_t is_valid_bit_updated_only_on_x_write; 

    enum kaps_jr1_model_tcam_format tcam_format; 

    enum kaps_jr1_model_xpt_version xpt_version; 

    uint32_t initialize_with_invalid_bb_search_intf; 
    
    uint32_t ads_width_8; 
 
};






kaps_jr1_status kaps_jr1_sw_model_init(enum kaps_jr1_device_pair_type pair_type,
                             uint32_t flags, uint32_t dev_id, uint32_t kaps_jr1_sub_type,
                             uint32_t profile,  
                             void **xpt);





kaps_jr1_status kaps_jr1_sw_model_destroy(void *xpt);




kaps_jr1_status kaps_jr1_sw_model_set_property(void *xpt, enum kaps_jr1_sw_model_property property, ...);

#ifdef __cplusplus
}
#endif
#endif 
