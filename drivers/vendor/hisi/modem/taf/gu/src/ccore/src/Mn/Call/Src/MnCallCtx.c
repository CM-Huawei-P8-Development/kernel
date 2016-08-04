


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallCtx.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_MN_CALL_CTX_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* MMC CTX,���ڱ���MMC״̬��,������ */
MN_CALL_CONTEXT_STRU                    g_stMnCallCtx;


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/


MN_CALL_CONTEXT_STRU*  MN_CALL_GetCtx( VOS_VOID )
{
    return &(g_stMnCallCtx);
}


MN_CALL_CUSTOM_CFG_INFO_STRU* MN_CALL_GetCustomCfgInfo( VOS_VOID )
{
    return &(MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg);
}


VOS_UINT8 TAF_CALL_GetAtaReportOkAsyncFlag(VOS_VOID)
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucAtaReportOkAsyncFlag;
}


VOS_VOID TAF_CALL_SetAtaReportOkAsyncFlag(
    VOS_UINT8                           ucAtaReportOkAsyncFlag
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucAtaReportOkAsyncFlag
                           = ucAtaReportOkAsyncFlag;
    return;
}



VOS_UINT32 MN_CALL_GetCallRedialSupportFlg(VOS_VOID)
{
    return (MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.stCallRedialCfg.ucIsCallRedialSupportFlg);
}


MN_CALL_MSG_BUFF_STRU*  MN_CALL_GetBufferedMsg( VOS_VOID )
{
    return &(MN_CALL_GetCtx()->stMnCallBufferedMsg);
}


VOS_VOID MN_CALL_ClearBufferedMsg(VOS_VOID)
{
    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();

    PS_MEM_SET(pstMsgBuff, 0x0, sizeof(MN_CALL_MSG_BUFF_STRU));
    return;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_ENUM_UINT8 enSrvccState)
{
    MN_CALL_GetCtx()->enSrvccState = enSrvccState;
}


MN_CALL_SRVCC_STATE_ENUM_UINT8 TAF_CALL_GetSrvccState(VOS_VOID)
{
    return (MN_CALL_GetCtx()->enSrvccState);
}
#endif


VOS_VOID MN_CALL_InitCtx(VOS_VOID)
{
    PS_MEM_SET(MN_CALL_GetCtx(), 0x0, sizeof(g_stMnCallCtx));

    #if (FEATURE_ON == FEATURE_IMS)    
    TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_BUTT);
    #endif
}




VOS_VOID TAF_CALL_SetCallStatusControl(
    VOS_UINT8                           ucCallStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafCallStatusControl = ucCallStatus;
}


VOS_UINT8 TAF_CALL_GetCallStatusControl( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafCallStatusControl;
}


VOS_VOID TAF_CALL_SetMultiSimCallStatusControl(
    VOS_UINT8                           ucMultiSimCallStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafMultiSimCallStatusControl = ucMultiSimCallStatus;
}


VOS_UINT8 TAF_CALL_GetMultiSimCallStatusControl( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.ucTafMultiSimCallStatusControl;
}



VOS_VOID TAF_CALL_SetVpCfgState(
    MN_CALL_VP_NV_CFG_STATE_ENUM_U8     enVpStateStatus
)
{
    MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.enVpNvCfgState = enVpStateStatus;
}


MN_CALL_VP_NV_CFG_STATE_ENUM_U8 TAF_CALL_GetVpCfgState( VOS_VOID  )
{
    return MN_CALL_GetCtx()->stMsCfgInfo.stCustomCfg.enVpNvCfgState;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



