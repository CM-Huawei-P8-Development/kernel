

#ifndef __ATCMDMSGPROC_H__
#define __ATCMDMSGPROC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "AtTypeDef.h"
#include  "AtCtx.h"
#include  "AcpuReset.h"
#include  "TafDrvAgent.h"
#include  "AtMtaInterface.h"
#include  "AtInternalMsg.h"
#if (FEATURE_ON == FEATURE_IMS)
#include  "AtImsaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


extern VOS_INT8                         g_acATE5DissdPwd[AT_DISSD_PWD_LEN+1];


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*��Ϣ��������ָ��*/
typedef VOS_UINT32 (*pAtProcMsgFromDrvAgentFunc)(VOS_VOID *pMsg);

/*AT��MTAģ�����Ϣ��������ָ��*/
typedef VOS_UINT32 (*AT_MTA_MSG_PROC_FUNC)(VOS_VOID *pMsg);


/*AT��MMAģ�����Ϣ��������ָ��*/
typedef VOS_UINT32 (*AT_MMA_MSG_PROC_FUNC)(VOS_VOID *pMsg);



/*****************************************************************************
 �ṹ��    : DRV_AGENT_MSG_PROC_STRU
 �ṹ˵��  : ��Ϣ���Ӧ���������Ľṹ
*****************************************************************************/
typedef struct
{
    DRV_AGENT_MSG_TYPE_ENUM_UINT32       ulMsgType;
    pAtProcMsgFromDrvAgentFunc           pProcMsgFunc;
}AT_PROC_MSG_FROM_DRV_AGENT_STRU;

/*****************************************************************************
 Structure      : NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST
 Description    : PC�طŹ��̣��洢����AT��ص�ȫ�ֱ�����Ŀǰ���ж������ȫ�ֱ���
 Message origin :
 Note:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsed;                                 /* ָʾ��ǰ�����Ƿ��ѱ�ʹ�� */
    AT_USER_TYPE                        UserType;                               /* ָʾ��ǰ�û����� */
    AT_MODE_TYPE                        Mode;                                   /* ָʾ��ǰ����ģʽ��ֻ���MUX��APP */
    AT_IND_MODE_TYPE                    IndMode;                                /* ָʾ��ǰ����ģʽ��ֻ���MUX��APP */
    VOS_UINT16                          usClientId;                             /* ָʾ��ǰ�û��� */
    MN_OPERATION_ID_T                   opId;                                   /* Operation ID, ��ʶ���β���             */
    VOS_UINT8                           aucReserved[1];
}NAS_AT_CLIENT_MANAGE_SIMPLE_STRU;

/*****************************************************************************
 Structure      : NAS_AT_SDT_AT_CLIENT_TABLE_STRU
 Description    : PC�طŹ��̣�����AT��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_INTER_MSG_ID_ENUM_UINT32             enMsgID;
    VOS_UINT8                               ucType;
    VOS_UINT8                               aucReserved[3];                     /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_AT_CLIENT_MANAGE_SIMPLE_STRU        gastAtClientTab[AT_MAX_CLIENT_NUM];
}NAS_AT_SDT_AT_CLIENT_TABLE_STRU;

typedef struct
{
    AT_CSCS_TYPE                        gucAtCscsType;
    AT_CSDH_TYPE                        gucAtCsdhType;
    MN_OPERATION_ID_T                   g_OpId;
    MN_MSG_CSMS_MSG_VERSION_ENUM_U8     g_enAtCsmsMsgVersion;
    AT_CNMI_TYPE_STRU                   gstAtCnmiType;
    AT_CMGF_MSG_FORMAT_ENUM_U8          g_enAtCmgfMsgFormat;
    VOS_UINT8                           aucReserved[3];                         /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    AT_CGSMS_SEND_DOMAIN_STRU           g_stAtCgsmsSendDomain;
    AT_CSCA_CSMP_INFO_STRU              g_stAtCscaCsmpInfo;
    AT_MSG_CPMS_STRU                    g_stAtCpmsInfo;
}NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST;

/*****************************************************************************
 Structure      : NAS_AT_SDT_AT_PART_ST
 Description    : PC�طŹ��̣�����AT��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    AT_INTER_MSG_ID_ENUM_UINT32             enMsgID; /* ƥ��AT_MSG_STRU��Ϣ�е�ulMsgID  */
    VOS_UINT8                               ucType;  /* ֮ǰ��ucMsgIDs */
    VOS_UINT8                               aucReserved[3];                     /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST  astOutsideCtx[MODEM_ID_BUTT];
}NAS_AT_SDT_AT_PART_ST;

/*****************************************************************************
 �ṹ��    : AT_PROC_MSG_FROM_MTA_STRU
 �ṹ˵��  : AT��MTA��Ϣ���Ӧ���������Ľṹ
*****************************************************************************/
typedef struct
{
    AT_MTA_MSG_TYPE_ENUM_UINT32         ulMsgType;
    AT_MTA_MSG_PROC_FUNC                pProcMsgFunc;
}AT_PROC_MSG_FROM_MTA_STRU;

/*****************************************************************************
 �ṹ��    : AT_PROC_MSG_FROM_MTA_STRU
 �ṹ˵��  : AT��MTA��Ϣ���Ӧ���������Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgName;
    AT_MMA_MSG_PROC_FUNC                pProcMsgFunc;
}AT_PROC_MSG_FROM_MMA_STRU;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 AT_FormatAtiCmdQryString(
    MODEM_ID_ENUM_UINT16                enModemId,
    DRV_AGENT_MSID_QRY_CNF_STRU         *pstDrvAgentMsidQryCnf
);
VOS_UINT32 AT_RcvDrvAgentMsidQryCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentGasMntnCmdRsp(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentVertimeQryRsp(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentYjcxSetCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentYjcxQryCnf(VOS_VOID *pMsg);

VOS_UINT32 At_RcvAtCcMsgStateQryCnfProc(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentHardwareQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentFullHardwareQryRsp(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentSetRxdivCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentQryRxdivCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentSetSimlockCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvMmaCrpnQueryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMmaCmmSetCmdRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvAtMmaUsimStatusInd(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentSetNvRestoreCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentQryNvRestoreRstCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentNvRestoreManuDefaultRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_DeciDigit2Ascii(
    VOS_UINT8                           aucDeciDigit[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
);
VOS_UINT32  AT_GetImeiValue(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8 aucImei[TAF_PH_IMEI_LEN + 1]
);
VOS_BOOL AT_IsSimLockPlmnInfoValid(VOS_VOID);

VOS_UINT32 AT_RcvDrvAgentSetGpioplRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQryGpioplRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentSetDatalockRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQryTbatvoltRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQryVersionRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQrySecuBootRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentSetFchanRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQrySfeatureRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQryProdtypeRsp(VOS_VOID * pMsg);


extern VOS_VOID At_CmdMsgDistr(AT_MSG_STRU *pstMsg);

extern VOS_VOID At_CovertMsInternalRxDivParaToUserSet(
    VOS_UINT16                          usCurBandSwitch,
    VOS_UINT32                         *pulUserDivBandsLow,
    VOS_UINT32                         *pulUserDivBandsHigh
);

extern VOS_UINT32 AT_RcvDrvAgentSetAdcRsp(VOS_VOID *pMsg);

extern VOS_BOOL AT_E5CheckRight(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);

VOS_UINT32 AT_RcvDrvAgentTseLrfSetRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentHkAdcGetRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentQryTbatRsp(VOS_VOID *pMsg);

#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
VOS_UINT32 AT_RcvDrvAgentSetSpwordRsp(VOS_VOID *pMsg);
#endif
VOS_UINT32 AT_RcvDrvAgentSetSecuBootRsp(VOS_VOID *pMsg);

extern VOS_UINT32 AT_RcvMmaCipherInfoQueryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMmaLocInfoQueryCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentNvBackupStatQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentNandBadBlockQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentNandDevInfoQryRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentChipTempQryRsp(VOS_VOID *pMsg);


VOS_UINT32 AT_RcvDrvAgentAntStateIndRsp(VOS_VOID *pMsg);


VOS_VOID  AT_ReadSystemAppConfigNV(VOS_VOID);


VOS_UINT32 AT_RcvMmaOmMaintainInfoInd(
    VOS_VOID                           *pstMsg
);
VOS_UINT32 AT_RcvDrvAgentSetMaxLockTmsRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentSetApSimstRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvDrvAgentHukSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentFacAuthPubkeySetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentIdentifyStartSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentIdentifyEndSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentSimlockDataWriteSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPhoneSimlockInfoQryCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentSimlockDataReadQryCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPhonePhynumSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPhonePhynumQryCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPortctrlTmpSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPortAttribSetCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentPortAttribSetQryCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvDrvAgentOpwordSetCnf(VOS_VOID *pMsg);

extern VOS_UINT32 AT_RcvMtaCposSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMtaCposrInd(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMtaXcposrRptInd(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMtaCgpsClockSetCnf(VOS_VOID *pMsg);
extern VOS_VOID At_ProcMtaMsg(AT_MTA_MSG_STRU *pMsg);

extern VOS_UINT32 AT_RcvMtaApSecSetCnf( VOS_VOID *pMsg );

extern VOS_VOID AT_Rpt_NV_Read( VOS_VOID );

extern VOS_UINT32 AT_RcvMtaSimlockUnlockSetCnf( VOS_VOID *pMsg );

VOS_UINT32 AT_RcvMtaQryNmrCnf( VOS_VOID *pMsg );

VOS_UINT32 AT_RcvMtaWrrAutotestQryCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrCellinfoQryCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrMeanrptQryCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrCellSrhSetCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrCellSrhQryCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrFreqLockSetCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrFreqLockQryCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrRrcVersionSetCnf( VOS_VOID *pMsg );
VOS_UINT32 AT_RcvMtaWrrRrcVersionQryCnf( VOS_VOID *pMsg );

VOS_UINT32 AT_RcvMmaAcInfoQueryCnf(VOS_VOID *pstMsg);


extern VOS_VOID AT_ReadWasCapabilityNV(VOS_VOID);

VOS_UINT32 AT_RcvMtaBodySarSetCnf(VOS_VOID *pstMsg);

extern VOS_VOID AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_ENUM_UINT32 enCause);
extern VOS_VOID AT_StopAllTimer(VOS_VOID);
extern VOS_VOID AT_ResetParseCtx(VOS_VOID);
extern VOS_VOID AT_ResetClientTab(VOS_VOID);
extern VOS_VOID AT_ResetOtherCtx(VOS_VOID);
extern VOS_UINT32 AT_RcvCcpuResetStartInd(
    VOS_VOID                           *pstMsg
);
extern VOS_UINT32 AT_RcvCcpuResetEndInd(
    VOS_VOID                           *pstMsg
);
extern VOS_UINT32 AT_RcvHifiResetStartInd(
    VOS_VOID                           *pstMsg
);

VOS_UINT32 AT_RcvHifiResetEndInd(
    VOS_VOID                           *pstMsg
);

#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_UINT32 At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
#endif

VOS_UINT32 AT_RcvMtaQryCurcCnf(VOS_VOID *pstMsg);
VOS_UINT32 AT_RcvMtaSetUnsolicitedRptCnf(VOS_VOID *pstMsg);
VOS_UINT32 AT_RcvMtaQryUnsolicitedRptCnf(VOS_VOID *pstMsg);
VOS_UINT32 AT_ProcMtaUnsolicitedRptQryCnf(
    VOS_UINT8                               ucIndex,
    VOS_VOID                               *pstMsg
);

VOS_UINT32 AT_RcvMmaCerssiInfoQueryCnf(VOS_VOID *pstMsg);

/*****************************************************************************
 �� �� ��  : AT_RcvMtaImeiVerifyQryCnf
 ��������  : �յ�IMEIУ���ѯ�Ĵ���
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_RcvMtaImeiVerifyQryCnf(VOS_VOID *pstMsg);
/*****************************************************************************
 �� �� ��  : AT_RcvMtaCgsnQryCnf
 ��������  : �յ�UE��Ϣ�ϱ��Ĵ���
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_RcvMtaCgsnQryCnf(VOS_VOID *pstMsg);


VOS_UINT32 AT_RcvMmaCopnInfoQueryCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMtaSetNCellMonitorCnf(VOS_VOID *pstMsg);
VOS_UINT32 AT_RcvMtaQryNCellMonitorCnf(VOS_VOID *pstMsg);
VOS_UINT32 AT_RcvMtaNCellMonitorInd(VOS_VOID *pstMsg);

VOS_UINT32 AT_RcvMmaSimInsertRsp(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMtaRefclkfreqSetCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMtaRefclkfreqQryCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMtaRefclkfreqInd(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMtaHandleDectSetCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMtaHandleDectQryCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMtaPsTransferInd(VOS_VOID *pMsg);

/*****************************************************************************
 �� �� ��  : AT_RcvSwitchCmdModeMsg
 ��������  : �����˿��л�����ģʽ��Ϣ
 �������  : ucIndex - �˿�������
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_RcvSwitchCmdModeMsg(VOS_UINT8 ucIndex);

VOS_UINT32 AT_RcvMtaEcidSetCnf(VOS_VOID *pMsg);

VOS_UINT32 AT_RcvMtaMipiInfoCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMtaMipiInfoInd(
    VOS_VOID                           *pMsg
);



VOS_UINT32 AT_RcvMmaSysCfgSetCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMmaPhoneModeSetCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMmaDetachCnf(
    VOS_VOID                           *pMsg
);


VOS_UINT32 AT_RcvMtaSetFemctrlCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMtaXpassInfoInd(
    VOS_VOID                           *pMsg
);

extern VOS_UINT32 AT_RcvMmaSrchedPlmnInfoInd(
    VOS_VOID                           *pMsg
);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AtCmdMsgProc.h */
