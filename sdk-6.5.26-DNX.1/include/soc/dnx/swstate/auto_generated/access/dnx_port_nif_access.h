
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */

#ifndef __DNX_PORT_NIF_ACCESS_H__
#define __DNX_PORT_NIF_ACCESS_H__

#include <soc/dnx/swstate/auto_generated/types/dnx_port_nif_types.h>



typedef int (*dnx_port_nif_db_is_init_cb)(
    int unit, uint8 *is_init);


typedef int (*dnx_port_nif_db_init_cb)(
    int unit);


typedef int (*dnx_port_nif_db_arb_link_list_list_info_head_set_cb)(
    int unit, int head);


typedef int (*dnx_port_nif_db_arb_link_list_list_info_head_get_cb)(
    int unit, int *head);


typedef int (*dnx_port_nif_db_arb_link_list_list_info_tail_set_cb)(
    int unit, int tail);


typedef int (*dnx_port_nif_db_arb_link_list_list_info_tail_get_cb)(
    int unit, int *tail);


typedef int (*dnx_port_nif_db_arb_link_list_list_info_size_set_cb)(
    int unit, int size);


typedef int (*dnx_port_nif_db_arb_link_list_list_info_size_get_cb)(
    int unit, int *size);


typedef int (*dnx_port_nif_db_arb_link_list_linking_info_alloc_cb)(
    int unit, uint32 nof_instances_to_alloc_0);


typedef int (*dnx_port_nif_db_arb_link_list_linking_info_next_section_set_cb)(
    int unit, uint32 linking_info_idx_0, int next_section);


typedef int (*dnx_port_nif_db_arb_link_list_linking_info_next_section_get_cb)(
    int unit, uint32 linking_info_idx_0, int *next_section);


typedef int (*dnx_port_nif_db_arb_link_list_nof_sections_allocated_set_cb)(
    int unit, uint32 nof_sections_allocated_idx_0, uint32 nof_sections_allocated);


typedef int (*dnx_port_nif_db_arb_link_list_nof_sections_allocated_get_cb)(
    int unit, uint32 nof_sections_allocated_idx_0, uint32 *nof_sections_allocated);


typedef int (*dnx_port_nif_db_arb_link_list_nof_sections_allocated_alloc_cb)(
    int unit, uint32 nof_instances_to_alloc_0);


typedef int (*dnx_port_nif_db_oft_link_list_list_info_head_set_cb)(
    int unit, int head);


typedef int (*dnx_port_nif_db_oft_link_list_list_info_head_get_cb)(
    int unit, int *head);


typedef int (*dnx_port_nif_db_oft_link_list_list_info_tail_set_cb)(
    int unit, int tail);


typedef int (*dnx_port_nif_db_oft_link_list_list_info_tail_get_cb)(
    int unit, int *tail);


typedef int (*dnx_port_nif_db_oft_link_list_list_info_size_set_cb)(
    int unit, int size);


typedef int (*dnx_port_nif_db_oft_link_list_list_info_size_get_cb)(
    int unit, int *size);


typedef int (*dnx_port_nif_db_oft_link_list_linking_info_alloc_cb)(
    int unit, uint32 nof_instances_to_alloc_0);


typedef int (*dnx_port_nif_db_oft_link_list_linking_info_next_section_set_cb)(
    int unit, uint32 linking_info_idx_0, int next_section);


typedef int (*dnx_port_nif_db_oft_link_list_linking_info_next_section_get_cb)(
    int unit, uint32 linking_info_idx_0, int *next_section);


typedef int (*dnx_port_nif_db_oft_link_list_nof_sections_allocated_set_cb)(
    int unit, uint32 nof_sections_allocated_idx_0, uint32 nof_sections_allocated);


typedef int (*dnx_port_nif_db_oft_link_list_nof_sections_allocated_get_cb)(
    int unit, uint32 nof_sections_allocated_idx_0, uint32 *nof_sections_allocated);


typedef int (*dnx_port_nif_db_oft_link_list_nof_sections_allocated_alloc_cb)(
    int unit, uint32 nof_instances_to_alloc_0);


typedef int (*dnx_port_nif_db_ofr_link_list_list_info_alloc_cb)(
    int unit, uint32 nof_instances_to_alloc_0);


typedef int (*dnx_port_nif_db_ofr_link_list_list_info_head_set_cb)(
    int unit, uint32 list_info_idx_0, int head);


typedef int (*dnx_port_nif_db_ofr_link_list_list_info_head_get_cb)(
    int unit, uint32 list_info_idx_0, int *head);


typedef int (*dnx_port_nif_db_ofr_link_list_list_info_tail_set_cb)(
    int unit, uint32 list_info_idx_0, int tail);


typedef int (*dnx_port_nif_db_ofr_link_list_list_info_tail_get_cb)(
    int unit, uint32 list_info_idx_0, int *tail);


typedef int (*dnx_port_nif_db_ofr_link_list_list_info_size_set_cb)(
    int unit, uint32 list_info_idx_0, int size);


typedef int (*dnx_port_nif_db_ofr_link_list_list_info_size_get_cb)(
    int unit, uint32 list_info_idx_0, int *size);


typedef int (*dnx_port_nif_db_ofr_link_list_linking_info_alloc_cb)(
    int unit, uint32 nof_instances_to_alloc_0, uint32 nof_instances_to_alloc_1);


typedef int (*dnx_port_nif_db_ofr_link_list_linking_info_next_section_set_cb)(
    int unit, uint32 linking_info_idx_0, uint32 linking_info_idx_1, int next_section);


typedef int (*dnx_port_nif_db_ofr_link_list_linking_info_next_section_get_cb)(
    int unit, uint32 linking_info_idx_0, uint32 linking_info_idx_1, int *next_section);


typedef int (*dnx_port_nif_db_ofr_link_list_nof_sections_allocated_set_cb)(
    int unit, uint32 nof_sections_allocated_idx_0, uint32 nof_sections_allocated_idx_1, uint32 nof_sections_allocated);


typedef int (*dnx_port_nif_db_ofr_link_list_nof_sections_allocated_get_cb)(
    int unit, uint32 nof_sections_allocated_idx_0, uint32 nof_sections_allocated_idx_1, uint32 *nof_sections_allocated);


typedef int (*dnx_port_nif_db_ofr_link_list_nof_sections_allocated_alloc_cb)(
    int unit, uint32 nof_instances_to_alloc_0, uint32 nof_instances_to_alloc_1);


typedef int (*dnx_port_nif_db_g_hao_active_client_set_cb)(
    int unit, int g_hao_active_client);


typedef int (*dnx_port_nif_db_g_hao_active_client_get_cb)(
    int unit, int *g_hao_active_client);




typedef struct {
    dnx_port_nif_db_arb_link_list_list_info_head_set_cb set;
    dnx_port_nif_db_arb_link_list_list_info_head_get_cb get;
} dnx_port_nif_db_arb_link_list_list_info_head_cbs;


typedef struct {
    dnx_port_nif_db_arb_link_list_list_info_tail_set_cb set;
    dnx_port_nif_db_arb_link_list_list_info_tail_get_cb get;
} dnx_port_nif_db_arb_link_list_list_info_tail_cbs;


typedef struct {
    dnx_port_nif_db_arb_link_list_list_info_size_set_cb set;
    dnx_port_nif_db_arb_link_list_list_info_size_get_cb get;
} dnx_port_nif_db_arb_link_list_list_info_size_cbs;


typedef struct {
    
    dnx_port_nif_db_arb_link_list_list_info_head_cbs head;
    
    dnx_port_nif_db_arb_link_list_list_info_tail_cbs tail;
    
    dnx_port_nif_db_arb_link_list_list_info_size_cbs size;
} dnx_port_nif_db_arb_link_list_list_info_cbs;


typedef struct {
    dnx_port_nif_db_arb_link_list_linking_info_next_section_set_cb set;
    dnx_port_nif_db_arb_link_list_linking_info_next_section_get_cb get;
} dnx_port_nif_db_arb_link_list_linking_info_next_section_cbs;


typedef struct {
    dnx_port_nif_db_arb_link_list_linking_info_alloc_cb alloc;
    
    dnx_port_nif_db_arb_link_list_linking_info_next_section_cbs next_section;
} dnx_port_nif_db_arb_link_list_linking_info_cbs;


typedef struct {
    dnx_port_nif_db_arb_link_list_nof_sections_allocated_set_cb set;
    dnx_port_nif_db_arb_link_list_nof_sections_allocated_get_cb get;
    dnx_port_nif_db_arb_link_list_nof_sections_allocated_alloc_cb alloc;
} dnx_port_nif_db_arb_link_list_nof_sections_allocated_cbs;


typedef struct {
    
    dnx_port_nif_db_arb_link_list_list_info_cbs list_info;
    
    dnx_port_nif_db_arb_link_list_linking_info_cbs linking_info;
    
    dnx_port_nif_db_arb_link_list_nof_sections_allocated_cbs nof_sections_allocated;
} dnx_port_nif_db_arb_link_list_cbs;


typedef struct {
    dnx_port_nif_db_oft_link_list_list_info_head_set_cb set;
    dnx_port_nif_db_oft_link_list_list_info_head_get_cb get;
} dnx_port_nif_db_oft_link_list_list_info_head_cbs;


typedef struct {
    dnx_port_nif_db_oft_link_list_list_info_tail_set_cb set;
    dnx_port_nif_db_oft_link_list_list_info_tail_get_cb get;
} dnx_port_nif_db_oft_link_list_list_info_tail_cbs;


typedef struct {
    dnx_port_nif_db_oft_link_list_list_info_size_set_cb set;
    dnx_port_nif_db_oft_link_list_list_info_size_get_cb get;
} dnx_port_nif_db_oft_link_list_list_info_size_cbs;


typedef struct {
    
    dnx_port_nif_db_oft_link_list_list_info_head_cbs head;
    
    dnx_port_nif_db_oft_link_list_list_info_tail_cbs tail;
    
    dnx_port_nif_db_oft_link_list_list_info_size_cbs size;
} dnx_port_nif_db_oft_link_list_list_info_cbs;


typedef struct {
    dnx_port_nif_db_oft_link_list_linking_info_next_section_set_cb set;
    dnx_port_nif_db_oft_link_list_linking_info_next_section_get_cb get;
} dnx_port_nif_db_oft_link_list_linking_info_next_section_cbs;


typedef struct {
    dnx_port_nif_db_oft_link_list_linking_info_alloc_cb alloc;
    
    dnx_port_nif_db_oft_link_list_linking_info_next_section_cbs next_section;
} dnx_port_nif_db_oft_link_list_linking_info_cbs;


typedef struct {
    dnx_port_nif_db_oft_link_list_nof_sections_allocated_set_cb set;
    dnx_port_nif_db_oft_link_list_nof_sections_allocated_get_cb get;
    dnx_port_nif_db_oft_link_list_nof_sections_allocated_alloc_cb alloc;
} dnx_port_nif_db_oft_link_list_nof_sections_allocated_cbs;


typedef struct {
    
    dnx_port_nif_db_oft_link_list_list_info_cbs list_info;
    
    dnx_port_nif_db_oft_link_list_linking_info_cbs linking_info;
    
    dnx_port_nif_db_oft_link_list_nof_sections_allocated_cbs nof_sections_allocated;
} dnx_port_nif_db_oft_link_list_cbs;


typedef struct {
    dnx_port_nif_db_ofr_link_list_list_info_head_set_cb set;
    dnx_port_nif_db_ofr_link_list_list_info_head_get_cb get;
} dnx_port_nif_db_ofr_link_list_list_info_head_cbs;


typedef struct {
    dnx_port_nif_db_ofr_link_list_list_info_tail_set_cb set;
    dnx_port_nif_db_ofr_link_list_list_info_tail_get_cb get;
} dnx_port_nif_db_ofr_link_list_list_info_tail_cbs;


typedef struct {
    dnx_port_nif_db_ofr_link_list_list_info_size_set_cb set;
    dnx_port_nif_db_ofr_link_list_list_info_size_get_cb get;
} dnx_port_nif_db_ofr_link_list_list_info_size_cbs;


typedef struct {
    dnx_port_nif_db_ofr_link_list_list_info_alloc_cb alloc;
    
    dnx_port_nif_db_ofr_link_list_list_info_head_cbs head;
    
    dnx_port_nif_db_ofr_link_list_list_info_tail_cbs tail;
    
    dnx_port_nif_db_ofr_link_list_list_info_size_cbs size;
} dnx_port_nif_db_ofr_link_list_list_info_cbs;


typedef struct {
    dnx_port_nif_db_ofr_link_list_linking_info_next_section_set_cb set;
    dnx_port_nif_db_ofr_link_list_linking_info_next_section_get_cb get;
} dnx_port_nif_db_ofr_link_list_linking_info_next_section_cbs;


typedef struct {
    dnx_port_nif_db_ofr_link_list_linking_info_alloc_cb alloc;
    
    dnx_port_nif_db_ofr_link_list_linking_info_next_section_cbs next_section;
} dnx_port_nif_db_ofr_link_list_linking_info_cbs;


typedef struct {
    dnx_port_nif_db_ofr_link_list_nof_sections_allocated_set_cb set;
    dnx_port_nif_db_ofr_link_list_nof_sections_allocated_get_cb get;
    dnx_port_nif_db_ofr_link_list_nof_sections_allocated_alloc_cb alloc;
} dnx_port_nif_db_ofr_link_list_nof_sections_allocated_cbs;


typedef struct {
    
    dnx_port_nif_db_ofr_link_list_list_info_cbs list_info;
    
    dnx_port_nif_db_ofr_link_list_linking_info_cbs linking_info;
    
    dnx_port_nif_db_ofr_link_list_nof_sections_allocated_cbs nof_sections_allocated;
} dnx_port_nif_db_ofr_link_list_cbs;


typedef struct {
    dnx_port_nif_db_g_hao_active_client_set_cb set;
    dnx_port_nif_db_g_hao_active_client_get_cb get;
} dnx_port_nif_db_g_hao_active_client_cbs;


typedef struct {
    dnx_port_nif_db_is_init_cb is_init;
    dnx_port_nif_db_init_cb init;
    
    dnx_port_nif_db_arb_link_list_cbs arb_link_list;
    
    dnx_port_nif_db_oft_link_list_cbs oft_link_list;
    
    dnx_port_nif_db_ofr_link_list_cbs ofr_link_list;
    
    dnx_port_nif_db_g_hao_active_client_cbs g_hao_active_client;
} dnx_port_nif_db_cbs;





extern dnx_port_nif_db_cbs dnx_port_nif_db;

#endif 
