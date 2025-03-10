# $Id: $
# This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
# 
# Copyright 2007-2020 Broadcom Inc. All rights reserved.
#
# Makefile for streamlined packet I/O drivers
#

LOCALDIR = src/bcm/esw/pktio

export PKTIO_FUNCS =                                            \
    bcmcnet_buf_mngr_init                                       \
    bcmcnet_cmicx_pdma_desc_ops_init                            \
    bcmcnet_cmicx_pdma_driver_attach                            \
    bcmcnet_cmicx_pdma_driver_detach                            \
    bcmcnet_cmicx_pdma_hw_hdls_init                             \
    bcmcnet_group_intr_ack                                      \
    bcmcnet_group_intr_check                                    \
    bcmcnet_group_intr_disable                                  \
    bcmcnet_group_intr_enable                                   \
    bcmcnet_group_poll                                          \
    bcmcnet_pdma_dev_chan_to_queue                              \
    bcmcnet_pdma_dev_cleanup                                    \
    bcmcnet_pdma_dev_dock                                       \
    bcmcnet_pdma_dev_info_get                                   \
    bcmcnet_pdma_dev_init                                       \
    bcmcnet_pdma_dev_queue_to_chan                              \
    bcmcnet_pdma_dev_resume                                     \
    bcmcnet_pdma_dev_rx_resume                                  \
    bcmcnet_pdma_dev_rx_suspend                                 \
    bcmcnet_pdma_dev_start                                      \
    bcmcnet_pdma_dev_stats_get                                  \
    bcmcnet_pdma_dev_stats_reset                                \
    bcmcnet_pdma_dev_stop                                       \
    bcmcnet_pdma_dev_suspend                                    \
    bcmcnet_pdma_dev_undock                                     \
    bcmcnet_queue_intr_ack                                      \
    bcmcnet_queue_intr_check                                    \
    bcmcnet_queue_intr_disable                                  \
    bcmcnet_queue_intr_enable                                   \
    bcmcnet_queue_poll                                          \
    bcmcnet_rx_queue_intr_ack                                   \
    bcmcnet_rx_queue_intr_check                                 \
    bcmcnet_rx_queue_intr_disable                               \
    bcmcnet_rx_queue_intr_enable                                \
    bcmcnet_rx_queue_poll                                       \
    bcmcnet_tx_queue_intr_ack                                   \
    bcmcnet_tx_queue_intr_check                                 \
    bcmcnet_tx_queue_intr_disable                               \
    bcmcnet_tx_queue_intr_enable                                \
    bcmcnet_tx_queue_poll                                       \
    bcmcnet_pdma_open                                           \
    bcmcnet_pdma_rx_queue_int_coalesce                          \
    bcmcnet_pdma_rx_queue_reg_dump                              \
    bcmcnet_pdma_tx_queue_int_coalesce                          \
    bcmcnet_pdma_tx_queue_reg_dump                              \
    bcmcnet_intr_cb_register                                    \
    bcmcnet_intr_cb_unregister                                  \
    bcmcnet_intr_ctrl_cleanup                                   \
    bcmcnet_intr_ctrl_init                                      \
    bcmcnet_poll_check                                          \
    bcmcnet_poll_complete                                       \
    bcmcnet_poll_disable                                        \
    bcmcnet_poll_enable                                         \
    bcmcnet_poll_schedule                                       \
    bcmcnet_dev_chan_config                                     \
    bcmcnet_dev_chan_query                                      \
    bcmcnet_dev_cleanup                                         \
    bcmcnet_dev_info_get                                        \
    bcmcnet_dev_init                                            \
    bcmcnet_dev_resume                                          \
    bcmcnet_dev_rx_queue_reg_dump                               \
    bcmcnet_dev_rx_queue_ring_dump                              \
    bcmcnet_dev_start                                           \
    bcmcnet_dev_stats_get                                       \
    bcmcnet_dev_stats_reset                                     \
    bcmcnet_dev_stop                                            \
    bcmcnet_dev_suspend                                         \
    bcmcnet_dev_tx_queue_reg_dump                               \
    bcmcnet_dev_tx_queue_ring_dump                              \
    bcmcnet_rx_cb_register                                      \
    bcmcnet_rx_cb_unregister                                    \
    bcmcnet_tx                                                  \
    bcmcnet_vnet_ops_register                                   \
    bcmcnet_pdma_group_poll                                     \
    bcmcnet_pdma_rx_queue_poll                                  \
    bcmcnet_pdma_rx_queue_release                               \
    bcmcnet_pdma_rx_queue_restore                               \
    bcmcnet_pdma_rx_queue_resume                                \
    bcmcnet_pdma_rx_queue_setup                                 \
    bcmcnet_pdma_rx_queue_suspend                               \
    bcmcnet_pdma_rx_ring_dump                                   \
    bcmcnet_pdma_rx_vqueue_release                              \
    bcmcnet_pdma_rx_vqueue_setup                                \
    bcmcnet_pdma_tx_queue_poll                                  \
    bcmcnet_pdma_tx_queue_release                               \
    bcmcnet_pdma_tx_queue_restore                               \
    bcmcnet_pdma_tx_queue_resume                                \
    bcmcnet_pdma_tx_queue_setup                                 \
    bcmcnet_pdma_tx_queue_suspend                               \
    bcmcnet_pdma_tx_queue_wakeup                                \
    bcmcnet_pdma_tx_queue_xmit                                  \
    bcmcnet_pdma_tx_ring_dump                                   \
    bcmcnet_pdma_tx_vqueue_release                              \
    bcmcnet_pdma_tx_vqueue_setup                                \
    bcmpkt_alloc                                                \
    bcmpkt_bpool_alloc                                          \
    bcmpkt_bpool_cleanup                                        \
    bcmpkt_bpool_create                                         \
    bcmpkt_bpool_destroy                                        \
    bcmpkt_bpool_free                                           \
    bcmpkt_bpool_info_dump                                      \
    bcmpkt_bpool_status_get                                     \
    bcmpkt_data_buf_alloc                                       \
    bcmpkt_data_buf_copy                                        \
    bcmpkt_data_buf_dump                                        \
    bcmpkt_data_buf_free                                        \
    bcmpkt_data_dump                                            \
    bcmpkt_dev_cleanup                                          \
    bcmpkt_dev_disable                                          \
    bcmpkt_dev_drv_attach                                       \
    bcmpkt_dev_drv_attached                                     \
    bcmpkt_dev_drv_detach                                       \
    bcmpkt_dev_drv_inuse                                        \
    bcmpkt_dev_drv_register                                     \
    bcmpkt_dev_drv_type_get                                     \
    bcmpkt_dev_drv_unet_attach                                  \
    bcmpkt_dev_drv_unet_detach                                  \
    bcmpkt_dev_drv_unregister                                   \
    bcmpkt_dev_enable                                           \
    bcmpkt_dev_enabled                                          \
    bcmpkt_dev_id_get                                           \
    bcmpkt_dev_info_dump                                        \
    bcmpkt_dev_init                                             \
    bcmpkt_dev_initialized                                      \
    bcmpkt_dev_stats_clear                                      \
    bcmpkt_dev_stats_dump                                       \
    bcmpkt_dev_stats_get                                        \
    bcmpkt_dev_type_get                                         \
    bcmpkt_dma_chan_get                                         \
    bcmpkt_dma_chan_get_list                                    \
    bcmpkt_dma_chan_set                                         \
    bcmpkt_filter_create                                        \
    bcmpkt_filter_destroy                                       \
    bcmpkt_filter_get                                           \
    bcmpkt_filter_traverse                                      \
    bcmpkt_framesize_min_get                                    \
    bcmpkt_framesize_min_set                                    \
    bcmpkt_free                                                 \
    bcmpkt_fwd_port_set                                         \
    bcmpkt_fwd_type_set                                         \
    bcmpkt_gih_dump                                             \
    bcmpkt_gih_fid_support_get                                  \
    bcmpkt_gih_field_get                                        \
    bcmpkt_gih_field_id_get                                     \
    bcmpkt_gih_field_list_dump                                  \
    bcmpkt_gih_field_name_get                                   \
    bcmpkt_gih_field_set                                        \
    bcmpkt_gih_is_supported                                     \
    bcmpkt_headroom                                             \
    bcmpkt_higig3_dump                                          \
    bcmpkt_higig3_fid_support_get                               \
    bcmpkt_higig3_field_get                                     \
    bcmpkt_higig3_field_id_get                                  \
    bcmpkt_higig3_field_list_dump                               \
    bcmpkt_higig3_field_name_get                                \
    bcmpkt_higig3_field_set                                     \
    bcmpkt_higig3_is_supported                                  \
    bcmpkt_higig_get                                            \
    bcmpkt_knet_drv_register                                    \
    bcmpkt_knet_drv_unregister                                  \
    bcmpkt_lbhdr_dump                                           \
    bcmpkt_lbhdr_fid_support_get                                \
    bcmpkt_lbhdr_field_get                                      \
    bcmpkt_lbhdr_field_id_get                                   \
    bcmpkt_lbhdr_field_list_dump                                \
    bcmpkt_lbhdr_field_name_get                                 \
    bcmpkt_lbhdr_field_set                                      \
    bcmpkt_lbhdr_get                                            \
    bcmpkt_net_drv_register                                     \
    bcmpkt_net_drv_type_get                                     \
    bcmpkt_net_drv_unregister                                   \
    bcmpkt_netif_create                                         \
    bcmpkt_netif_destroy                                        \
    bcmpkt_netif_get                                            \
    bcmpkt_netif_traverse                                       \
    bcmpkt_packet_claim                                         \
    bcmpkt_packet_clone                                         \
    bcmpkt_pmd_format                                           \
    bcmpkt_ppool_alloc                                          \
    bcmpkt_ppool_create                                         \
    bcmpkt_ppool_destroy                                        \
    bcmpkt_ppool_free                                           \
    bcmpkt_ppool_info_dump                                      \
    bcmpkt_ppool_status_get                                     \
    bcmpkt_pull                                                 \
    bcmpkt_push                                                 \
    bcmpkt_put                                                  \
    bcmpkt_rcpu_hdr                                             \
    bcmpkt_rcpu_hdr_get                                         \
    bcmpkt_rcpu_hdr_set                                         \
    bcmpkt_reserve                                              \
    bcmpkt_rx_rate_limit_get                                    \
    bcmpkt_rx_rate_limit_set                                    \
    bcmpkt_rx_reason_dump                                       \
    bcmpkt_rx_reason_name_get                                   \
    bcmpkt_rx_register                                          \
    bcmpkt_rx_unregister                                        \
    bcmpkt_rxpmd_dump                                           \
    bcmpkt_rxpmd_fid_support_get                                \
    bcmpkt_rxpmd_field_get                                      \
    bcmpkt_rxpmd_field_id_get                                   \
    bcmpkt_rxpmd_field_list_dump                                \
    bcmpkt_rxpmd_field_name_get                                 \
    bcmpkt_rxpmd_field_set                                      \
    bcmpkt_rxpmd_flex_dump                                      \
    bcmpkt_rxpmd_flex_fid_support_get                           \
    bcmpkt_rxpmd_flex_field_get                                 \
    bcmpkt_rxpmd_flex_field_id_get                              \
    bcmpkt_rxpmd_flex_field_list_dump                           \
    bcmpkt_rxpmd_flex_field_name_get                            \
    bcmpkt_rxpmd_flex_field_set                                 \
    bcmpkt_rxpmd_flex_reason_dump                               \
    bcmpkt_rxpmd_flex_reason_name_get                           \
    bcmpkt_rxpmd_flex_reasons_get                               \
    bcmpkt_rxpmd_flex_reasons_set                               \
    bcmpkt_rxpmd_flexdata_get                                   \
    bcmpkt_rxpmd_get                                            \
    bcmpkt_rxpmd_len_get                                        \
    bcmpkt_rxpmd_mh_get                                         \
    bcmpkt_rxpmd_reasons_get                                    \
    bcmpkt_rxpmd_reasons_set                                    \
    bcmpkt_socket_create                                        \
    bcmpkt_socket_created                                       \
    bcmpkt_socket_destroy                                       \
    bcmpkt_socket_drv_attach                                    \
    bcmpkt_socket_drv_detach                                    \
    bcmpkt_socket_drv_inuse                                     \
    bcmpkt_socket_drv_register                                  \
    bcmpkt_socket_drv_type_get                                  \
    bcmpkt_socket_drv_unregister                                \
    bcmpkt_socket_stats_clear                                   \
    bcmpkt_socket_stats_dump                                    \
    bcmpkt_tailroom                                             \
    bcmpkt_trace_counter_get                                    \
    bcmpkt_trace_data_collect                                   \
    bcmpkt_trace_data_len_get                                   \
    bcmpkt_trace_dop_data_collect                               \
    bcmpkt_trace_dop_fids_get                                   \
    bcmpkt_trace_dop_field_get                                  \
    bcmpkt_trace_drop_reasons_get                               \
    bcmpkt_trace_drv_get                                        \
    bcmpkt_trace_egr_dop_cnt_get                                \
    bcmpkt_trace_extract_field                                  \
    bcmpkt_trace_field_get                                      \
    bcmpkt_trace_fields_dump                                    \
    bcmpkt_trace_ing_dop_cnt_get                                \
    bcmpkt_trace_init                                           \
    bcmpkt_trace_max_dop_phase_get                              \
    bcmpkt_trace_pt_hit_info_get                                \
    bcmpkt_trace_pt_lookup_info_get                             \
    bcmpkt_trace_pt_to_dop_info_get                             \
    bcmpkt_trim                                                 \
    bcmpkt_tx                                                   \
    bcmpkt_txpmd_dump                                           \
    bcmpkt_txpmd_fid_support_get                                \
    bcmpkt_txpmd_field_get                                      \
    bcmpkt_txpmd_field_id_get                                   \
    bcmpkt_txpmd_field_list_dump                                \
    bcmpkt_txpmd_field_name_get                                 \
    bcmpkt_txpmd_field_set                                      \
    bcmpkt_txpmd_get                                            \
    bcmpkt_txpmd_len_get                                        \
    bcmpkt_unet_create                                          \
    bcmpkt_unet_created                                         \
    bcmpkt_unet_destroy                                         \
    bcmpkt_unet_drv_attach                                      \
    bcmpkt_unet_drv_detach                                      \
    bcmpkt_unet_drv_inuse                                       \
    bcmpkt_unet_drv_register                                    \
    bcmpkt_unet_drv_type_get                                    \
    bcmpkt_unet_drv_unregister                                  \
    bcmpkt_unet_stats_clear                                     \
    bcmpkt_unet_stats_dump                                      \
    bcmdrd_dev_exists                                           \
    bcmdrd_hal_dma_alloc                                        \
    bcmdrd_hal_dma_free                                         \
    bcmdrd_hal_dma_map                                          \
    bcmdrd_hal_dma_unmap                                        \
    bcmdrd_dev_type_str                                         \
    bcmdrd_feature_enabled                                      \
    bcmdrd_hal_reg32_read                                       \
    bcmdrd_hal_reg32_write                                      \
    bcmdrd_dev_byte_swap_packet_dma_get                         \
    bcmdrd_dev_byte_swap_non_packet_dma_get                     \
    bcmlrd_variant_get                                          \
    bcmbd_knet_enable_set                                       \
    bcmbd_knet_enable_get

PKTIO_IMPL = 1
CFLAGS =
include ${SDK}/make/Make.config

subdirs := bcmcnet bcmpkt chip
include ${SDK}/make/Make.subdirs

lib = libesw_pktio

include ${SDK}/make/Make.lib
include ${SDK}/make/Make.depend
