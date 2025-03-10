/** \file dnx/swstate/auto_generated/diagnostic/dnx_field_tcam_access_commandline.h
 *
 * sw state functions declarations
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 *
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __DNX_FIELD_TCAM_ACCESS_COMMANDLINE_H__
#define __DNX_FIELD_TCAM_ACCESS_COMMANDLINE_H__

#include <appl/diag/sand/diag_sand_framework.h>
#include <appl/diag/sand/diag_sand_utils.h>
#include <soc/dnxc/swstate/dnxc_sw_state_h_includes.h>
#include <soc/dnxc/swstate/dnx_sw_state_dump.h>
#include <soc/dnx/swstate/auto_generated/types/dnx_field_tcam_access_types.h>
#include <soc/dnxc/swstate/callbacks/sw_state_htb_callbacks.h>
#include <soc/dnxc/swstate/types/sw_state_bitmap.h>
#include <soc/dnxc/swstate/types/sw_state_hash_table.h>
#include <soc/dnx/swstate/auto_generated/types/dnx_field_types.h>
#include <soc/dnx/swstate/auto_generated/types/dnx_field_tcam_manager_types.h>
#if defined(DNX_SW_STATE_DIAGNOSTIC)
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_dump_man;
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_size_get_man;
extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_desc[];

extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_entry_location_hash_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_entry_location_hash_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_entry_location_hash_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_entry_location_hash_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_entry_location_hash_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_entry_location_hash_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_entry_location_hash_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_entry_location_hash_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_entry_location_hash_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_valid_bmp_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_valid_bmp_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_valid_bmp_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_valid_bmp_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_valid_bmp_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_valid_bmp_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_valid_bmp_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_valid_bmp_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_valid_bmp_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_valid_bmp_v_bit_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_valid_bmp_v_bit_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_valid_bmp_v_bit_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_valid_bmp_v_bit_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_valid_bmp_v_bit_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_valid_bmp_v_bit_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_valid_bmp_v_bit_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_valid_bmp_v_bit_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_valid_bmp_v_bit_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_v_bit_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_v_bit_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_v_bit_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_v_bit_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_v_bit_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_v_bit_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_v_bit_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_v_bit_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_entry_in_use_bmp_v_bit_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_params_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_params_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_params_dt_bank_id_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_dt_bank_id_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_params_dt_bank_id_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_dt_bank_id_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_dt_bank_id_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_dt_bank_id_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_dt_bank_id_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_dt_bank_id_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_dt_bank_id_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_params_stage_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_stage_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_params_stage_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_stage_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_stage_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_stage_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_stage_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_stage_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_stage_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_params_bank_allocation_mode_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_bank_allocation_mode_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_params_bank_allocation_mode_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_bank_allocation_mode_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_bank_allocation_mode_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_bank_allocation_mode_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_bank_allocation_mode_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_bank_allocation_mode_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_bank_allocation_mode_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_params_key_size_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_key_size_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_params_key_size_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_key_size_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_key_size_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_key_size_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_key_size_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_key_size_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_key_size_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_params_action_size_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_action_size_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_params_action_size_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_action_size_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_action_size_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_action_size_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_action_size_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_action_size_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_action_size_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_params_actual_action_size_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_actual_action_size_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_params_actual_action_size_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_actual_action_size_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_actual_action_size_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_actual_action_size_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_actual_action_size_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_actual_action_size_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_actual_action_size_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_params_prefix_size_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_prefix_size_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_params_prefix_size_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_prefix_size_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_prefix_size_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_prefix_size_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_prefix_size_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_prefix_size_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_prefix_size_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_params_direct_table_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_direct_table_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_params_direct_table_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_direct_table_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_direct_table_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_direct_table_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_direct_table_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_direct_table_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_direct_table_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_params_context_sharing_handlers_cb_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_context_sharing_handlers_cb_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_params_context_sharing_handlers_cb_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_context_sharing_handlers_cb_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_context_sharing_handlers_cb_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_context_sharing_handlers_cb_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_params_context_sharing_handlers_cb_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_params_context_sharing_handlers_cb_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_params_context_sharing_handlers_cb_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_fg_prefix_per_core_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_prefix_per_core_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_fg_prefix_per_core_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_prefix_per_core_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_prefix_per_core_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_prefix_per_core_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_fg_prefix_per_core_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_fg_prefix_per_core_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_fg_prefix_per_core_size_get_man;



extern sh_sand_cmd_t sh_dnx_swstate_dnx_field_tcam_access_cache_install_in_progress_cmds[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_cache_install_in_progress_man;
extern const char cmd_dnx_swstate_dnx_field_tcam_access_cache_install_in_progress_desc[];
shr_error_e sh_dnx_swstate_dnx_field_tcam_access_cache_install_in_progress_dump_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_cache_install_in_progress_dump_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_cache_install_in_progress_dump_man;


shr_error_e sh_dnx_swstate_dnx_field_tcam_access_cache_install_in_progress_size_get_cmd(int unit, args_t *args, sh_sand_control_t *sand_control);
extern sh_sand_option_t dnx_swstate_dnx_field_tcam_access_cache_install_in_progress_size_get_options[];
extern sh_sand_man_t dnx_swstate_dnx_field_tcam_access_cache_install_in_progress_size_get_man;


#endif /* DNX_SW_STATE_DIAGNOSTIC */

#endif /* __DNX_FIELD_TCAM_ACCESS_COMMANDLINE_H__ */
