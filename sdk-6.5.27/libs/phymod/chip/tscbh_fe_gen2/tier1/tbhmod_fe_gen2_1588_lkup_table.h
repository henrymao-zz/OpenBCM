#include <phymod/phymod.h>

#define TBHMOD_FE_GEN2_TS_MPP_MEM_SIZE 160
#define TBHMOD_FE_GEN2_TS_DEFAULT_TABLE_SIZE 40
#define TBHMOD_FE_GEN2_TS_TABLE_SIZE 120
#define TBHMOD_FE_GEN2_TS_MAPP_MEM_TABLE_CNT 4
#define TBHMOD_FE_GEN2_TS_ENTRY_SIZE 3
#define TBHMOD_FE_GEN2_TS_PSLL_BASED_ENTRY_SIZE 4
#define TBHMOD_FE_GEN2_TS_RX_MPP1_NATIVE_START_ADDR 80
#define TBHMOD_FE_GEN2_TS_RX_MPP_EVEN_BANK_NATIVE_TO_ADDR(na)      (na * 2)
#define TBHMOD_FE_GEN2_TS_RX_MPP_ODD_BANK_NATIVE_TO_ADDR(na)       ((na * 2)+1)

typedef enum {
    TBHMOD_FE_GEN2_SPEED_10G_IEEE_KR1,
    TBHMOD_FE_GEN2_SPEED_10G_IEEE_KR1_CL74,
    TBHMOD_FE_GEN2_SPEED_25G_IEEE_KS1_CS1,
    TBHMOD_FE_GEN2_SPEED_25G_IEEE_KS1_CS1_CL74,
    TBHMOD_FE_GEN2_SPEED_25G_IEEE_KR1_CR1,
    TBHMOD_FE_GEN2_SPEED_25G_IEEE_KR1_CR1_CL74,
    TBHMOD_FE_GEN2_SPEED_25G_IEEE_KR1_CR1_RS528,
    TBHMOD_FE_GEN2_SPEED_40G_IEEE_KR4,
    TBHMOD_FE_GEN2_SPEED_40G_IEEE_KR4_CL74,
    TBHMOD_FE_GEN2_SPEED_40G_IEEE_CR4,
    TBHMOD_FE_GEN2_SPEED_40G_IEEE_CR4_CL74,
    TBHMOD_FE_GEN2_SPEED_50G_IEEE_KR1_CR1,
    TBHMOD_FE_GEN2_SPEED_100G_IEEE_KR4,
    TBHMOD_FE_GEN2_SPEED_100G_IEEE_CR4,
    TBHMOD_FE_GEN2_SPEED_100G_IEEE_KR2_CR2,
    TBHMOD_FE_GEN2_SPEED_200G_IEEE_KR4_CR4,
    TBHMOD_FE_GEN2_SPEED_400G_IEEE_X8,
    TBHMOD_FE_GEN2_SPEED_20G_BRCM_KR1,
    TBHMOD_FE_GEN2_SPEED_20G_BRCM_KR1_CL74,
    TBHMOD_FE_GEN2_SPEED_20G_BRCM_CR1,
    TBHMOD_FE_GEN2_SPEED_20G_BRCM_CR1_CL74,
    TBHMOD_FE_GEN2_SPEED_25G_BRCM_KR1,
    TBHMOD_FE_GEN2_SPEED_25G_BRCM_KR1_CL74,
    TBHMOD_FE_GEN2_SPEED_25G_BRCM_KR1_RS528,
    TBHMOD_FE_GEN2_SPEED_25G_BRCM_CR1,
    TBHMOD_FE_GEN2_SPEED_25G_BRCM_CR1_CL74,
    TBHMOD_FE_GEN2_SPEED_25G_BRCM_CR1_RS528,
    TBHMOD_FE_GEN2_SPEED_25G_BRCM_NO_FEC_KR1_CR1,
    TBHMOD_FE_GEN2_SPEED_25G_BRCM_FEC_BASE_R_KR1_CR1,
    TBHMOD_FE_GEN2_SPEED_25G_BRCM_FEC_528_KR1_CR1,
    TBHMOD_FE_GEN2_SPEED_40G_BRCM_KR2,
    TBHMOD_FE_GEN2_SPEED_40G_BRCM_CR2,
    TBHMOD_FE_GEN2_SPEED_50G_BRCM_CR2_KR2_NO_FEC,
    TBHMOD_FE_GEN2_SPEED_50G_BRCM_CR2_KR2_RS_FEC,
    TBHMOD_FE_GEN2_SPEED_50G_BRCM_FEC_544_CR2_KR2,
    TBHMOD_FE_GEN2_SPEED_50G_BRCM_NO_FEC_CR1_KR1,
    TBHMOD_FE_GEN2_SPEED_50G_BRCM_FEC_528_CR1_KR1,
    TBHMOD_FE_GEN2_SPEED_50G_BRCM_FEC_272_CR1_KR1,
    TBHMOD_FE_GEN2_SPEED_100G_BRCM_NO_FEC_X4,
    TBHMOD_FE_GEN2_SPEED_100G_BRCM_KR4_CR4,
    TBHMOD_FE_GEN2_SPEED_100G_BRCM_NO_FEC_KR2_CR2,
    TBHMOD_FE_GEN2_SPEED_100G_BRCM_FEC_528_KR2_CR2,
    TBHMOD_FE_GEN2_SPEED_100G_BRCM_FEC_272_CR2_KR2,
    TBHMOD_FE_GEN2_SPEED_200G_BRCM_FEC_544_CR8_KR8,
    TBHMOD_FE_GEN2_SPEED_200G_BRCM_NO_FEC_KR4_CR4,
    TBHMOD_FE_GEN2_SPEED_200G_BRCM_KR4_CR4,
    TBHMOD_FE_GEN2_SPEED_200G_BRCM_FEC_272_CR4_KR4,
    TBHMOD_FE_GEN2_SPEED_200G_BRCM_FEC_272_N4,
    TBHMOD_FE_GEN2_SPEED_400G_BRCM_FEC_KR8_CR8,
    TBHMOD_FE_GEN2_SPEED_400G_BRCM_FEC_272_N8,
    TBHMOD_FE_GEN2_SPEED_MODE_COUNT
}tbhmod_fe_gen2_1588_table_index_t;

typedef struct tbhmod_fe_gen2_1588_lkup_table_entry_s {
    /* Index for the default speed entry */
    uint32_t mapped_spd_table_index;
    phymod_fec_type_t fec_type;
    /* Index of the 1588 table */
    tbhmod_fe_gen2_1588_table_index_t ts_table_index;
    uint32_t table_size;
} tbhmod_fe_gen2_1588_lkup_table_entry_t;

typedef uint32_t tbhmod_fe_gen2_ts_table_entry[TBHMOD_FE_GEN2_TS_TABLE_SIZE][TBHMOD_FE_GEN2_TS_ENTRY_SIZE];
typedef uint32_t tbhmod_fe_gen2_ts_table_entry_mem[TBHMOD_FE_GEN2_TS_ENTRY_SIZE];

int tbhmod_fe_gen2_1588_table_index_get(uint32_t speed_index, phymod_fec_type_t fec, int *ts_table_index, uint32_t* table_size);
int tbhmod_fe_gen2_tbl_entry_to_psll_entry_map(uint32_t* tbl_entry, uint32_t* psll_entry);
int tbhmod_fe_gen2_psll_entry_to_tbl_entry_map(uint32_t* psll_entry, uint32_t* tbl_entry);
int tbhmod_fe_gen2_ts_tx_table_get(int index, int is_sfd, tbhmod_fe_gen2_ts_table_entry** tbl);
int tbhmod_fe_gen2_ts_rx_table_get(int index, int is_sfd, tbhmod_fe_gen2_ts_table_entry** tbl);

extern tbhmod_fe_gen2_ts_table_entry* tbhmod_fe_gen2_ts_table_tx_sop_get(void);
extern tbhmod_fe_gen2_ts_table_entry* tbhmod_fe_gen2_ts_table_rx_sop_get(void);
extern tbhmod_fe_gen2_ts_table_entry* tbhmod_fe_gen2_ts_table_tx_sfd_get(void);
extern tbhmod_fe_gen2_ts_table_entry* tbhmod_fe_gen2_ts_table_rx_sfd_get(void);
