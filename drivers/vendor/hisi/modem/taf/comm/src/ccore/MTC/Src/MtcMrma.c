

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MtcRcmInterface.h"
#include "MtcCtx.h"
#include "MtcDebug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_MTC_MRMA_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

VOS_VOID MTC_SndRcmModemStateInd(VOS_VOID)
{
    MTC_RCM_MODEM_STATE_NOTIFY_STRU    *pstModemState;
    MODEM_ID_ENUM_UINT16                enModemId;

    /* ������Ϣ�� */
    pstModemState = (MTC_RCM_MODEM_STATE_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_MODEM_STATE_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstModemState)
    {
        MTC_ERROR_LOG("MTC_SndRcmModemStateInd: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstModemState) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTC_RCM_MODEM_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    MTC_CFG_RCM_MSG_HDR(&pstModemState->stMsgHeader, ID_MTC_RCM_MODEM_STATUS_NOTIFY);

    /* ��дmodem0��modem1��״̬��Ϣ */
    for (enModemId = 0; enModemId < MODEM_ID_BUTT ; enModemId++)
    {
        pstModemState->astModemState[enModemId].enCsSrvConnState        = MTC_GetCsConnStateInfo(enModemId);
        pstModemState->astModemState[enModemId].enPsSrvConnState        = MTC_GetPsConnStateInfo(enModemId);
        pstModemState->astModemState[enModemId].enModemPowerState       = MTC_GetModemPowerState(enModemId);
        pstModemState->astModemState[enModemId].enUsimmCardState        = MTC_GetUsimmStateInfo(enModemId);
        pstModemState->astModemState[enModemId].enModemType             = MTC_RCM_MODEM_0 + enModemId;
    }

    /* ��дCDMA״̬��Ϣ */
    pstModemState->astModemState[MTC_RCM_MODEM_CDMA].enCsSrvConnState   = MTC_GetOutSideCsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_CDMA].enPsSrvConnState   = MTC_GetOutSidePsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_CDMA].enModemPowerState  = MTC_GetOutSideModemPowerState(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_CDMA].enUsimmCardState   = MTC_GetOutSideModemUsimmState(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_CDMA].enModemType        = MTC_RCM_MODEM_CDMA;

    /* ������Ϣ */
    MTC_SEND_MSG(pstModemState);

    return;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

