/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       :   comm_nv_def.h
  Description     :   gutl��ģ����nv�ṹ�嶨��
  History         :
******************************************************************************/

#ifndef __COMM_NV_DEF_H__
#define __COMM_NV_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define NV_WLCOUNTRY_CODE_LEN     (5)
#define NV_WLMODE_LEN             (5)
#define NV_WLSSID_LEN             (33)
#define NV_FACTORY_INFO_I_SIZE    (78)
/* �汾��Ϣÿ������󳤶� */
#define VER_MAX_LENGTH            (30)

#define KPD_NV_UNIT               (16)  /* total 16 * 32Bit = 64bytes */
#define KPD_EVENT_MAX             (KPD_NV_UNIT-3)


/*NV ID = 50018*/
#pragma pack(1)
typedef struct
{
    BSP_S32        nvStatus;
    BSP_S8         nv_version_info[30];
}NV_SW_VER_STRU;
#pragma pack(4)

/*END NV ID = 50018*/

/*Resume_Flag   ID = 4*/
typedef struct
{
    BSP_U16                              Resume_Flag;    /*[0, 1]*/
}RESUME_FLAG_STRU;


/*LED_Control   ID = 7*/

typedef struct
{
	BSP_U8  Color;
	BSP_U8  Time;
}LED_STRU;

typedef struct
{
    LED_STRU                                     stLED[10];
}LED_CONTROL_STRU;
typedef struct
{
    LED_CONTROL_STRU                             stLED_Control[32];
}LED_CONTROL_STRU_ARRAY;





/*UE_Point_Ctrl   ID = 15*//*δʹ��*/
/*****************************************************************************
 �ṹ��    : UE_POINT_CTRL_STRU
 �ṹ˵��  : UE_POINT_CTRL�ṹ ID=15
*****************************************************************************/
typedef struct
{
    BSP_U32     Status;
    BSP_U32     ProductForm;
    BSP_U16     Pid;
    BSP_U16     FakePid;
    BSP_U8      Mac[8];
}UE_POINT_CTRL_STRU;

/*ExceptionRecord ������������   ID = 17*/
/*****************************************************************************
 �ṹ��    : EXCEPTION_RECORD_STRU
 �ṹ˵��  : EXCEPTION_RECORD�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32     IsEnable;
    BSP_U32     Config;
    BSP_U32     Reserve;
}EXCEPTION_RECORD_STRU;
/*sysPrtTask   ID = 20*/
/*�������ͣ�32bit unsigned������Ϊ4byte*/
/*****************************************************************************
 �ṹ��    : NV_SYS_PRT_STRU
 �ṹ˵��  : NV_SYS_PRT�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32    uintValue;
}NV_SYS_PRT_STRU;


/*usbEnumStatus ID = 21*/
/*****************************************************************************
 �ṹ��    : USB_ENUM_STATUS_STRU
 �ṹ˵��  : USB_ENUM_STATUS�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32    status;
    BSP_U32    value;
    BSP_U32    reserve1;
    BSP_U32    reserve2;
}USB_ENUM_STATUS_STRU;


/*���õ����ϵ��WatchDog����¼?ID =22*/
/*****************************************************************************
 �ṹ��    : LIVE_TIME_CONTROL_STRU
 �ṹ˵��  : LIVE_TIME_CONTROL�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32    ulEnable;
    BSP_U32    ulCycle;
} LIVE_TIME_CONTROL_STRU;



/*LiveTime   ID = 23*/
/*****************************************************************************
 �ṹ��    : LIVE_TIME_STRU
 �ṹ˵��  : LIVE_TIME�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32    ulLiveTime;
}LIVE_TIME_STRU;


/*NV_CUSTOMIZE_REWIND_DELAY_TIME_I   ID = 25*/ /*δʹ��*/
/*****************************************************************************
 �ṹ��    : NV_CUSTOMIZE_REWIND_DELAY_TIME_I_STRU
 �ṹ˵��  : NV_CUSTOMIZE_REWIND_DELAY_TIME_I�ṹ ID=25
*****************************************************************************/
typedef struct
{
    BSP_U32     Status;    /*Range:[0,1]*/
    BSP_U16     Timeout;
}NV_CUSTOMIZE_REWIND_DELAY_TIME_I_STRU;


/*����UE�ϱ��̶�SN��*/   /*ID = 26 ���� 16*/
/*****************************************************************************
 �ṹ��    : USB_SN_NV_INFO_STRU
 �ṹ˵��  : USB_SN_NV_INFO�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32    usbSnNvStatus;
    BSP_U32    usbSnNvSucFlag;
    BSP_U32    usbSnReserved1;
    /*BSP_U32    usbSnReserved2;*/
}USB_SN_NV_INFO_STRU;




/*Ӳ���汾�š�ID = 30 ���� 12*/
/*****************************************************************************
 �ṹ��    : NVHWVER
 �ṹ˵��  : NVHWVER�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32    NV_HW_VER_Flag;
    BSP_U8     NV_HW_VER_VAL[8];
} NVHWVER;


/*PID�Ż��������� ID = 31 ���� 4*/
/*****************************************************************************
 �ṹ��    : nv_pid_enable_type
 �ṹ˵��  : nv_pid_enable_type�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32    pid_enabled;
}nv_pid_enable_type;


/*NV_AT_SHELL_OPEN_FLAG   ID = 33*/
/*****************************************************************************
 �ṹ��    : NV_AT_SHELL_OPEN_FLAG_STRU
 �ṹ˵��  : NV_AT_SHELL_OPEN_FLAG�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32    NV_AT_SHELL_OPEN_FLAG;
}NV_AT_SHELL_OPEN_FLAG_STRU;


/*���ڵ�ص��¶Ȳ�ѯ���¶�����Ϊ1��Ϊ��׼��Ԫ ID = 35*/

/*****************************************************************************
 �ṹ��    : TEMP_ADC_STRU
 �ṹ˵��  : TEMP_ADC�ṹ
*****************************************************************************/
typedef struct
{
    BSP_S16    sTemp;
    BSP_U16    usADC;
}TEMP_ADC_STRU;

/*****************************************************************************
 �ṹ��    : TEMP_ADC_STRU_ARRAY
 �ṹ˵��  : TEMP_ADC_STRU_ARRAY�ṹ
*****************************************************************************/
typedef struct
{
    TEMP_ADC_STRU    stTempAdc[28];
}TEMP_ADC_STRU_ARRAY;


/*DRV_CUSTOMIZE_TYPE   ID = 41 ����*/
/*****************************************************************************
 �ṹ��    : nv_drv_customize_type
 �ṹ˵��  : nv_drv_customize_type�ṹ
*****************************************************************************/
typedef struct DRV_CUSTOMIZE_TYPE
{
    BSP_U32 drv_customize_type;
} nv_drv_customize_type;

/*NV_OLED_TEMP_ADC   ID = 49*/
/*****************************************************************************
 �ṹ��    : NV_OLED_TEMP_ADC_STRU
 �ṹ˵��  : NV_OLED_TEMP_ADC�ṹ
*****************************************************************************/
typedef struct
{
    BSP_S16       sTemp;
    BSP_S16       sADC;
}NV_OLED_TEMP_ADC_STRU;

/*****************************************************************************
 �ṹ��    : NV_OLED_TEMP_ADC_STRU_ARRAY
 �ṹ˵��  : NV_OLED_TEMP_ADC_STRU_ARRAY�ṹ  ID=49
*****************************************************************************/
typedef struct
{
    NV_OLED_TEMP_ADC_STRU          stNV_OLED_TEMP_ADC[28];
}NV_OLED_TEMP_ADC_STRU_ARRAY;

/*NV_ITEM_MODIFY_LINKINFO_FLAG   ID = 50*/
/*****************************************************************************
 �ṹ��    : NV_ITEM_MODIFY_LINKINFO_FLAG_STRU
 �ṹ˵��  : NV_ITEM_MODIFY_LINKINFO_FLAG�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U16    NV_ITEM_MODIFY_LINKINFO_FLAG;  /*Range:[0,1]*/
}NV_ITEM_MODIFY_LINKINFO_FLAG_STRU;

/*NV_WEBNAS_SD_WORKMODE   ID = 51*/
/*****************************************************************************
 �ṹ��    : NV_WEBNAS_SD_WORKMODE_STRU
 �ṹ˵��  : NV_WEBNAS_SD_WORKMODE�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32 ulSDWorkMode;
}NV_WEBNAS_SD_WORKMODE_STRU;

/*HW_WDT_FLAG   ID = 52*/
/*****************************************************************************
 �ṹ��    : HW_WDT_FLAG_STRU
 �ṹ˵��  : HW_WDT_FLAG�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32   HW_WDT_FLAG;
}HW_WDT_FLAG_STRU;

/*POWER_LED_ENABLE   ID = 54*/
/*****************************************************************************
 �ṹ��    : POWER_LED_ENABLE_STRU
 �ṹ˵��  : POWER_LED_ENABLE�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32   POWER_LED_ENABLE;
}POWER_LED_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : NV_HW_CONFIG_STRU
 �ṹ˵��  : NV_HW_CONFIG�ṹ ID = 55
*****************************************************************************/
/* PMUÿһ·����,8Byte */
typedef struct
{
	BSP_U8 PowerEn;
	BSP_U8 ModuleID;
	BSP_U8 DevID;
	BSP_U8 PowerID;
	BSP_U8 ConsumerID;
	BSP_U8 Reserve;
	BSP_U16 Voltage;
}PMU_POWER_CFG;

/* PMU����,16· */
typedef struct
{
	PMU_POWER_CFG RF0_PA;
	PMU_POWER_CFG RFIC0_TX;
	PMU_POWER_CFG RFIC0_RX;
	PMU_POWER_CFG FEM0;
	PMU_POWER_CFG RF0_VBIAS;

	PMU_POWER_CFG RF1_PA;
	PMU_POWER_CFG RFIC1_TX;
	PMU_POWER_CFG RFIC1_RX;
	PMU_POWER_CFG FEM1;
	PMU_POWER_CFG RF1_VBIAS;

	PMU_POWER_CFG PMU_RESERVE0;
	PMU_POWER_CFG PMU_RESERVE1;
	PMU_POWER_CFG PMU_RESERVE2;
	PMU_POWER_CFG PMU_RESERVE3;
	PMU_POWER_CFG PMU_RESERVE4;
	PMU_POWER_CFG PMU_RESERVE5;
}PMU_CFG_STRU;

/*���ȱ�������*/
typedef struct
{
	BSP_U8 OTMP_TMP;          /*���ȱ����¶�����*/
	BSP_U8 OTMP_PWR_DOWN;     /*���Ⱥ󣬷Ǻ��ĵ�Դ�Ƿ��µ�*/
	BSP_U8 OTMP_RESET;        /*���Ⱥ��Ƿ������λ*/
	BSP_U8 RESERVE;
}PMU_PROTECT_STRU;

typedef struct
{
	BSP_U32 RESERVE0;           	/* ����,4Byte */
	BSP_U16 W_PA_V;            		/* W PA��ѹ 2Byte */
	BSP_U16 G_PA_V;             	/* G PA��ѹ 2Byte */
	BSP_U32 USB_EYE_CFG;        	/* USB��ͼ 4Byte */
	BSP_U32 APT_MODE;           	/* APT ģʽ 4Byte���μ�DR_APT_CFG_ENUM */
	PMU_PROTECT_STRU PMU_PROTECT;   /* PMU ���ȱ��� 4Byte*/
	BSP_U32 DRV_LOG_CTRL;       	/* DRVLOG��ӡ���� 4Byte */
	BSP_U32 DRV_LOG_LEVEL;      	/* DRVLOG��ӡ�ȼ� 4Byte */
	BSP_U32 RESERVE7;           	/* ����,4Byte */

	/*PMU NV������*/
	PMU_CFG_STRU PMU_CFG;
	BSP_U32 PMU_CRC32;	     /* PMU CRCУ��,4Byte */

	/* ����,ʣ��23(*)4Byte */
	BSP_U32 RESERVE41;
	BSP_U32 RESERVE42;
	BSP_U32 RESERVE43;
	BSP_U32 RESERVE44;
	BSP_U32 RESERVE45;
	BSP_U32 RESERVE46;
	BSP_U32 RESERVE47;
	BSP_U32 RESERVE48;
	BSP_U32 RESERVE49;
	BSP_U32 RESERVE50;
	BSP_U32 RESERVE51;
	BSP_U32 RESERVE52;
	BSP_U32 RESERVE53;
	BSP_U32 RESERVE54;
	BSP_U32 RESERVE55;
	BSP_U32 RESERVE56;
	BSP_U32 RESERVE57;
	BSP_U32 RESERVE58;
	BSP_U32 RESERVE59;
	BSP_U32 RESERVE60;
	BSP_U32 RESERVE61;
	BSP_U32 RESERVE62;
	BSP_U32 RESERVE63;
}NV_HW_CONFIG_STRU;



/*ͨ����NV����Ƹ������Ĵ���ʱ�����Ӧʱ�䡣��ʱ��Ϊ��Ʒ�߶��ƣ����������޸ġ�ID = 56 ���� 64*/
/*****************************************************************************
 �ṹ��    : KPD_NV_VERSION_1_1_T
 �ṹ˵��  : KPD_NV_VERSION_1_1_T�ṹ ID = 56
*****************************************************************************/
typedef struct
{
    BSP_U32  ulversion;                    /* Should be 0x0001_0000. major + minor */
    BSP_U32  ulkeyupdatetime;              /* 0 means not support. non-zero is the update check time */
    BSP_U32  ultickunit;                   /* the tick unit. ms */
    BSP_U32  ulitemtable[ KPD_EVENT_MAX ]; /* sizeof(versio_1_1) = 64bytes */
}KPD_NV_VERSION_1_1_T;                     /* version 1.1 structure */


/*WIFI_TARGET_ASSERT_ENABLE   ID = 57*/
/*****************************************************************************
 �ṹ��    : HWIFI_TARGET_ASSERT_ENABLE_STRU
 �ṹ˵��  : HWIFI_TARGET_ASSERT_ENABLE�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32   WIFI_TARGET_ASSERT_ENABLE;
}HWIFI_TARGET_ASSERT_ENABLE_STRU;

/*HILINK_AUTORUN_FLAG   ID = 61 ���� 2*/
/*****************************************************************************
 �ṹ��    : HILINK_AUTORUN_FLAG_STRU
 �ṹ˵��  : HILINK_AUTORUN_FLAG�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U16   HILINK_AUTORUN_FLAG;
}HILINK_AUTORUN_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NV_FACTORY_INFO_I_STRU
 �ṹ˵��  : NV_FACTORY_INFO_I�ṹ ID=114
*****************************************************************************/
typedef struct
{
    BSP_CHAR aucFactoryInfo[NV_FACTORY_INFO_I_SIZE];
}NV_FACTORY_INFO_I_STRU;

/*NV_Battery ID = 90*/
/*****************************************************************************
 �ṹ��    : VBAT_CALIBART_TYPE
 �ṹ˵��  : ���У׼�������ݽṹ
*****************************************************************************/
typedef struct
{
    BSP_U16 min_value;
    BSP_U16 max_value;
}VBAT_CALIBART_TYPE;

/*NV_USB_LOG_SAVE_LEV   ID = 118*/

/*****************************************************************************
 �ṹ��    : NV_USB_LOG_SAVE_LEV
 �ṹ˵��  : NV_USB_LOG_SAVE_LEV�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32 NV_USB_LOG_SAVE_LEV;
}NV_USB_LOG_SAVE_LEV_STRU;

/*NV_Usb_Mntn_Flag   ID = 119 ���� 2*/
/*****************************************************************************
 �ṹ��    : NV_ITEM_USB_PKT_HOOK_STRU
 �ṹ˵��  : NV_ITEM_USB_PKT_HOOK�ṹ ID=119
*****************************************************************************/
typedef struct
{
    BSP_U16 usUsbPktHookFlag;
}NV_ITEM_USB_PKT_HOOK_STRU;   /*USB����NV������*/


/*****************************************************************************
 �ṹ��    : NV_SCI_CFG_STRU
 �ṹ˵��  : NV_SCI_CFG�ṹ ID=128
*****************************************************************************/
typedef struct
{
    BSP_U32 value;
} NV_SCI_CFG_STRU;

/*�洢��ͬ�����µ����� ID = 50027*/
/*****************************************************************************
 �ṹ��    : nv_huawei_connect_display_rate_type
 �ṹ˵��  : nv_huawei_connect_display_rate_type�ṹ     ID=50027
*****************************************************************************/
typedef struct
{
    BSP_U8 gsm_connect_rate;
    BSP_U8 gprs_connect_rate;
    BSP_U8 edge_connect_rate;
    BSP_U8 wcdma_connect_rate;
    BSP_U8 hspda_connect_rate;
    BSP_U8 reserved;           /*����ʹ��*/
}nv_huawei_connect_display_rate_type;

/*�豸ö�ٹ������ϱ���PID��Ϣ ID = 50071*/
/*****************************************************************************
 �ṹ��    : nvi_cust_pid_type
 �ṹ˵��  : nvi_cust_pid_type�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32  nv_status;
    BSP_U16  cust_first_pid;
    BSP_U16  cust_rewind_pid;
}nvi_cust_pid_type;

/*WIFI��SSID����Ʒ��ʹ�ã�����ʱд�� ID=  52000*/
/*****************************************************************************
 �ṹ��    : nv_wifibs_type
 �ṹ˵��  : nv_wifibs_type�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U8   aucwlSsid[NV_WLSSID_LEN];
    BSP_U32  ulwlChannel;
    BSP_U32  ulwlHide;
    BSP_U8   aucwlCountry[NV_WLCOUNTRY_CODE_LEN];
    BSP_U8   aucwlMode[NV_WLMODE_LEN];
    BSP_U32  ulwlRate;
    BSP_U32  ulwlTxPwrPcnt;
    BSP_U32  ulwlMaxAssoc;
    BSP_U8   ucwlEnbl;
    BSP_U32  ulwlFrgThrshld;
    BSP_U32  ulwlRtsThrshld;
    BSP_U32  ulwlDtmIntvl;
    BSP_U32  ulwlBcnIntvl;
    BSP_U32  ulwlWme;
    BSP_U32  ulwlPamode;
    BSP_U32  ulwlIsolate;
    BSP_U32  ulwlProtectionmode;
    BSP_U32  ulwloffenable;
    BSP_U32  ulwlofftime;
    BSP_U8   aucwlExtends[12];
}nv_wifibs_type;


/*���±��� ID = 52005*/
/*****************************************************************************
 �ṹ��    : CHG_BATTERY_LOW_TEMP_PROTECT_NV
 �ṹ˵��  : CHG_BATTERY_LOW_TEMP_PROTECT_NV�ṹ ID=52005
*****************************************************************************/
typedef struct
{
    BSP_U32  ulIsEnable;
    BSP_S32  lCloseAdcThreshold;
    BSP_U32  ulTempLowCount;
}CHG_BATTERY_LOW_TEMP_PROTECT_NV;

/*****************************************************************************
 �ṹ��    : nv_wifi_info
 �ṹ˵��  : nv_wifi_info�ṹ
*****************************************************************************/
typedef struct
{
    BSP_U32 ulOpSupport;
    BSP_U8  usbHighChannel;
    BSP_U8  usbLowChannel;
    BSP_U8  aucRsv1[2];
    BSP_U16 ausbPower[2];
    BSP_U8  usgHighsChannel;
    BSP_U8  usgLowChannel;
    BSP_U8  aucRsv2[2];
    BSP_U16 ausgPower[2];
    BSP_U8  usnHighsChannel;
    BSP_U8  usnLowChannel;
    BSP_U8  ausnRsv3[2];
    BSP_U16 ausnPower[2];
}nv_wifi_info;


/*�豸ö�ٹ������ϱ��Ķ˿���̬���� ID = 50091*/
typedef struct PACKED_POST
{
    BSP_U32  nv_status;
    BSP_U8  first_port_style[17];
    BSP_U8  rewind_port_style[17];
    BSP_U8  reserved[22];
} nv_huawei_dynamic_pid_type;


/*NV_SEC_BOOT_ENABLE_FLAG   ID = 50201*/
/*****************************************************************************
 �ṹ��    : NV_SECBOOT_ENABLE_FLAG
 �ṹ˵��  : NV_SECBOOT_ENABLE_FLAG�ṹ ID=50201
*****************************************************************************/
typedef struct
{
    BSP_U16 usNVSecBootEnableFlag; /*Range:[0,1]*/
}NV_SECBOOT_ENABLE_FLAG;


/* NV_ID_DRV_PPP_DIAL_ERR_CODE            = 50061, */
typedef struct
{
    BSP_U8                               Ppp_Dial_Err_Code[2];
}PPP_DIAL_ERR_CODE_STRU;


/*****************************************************************************
 �ṹ��    : PROIDNvInfo
 �ṹ˵��  : PROIDNvInfo�ṹ     ID=50018
*****************************************************************************/
typedef struct _productIDNvInfo
{
    BSP_U32   NvStatus;
    BSP_U8    ucCompVer[VER_MAX_LENGTH];
} PROIDNvInfo;


/*****************************************************************************
 �ṹ��    : DR_NV_ENHANCE_SIMCARD_LOCK_STATUS_STRU
 �ṹ˵��  : ��ǿ������״̬�ṹ��   ID=8517
*****************************************************************************/
typedef struct
{
    BSP_U8  EnhanceSimcardStatus;     /* ��ǿ�����������Ƿ񼤻� 0:������, 1: ���� */
    BSP_U8  SimcardStatus;            /* SimCardLockStatus����״̬ 1: �����汾, 2: �������汾 */
}DR_NV_ENHANCE_SIMCARD_LOCK_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : nv_protocol_base_type
 �ṹ˵��  : nv_protocol_base_type�ṹ ID= 52110
*****************************************************************************/
typedef struct
{
    BSP_U32  nv_status;
    BSP_U32  protocol_base;
}nv_protocol_base_type;

/*****************************************************************************
 �ṹ��    : NV_FEM_GPIO_MIPI_CTRL_STRU
 �ṹ˵��  : en_NV_Item_FEM_GPIO_MIPI_CTRL �ṹ ID= 18002
*****************************************************************************/
#define FEM_MIPI_CMD_MAX  4  /*mipiָ��������*/
#define FEM_IO_CFG_MAX    16 /*18002 nv�����֧�ֵ����ø���*/
#define FEM_PIN_MAX       32 /*��Ƶ�ܽŸ���*/
#define GPIO_NUM_INVAILId 0xffff
typedef struct{
	BSP_U32 cfg[FEM_PIN_MAX];
}NV_FEMPIN_TO_GPIO_STRU;

typedef struct
{
	BSP_U32 pin_00    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_01    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_02    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_03    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_04    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_05	  : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_06 	  : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_07    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_08    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_09    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_10    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_11    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_12    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_13    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_14    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_15	  : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_16 	  : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_17    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_18    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_19    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_20    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_21    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_22    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_23    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_24    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_25	  : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_26 	  : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_27    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_28    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_29    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_30    : 1; /*1 is select, 0 is not select*/
	BSP_U32 pin_31    : 1; /*1 is select, 0 is not select*/
}FEMIO_PIN_CFG_STRU;

typedef struct
{	
    union
    {
        BSP_U32              value;
        FEMIO_PIN_CFG_STRU   cfg;
    } pin_mask;              /*��Ƶ�ܽ�����,0��ʾ��bitλ����Ҫ����*/
    union
    {
        BSP_U32              level;
        FEMIO_PIN_CFG_STRU   cfg;
    } pin_level;              /*��Ƶ�ܽ������ƽ ֵ,0��ʾ�õ͵�ƽ��1��ʾ�ߵ�ƽ*/
			
}FEMIO_GPIO_CTRL_STRU;

typedef struct
{
	BSP_U8 mipi_chn;  /*mipiͨ����*/
	BSP_U8 slave_id;  /*���߿��ص�slave id*/
	BSP_U8 reg_offset;/*���õļĴ���ƫ��*/
	BSP_U8 value;     /*���õ�ֵ*/

}FEM_MIPI_CFG_STRU;

typedef struct
{  
	BSP_U32             count;                    /*��Ч��mipi ָ�����*/
	FEM_MIPI_CFG_STRU   cmd[FEM_MIPI_CMD_MAX];	  /*mipi������*/
}FEMIO_MIPI_CTRL_STRU;

typedef enum{
	FEMIO_CTRL_TOP = 0,/*��������*/
	GPIO_ONLY = 1,     /*ֻ����GPIO*/
	MIPI_ONLY = 2,     /*ֻ����MIPI*/
	GPIO_MIPI = 3,     /*����GPIO��MIPI*/
	FEMIO_CTRL_BUTT
}FEMIO_CTRL_MODE;

typedef struct
{
	FEMIO_CTRL_MODE       mode;     /*����ģʽ*/
	FEMIO_GPIO_CTRL_STRU  gpio_ctrl;/*GPIO ����  */
	FEMIO_MIPI_CTRL_STRU  mipi_ctrl;/*MIPI  ����  */
}FEM_GPIO_MIPI_CTRL_STRU;

typedef struct
{
	FEM_GPIO_MIPI_CTRL_STRU cfg[FEM_IO_CFG_MAX];
}NV_FEM_GPIO_MIPI_CTRL_STRU;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


