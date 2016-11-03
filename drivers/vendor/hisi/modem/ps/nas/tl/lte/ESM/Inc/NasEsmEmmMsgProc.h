

#ifndef _NASESMEMMMSGPROC_H
#define _NASESMEMMMSGPROC_H


/*****************************************************************************
  1 ÆäËûÍ·ÎÄ¼þ°üº¬
*****************************************************************************/
#include    "vos.h"
#include    "NasEsmPublic.h"
#include    "LnasErrlogInterface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    ÉèÖÃ×Ö½Ú¶ÔÆë·½Ê½
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define ESM_MAX_SND_MSG_LEN              (256)               /*¿Õ¿ÚÏûÏ¢Õ¼ÓÃµÄ×î´ó¿Õ¼ä*/
#define ESM_MIN_SND_MSG_LEN              (4)                 /*¿Õ¿ÚÏûÏ¢Õ¼ÓÃµÄ×îÐ¡¿Õ¼ä*/
#define ESM_MAX_MSG_CONTAINER_CNTNTS_LEN (1024)              /*ESM message container contents×î´ó³¤¶È*/

#define NAS_ESM_COMM_BULID_ERRLOG_HEADER_INFO(pstHeader, ModemId, AlmId, AlmLevel, ulSlice, ulLength) \
{ \
    (pstHeader)->ulMsgModuleId     = OM_ERR_LOG_MOUDLE_ID_LMM; \
    (pstHeader)->usModemId         = ModemId; \
    (pstHeader)->usAlmId           = AlmId; \
    (pstHeader)->usAlmLevel        = AlmLevel; \
    (pstHeader)->usAlmType         = EMM_OM_ERRLOG_ALM_TYPE_COMMUNICATION; \
    (pstHeader)->ulAlmLowSlice     = ulSlice; \
    (pstHeader)->ulAlmHighSlice    = 0; \
    (pstHeader)->ulAlmLength       = ulLength; \
}

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

typedef struct
{
    NAS_ESM_CAUSE_ENUM_UINT8            ulEsmCnCasue;
    ESM_OM_ERRLOG_ID_ENUM_UINT16        ulEsmErrId;
}NAS_ESM_CN_CAUSE_TRANS_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_ESM_EmmMsgDistr( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_RcvEmmDetachMsg( VOS_VOID );
extern VOS_VOID NAS_ESM_RcvEsmEmmBearerStatusInd(const EMM_ESM_BEARER_STATUS_IND_STRU *pRcvMsg );
extern VOS_VOID NAS_ESM_RcvEsmEmmDataInd( EMM_ESM_DATA_IND_STRU *pRcvMsg );
extern VOS_VOID NAS_ESM_RcvEsmEmmEstCnf(const EMM_ESM_EST_CNF_STRU *pRcvMsg );
extern VOS_VOID NAS_ESM_RcvEsmEmmPdnConInd(const EMM_ESM_PDN_CON_IND_STRU *pRcvMsg );
extern VOS_VOID NAS_ESM_RcvEsmEmmStatusInd(const EMM_ESM_STATUS_IND_STRU *pRcvMsg );
extern VOS_VOID NAS_ESM_RcvEsmEmmDeactAllNonEmcBearerInd(VOS_VOID);
extern VOS_VOID NAS_ESM_SndEsmEmmBearerStatusReqMsg(
                    EMM_ESM_BEARER_CNTXT_MOD_ENUM_UINT32 enBearerCntxtChangeMod);
extern VOS_VOID  NAS_ESM_SndEsmEmmDataReqMsg( VOS_UINT32 ulOpId,
                                                VOS_UINT8  ulIsEmcPdnType,
                                                VOS_UINT32 ulLength,
                                                const VOS_UINT8 *pucSendMsg);
extern VOS_VOID NAS_ESM_SndEsmEmmEstReqMsg(VOS_UINT32 ulOpId,
                                             VOS_UINT8 ulIsEmcPdnType,
                                             VOS_UINT32 ulLength,
                                             const VOS_UINT8 *pucSendMsg);
extern VOS_VOID NAS_ESM_SndEsmEmmPdnConRspMsg( EMM_ESM_PDN_CON_RSLT_ENUM_UINT32        ulRst,
                                                                 VOS_UINT32 ulLength, const VOS_UINT8 *pucSendMsg);
extern VOS_VOID NAS_ESM_SndEsmEmmRelReqMsg( VOS_VOID );
extern VOS_VOID  NAS_ESM_ClearStateTable( VOS_UINT32 ulAppErrType, VOS_UINT32 ulKeepEmc );
extern VOS_VOID  NAS_ESM_SndEsmEmmPdnConSuccReqMsg
(
     VOS_UINT32                         ulLength,
     const VOS_UINT8                   *pucSendMsg
);
extern VOS_VOID  NAS_ESM_BufferDecodedNwMsg
(
    const EMM_ESM_INTRA_DATA_IND_STRU  *pstEmmEsmIntraDataIndMsg,
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause
);
extern VOS_VOID NAS_ESM_BufferedNwMsgProc();
extern VOS_VOID  NAS_ESM_RcvEsmEmmSuspendInd(const EMM_ESM_SUSPEND_IND_STRU *pRcvMsg );
extern VOS_VOID  NAS_ESM_RcvEsmEmmResumeInd(const EMM_ESM_RESUME_IND_STRU *pRcvMsg );
extern VOS_VOID NAS_ESM_SndEsmEmmSuspendRsp
(
    EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt
);
extern VOS_VOID NAS_ESM_SndEsmEmmResumeRsp
(
    EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt
);

extern VOS_VOID  NAS_ESM_ProcPfPrecedenceCollision
(
    const NAS_ESM_NW_MSG_STRU                *pstNwMsg
);
extern VOS_UINT32  NAS_ESM_IsNeedPreferrenceCollision
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
);
/*leili modify for isr begin*/
extern VOS_VOID NAS_ESM_SndEsmEmmBearerModifyReq( VOS_UINT32 ulEpsId);
/*leili modify for isr end*/
extern VOS_UINT32 NAS_ESM_GetRegistCid( VOS_VOID );
extern VOS_VOID NAS_ESM_ReestablishAttachBearer( VOS_VOID );

extern VOS_VOID NAS_ESM_SndEsmEmmClrEsmProcResNtyMsg(VOS_UINT32 ulOpId, VOS_UINT8 ucIsEmcPdnType);

extern VOS_VOID  NAS_ESM_PdnConRejRecord(const EMM_ESM_INTRA_DATA_IND_STRU *pstEmmEsmDataInd);
extern VOS_VOID  NAS_ESM_PdnDisconRejRecord(const EMM_ESM_INTRA_DATA_IND_STRU *pstEmmEsmDataInd);
extern VOS_VOID  NAS_ESM_ResModRejRecord(const EMM_ESM_INTRA_DATA_IND_STRU *pstEmmEsmDataInd);
extern VOS_VOID  NAS_ESM_ResAllocRejRecord(const EMM_ESM_INTRA_DATA_IND_STRU *pstEmmEsmDataInd);
extern VOS_VOID NAS_ESM_SndEsmErrlogToEmm(
                 VOS_VOID     *pstEsmErrRslt,  VOS_UINT32   ulEsmErrLength);
extern ESM_OM_ERRLOG_ID_ENUM_UINT16  NAS_ESM_CnCauseProc(VOS_UINT8 ucCnCause);


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

#endif /* end of NasEsmEmmMsgProc.h*/
