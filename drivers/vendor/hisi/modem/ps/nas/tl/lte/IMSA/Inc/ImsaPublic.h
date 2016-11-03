

#ifndef __IMSAPUBLIC_H__
#define __IMSAPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include "PsCommonDef.h"
#include "LPSCommon.h"
#include "ImsaEntity.h"
#include "LPsOm.h"
#include "ImsaImsEvent.h"
#include "ImsParm.h"
#include "NasFileId.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define IMSA_NULL                       (0)
#define IMSA_SUCC                       (0)
#define IMSA_FAIL                       (1)
#define IMSA_OP_FALSE                   (0)
#define IMSA_OP_TRUE                    (1)
#define IMSA_TRUE                       (1)
#define IMSA_FALSE                      (0)
#define IMSA_CLIENT_ID                  (0x66)

#define IMSA_PRINT_BUFF_LEN             (3096)              /* 1024ÿ�δ�ӡԤ�軺�� */
extern VOS_CHAR                         g_acImsaPrintBuf[IMSA_PRINT_BUFF_LEN];
#define IMSA_GET_IMSA_PRINT_BUF()       (g_acImsaPrintBuf)

#define IMSA_Min(ulX1, ulX2)            (((ulX1) > (ulX2)) ? (ulX2) : (ulX1))
#define IMSA_Max(ulX1, ulX2)            (((ulX1) > (ulX2)) ? (ulX1) : (ulX2))

#define IMSA_MOVEMENT_8                 (8)
#define IMSA_MOVEMENT_16                (16)
#define IMSA_MOVEMENT_24                (24)

#define IMSA_MSG_NOT_PROC               (0)
#define IMSA_MSG_PROCED                 (1)
#define IMSA_NV_INFO_LEN                (4)

#define IMSA_TIMER_1_TICK_10_MS         (10)            /* 1 tickΪ10ms */

#define IMSA_AUTH_TYPE_AKA               (0)
#define IMSA_AUTH_TYPE_DIGIST            (1)
#define IMSA_AUTH_TYPE_AKA_IPSEC         (2)

#define IMSA_USIM_MAX_OPID              (0x7F)

#ifdef PS_ITT_PC_TEST
#define IMSA_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String)
 */
#define IMSA_INFO_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1 )
 */
#define IMSA_INFO_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1, (long)Para2)
 */
#define IMSA_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String)
 */
#define IMSA_NORM_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1 )
 */
#define IMSA_NORM_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1, (long)Para2)
 */
#define IMSA_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String)
 */
#define IMSA_WARN_LOG1(String, Para1) \
                     vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String, (long)Para1 )
 */
#define IMSA_WARN_LOG2(String, Para1, Para2) \
                         vos_printf(" %s %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String, (long)Para1, (long)Para2)
 */
#define IMSA_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String)
 */
#define IMSA_ERR_LOG1(String, Para1) \
                     vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String, (long)Para1 )
 */

#else
#define IMSA_INFO_LOG(String) \
                 LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_INFO, String)
#define IMSA_INFO_LOG1(String, Para1) \
                 LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define IMSA_INFO_LOG2(String, Para1, Para2) \
                 LPS_LOG2(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define IMSA_NORM_LOG(String) \
                 LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define IMSA_NORM_LOG1(String, Para1) \
                 LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define IMSA_NORM_LOG2(String, Para1, Para2) \
                 LPS_LOG2(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#define IMSA_WARN_LOG(String) \
                 LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_WARNING, String)
#define IMSA_WARN_LOG1(String, Para1) \
                 LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_WARNING, String, (long)Para1 )
#define IMSA_WARN_LOG2(String, Para1, Para2) \
                 LPS_LOG2(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2)
#define IMSA_ERR_LOG(String) \
                 LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_ERROR, String)
#define IMSA_ERR_LOG1(String, Para1) \
                 LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_ERROR, String, (long)Para1 )


#endif

/* �ڴ濽���궨�� */
#define IMSA_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulBufferLen) PS_MEM_CPY_ALL_CHECK((pucDestBuffer),(pucSrcBuffer),(ulBufferLen))

#define IMSA_MEM_SET(pucBuffer, ucData, ulBufferLen) \
            PS_MEM_SET_ALL_CHECK( (pucBuffer), (ucData), (ulBufferLen))


#define IMSA_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
            PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define IMSA_ALLOC_MSG(ulLen) \
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_IMSA) , (ulLen))

#define IMSA_FREE_MSG(pMsg) \
            PS_FREE_MSG( PS_PID_IMSA, pMsg )

extern VOS_VOID IMSA_Send_Msg(VOS_VOID* pMsg);

/* ������Ϣ */
#define IMSA_SND_MSG(pMsg)\
            IMSA_Send_Msg(pMsg)

extern VOS_VOID IMSA_Send_Intra_Msg(VOS_VOID* pIntraMsg);

#define IMSA_SEND_INTRA_MSG(pIntraMsg)\
            IMSA_Send_Intra_Msg(pIntraMsg)

/*�ڴ��ͷ�*/
#define IMSA_MEM_FREE(pAddr)  PS_MEM_FREE(PS_PID_IMSA, pAddr)

/*�ڴ涯̬����*/
#define IMSA_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_IMSA) , (ulSize))


#define IMSA_NV_Read( ulId, pItemData, usItemDataLen ) \
        LPs_NvimItem_Read( ulId, pItemData, usItemDataLen)

#define IMSA_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define IMSA_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))

#define IMSA_GET_MSG_ENTITY_BY_NAME(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgName))

/*��װдSPM��Ϣͷ�ĺ�*/
#define IMSA_WRITE_SPM_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_TAF;

/*��װдMMA��Ϣͷ�ĺ�*/
#define IMSA_WRITE_MMA_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_MMA;

/*��װдIMSA�ڲ���Ϣͷ�ĺ�*/
#define IMSA_WRITE_INTRA_MSG_HEAD(pstMsg, ulMsgID, ulLen)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_IMSA;\
                    (pstMsg)->ulLength          = (ulLen - VOS_MSG_HEAD_LENGTH);

/*��װдCDS��Ϣͷ�ĺ�*/
#define IMSA_WRITE_CDS_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = UEPS_PID_CDS;


/*��װдVC��Ϣͷ�ĺ�*/
#define IMSA_WRITE_VC_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgName           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = WUEPS_PID_VC;

/*��װдIMS��Ϣͷ�ĺ�*/
#define IMSA_WRITE_IMS_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_IMSVA;

/*��װD2дIMSA��Ϣͷ�ĺ�*/
#define IMSA_WRITE_IMSA_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSVA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_IMSA;

/*��װдMSG��Ϣͷ�ĺ�*/
#define IMSA_WRITE_MSG_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgName         = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = WUEPS_PID_TAF;

/*��װдAT MSG��Ϣͷ�ĺ�*/
#define IMSA_WRITE_AT_MSG_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId         = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = WUEPS_PID_AT;

/*��װдSPM��Ϣͷ�ĺ�*/
#define IMSA_WRITE_CALL_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_TAF;

#define IMSA_WRITE_RNIC_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = ACPU_PID_RNIC;


/*��װдMTC MSG��Ϣͷ�ĺ�*/
#define IMSA_WRITE_MTC_MSG_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = UEPS_PID_MTC;
#define IMSA_WRITE_ERRLOG_HEADER_INFO(pstHeader, ModemId, AlmId, AlmLevel, ulSlice, ulLength) \
                    (pstHeader)->ulMsgModuleId     = OM_ERR_LOG_MOUDLE_ID_IMSA; \
                    (pstHeader)->usModemId         = ModemId; \
                    (pstHeader)->usAlmId           = AlmId; \
                    (pstHeader)->usAlmLevel        = AlmLevel; \
                    (pstHeader)->usAlmType         = IMSA_ERR_LOG_ALARM_TYPE_COMMUNICATION; \
                    (pstHeader)->usAlmLowSlice     = ulSlice; \
                    (pstHeader)->usAlmHighSlice    = 0; \
                    (pstHeader)->ulAlmLength       = ulLength;

#define IMSA_WRITE_OM_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = ACPU_PID_OM;
/*��װдLRRC��Ϣͷ�ĺ�*/
#define IMSA_WRITE_LRRC_MSG_HEAD(pstMsg, ulMsgID,ulLen)\
                    (pstMsg)->stMsgHeader.ulMsgName   = (ulMsgID);\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulReceiverPid = PS_PID_ERRC;\
                    (pstMsg)->stMsgHeader.ulLength      = (ulLen - VOS_MSG_HEAD_LENGTH);
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
    ö����    : IMSA_TIMER_ID_ENUM
    ö��˵��  : ��ʱ��ID
*****************************************************************************/
enum IMSA_TIMER_ID_ENUM
{
    TI_IMSA_START_OR_STOP               = 0x0000,           /* ���ػ���ʱ�� */
    TI_IMSA_PERIOD_TRY_IMS_SRV          = 0x0001,           /* �����Գ���IMS����ʱ�� */
    TI_IMSA_PERIOD_TRY_IMS_EMC_SRV          = 0x0002,           /* �����Գ��Խ���IMS����ʱ�� */

    TI_IMSA_SIP_SIGAL_PDP_ORIG          = 0x0100,           /* SIP������ز��Ŷ�ʱ�� */
    TI_IMSA_SIP_SIGAL_PDP_END           = 0x0101,           /* SIP�������ȥ���Ŷ�ʱ�� */
    TI_IMSA_WAIT_IPV6_INFO              = 0x0102,           /* �ȴ�IPV6��Ϣ��ʱ�� */

    TI_IMSA_REG_PROTECT                 = 0x0200,           /* ע��ģ��ı�����ʱ�� */
    TI_IMSA_REG_RETRY                   = 0x0201,           /* ע��ģ������Զ�ʱ�� */

    TI_IMSA_CALL_PROTECT                = 0x0300,           /* ����ģ��ı�����ʱ�� */
    TI_IMSA_CALL_RES_READY              = 0x0301,           /* ����ģ��ȴ���ԴԤ�������ʱ�� */
    TI_IMSA_CALL_DTMF_DURATION          = 0x0302,           /* ����ģ��dtmf����ʱ����ʱ�� */
    TI_IMSA_CALL_DTMF_PROTECT           = 0x0303,           /* ����ģ��dtmf������ʱ�� */
    TI_IMSA_CALL_REDIAL_MAX_TIME        = 0x0304,           /* ����ģ���ز����ʱ����ʱ�� */
    TI_IMSA_CALL_REDIAL_INTERVEL        = 0x0305,           /* ����ģ���ز������ʱ�� */
    TI_IMSA_CONFIG_PARA_CMCC_TCALL      = 0x0306,           /* IMSA_CONFIG_PARA_STRU�����CMCC Tcall��ʱ��*/

    TI_IMSA_SMS_TR1M                    = 0x0400,           /* ����TR1M��ʱ�� */
    TI_IMSA_SMS_TR2M                    = 0x0401,           /* ����TR2M��ʱ�� */
    TI_IMSA_SMS_TRAM                    = 0x0402,           /* ����TRAM��ʱ�� */

    TI_IMSA_BACK_OFF_TX                 = 0x0500,           /* SSAC*/
    TI_IMSA_BACK_OFF_TY                 = 0x0501,           /**/

    TI_IMSA_USSD_WAIT_NET_RSP           = 0x0600,           /*USSD�ȴ�������Ӧ��ʱ��*/
    TI_IMSA_USSD_WAIT_APP_RSP           = 0x0601,           /*USSD�ȴ��ϲ���Ӧ��ʱ��*/

    IMSA_TIMER_ID_BUTT
};
typedef VOS_UINT16 IMSA_TIMER_ID_ENUM_UINT16;

/*****************************************************************************
    ö����    : IMSA_ISIM_FILE_ENUM
    ö��˵��  : ISIM IDö��
*****************************************************************************/
enum IMSA_ISIM_FILE_ID_ENUM
{
    IMSA_ISIM_FILE_ID_INVALID           = 0x0000,
    IMSA_ISIM_FILE_ID_IMPI              = 0x6F02,               /*IMS private user identity*/
    IMSA_ISIM_FILE_ID_DOMAIN            = 0x6F03,               /*Home Network Domain Name*/
    IMSA_ISIM_FILE_ID_IMPU              = 0x6F04,               /*IMS public user identity*/
    IMSA_ISIM_FILE_ID_AD                = 0x6FAD,               /*Administrative Data*/
    IMSA_ISIM_FILE_ID_IST               = 0x6F07,               /*ISIM Service Table*/
    IMSA_ISIM_FILE_ID_P_CSCF            = 0x6F09,               /*P-CSCF Address*/
    IMSA_ISIM_FILE_ID_GBABP             = 0x6FD5,               /*GBA Bootstrapping parameters*/
    IMSA_ISIM_FILE_ID_GBANL             = 0x6FD7,               /*GBA NAF List*/
    IMSA_ISIM_FILE_ID_NAFKCA            = 0x6FDD,               /*NAF Key Centre Address*/
    IMSA_ISIM_FILE_ID_UICCIARI          = 0x6FE7,               /*UICC IARI*/

    IMSA_ISIM_FILE_ID_BUTT
};
typedef VOS_UINT32 IMSA_ISIM_FILE_ID_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_SIP_NW_ERROR_CAUSE_ENUM
    ö��˵��  : SIP�տھܾ�ԭ��ֵ
*****************************************************************************/
enum IMSA_SIP_NW_ERROR_CAUSE_ENUM
{
    IMSA_SIP_NW_ERROR_CAUSE_USE_PROXY               = 305,
    IMSA_SIP_NW_ERROR_CAUSE_ALTERNATIVE_SERVICE     = 380,
    IMSA_SIP_NW_ERROR_CAUSE_UNAUTHORIZED            = 401,
    IMSA_SIP_NW_ERROR_CAUSE_REQUEST_TIMEOUT         = 408,
    IMSA_SIP_NW_ERROR_CAUSE_SERVER_INTERNAL_ERROR   = 500,
    IMSA_SIP_NW_ERROR_CAUSE_SERVICE_UNAVAILABLE     = 503,
    IMSA_SIP_NW_ERROR_CAUSE_SERVER_TIMEOUT          = 504,
    IMSA_SIP_NW_ERROR_CAUSE_BUSY_EVERYWHERE         = 600,

    IMSA_SIP_NW_ERROR_CAUSE_BUTT
};
typedef VOS_UINT32 IMSA_SIP_NW_ERROR_CAUSE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
#if (FEATURE_ON == FEATURE_PTM)

typedef struct
{
    IMSA_ERR_LOG_ALM_ID_ENUM_UINT16         enAlmID;        /* �쳣ģ��ID */
    VOS_UINT16                              usLogLevel;     /* �ϱ�log�ȼ� */
}IMSA_ERR_LOG_ALM_LEVEL_STRU;
#endif

typedef struct
{
    VOS_UINT8            *pData;      /*����*/
    VOS_UINT16          usDataLen;   /*����*/
}IMSA_ISIM_DATA_STRU;

typedef VOS_UINT32 ( * IMSA_ISIM_ACTION_FUN )
(
    const IMSA_ISIM_DATA_STRU *    /*����ָ��*/
);


typedef struct
{
    IMSA_ISIM_FILE_ID_ENUM_UINT32       enIsimFileId;        /* ISIMЭ���ļ�ID*/
    IMSA_ISIM_ACTION_FUN                pfDecodeActionFun;   /* �������� */
    IMSA_ISIM_ACTION_FUN                pfEncodeActionFun;   /* �������� */
}IMSA_ISIM_ACT_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


extern VOS_VOID IMSA_ReadImsaNV(VOS_VOID);

extern VOS_VOID IMSA_StartTimer(IMSA_TIMER_STRU *pstTimer);
extern VOS_VOID IMSA_StopTimer(IMSA_TIMER_STRU *pstTimer);
extern VOS_UINT32 IMSA_IsTimerRunning(const IMSA_TIMER_STRU *pstTimer);
extern VOS_VOID IMSA_GetRemainTimeLen
(
    IMSA_TIMER_STRU                    *pstTimer,
    VOS_UINT32                         *pulRemainTimeLen
);
extern VOS_UINT32 IMSA_AllocImsOpId(VOS_VOID);
extern VOS_VOID   IMSA_ResetImsOpId(VOS_VOID);
extern VOS_UINT32 IMSA_GetImsOpId(VOS_VOID);
extern VOS_VOID IMSA_SaveRcvImsNormOpid(VOS_UINT32 ulImsOpid);

extern VOS_UINT32 IMSA_GetRcvImsNormOpid(VOS_VOID);

extern VOS_VOID IMSA_SaveRcvImsEmcOpid(VOS_UINT32 ulImsOpid);

extern VOS_UINT32 IMSA_GetRcvImsEmcOpid(VOS_VOID);
extern VOS_UINT8 IMSA_AllocUsimOpId(VOS_VOID);
extern VOS_VOID IMSA_ResetUsimOpId(VOS_VOID);
extern VOS_UINT8 IMSA_GetUsimOpId(VOS_VOID);

extern VOS_VOID IMSA_ProcIsimStatusInd(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_ProcIsimRefreshInd(const VOS_VOID *pRcvMsg);

extern VOS_UINT32 IMSA_ProcReadIsimFileResult(VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_ProcIsimAuthRsp(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_ReadIsimFile(VOS_VOID);
extern VOS_UINT32  IMSA_UtilBcdNumberToAscii(
    const VOS_UINT8                     *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                            *pcAsciiNumber
);
extern VOS_UINT32  IMSA_UtilAsciiNumberToBcd(
    const VOS_CHAR                      *pcAsciiNumber,
    VOS_UINT8                           *pucBcdNumber,
    VOS_UINT8                           *pucBcdLen
);


extern VOS_VOID IMSA_UtilStrNCpy(VOS_CHAR *pDst, const VOS_CHAR *pSrc, VOS_UINT32 ulLen);
extern VOS_VOID IMSA_PrintImsaSendMsg
(
    const PS_MSG_HEADER_STRU               *pstMsg,
    VOS_CHAR                               *pcBuff
);
extern VOS_INT32  IMSA_PrintSpmImsaCallSupsCmdReq
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaSpmCallMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputCall
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputSms
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputService
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputSystem
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintCallImsaSrvccStatusNotify
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputPara
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  IMSA_PrintImsaImsOutputSms
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputSystem
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputPara
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputCall
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputService
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_VOID IMSA_PrintImsaRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);
extern VOS_VOID IMSA_ConfigCgi2Ims( VOS_VOID );
extern VOS_CHAR IMSA_ConverterDigit2Chacter
(
    VOS_UINT8                           ucDigit
);
extern VOS_VOID IMSA_ConfigImei2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigTimerLength2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigUeCapabilityInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigNetCapInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigAccoutInfo2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);
extern VOS_UINT32  IMSA_AsciiToDtmfKeyEnum
(
    VOS_CHAR                            cAsciiCode,
    IMSA_IMS_DTMF_KEY_ENUM_UINT8       *penDtmfKey
);
extern VOS_VOID IMSA_ConfigSipInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigVoipInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigCodeInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigSsConfInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigSecurityInfo2Ims( VOS_VOID );

extern VOS_VOID IMSA_ConfigMediaParmInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigSipPort2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConverterSipPort2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvt
);
extern VOS_UINT32 IMSA_SetCurrentPara
(
    IMSA_CONN_TYPE_ENUM_UINT32      enConnType,
    VOS_CHAR                        *pacUeAddr,
    VOS_CHAR                        *pacPcscfAddr
);
extern VOS_UINT32 IMSA_IsRegParaAvailable
(
    IMSA_CONN_TYPE_ENUM_UINT32      enConnType,
    VOS_CHAR                        *pacUeAddr,
    VOS_CHAR                        *pacPcscfAddr
);

extern VOS_VOID IMSA_SndMtcSrvConnStatusNotify(VOS_UINT8 ucIsImsExist);
extern VOS_UINT32 IMSA_IsImsExist(VOS_VOID);
extern VOS_VOID IMSA_WhenImsSrvConnStatusChangeNotifyMtc(VOS_VOID);
extern VOS_UINT32 IMSA_IsCurrentAccessTypeSupportIms(VOS_VOID);

#if (FEATURE_ON == FEATURE_PTM)

extern VOS_VOID IMSA_InitErrLogInfo(VOS_VOID);
extern IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8 IMSA_CallImsaState2ErrlogState(IMSA_CALL_STATUS_ENUM_UINT8 enImsaState);
extern VOS_UINT16 IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_ID_ENUM_UINT16 enAlmId);

extern VOS_UINT32 IMSA_IsErrLogNeedRecord(VOS_UINT16 usLevel);

extern VOS_UINT32 IMSA_GetErrLogRingBufContent
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern VOS_UINT32 IMSA_GetErrLogRingBufferUseBytes(VOS_VOID);
extern VOS_VOID IMSA_CleanErrLogRingBuf(VOS_VOID);
extern VOS_UINT32 IMSA_PutErrLogRingBuf
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8 IMSA_PsSerStates2ErrlogPsStates
(
    IMSA_PS_SERVICE_STATUS_ENUM_UINT8 enImsaPsStates
);
extern IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8 IMSA_ConnState2ErrlogConnState(IMSA_CONN_STATUS_ENUM_UINT8 enImsaConnState);
extern IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8 IMSA_VoPsState2ErrlogVoPsState(IMSA_IMS_VOPS_STATUS_ENUM_UINT8 enImsaImsVoPsStatus);
extern IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8 IMSA_CallImsaMpty2ErrlogMpty(MN_CALL_MPTY_STATE_ENUM_UINT8 enImsaMpty);
extern IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8 IMSA_RegState2ErrlogState(IMSA_REG_STAUTS_ENUM_UINT8 enImsaRegState);
extern IMSA_ERR_LOG_REGISTER_REASON_ENUM_UINT8 IMSA_RegAddrType2ErrlogRegReason(IMSA_REG_ADDR_PARAM_ENUM_UINT32 enImsaRegAddr);
#endif
/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaPublic.h */




