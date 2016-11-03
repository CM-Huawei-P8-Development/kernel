#ifndef __BSP_PMU_HI6561_H__
#define __BSP_PMU_HI6561_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <bsp_shared_ddr.h>
#include <bsp_icc.h>

#define SRAM_PASTAR_DPM_INFO (unsigned long)(SHM_MEM_PASTAR_DPM_INFO_ADDR)
#define PASTAR_DPM_SUSPEND_MASK_OFFSET 0
#define PASTAR_DPM_EN_TIMESTAMP_OFFSET 4
#define PASTAR_DPM_SWITCH_OFFSET 8

#define PASTAR_ICC_CHN_ID                          ((ICC_CHN_IFC << 16) | IFC_RECV_FUNC_PASTAR)
#define  pastar_print(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PASTAR, fmt,  ##__VA_ARGS__))

#if defined (__KERNEL__) || defined(__VXWORKS__)

#include <drv_dpm.h>
#include <drv_pmu.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <osl_spinlock.h>
#include <osl_types.h>
#include <drv_fs.h>

#define PMU_HI6561_OM_LOG            "/modem_log/log/pmu_hi6561_om.log"
#define RF_POWER_FROM_LDO 2
#define RF_POWER_FROM_HI6561 1
#define RF_POWER_FROM_NONE 0

#define PA_POWER_FROM_VSYS      2
#define PA_POWER_FROM_HI6561    1
#define PA_POWER_FROM_NONE      0

/*hi6561 power source id*/
typedef enum HI6561_POWER_ID_E
{
    PMU_HI6561_LDO1 = 0,
    PMU_HI6561_LDO2,
    PMU_HI6561_BUCK_PA,
    PMU_HI6561_BUCK1,
    PMU_HI6561_BUCK2,
    PMU_HI6561_POWER_ID_BUTT
}HI6561_POWER_ID;

typedef enum{
	HI6561_0=0,
	HI6561_1,
	HI6561_BUTT
}HI6561_ID_ENUM;

/****************************************************************
*
*function declare

*****************************************************************/

/*****************************************************************************
 �� �� ��  : drv_pmu_hi6561_exc_check
 ��������  : ͨ��ģ����PASTAR�Ƿ����쳣�ӿ�
 �������  : modem_id       ����
 �������  : ��
 �� �� ֵ  : BSP_OK          û���쳣
             BSP_ERROR       �����쳣
*****************************************************************************/
s32 drv_pmu_hi6561_exc_check(PWC_COMM_MODEM_E modem_id);
/*****************************************************************************
 �� �� ��  : drv_pmu_hi6561_voltage_set
 ��������  : ͨ��ģ�����õ�ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ���õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : BSP_OK          ���óɹ�
             BSP_ERROR       ����ʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_voltage_set(EM_MODEM_CONSUMER_ID consumer_id, u32 voltage_mv );

/*****************************************************************************
 �� �� ��  : drv_pmu_hi6561_voltage_get
 ��������  : ͨ��ģ���ȡ��ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ��õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : BSP_OK          ��ȡ�ɹ�
             BSP_ERROR       ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_voltage_get(EM_MODEM_CONSUMER_ID consumer_id, u32 *voltage_mv );

/*****************************************************************************
 �� �� ��  : drv_pmu_hi6561_voltage_list
 ��������  : ͨ��ģ���ȡ��ѹ���÷�Χ�ӿ�
 �������  : consumer_id     �û�id
             list            ��ѹ��Χ����
             size            �����С
 �������  : ��
 �� �� ֵ  : BSP_OK          ��ȡ�ɹ�
             BSP_ERROR       ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_voltage_list(EM_MODEM_CONSUMER_ID consumer_id, u16 **list, u32 *size);

/*****************************************************************************
 ����	: drv_pmu_hi6561_apt_enable
 ����	: ͨ��ģ��ʹ��APT״̬�ӿ�
 ����	: modem_id       ����
 ���	: ��
 ����	: 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_apt_enable(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 ����	: drv_pmu_hi6561_apt_disable
 ����	: ͨ��ģ��ȥʹ��APT״̬�ӿ�
 ����	: modem_id       ����
 ���	: ��
 ����	: 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_apt_disable(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 ����	: drv_pmu_hi6561_apt_status_get
 ����	: ͨ��ģ���ȡ��ǰAPT״̬�ӿ�
 ����	: modem_id       ����
 ���	: ��
 ����	: 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_apt_status_get(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 ���� 	: drv_pmu_hi6561_mode_config
 ����	: ͨ��ģ������Gģ��Wģ�ӿ�
 ����	: modem_id       ����
 ���	: ��
 ����  : BSP_OK         ���óɹ�/  BSP_ERROR      ����ʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_mode_config(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 fun_name	: pmu_hi6561_init
 function		: hi6561 init
 para_in		: void
 para_out		: no
 back_val    	:
 			  0:success
 			-1:fail
*****************************************************************************/
int pmu_hi6561_init_phase1(void);
int pmu_hi6561_init_phase2(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_hi6561_pa_poweron
 ��������  :PA �ϵ�
 �������  : ��

 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
int bsp_pmu_hi6561_pa_poweron(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 �� �� ��  : bsp_pmu_hi6561_pa_poweroff
 ��������  :PA �µ�
 �������  : ��

 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
int bsp_pmu_hi6561_pa_poweroff(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 �� �� ��  : PWRCTRL_RfPowerDown
 ��������  :RF �µ�
 �������  : ��

 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/

int bsp_pmu_hi6561_rf_poweroff(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_pmu_hi6561_rf_poweron
 ��������  :RF �µ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
int bsp_pmu_hi6561_rf_poweron(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��     : bsp_pmu_hi6561_get_rf_powerstatus
 ��������  :RF ��Դ״̬��ѯ
 �������  : ��

 �������  :
 				PWC_COMM_STATUS_BUTT :error
 				-1:error

 				0x10:power on
 				0x20:power off
 �� �� ֵ  : pa��Դ����״̬
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pmu_hi6561_get_pa_powerstatus(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 �� �� ��     : bsp_pmu_hi6561_get_rf_powerstatus
 ��������  :RF ��Դ״̬��ѯ
 �������  : ��

 �������  :
 				PWC_COMM_STATUS_BUTT :error

 				0x10:power on
 				0x20:power off
 �� �� ֵ  : rf��Դ����״̬
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pmu_hi6561_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id);

int pmu_hi6561_voltage_list_get(HI6561_POWER_ID power_id,u16 **list, u32 *size);


int adp_pmu_hi6561_initial(HI6561_ID_ENUM chip_id);

void adp_pmu_hi6561_resume(void);


unsigned int pmu_hi6561_reg_save(void);


unsigned int pmu_hi6561_reg_resume(void);

/*****************************************************************************
 �� �� ��  : pmu_hi6561_init
 ��������  : pastar������ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
int pmu_hi6561_init(void);


char *pmu_hi6561_exc_isr(HI6561_ID_ENUM chip_id );

/* ����GU DrvNvInterface.h���� drv_nv_def.h��ͻ���˴�ֱ���ٶ���һ�� */
/* NV ID =18001 start, pa power control, pastar config */
typedef struct{
	BSP_U8 papower_ch0[4];/*����ͨ��0��ӦƵ�ε�PA�Ĺ��絥Ԫ��ֵΪ0��ʾ���򿪵�Դ��Ϊ1��ʾΪpastar���磬Ϊ2��ʾ��ع��磬[0],[1],[2],[3]�ֱ��ӦG U L T*/
	BSP_U8 papower_ch1[4];/*����ͨ��1��ӦƵ�ε�PA�Ĺ��絥Ԫ��ֵΪ0��ʾ���򿪵�Դ��Ϊ1��ʾΪpastar���磬Ϊ2��ʾ��ع��磬[0],[1],[2],[3]�ֱ��ӦG U L T*/
}NV_PA_POWER_UNIT_STRU;
/* NV ID =18001 end */
int bsp_pmu_hi6561_rf_poweron(PWC_COMM_MODEM_E modem_id);
int pmu_hi6561_power_on(HI6561_POWER_ID power_id ,HI6561_ID_ENUM chip_id);
int pmu_hi6561_power_off(HI6561_POWER_ID power_id,HI6561_ID_ENUM chip_id );
int bsp_pmu_fem_poweron(PWC_COMM_MODEM_E modem_id);

#else
void pastar_resume_early(void);
void pastar_suspend_late(void);

#endif
void bsp_pastar_leakage_bugfix(void);
#ifdef __cplusplus
}
#endif
#endif
