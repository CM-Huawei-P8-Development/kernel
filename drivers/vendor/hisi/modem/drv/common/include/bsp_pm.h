/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : pm.c */
/* Version       : 2.0 */
/* Created       : 2013-09-22*/
/* Last Modified : */
/* Description   :  pm drv*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/
#ifndef __BSP_PM_H__
#define __BSP_PM_H__

#include <osl_types.h>
#include <drv_pm.h>
#include <bsp_memmap.h>
/*
��̬���û���Դ
���� int_id  ��Ӧ m3 �ϵ��жϺ�
*/
#define GIC_CPU_BASE                    (HI_MDM_GIC_BASE_ADDR_VIRT+0x100)

#ifdef CONFIG_CCORE_BALONG_PM
void pm_enable_wake_src(enum pm_wake_src wake_src);
void pm_disable_wake_src(enum pm_wake_src wake_src);
u32 pm_in_waiting_pd(void);

#else
static inline void pm_enable_wake_src(enum pm_wake_src wake_src){}
static inline void pm_disable_wake_src(enum pm_wake_src wake_src){}
static inline u32 pm_in_waiting_pd(void){return 0;}
#endif

enum PM_LOG_TYPE{
	PM_LOG_NORMAL_RECORD,
	PM_LOG_IDLE_RECORD,
	PM_LOG_SET_WAKE_SRC_RECORD,
};


#endif/*__BSP_PM_H__*/
