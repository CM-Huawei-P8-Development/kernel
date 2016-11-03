/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : adp_pmu_hi6561.c */
/* Version       : 2.0 */
/* Created       : 2013-05-8*/
/* Last Modified : */
/* Description   :  The C union definition file for the module LTE_PMU*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/
/*lint --e{537}*/
#include "string.h"
#include "product_config.h"
#include <osl_spinlock.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include "drv_dpm.h"
#include "drv_pmu.h"
#include "bsp_mipi.h"
#include "bsp_pmu_hi6561.h"
#include <bsp_nvim.h>
//#include <DrvNvInterface.h>
#include "hi6561/pmu_hi6561.h"
#include "gpio_balong.h"
#include "rse_balong.h"

#ifdef CONFIG_PASTAR

/*surport for v9r1 interface*/
//extern char *err_list[];

/*lock for pa pwerctrl */
spinlock_t    pctrl_pa_lock[HI6561_BUTT];
/*lock for rf pwerctrl */
spinlock_t    pctrl_rf_lock[HI6561_BUTT];
/*lock for rf pwerctrl */
spinlock_t    pctrl_fem_lock[HI6561_BUTT];

u32 fem_power_vote = 0;/*0bit��ʾmodem0��1bit��ʾmodem1*/

extern NV_RFPOWER_UNIT_STRU rf_power_unit;
extern NV_PA_POWER_UNIT_STRU pa_power_unit;

/*���߿��ز��µ�����nv*/
extern unsigned int   sw_unpd_en;
extern NV_DRV_FEM_SHARE_POWER fem_share_power;
extern unsigned int              rse_mipi_en;

extern int bsp_antn_sw_unpd_config(ANTN_SW_GROUP_E sw_group ,unsigned int mux);

static HI6561_POWER_ID bsp_adpter_hi6561_powerid(EM_MODEM_CONSUMER_ID consumer_id)
{
    switch(consumer_id)
    {
        case MODEM_PA0:
        case MODEM_PA1:
            return PMU_HI6561_BUCK_PA;
        case MODEM_RFIC0_ANALOG0:
        case MODEM_RFIC1_ANALOG0:
            return PMU_HI6561_BUCK1;
        case MODEM_RFIC0_ANALOG1:
        case MODEM_RFIC1_ANALOG1:
            return PMU_HI6561_BUCK2;
        case MODEM_FEM0:
        case MODEM_FEM1:
            return PMU_HI6561_LDO1;
        case MODEM_PA_VBIAS0:
        case MODEM_PA_VBIAS1:
            return PMU_HI6561_LDO2;
        default:
            return PMU_HI6561_POWER_ID_BUTT;
    }
}

static HI6561_ID_ENUM bsp_adpter_hi6561_chipid(EM_MODEM_CONSUMER_ID consumer_id)
{
    switch(consumer_id)
    {
        case MODEM_PA0:
        case MODEM_RFIC0_ANALOG0:
        case MODEM_RFIC0_ANALOG1:
        case MODEM_FEM0:
        case MODEM_PA_VBIAS0:
            return HI6561_0;

        case MODEM_PA1:
        case MODEM_RFIC1_ANALOG0:
        case MODEM_RFIC1_ANALOG1:
        case MODEM_FEM1:
        case MODEM_PA_VBIAS1:
            return HI6561_1;
        default:
            return HI6561_BUTT;
    }
}


static int pmu_hi6561_config_mode(PWC_COMM_MODE_E mode_id,HI6561_ID_ENUM chip_id)
{
    int ret=MIPI_OK;
    switch(mode_id){
        case PWC_COMM_MODE_LTE :
        case PWC_COMM_MODE_TDS :
        case PWC_COMM_MODE_WCDMA :
            /*����buck pa�ĵ�ѹΪ3.3v*/
            ret|= pmu_hi6561_voltage_set(PMU_HI6561_BUCK_PA,3300,chip_id);

            /*�ر�APT*/
            ret |= pmu_hi6561_apt_disable(chip_id);
            break;
        case PWC_COMM_MODE_GSM:

            /*BU0=3.7v*/
            ret|= pmu_hi6561_voltage_set(PMU_HI6561_BUCK_PA,3700,chip_id);

            /*�ر�APT*/
            ret |= pmu_hi6561_apt_disable(chip_id);
            break;

        default:
            ;

    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : drv_pmu_hi6561_exc_check
 ��������  : ͨ��ģ����PASTAR�Ƿ����쳣�ӿ�
 �������  : modem_id       ����
 �������  : ��
 �� �� ֵ  : BSP_OK          û���쳣
             BSP_ERROR       �����쳣
*****************************************************************************/
s32 drv_pmu_hi6561_exc_check(PWC_COMM_MODEM_E modem_id)
{
    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }

    /* ����PA/RF����PAStar����ʱ����ȥcheck modem1�� */
    if((pa_power_unit.papower_ch1[PWC_COMM_MODE_GSM] != PA_POWER_FROM_HI6561) && 
       (pa_power_unit.papower_ch1[PWC_COMM_MODE_WCDMA] != PA_POWER_FROM_HI6561) && 
       (pa_power_unit.papower_ch1[PWC_COMM_MODE_LTE] != PA_POWER_FROM_HI6561) && 
       (pa_power_unit.papower_ch1[PWC_COMM_MODE_TDS] != PA_POWER_FROM_HI6561) && 
       (rf_power_unit.rfpower_m1 != RF_POWER_FROM_HI6561) && 
       (PWC_COMM_MODEM_1 == modem_id))
    {
        return MIPI_OK;
    }

    if(strcmp("UNKOWN",pmu_hi6561_exc_isr((HI6561_ID_ENUM)modem_id))){
        return (BSP_S32)MIPI_ERROR;/*pmu �����쳣*/
    }

    return (BSP_S32)MIPI_OK;
}

/*****************************************************************************
 �� �� ��  : drv_pmu_hi6561_voltage_set
 ��������  : ͨ��ģ�����õ�ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ���õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : BSP_OK          ���óɹ�
             BSP_ERROR       ����ʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_voltage_set(EM_MODEM_CONSUMER_ID consumer_id, u32 voltage_mv )
{
    HI6561_POWER_ID power_id;
    HI6561_ID_ENUM chip_id;
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];

    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    /*��ȡchip id / power id*/
    /* coverity[assignment] */
    chip_id = bsp_adpter_hi6561_chipid(consumer_id);
    power_id=bsp_adpter_hi6561_powerid(consumer_id);

    /* ������ʹ��PAStar���磬��ֱ�ӷ��� */
    if(RF_POWER_FROM_HI6561 != rfpower_local[chip_id])
    {
        return MIPI_OK;
    }

    /* coverity[overrun-call] */
    return pmu_hi6561_voltage_set(power_id, (u16)voltage_mv,chip_id);
}

/*****************************************************************************
 �� �� ��  : drv_pmu_hi6561_voltage_get
 ��������  : ͨ��ģ���ȡ��ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ��õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : BSP_OK          ��ȡ�ɹ�
             BSP_ERROR       ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_voltage_get(EM_MODEM_CONSUMER_ID consumer_id, u32 *voltage_mv )
{
    HI6561_POWER_ID power_id;
    HI6561_ID_ENUM chip_id;
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];

    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;
    
    /*��ȡchip id / power id*/
    /* coverity[assignment] */
    chip_id = bsp_adpter_hi6561_chipid(consumer_id);
    power_id= bsp_adpter_hi6561_powerid(consumer_id);

    /* ������ʹ��PAStar���磬��ֱ�ӷ��� */
    if(RF_POWER_FROM_HI6561 != rfpower_local[chip_id])
    {
        return MIPI_OK;
    }    
    /* coverity[overrun-call] */
    return pmu_hi6561_voltage_get(power_id,voltage_mv,chip_id);
}

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
s32 drv_pmu_hi6561_voltage_list(EM_MODEM_CONSUMER_ID consumer_id, u16 **list, u32 *size)
{
    HI6561_POWER_ID power_id;
    HI6561_ID_ENUM chip_id;
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];

    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    power_id= bsp_adpter_hi6561_powerid(consumer_id);
    chip_id = bsp_adpter_hi6561_chipid(consumer_id);

    if(HI6561_BUTT == chip_id)
    {
        mipi_print_error("ERROR! bsp_adpter_hi6561_chipid return %d\n",chip_id);
        return MIPI_ERROR;
    }

    /* ������ʹ��PAStar���磬��ֱ�ӷ��� */
    if(RF_POWER_FROM_HI6561 != rfpower_local[chip_id])
    {
        return MIPI_OK;
    }  
    return pmu_hi6561_voltage_list_get(power_id, list, size);
}

/*****************************************************************************
 ����    : drv_pmu_hi6561_apt_enable
 ����    : ͨ��ģ��ʹ��APT״̬�ӿ�
 ����    : modem_id       ����
 ���    : ��
 ����    : 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_apt_enable(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    
    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }

    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    /* ������ʹ��PAStar���磬��ֱ�ӷ��� */
    if(RF_POWER_FROM_HI6561 != rfpower_local[modem_id])
    {
        return MIPI_OK;
    }  
    
    return pmu_hi6561_apt_enable((HI6561_ID_ENUM)modem_id);
}

/*****************************************************************************
 ����    : drv_pmu_hi6561_apt_disable
 ����    : ͨ��ģ��ȥʹ��APT״̬�ӿ�
 ����    : modem_id       ����
 ���    : ��
 ����    : 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_apt_disable(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    
    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }

    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    /* ������ʹ��PAStar���磬��ֱ�ӷ��� */
    if(RF_POWER_FROM_HI6561 != rfpower_local[modem_id])
    {
        return MIPI_OK;
    }  
    
    return pmu_hi6561_apt_disable((HI6561_ID_ENUM)modem_id);
}

/*****************************************************************************
 ����    : drv_pmu_hi6561_apt_status_get
 ����    : ͨ��ģ���ȡ��ǰAPT״̬�ӿ�
 ����    : modem_id       ����
 ���    : ��
 ����    : 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_apt_status_get(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    
    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }

    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    /* ������ʹ��PAStar���磬��ֱ�ӷ��� */
    if(RF_POWER_FROM_HI6561 != rfpower_local[modem_id])
    {
        return MIPI_OK;
    } 
    return pmu_hi6561_apt_status_get((HI6561_ID_ENUM)modem_id);
}

/*****************************************************************************
 ����     : drv_pmu_hi6561_mode_config
 ����    : ͨ��ģ������Gģ��Wģ�ӿ�
 ����    : modem_id       ����
 ���    : ��
 ����  : BSP_OK         ���óɹ�/  BSP_ERROR      ����ʧ��
*****************************************************************************/
s32 drv_pmu_hi6561_mode_config(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)    
{
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    
    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }

    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    /* ������ʹ��PAStar���磬��ֱ�ӷ��� */
    if(RF_POWER_FROM_HI6561 != rfpower_local[modem_id])
    {
        return MIPI_OK;
    } 
    return pmu_hi6561_config_mode(mode_id,(HI6561_ID_ENUM)modem_id);
}

/*****************************************************************************
 ����     : bsp_pmu_hi6561_pa_poweron
 ����    :PA �ϵ�
 ����    : ��

 ���    : ��
 ����    : pa��Դ����״̬
*****************************************************************************/
/*lint -save -e801*/
int bsp_pmu_hi6561_pa_poweron(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    int ret = MIPI_OK;
    HI6561_POWER_ID power_id1;
    HI6561_POWER_ID power_id2;
    unsigned long flags;
    int i = 0;
    u8 papower_local[PWC_COMM_MODEM_BUTT][PWC_COMM_MODE_BUTT - 1];

    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }

    for(i = PWC_COMM_MODE_GSM; i < PWC_COMM_MODE_BUTT - 1; i++)
    {
        papower_local[PWC_COMM_MODEM_0][i] = pa_power_unit.papower_ch0[i];
    }
    for(i = PWC_COMM_MODE_GSM; i < PWC_COMM_MODE_BUTT - 1; i++)
    {
        papower_local[PWC_COMM_MODEM_1][i] = pa_power_unit.papower_ch1[i];
    }
    
    if(PA_POWER_FROM_HI6561 != papower_local[modem_id][mode_id]) 
    {
        return MIPI_OK;
    }

    power_id1=bsp_adpter_hi6561_powerid(MODEM_PA0);
    power_id2=bsp_adpter_hi6561_powerid(MODEM_PA_VBIAS0);


    /*����Դ�Ѵ򿪣��������¿�*/
    if(PWC_COMM_MODEM_ON == bsp_pmu_hi6561_get_pa_powerstatus(modem_id,mode_id)){
        ret = MIPI_OK;
        return ret;
    }

    /*��������*/
    spin_lock_irqsave(&pctrl_pa_lock[modem_id],flags);

    /*��MODEM_PA*/
    ret=pmu_hi6561_power_on(power_id1,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("pmu_hi6561_power_on failed! power id=%d\n",power_id1);
        ret = MIPI_ERROR;
        goto out;
    }

    /*��MODEM_PA_VBIAS*/
    ret=pmu_hi6561_power_on(power_id2,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("pmu_hi6561_power_on failed! power id=%d\n",power_id2);
        ret = MIPI_ERROR;
        goto out;
    }

out:
    spin_unlock_irqrestore(&pctrl_pa_lock[modem_id],flags);
    return ret;
}

/*****************************************************************************
 ����     : bsp_pmu_hi6561_pa_poweron
 ����    : PA �ϵ�
 ����    : ��

 ���    : ��
 ����    : pa��Դ����״̬
*****************************************************************************/
int bsp_pmu_hi6561_pa_poweroff(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    int ret = 0;
    HI6561_POWER_ID power_id1;
    HI6561_POWER_ID power_id2;
    unsigned long flags;
    int i = 0;
    u8 papower_local[PWC_COMM_MODEM_BUTT][PWC_COMM_MODE_BUTT - 1];
    
    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }

    for(i = PWC_COMM_MODE_GSM; i < PWC_COMM_MODE_BUTT - 1; i++)
    {
        papower_local[PWC_COMM_MODEM_0][i] = pa_power_unit.papower_ch0[i];
    }
    for(i = PWC_COMM_MODE_GSM; i < PWC_COMM_MODE_BUTT - 1; i++)
    {
        papower_local[PWC_COMM_MODEM_1][i] = pa_power_unit.papower_ch1[i];
    }
    
    if(PA_POWER_FROM_HI6561 != papower_local[modem_id][mode_id]) 
    {
        return MIPI_OK;
    }

    /*��ԴIDת��*/
    power_id1=bsp_adpter_hi6561_powerid(MODEM_PA0);
    power_id2=bsp_adpter_hi6561_powerid(MODEM_PA_VBIAS0);


    /*����Դ�ѹرգ������ظ��ر�*/
    if(PWC_COMM_MODEM_OFF == bsp_pmu_hi6561_get_pa_powerstatus(modem_id,mode_id)){
        ret = MIPI_OK;
        return ret;
    }

    /*��������*/
    spin_lock_irqsave(&pctrl_pa_lock[modem_id],flags);

    ret=pmu_hi6561_power_off(power_id1,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("pmu_hi6561_power_off failed! power id=%d\n",power_id1);
        ret = MIPI_ERROR;
        goto out;
    }

    ret=pmu_hi6561_power_off(power_id2,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("pmu_hi6561_power_off failed! power id=%d\n",power_id2);
        ret = MIPI_ERROR;
        goto out;
    }

out:
    spin_unlock_irqrestore(&pctrl_pa_lock[modem_id],flags);
    return ret;

}
static PWC_COMM_STATUS_E pmu_hi6561_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id)
{

    int ret = 0;
    HI6561_POWER_ID power_id1 = PMU_HI6561_POWER_ID_BUTT;
    HI6561_POWER_ID power_id2 = PMU_HI6561_POWER_ID_BUTT;
    PWC_COMM_STATUS_E result = PWC_COMM_STATUS_BUTT;
    u8 status1 = 0;
    u8 status2 = 0;

    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return PWC_COMM_STATUS_BUTT;
    }

    power_id1=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG0);
    power_id2=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG1);

    /*��������*/
    
    ret=pmu_hi6561_power_status(power_id1,&status1,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("get rf power status failed!power id is %d\n",power_id1);
        result = PWC_COMM_STATUS_BUTT;
        goto out;
    }

    ret=pmu_hi6561_power_status(power_id2,&status2,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("get rf power status failed!power id is %d\n",power_id2);
        result = PWC_COMM_STATUS_BUTT;
        goto out;
    }

    if(status1&&status2){
        result = PWC_COMM_MODEM_ON;
    }
    else if(0 == (status1 | status2)){
        result = PWC_COMM_MODEM_OFF;
    }
    else{
        result = PWC_COMM_STATUS_BUTT;
    }
    
out:
    return result;
}
static PWC_COMM_STATUS_E pmu_hi6561_get_fem_powerstatus(PWC_COMM_MODEM_E modem_id)
{

    int ret                  = 0;
    HI6561_POWER_ID power_id = PMU_HI6561_POWER_ID_BUTT;
    PWC_COMM_STATUS_E result = PWC_COMM_STATUS_BUTT;
    u8 status                = 0;

    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return PWC_COMM_STATUS_BUTT;
    }

    power_id = bsp_adpter_hi6561_powerid(MODEM_FEM0);

    /*���������߹���Դ����*/
    if(fem_share_power.en_flag && (PWC_COMM_MODEM_1 == modem_id)){
        modem_id = PWC_COMM_MODEM_0;
    }

    ret=pmu_hi6561_power_status(power_id,&status,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("get rf power status failed!power id is %d\n",power_id);
        result = PWC_COMM_STATUS_BUTT;
        goto out;
    }

    if(status){
        result = PWC_COMM_MODEM_ON;
    }
    
out:

    return result;
}

static PWC_COMM_STATUS_E pmu_ldo_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id)
{
    /*todo:��ȡGPIO�ӿ�*/
    int status1 = gpio_power_get_status(GPIO_POWER_FEM);
    int status2 = gpio_power_get_status(GPIO_POWER_RF);

    if(1==status1 && 1==status2){
        return PWC_COMM_MODEM_ON;
    }
    else if(0==status1 && 0==status2){
        return PWC_COMM_MODEM_OFF;
    }

    return PWC_COMM_STATUS_BUTT;
}
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
PWC_COMM_STATUS_E bsp_pmu_hi6561_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id)
{
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    PWC_COMM_STATUS_E rf_status  = PWC_COMM_STATUS_BUTT;
    PWC_COMM_STATUS_E fem_status = PWC_COMM_STATUS_BUTT;
    PWC_COMM_STATUS_E ret        = PWC_COMM_STATUS_BUTT;
    unsigned long flags;

    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    spin_lock_irqsave(&pctrl_rf_lock[modem_id],flags);
    if(RF_POWER_FROM_HI6561 == rfpower_local[modem_id]){/*��Ҫpastar����*/
        rf_status  = pmu_hi6561_get_rf_powerstatus(modem_id);
        fem_status = pmu_hi6561_get_fem_powerstatus(modem_id);

        if((PWC_COMM_MODEM_ON == rf_status) && (PWC_COMM_MODEM_ON == fem_status)){
            ret = PWC_COMM_MODEM_ON;
        }
        else if((PWC_COMM_MODEM_OFF == rf_status) && (PWC_COMM_MODEM_OFF == fem_status)){
            ret = PWC_COMM_MODEM_OFF;
        }
        else{            
            ret = PWC_COMM_STATUS_BUTT;
        }
    }
    else if(RF_POWER_FROM_LDO == rfpower_local[modem_id]){/*��Ҫldo����*/
        ret = pmu_ldo_get_rf_powerstatus(modem_id);
    }
    else{/*����Ҫpastar��LDO����*/
        mipi_print_error("modem [%d] hasn't use pastar ,please check nv!\n",modem_id);
        ret = PWC_COMM_STATUS_BUTT;
    }


    spin_unlock_irqrestore(&pctrl_rf_lock[modem_id],flags);

    return ret;
}
static int pmu_hi6561_rf_poweron(PWC_COMM_MODEM_E modem_id)
{
    int ret = MIPI_OK;
    HI6561_POWER_ID power_id1;
    HI6561_POWER_ID power_id2;

    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }
    power_id1=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG0);
    power_id2=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG1);

    /*����Դ�Ѵ򿪣��������¿�*/
    if(PWC_COMM_MODEM_ON == pmu_hi6561_get_rf_powerstatus(modem_id)){
        return MIPI_OK;
    }

    /*�ϵ������Ҫ�����������м��йرյ�Դ����*/

    /* ���buck1/2���󱨹��� */
    ret = pmu_hi6561_buck1_2_phony_exception_clear((HI6561_ID_ENUM)modem_id);
    if(MIPI_OK != ret)
    {
        mipi_print_error("Error:clear buck1/2 phony over current status failed! modem id:%d\n", modem_id);
    }
    
    /*��MODEM_RFIC_ANALOG0*/
    ret=pmu_hi6561_power_on(power_id1,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("pmu_hi6561_power_on failed!power id is %d\n",power_id1);
        goto out;
    }

    /*��MODEM_RFIC_ANALOG1*/
    ret=pmu_hi6561_power_on(power_id2,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("pmu_hi6561_power_on failed!power id is %d\n",power_id2);
        goto out;
    }
    
out:

    return ret;

}
static int pmu_hi6561_fem_poweron(PWC_COMM_MODEM_E modem_id)
{
    int ret = MIPI_OK;
    HI6561_POWER_ID power_id;

    if(PWC_COMM_MODEM_BUTT <= modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }
    
    power_id = bsp_adpter_hi6561_powerid(MODEM_FEM0);

    /*����Դ�Ѵ򿪣��������¿�*/
    if(PWC_COMM_MODEM_ON == pmu_hi6561_get_fem_powerstatus(modem_id)){
        ret = MIPI_OK;
    }

    /*�ϵ������Ҫ�����������м��йرյ�Դ����*/
    
    /*��FEM*/
    ret=pmu_hi6561_power_on(power_id,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("pmu_hi6561_power_on failed!power id is %d\n",power_id);
        ret = MIPI_ERROR;
    }

        

    return ret;

}

static int pmu_ldo_rf_poweron(PWC_COMM_MODEM_E modem_id)
{

    if(PWC_COMM_MODEM_1 == modem_id){

        /*����GPIO ����*/
        gpio_power_set_high(GPIO_POWER_RF);
        

        return MIPI_OK;
    }
    else{
        mipi_print_error("ldo power didn't supplied to modem[%d],please check nv congfig or hardware!\n",modem_id);
        return MIPI_ERROR;
    }
}
static int pmu_ldo_fem_poweron(PWC_COMM_MODEM_E modem_id)
{

    if(PWC_COMM_MODEM_1 == modem_id){
        /*����GPIO 123\124����*/
        gpio_power_set_high(GPIO_POWER_FEM);
        

        return MIPI_OK;
    }
    else{
        mipi_print_error("ldo power didn't supplied to modem[%d],please check nv congfig or hardware!\n",modem_id);
        return MIPI_ERROR;
    }
}
int bsp_pmu_rfic_poweron(PWC_COMM_MODEM_E modem_id)
{
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    int ret = MIPI_OK;
    unsigned long flags;

    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;
    spin_lock_irqsave(&pctrl_rf_lock[modem_id],flags);
    if(RF_POWER_FROM_HI6561 == rfpower_local[modem_id]){/*��Ҫpastar����*/
        ret =  pmu_hi6561_rf_poweron(modem_id);
    }
    else if(RF_POWER_FROM_LDO == rfpower_local[modem_id]){/*��Ҫldo����*/
        ret = pmu_ldo_rf_poweron(modem_id);
    }
    else{/*����Ҫpastar��LDO����*/
        mipi_print_error("modem [%d] hasn't use pastar ,please check nv!\n",modem_id);
        ret = MIPI_ERROR;
    }
    spin_unlock_irqrestore(&pctrl_rf_lock[modem_id],flags);
    return ret;
}
int bsp_pmu_fem_poweron(PWC_COMM_MODEM_E modem_id)
{
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    int ret = MIPI_OK;
    unsigned long flags;
    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;
    spin_lock_irqsave(&pctrl_fem_lock[modem_id],flags);

    /*���������߹���Դ����*/    
    if(fem_share_power.en_flag ){
        
        fem_power_vote |= 1 << modem_id;

        if(PWC_COMM_MODEM_1 == modem_id){
        ret |= pmu_hi6561_fem_poweron(PWC_COMM_MODEM_0);/*[false alarm]*/
        }
    }
    
    if(RF_POWER_FROM_HI6561 == rfpower_local[modem_id]){/*��Ҫpastar����*/
        ret |=    pmu_hi6561_fem_poweron(modem_id);
    }
    else if(RF_POWER_FROM_LDO == rfpower_local[modem_id]){/*��Ҫldo����*/
        ret |= pmu_ldo_fem_poweron(modem_id);
    }
    else{/*����Ҫpastar��LDO����*/
        mipi_print_error("modem [%d] hasn't use pastar ,please check nv!\n",modem_id);
        ret = MIPI_ERROR;
    }

    /*�����߹ܽ��л�Ϊ���ܹܽ�*/    
    if(sw_unpd_en){
        if(PWC_COMM_MODEM_0 == modem_id){
            /*�����ּ����߿�������Ϊantn ����*/
            ret = bsp_antn_sw_unpd_config(MASTER_0 , 1);
            if(ret){
                mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 0,mux 0\n");
            }
            
            ret = bsp_antn_sw_unpd_config(MASTER_1 , 1);        
            if(ret){
                mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 1,mux 0\n");
            }
        }
        /*����modem���߿�������Ϊantn ����*/
        else if(PWC_COMM_MODEM_1 == modem_id){
            ret = bsp_antn_sw_unpd_config(NAGTIVE , 1);
            if(ret)
                mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 0,mux 0\n");
        }
    }
    spin_unlock_irqrestore(&pctrl_fem_lock[modem_id],flags);
    return ret;
    }
int bsp_pmu_hi6561_rf_poweron(PWC_COMM_MODEM_E modem_id)
{
    int  ret = MIPI_ERROR;
    ret  = bsp_pmu_rfic_poweron(modem_id);
    ret |= bsp_pmu_fem_poweron(modem_id);

    return ret;

}
static int pmu_ldo_rf_poweroff(PWC_COMM_MODEM_E modem_id)
{
    if(PWC_COMM_MODEM_1 == modem_id){

        /*����GPIO����*/
        gpio_power_set_low(GPIO_POWER_RF);
        
        return MIPI_OK;
    }
    else{
        mipi_print_error("ldo power didn't supplied to modem[%d],please check nv congfig or hardware!\n",modem_id);
        return MIPI_ERROR;
    }
}
static int pmu_ldo_fem_poweroff(PWC_COMM_MODEM_E modem_id)
{

    if(PWC_COMM_MODEM_1 == modem_id){
        
        if((!rse_mipi_en) && (!sw_unpd_en)){
            /*����GPIO����*/
            gpio_power_set_low(GPIO_POWER_FEM);
        }
        return MIPI_OK;
    }
    else{
        mipi_print_error("ldo power didn't supplied to modem[%d],please check nv congfig or hardware!\n",modem_id);
        return MIPI_ERROR;
    }
}
static int pmu_hi6561_rf_poweroff(PWC_COMM_MODEM_E modem_id)
{
    int ret = MIPI_OK;
    HI6561_POWER_ID power_id1;
    HI6561_POWER_ID power_id2;

    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }

    power_id1=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG0);
    power_id2=bsp_adpter_hi6561_powerid(MODEM_RFIC0_ANALOG1);

    /*����Դ�ѹرգ��������¿�*/
    if(PWC_COMM_MODEM_OFF == pmu_hi6561_get_rf_powerstatus(modem_id)){
        return MIPI_OK;
    }

    /*��������*/

    /*�ر�RFIC_ANALOG0*/
    ret=pmu_hi6561_power_off(power_id1,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("pmu_hi6561_power_off failed!power id is %d\n",power_id1);
        ret = MIPI_ERROR;
        goto out;
    }

    /*�ر�RFIC_ANALOG1*/
    ret=pmu_hi6561_power_off(power_id2,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("pmu_hi6561_power_off failed!power id is %d\n",power_id2);
        ret = MIPI_ERROR;
        goto out;
    }

    /* ���buck1/2�Ĺ������ */
    ret = pmu_hi6561_buck1_2_real_exception_clear((HI6561_ID_ENUM)modem_id);
    if(MIPI_OK != ret)
    {
        mipi_print_error("Error:clear buck1/2 real over current status failed! modem id:%d\n", modem_id);
    }

out:
    return ret;
}
static int pmu_hi6561_fem_poweroff(PWC_COMM_MODEM_E modem_id)
{
    int ret = MIPI_OK;
    HI6561_POWER_ID power_id;

    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return MIPI_ERROR;
    }

    if(rse_mipi_en||sw_unpd_en){
        goto out;
    }
    power_id = bsp_adpter_hi6561_powerid(MODEM_FEM0);

    /*����Դ�ѹرգ������عر�*/
    if(PWC_COMM_MODEM_OFF == pmu_hi6561_get_fem_powerstatus(modem_id)){
        return MIPI_OK;
    }


    if (fem_share_power.en_flag){

        /*����Դ���ԣ�����FEM���������õ�Դ*/    
        if(!fem_power_vote){
            ret = pmu_hi6561_power_off(power_id,HI6561_0);
        }        
    }    
    else{
        /*û���κ����ԣ����������ر�FEM*/
        ret = pmu_hi6561_power_off(power_id,(HI6561_ID_ENUM)modem_id);
        if(ret){
            mipi_print_error("pmu_hi6561_power_off failed!power id is %d\n",power_id);
            ret = MIPI_ERROR;
            goto out;
        }
    }

out:
    return ret;
}
int bsp_pmu_rfic_poweroff(PWC_COMM_MODEM_E modem_id)
{
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    int ret = MIPI_ERROR;
    unsigned long flags;

    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;

    /*���������߹���Դ����*/
    spin_lock_irqsave(&pctrl_rf_lock[modem_id],flags);

    if(RF_POWER_FROM_HI6561 == rfpower_local[modem_id]){/*��Ҫpastar����*/
        ret  = pmu_hi6561_rf_poweroff(modem_id);
    }
    else if(RF_POWER_FROM_LDO == rfpower_local[modem_id]){/*��Ҫldo����*/
        ret  = pmu_ldo_rf_poweroff(modem_id);

    }
    else{/*����Ҫpastar��LDO����*/
        mipi_print_error("modem [%d] hasn't use pastar ,please check nv!\n",modem_id);
        ret = MIPI_ERROR;
    }
    spin_unlock_irqrestore(&pctrl_rf_lock[modem_id],flags);
    return ret;
}
int bsp_pmu_fem_poweroff(PWC_COMM_MODEM_E modem_id)
{
    u32 rfpower_local[PWC_COMM_MODEM_BUTT];
    int ret = MIPI_OK;
    unsigned long flags;
    rfpower_local[PWC_COMM_MODEM_0]=rf_power_unit.rfpower_m0;
    rfpower_local[PWC_COMM_MODEM_1]=rf_power_unit.rfpower_m1;
    spin_lock_irqsave(&pctrl_fem_lock[modem_id],flags);
    if(fem_share_power.en_flag ){
        fem_power_vote &= ~(unsigned int)(1 << modem_id);
        if(PWC_COMM_MODEM_1 == modem_id){
            ret = pmu_hi6561_fem_poweroff(PWC_COMM_MODEM_0);/*[false alarm]*/
        }
    }

    if(rse_mipi_en){
        ret = bsp_rse_mipi_base_config(modem_id);
        if(ret){
            mipi_print_error("rse mipi config fail!modem id %d\n",modem_id);
        }
    }
        
    if(sw_unpd_en){
        if (PWC_COMM_MODEM_0 == modem_id){
            /*rse gpio �������ԣ������ּ����߿�������ΪGPIOĬ��̬*/
            ret = bsp_antn_sw_unpd_config(MASTER_0 , 0);
            if(ret){
                mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 0,mux 0\n");
            }
            
            ret = bsp_antn_sw_unpd_config(MASTER_1 , 0);        
            if(ret){
                mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 1,mux 0\n");
            }

        }
        /*����modem���߿�������ΪGPIOĬ��̬*/
        else if(PWC_COMM_MODEM_1 == modem_id){/*ö��*/
            ret = bsp_antn_sw_unpd_config(NAGTIVE , 0);
            if(ret)
            mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 0,mux 0\n");
        }
    }
    if(RF_POWER_FROM_HI6561 == rfpower_local[modem_id]){/*��Ҫpastar����*/
        ret |= pmu_hi6561_fem_poweroff(modem_id);
    }
    else if(RF_POWER_FROM_LDO == rfpower_local[modem_id]){/*��Ҫldo����*/
        ret |= pmu_ldo_fem_poweroff(modem_id);
    }
    else{/*����Ҫpastar��LDO����*/
        mipi_print_error("modem [%d] hasn't use pastar ,please check nv!\n",modem_id);
        ret = MIPI_ERROR;
    }
    spin_unlock_irqrestore(&pctrl_fem_lock[modem_id],flags);
    return ret;
}
int bsp_pmu_hi6561_rf_poweroff(PWC_COMM_MODEM_E modem_id)
{
    int  ret = 0;
    ret  = bsp_pmu_rfic_poweroff(modem_id);
    ret |= bsp_pmu_fem_poweroff(modem_id);
    return ret;
}

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
PWC_COMM_STATUS_E bsp_pmu_hi6561_get_pa_powerstatus(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    int ret = 0;
    unsigned long flags;
    PWC_COMM_STATUS_E result=PWC_COMM_STATUS_BUTT;
    HI6561_POWER_ID power_id1 = PMU_HI6561_POWER_ID_BUTT;
    HI6561_POWER_ID power_id2 = PMU_HI6561_POWER_ID_BUTT;
    int i = 0;
    u8 papower_local[PWC_COMM_MODEM_BUTT][PWC_COMM_MODE_BUTT - 1];
    u8 status1 = 0;
    u8 status2 = 0;

    if(PWC_COMM_MODEM_BUTT<=modem_id){
        mipi_print_error("invalid param with modem id %d\n",modem_id);
        return PWC_COMM_STATUS_BUTT;
    }

    for(i = PWC_COMM_MODE_GSM; i < PWC_COMM_MODE_BUTT - 1; i++)
    {
        papower_local[PWC_COMM_MODEM_0][i] = pa_power_unit.papower_ch0[i];
    }
    for(i = PWC_COMM_MODE_GSM; i < PWC_COMM_MODE_BUTT - 1; i++)
    {
        papower_local[PWC_COMM_MODEM_1][i] = pa_power_unit.papower_ch1[i];
    }

    if(PA_POWER_FROM_HI6561 != papower_local[modem_id][mode_id]) 
    {
        return PWC_COMM_STATUS_BUTT;
    }
    power_id1=bsp_adpter_hi6561_powerid(MODEM_PA0);
    power_id2=bsp_adpter_hi6561_powerid(MODEM_PA_VBIAS0);
    
    /*��������*/
    spin_lock_irqsave(&pctrl_pa_lock[modem_id],flags);

    ret=pmu_hi6561_power_status(power_id1,&status1,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("get pa power status failed!power id is %d\n",power_id1);
        result = PWC_COMM_STATUS_BUTT;
        goto out;
    }

    ret=pmu_hi6561_power_status(power_id2,&status2,(HI6561_ID_ENUM)modem_id);
    if(ret){
        mipi_print_error("get pa power status failed!power id is %d\n",power_id2);
        result = PWC_COMM_STATUS_BUTT;
        goto out;
    }

    if(status1&&status2){
        result = PWC_COMM_MODEM_ON;
    }
    else if(0 == (status1 | status2)){
        result = PWC_COMM_MODEM_OFF;
    }
    else{
        result = PWC_COMM_STATUS_BUTT;
    }

out :
    spin_unlock_irqrestore(&pctrl_pa_lock[modem_id],flags);
    return result;
}
/*lint -restore +e801*/

int adp_pmu_hi6561_initial(HI6561_ID_ENUM chip_id)
{
    /*init lock*/
    spin_lock_init(&pctrl_pa_lock[chip_id]);

    spin_lock_init(&pctrl_rf_lock[chip_id]);

    spin_lock_init(&pctrl_fem_lock[chip_id]);

    /*for k3V3��Ƭ���򿪸���RF ��Դ*/
    //pmu_ldo_rf_poweron(PWC_COMM_MODEM_1);
    return 0;
}

void adp_pmu_hi6561_resume(void)
{
    int ret = 0;
    fem_power_vote = 0;
    
    if(sw_unpd_en || rse_mipi_en){
        ret =  bsp_pmu_fem_poweron(PWC_COMM_MODEM_0);
        ret |= bsp_pmu_fem_poweron(PWC_COMM_MODEM_1);
        if(ret){
            mipi_print_error("bsp_pmu_fem_poweron fail, ret:%d\n", ret);
        }
        if(rse_mipi_en){
            ret =  bsp_rse_mipi_base_config(PWC_COMM_MODEM_0);
            ret |= bsp_rse_mipi_base_config(PWC_COMM_MODEM_1);
            if(ret){
                mipi_print_error("rse mipi config fail, ret:%d\n", ret);
            }
        }
        if(sw_unpd_en){
            ret = bsp_antn_sw_unpd_config(MASTER_0 , 0);
            ret|= bsp_antn_sw_unpd_config(MASTER_1 , 0);
            ret|= bsp_antn_sw_unpd_config(NAGTIVE , 0);
            if(ret){
                mipi_print_error("bsp_antn_sw_unpd_config fail!gproup 0,mux 0\n");
            }
        }
    }
}
#else


int pmu_hi6561_init_config(void)
{
    return 0;
}
int adp_pmu_hi6561_initial(HI6561_ID_ENUM chip_id)
{
    mipi_print_error("pmu hi6561 didn't build all function!\n");
    return 0;
}

unsigned int pmu_hi6561_reg_save(void)
{
    return 0;
}


unsigned int pmu_hi6561_reg_resume(void)
{
    return 0;
}

void adp_pmu_hi6561_resume(void)
{
    return ;
}
#endif

int pmu_hi6561_init(void)
{
    return 0;
}


