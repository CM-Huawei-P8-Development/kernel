

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "om.h"
#include "MnComm.h"

#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasComm.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/

/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MNTN_C
/*lint +e767 */

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

VOS_UINT32   gulNasOTASwitch = NAS_OTA_SWITCH_OFF;

#if (FEATURE_ON == FEATURE_PTM)
/* NASģ��Error Log�쳣����� */
NAS_ERR_LOG_ALM_LEVEL_STRU g_astNasErrAlmLevelTb[] = {
    {NAS_ERR_LOG_ALM_CS_REG_FAIL,       NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PS_REG_FAIL,       NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_SEARCH_NW_FAIL,    NAS_ERR_LOG_CTRL_LEVEL_MAJOR},
    {NAS_ERR_LOG_ALM_CS_CALL_FAIL,      NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PS_CALL_FAIL,      NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_SMS_FAIL,          NAS_ERR_LOG_CTRL_LEVEL_MAJOR},
    {NAS_ERR_LOG_ALM_VC_OPT_FAIL,       NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CS_PAGING_FAIL,    NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,   NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_CSFB_MT_CALL_FAIL, NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_MNTN,              NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_NW_DETACH_IND,     NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL,   NAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
};
#endif

NAS_MNTN_MM_INFO_STRU                   g_stNasMntnErrorLogMm;

extern NAS_MNTN_SM_INFO_STRU            g_stNasMntnErrorlogSm;

NAS_TIMER_EVENT_INFO_STRU               g_stTimerReportCfg;

VOS_UINT32                              g_ulNasTraceLevle  = NAS_TRACE_LEVEL_HIGH;
VOS_UINT32                              g_ulNasTraceOutput = NAS_TRACE_OUTPUT_ASHELL;

/*****************************************************************************
  6 ��������
*****************************************************************************/

/*lint -save -e958 */

NAS_TIMER_EVENT_INFO_STRU* NAS_GetTimerEventReportCfg()
{
    return (&g_stTimerReportCfg);
}


VOS_VOID NAS_TIMER_EventReport(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId
)
{
    VOS_UINT32                ulEventType;
    NAS_TIMER_EVENT_STRU      stNasTimerEvent;

    ulEventType                 = NAS_BuildEventType(ulPid,ulTimerName);
    stNasTimerEvent.usPid       = (VOS_UINT16)ulPid;
    stNasTimerEvent.usTimerName = (VOS_UINT16)ulTimerName;

    if (VOS_TRUE == NAS_IsNeedTimerEventReport(ulEventType))
    {
        NAS_EventReport(ulPid, enEventId, &stNasTimerEvent, sizeof(stNasTimerEvent));
    }
}


VOS_UINT32 NAS_IsNeedTimerEventReport(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT32                          ulI;
    NAS_TIMER_EVENT_INFO_STRU          *pstTimerEventInfo;

    pstTimerEventInfo = NAS_GetTimerEventReportCfg();

    for ( ulI = 0; ulI < pstTimerEventInfo->ulItems; ulI++ )
    {
        if ( ulEventType == pstTimerEventInfo->aulTimerMsg[ulI] )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MNTN_OutputPositionInfo(NAS_MNTN_POSITION_INFO_STRU *pstPositionInfo)
{
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo;

    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    pstPositionInfo->stRai.usRac        = pstCampPlmnInfo->ucRac;

    pstPositionInfo->stRai.usLac        = (VOS_UINT16)(pstCampPlmnInfo->stLai.aucLac[1]
                                                    | (pstCampPlmnInfo->stLai.aucLac[0] << 8));

    /* ����ģʽ:
    #define MMC_NW_MODE_I                     0
    #define MMC_NW_MODE_II                    1
    #define MMC_NW_MODE_III                   2
    */
    /* ����MMC */
    pstPositionInfo->ucNetworkMode      = pstCampPlmnInfo->enNetworkMode;

    /* ��gstMmcCellInfo�л�ȡС����Ϣ�� */
    pstPositionInfo->ulCellId           = pstCampPlmnInfo->stCampCellInfo.astCellInfo[0].ulCellId;

    /* ��g_RrMmSysInfoInd�л�ȡ��ϵͳģʽ��PLMN��Ϣ
    #define     MMC_NET_TYPE_GSM            0
    #define     MMC_NET_TYPE_WCDMA          1
    #define     MMC_NET_TYPE_INVALID        0xff
    */
    pstPositionInfo->enSysSubMode       = pstCampPlmnInfo->enSysSubMode;
    pstPositionInfo->stRai.stPlmn.ulMcc = pstCampPlmnInfo->stLai.stPlmnId.ulMcc;
    pstPositionInfo->stRai.stPlmn.ulMnc = pstCampPlmnInfo->stLai.stPlmnId.ulMnc;

    /* ��g_MmSubLyrShare�л�ȡ���뼼�� */
    pstPositionInfo->ucRat              = pstCampPlmnInfo->enNetRatType;

    return;
}
VOS_VOID NAS_MNTN_RecordPdpActiveFail(
    NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32                       enFailType,
    VOS_UINT8                                                   ucCntxtIndex,
    VOS_UINT8                                                   ucSmCause,
    VOS_UINT8                                                   ucRegisterFlg
)
{
    NAS_MNTN_ACTIVE_FAIL_EVENT_STRU     stPsActiveFailEvent;
    VOS_UINT32                          ulRet;

    /* �ж��Ƿ���Ҫ��¼ */
    if (g_stNasMntnErrorlogSm.ucPdpActiveFailureCounter >= NAS_MNTN_ERRORLOG_ACTIVATE_FAIL_EVENT_MAX)
    {
        NAS_NORMAL_LOG(WUEPS_PID_SM, "NAS_MNTN_RecordPdpActiveFail: counter reach NAS_MNTN_ERRORLOG_SMS_MO_FAILURE_MAX.");
        return;
    }

    PS_MEM_SET(&stPsActiveFailEvent, 0x00, sizeof(stPsActiveFailEvent));

    /* ��д����ʧ���¼���Ϣ */
    /* �洢PDP����ʧ��ֱ��������� */
    stPsActiveFailEvent.stPsActiveFail.enFailType    = enFailType;
    stPsActiveFailEvent.stPsActiveFail.ucSmCause     = ucSmCause;

    /* ��¼PS�����״̬ */
    stPsActiveFailEvent.stPsActiveFail.ucRegisterFlg = ucRegisterFlg;

    NAS_MMA_OutputUsimInfo(&stPsActiveFailEvent.stUsimInfo);

    NAS_MNTN_OutputPositionInfo(&stPsActiveFailEvent.stPositionInfo);

    /* �������ʧ���¼���Ϣ */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_SM,MNTN_NAS_ERRORLOG_ACTIVATE_FAIL_EVENT),
                                &stPsActiveFailEvent,
                                sizeof(stPsActiveFailEvent));
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_MNTN_RecordPdpActiveFail: MNTN_RecordErrorLog fail.");
        return;
    }

    g_stNasMntnErrorlogSm.ucPdpActiveFailureCounter++;

    return;
}


VOS_UINT32 NAS_MNTN_CheckServiceUnavailableEvent(
    NAS_OM_EVENT_ID_ENUM                enEventId
)
{
    /* ���˷�ҵ���ȡʧ���¼�����CS���PS��ҵ���ȡʧ������¼�����VOS_ERR
    �������¼�5���¼���ҵ���ȡʧ���¼� */
    if ((NAS_OM_EVENT_LOCATION_UPDATE_FAILURE != enEventId)
     && (NAS_OM_EVENT_ATTACH_FAIL             != enEventId)
     && (NAS_OM_EVENT_RAU_FAIL                != enEventId)
     && (NAS_OM_EVENT_AUTH_REJECT             != enEventId)
     && (NAS_OM_EVENT_AUTH_AND_CIPHER_REJ     != enEventId))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID NAS_MNTN_RecordServiceUnavailable(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    NAS_MNTN_SERVICE_UNAVAILABLE_EVENT_STRU                 stServiceUnavailableEvent;
    VOS_UINT32                                              ulIsHomePlmn;
    VOS_UINT32                                              ulRet;
    VOS_UINT8                                               ucCause;

    /* ����ܾ�UE��RAU,LAU�����ԭ��ֵ����1���ֽڳ��� */
    if ((VOS_NULL_PTR == pPara) || (1 != ulLen))
    {
        NAS_WARNING_LOG(ulPid, "NAS_MNTN_RecordServiceUnavailable: invalid input para.");
        return;
    }

    /* ����ע��ʧ���޹ص��¼� */
    ulRet = NAS_MNTN_CheckServiceUnavailableEvent(enEventId);
    if (VOS_OK != ulRet)
    {
        return;
    }

    /* ����פ����HOME PLMN�ϵ��޷����¼����м�¼��פ���������粻��¼ */
    ulIsHomePlmn = NAS_MMC_IsRoam();
    if (VOS_TRUE == ulIsHomePlmn)
    {
        return;
    }

    /* ��¼CS���PS��ҵ���ȡʧ��ԭ�� */
    ucCause = *(VOS_UINT8 *)pPara;
    if (WUEPS_PID_MM == ulPid)
    {
        NAS_MM_StoreCsUnavailableInfo(ucCause, &g_stNasMntnErrorLogMm.stCsUnavailableInfo);
    }
    else
    {
        NAS_GMM_StorePsUnavailableInfo(ucCause, &g_stNasMntnErrorLogMm.stPsUnavailableInfo);
    }

    /* �ж��Ƿ���Ҫ��¼�¼� */
    if ((VOS_TRUE != g_stNasMntnErrorLogMm.stCsUnavailableInfo.bRecordRequired)
     && (VOS_TRUE != g_stNasMntnErrorLogMm.stPsUnavailableInfo.bRecordRequired))
    {
        return;
    }

    /* �ж��Ƿ���Ҫ��¼:���������ޣ���ֱ�ӷ��� */
    if (g_stNasMntnErrorLogMm.ucServiceUnavailableCounter >= NAS_MNTN_ERRORLOG_SERVICE_UNAVAILABLE_EVENT_MAX)
    {
        NAS_NORMAL_LOG(ulPid, "NAS_MNTN_RecordServiceUnavailable: counter reach NAS_MNTN_ERRORLOG_SERVICE_UNAVAILABLE_EVENT_MAX.");
        return;
    }

    /* ��д�޷����¼���Ϣ */
    PS_MEM_SET(&stServiceUnavailableEvent, 0x00, sizeof(stServiceUnavailableEvent));

    NAS_MMA_OutputUsimInfo(&stServiceUnavailableEvent.stUsimInfo);

    NAS_MNTN_OutputPositionInfo(&stServiceUnavailableEvent.stPositionInfo);

    PS_MEM_CPY(&stServiceUnavailableEvent.stServiceInfo.stCsUnavailable,
               &g_stNasMntnErrorLogMm.stCsUnavailableInfo,
               sizeof(stServiceUnavailableEvent.stServiceInfo.stCsUnavailable));

    PS_MEM_CPY(&stServiceUnavailableEvent.stServiceInfo.stPsUnavailable,
               &g_stNasMntnErrorLogMm.stPsUnavailableInfo,
               sizeof(stServiceUnavailableEvent.stServiceInfo.stPsUnavailable));

    /* ����޷����¼���Ϣ */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(ulPid,MNTN_NAS_ERRORLOG_SERVICE_UNAVAILABLE_EVENT),
                        &stServiceUnavailableEvent,
                        sizeof(stServiceUnavailableEvent));
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(ulPid, "NAS_MNTN_RecordServiceUnavailable: Error Counter.");
        return;
    }

    /* �������ۼ� */
    g_stNasMntnErrorLogMm.ucServiceUnavailableCounter++;

    /* ����Ѽ�¼��Ϣ */
    if (VOS_TRUE == g_stNasMntnErrorLogMm.stCsUnavailableInfo.bRecordRequired)
    {
        PS_MEM_SET(&g_stNasMntnErrorLogMm.stCsUnavailableInfo,
                   0x00,
                   sizeof(g_stNasMntnErrorLogMm.stCsUnavailableInfo));
    }

    if (VOS_TRUE == g_stNasMntnErrorLogMm.stPsUnavailableInfo.bRecordRequired)
    {
        PS_MEM_SET(&g_stNasMntnErrorLogMm.stPsUnavailableInfo,
                   0x00,
                   sizeof(g_stNasMntnErrorLogMm.stPsUnavailableInfo));
    }

    return;
}


VOS_VOID NAS_MNTN_RecordPlmnUnavailable(
    VOS_UINT8                           ucValIndex,
    VOS_UINT8                           ucCurTimes
)
{
    NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU                        *pstPlmnUnavailableEvent = VOS_NULL_PTR;
    VOS_UINT32                                                   ulRet;
    VOS_UINT32                                                   ulEventLen;
    VOS_UINT32                                                   ulPos;
    VOS_UINT8                                                    ucHighPlmnLen;
    VOS_UINT8                                                    ucLowPlmnLen;
    VOS_UINT8                                                   *pucPlmnAvailable = VOS_NULL_PTR;

    /* �ж��Ƿ���Ҫ��¼:�жϵ�ǰ���������ʱ��ʱ������������ֵ��
       �������������ʱ��ʱ��Ϊ5���5������ʱ��¼ */
    if ((NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_LENGTH_ZERO   != ucValIndex)
     || (NAS_MNTN_AVAILABLE_PLMN_SRCH_TIMER_COUNTER_TIMES != ucCurTimes))
    {
        return;
    }

    /* �жϼ������Ƿ������ */
    if (g_stNasMntnErrorLogMm.ucPlmnUnavailableCounter >= NAS_MNTN_ERRORLOG_PLMN_UNAVAILABLE_EVENT_MAX)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MNTN_RecordPlmnUnavailable: counter reach NAS_MNTN_ERRORLOG_PLMN_UNAVAILABLE_EVENT_MAX.");
        return;
    }

    ucHighPlmnLen = (VOS_UINT8)(g_stNasMntnErrorLogMm.stPlmnAvailableList.ulHighPlmnNum * sizeof(MNTN_PLMN_ID_STRU));
    ucLowPlmnLen  = (VOS_UINT8)(g_stNasMntnErrorLogMm.stPlmnAvailableList.ulLowPlmnNum * sizeof(NAS_MNTN_LOW_PLMN_INFO_STRU));
    /* ����PLMN�б�ĳ��Ȳ���NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU�ṹ�м���
       aucPlmnAttempt[4]ռ�õ�4���ֽ���Ҫ��ȥ���� */
    ulEventLen = (sizeof(NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU) - 4)
                  + ((sizeof(ucHighPlmnLen) + ucHighPlmnLen)
                  + (sizeof(ucLowPlmnLen) + ucLowPlmnLen));

    pstPlmnUnavailableEvent = (NAS_MNTN_PLMN_UNAVAILABLE_EVENT_STRU *)PS_MEM_ALLOC(
                                WUEPS_PID_MMC, ulEventLen);
    if (VOS_NULL_PTR == pstPlmnUnavailableEvent)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MNTN_RecordPlmnUnavailable: Fail to alloc memory.");
        return;
    }

    /* ��д����ʧ���¼���Ϣ */
    PS_MEM_SET(pstPlmnUnavailableEvent, 0x00, ulEventLen);

    NAS_MMA_OutputUsimInfo(&pstPlmnUnavailableEvent->stUsimInfo);

    NAS_MNTN_OutputPositionInfo(&pstPlmnUnavailableEvent->stPositionInfo);

    NAS_MMA_OutputPlmnSrchBand(&pstPlmnUnavailableEvent->ulBand);

    pucPlmnAvailable = pstPlmnUnavailableEvent->aucPlmnAttempt;
    ulPos            = 0;

    /* ��д������PLMN���ݽṹ: LV��ʽ��V���ֽṹΪMNTN_PLMN_ID_STRU */
    *(pucPlmnAvailable + ulPos) = ucHighPlmnLen;
    ulPos++;

    PS_MEM_CPY((pucPlmnAvailable + ulPos),
                g_stNasMntnErrorLogMm.stPlmnAvailableList.astHighPlmnList,
                ucHighPlmnLen);
    ulPos += ucHighPlmnLen;

    /* ��д������PLMN���ݽṹ: LV��ʽ��V���ֽṹΪNAS_MNTN_LOW_PLMN_INFO_STRU */
    *(pucPlmnAvailable + ulPos) = ucLowPlmnLen;
    ulPos++;

    PS_MEM_CPY((pucPlmnAvailable + ulPos),
                g_stNasMntnErrorLogMm.stPlmnAvailableList.astLowPlmnList,
                ucLowPlmnLen);

    /* �������ʧ���¼���Ϣ */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_MMC, MNTN_NAS_ERRORLOG_PLMN_UNAVAILABLE_EVENT),
                         pstPlmnUnavailableEvent, ulEventLen);
    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnUnavailableEvent);

    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MNTN_RecordPlmnUnavailable: fail to MNTN_RecordErrorLog.");
        return;
    }

    /* �¼��������ۼ� */
    g_stNasMntnErrorLogMm.ucPlmnUnavailableCounter++;

    return;
}
VOS_VOID NAS_EventReport(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    PS_OM_EVENT_IND_STRU*               pstEvent;

    VOS_VOID                           *pData = pPara;
    VOS_UINT32                          ulRslt;

    if ((VOS_NULL_PTR == pData) && (ulLen > 0))
    {
        /* �����ӡ */
        PS_LOG(ulPid, VOS_NULL, PS_PRINT_WARNING, "NAS_EventReport:pPara is NULL.");
        return;
    }

    if (4 < ulLen)
    {
        pstEvent = (PS_OM_EVENT_IND_STRU*)PS_MEM_ALLOC(ulPid,
                              ((sizeof(PS_OM_EVENT_IND_STRU)-4)+ulLen));
    }
    else
    {
        pstEvent = (PS_OM_EVENT_IND_STRU*)PS_MEM_ALLOC(ulPid,
                              sizeof(PS_OM_EVENT_IND_STRU));
    }
    if (VOS_NULL_PTR == pstEvent)
    {
        PS_LOG(ulPid, VOS_NULL, PS_PRINT_WARNING, "NAS_EventReport:Alloc mem fail.");
        return;
    }
    PS_MEM_SET(pstEvent->aucData, 0x0, ((ulLen>4)?ulLen:4));

    /* ulLength ָ��usEventId��ʼ����β�ĳ��� */
    pstEvent->ulLength        = 8 + ulLen;
    pstEvent->usEventId       = (VOS_UINT16)enEventId;
    pstEvent->usReserved      = 0x0;
    pstEvent->ulModuleId      = ulPid;

    /* ulLen>0ʱ��ͨ����������pPara������Ϊ��ָ�� */
    if (VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY(pstEvent->aucData, pData, pstEvent->ulLength-8);
    }

    ulRslt = OM_Event(pstEvent);
    if (VOS_OK != ulRslt)
    {
        /* �����ӡ */
        PS_LOG(ulPid, VOS_NULL, PS_PRINT_WARNING, "NAS_EventReport:OM_Event fail.");
    }

    PS_MEM_FREE(ulPid, pstEvent);

    NAS_MNTN_RecordServiceUnavailable(ulPid, enEventId, pPara, ulLen);

    return;
}


VOS_VOID NAS_SendAirMsgToOM(
    VOS_UINT32                          ulPid,
    VOS_UINT16                          usMsgID,
    VOS_UINT8                           ucUpDown,
    VOS_UINT32                          ulMsgLen,
    VOS_UINT8                          *pucMsg
)
{
    NAS_OM_OTA_IND_STRUCT              *pstNasOtaInd = VOS_NULL_PTR;
    VOS_UINT32                          ulNasOtaIndLen;
    VOS_UINT8                          *pucMsgForPcLint;

    MODEM_ID_ENUM_UINT16       enModemId;

    PS_LOG(ulPid, VOS_NULL, PS_PRINT_NORMAL, "NAS_SendAirMsgToOM!");

    /* ��ڲ������ */
    /* ���տ���Ϣ����Ϊ 0 ���� �տ���Ϣָ��Ϊ��ʱ���쳣���� */
    if ( (0 == ulMsgLen)
        || (VOS_NULL_PTR == pucMsg ))
    {
        PS_LOG(ulPid, VOS_NULL, PS_PRINT_WARNING, "NAS_SendAirMsgToOM:WARNING: Input params invalid.");
        return;
    }

    pucMsgForPcLint = pucMsg;

    /* �������Ҫ�ϱ��տ���Ϣ����ֱ�ӷ��� */
    if ( NAS_OTA_SWITCH_OFF == gulNasOTASwitch )
    {
        return;
    }

    /* ������ϱ��Ŀտ���Ϣ�ռ� */
    ulNasOtaIndLen  = (sizeof(NAS_OM_OTA_IND_STRUCT) + ulMsgLen) - NAS_OM_DATA_PTR_LEN;
    pstNasOtaInd = (NAS_OM_OTA_IND_STRUCT *)PS_MEM_ALLOC(ulPid, ulNasOtaIndLen);

    if ( VOS_NULL_PTR == pstNasOtaInd )
    {
        PS_LOG(ulPid, VOS_NULL, PS_PRINT_WARNING, "NAS_SendAirMsgToOM:WARNING: Alloc mem fail.");
        return;
    }

    /* ��� �� OM��͸����Ϣ */
    PS_MEM_SET(pstNasOtaInd, 0, ulNasOtaIndLen);

    enModemId   =   VOS_GetModemIDFromPid(WUEPS_PID_MMC);
    pstNasOtaInd->ucFuncType        = ((enModemId << 6) & NAS_OM_FUNCTION_TYPE_MODEM_MASK) \
                                    | (OM_AIR_FUNC & NAS_OM_FUNCTION_TYPE_VALUE_MASK);

    pstNasOtaInd->usLength          = (VOS_UINT16)(ulNasOtaIndLen - 4);
    OM_AddSNTime( &(pstNasOtaInd->ulSn), &(pstNasOtaInd->ulTimeStamp) );

    pstNasOtaInd->usPrimId          = NAS_OM_OTA_IND;
    pstNasOtaInd->usOtaMsgID        = usMsgID;
    pstNasOtaInd->ucUpDown          = ucUpDown;
    pstNasOtaInd->ulLengthASN       = ulMsgLen;

    PS_MEM_CPY(pstNasOtaInd->aucData, pucMsgForPcLint, ulMsgLen);

    OM_SendData((OM_RSP_PACKET_STRU*)pstNasOtaInd,(VOS_UINT16)ulNasOtaIndLen);
    PS_MEM_FREE(ulPid,pstNasOtaInd);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_SetNasOtaSwitch
 ��������  : ����OTA�Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��22��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_SetNasOtaSwitch(
    VOS_UINT32                          ulNasOTASwitch
)
{
    gulNasOTASwitch = ulNasOTASwitch;
}

/*****************************************************************************
 �� �� ��  : NAS_GetNasOtaSwitch
 ��������  : ����OTA�Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��22��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GetNasOtaSwitch(VOS_VOID)
{
    return gulNasOTASwitch;
}

#if (FEATURE_ON == FEATURE_PTM)

VOS_UINT16 NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_ID_ENUM_U16 enAlmId)
{
    VOS_UINT16                          usTableLen;
    VOS_UINT16                          usStep;

    /* ��ȡTab���� */
    usTableLen = sizeof(g_astNasErrAlmLevelTb)/sizeof(g_astNasErrAlmLevelTb[0]);

    /* ����ض�ӦAlm ID��log�ȼ� */
    for (usStep = 0; usStep < usTableLen; usStep++)
    {
        if (g_astNasErrAlmLevelTb[usStep].enAlmID == enAlmId)
        {
            return g_astNasErrAlmLevelTb[usStep].usLogLevel;
        }
    }

    /* δ�鵽������δ����ȼ� */
    return NAS_ERR_LOG_CTRL_LEVEL_NULL;
}
VOS_VOID NAS_COM_MntnPutRingbuf(
    VOS_UINT32                          ulName,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen
)
{
    NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                           ulMsgLen;
    /*lint -e961*/
    ulMsgLen = sizeof(NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU) - 4 + ulLen;
    /*lint +e961*/

    pstMsg = (NAS_ERR_LOG_MNTN_PUT_BUF_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, ulMsgLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_MntnPutRingbuf:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0, ulMsgLen);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = ulPid;
    pstMsg->ulReceiverPid               = ACPU_PID_OM;
    pstMsg->ulLength                    = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgName                   = ulName;

    /* ��ָ�뱣�� */
    if (VOS_NULL_PTR != pucData)
    {
        PS_MEM_CPY(pstMsg->aucContent, pucData, ulLen);
    }

    OM_TraceMsgHook(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}

#endif
VOS_VOID NAS_MNTN_SndLogMsg(VOS_CHAR *pcData, VOS_UINT32 ulDataLength)
{
    TAF_MNTN_LOG_PRINT_STRU            *pstMsg;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulRet;

    /* ��Ϣ���� = sizeof(TAF_MNTN_LOG_PRINT_STRU) - 4 + ����ʵ�ʳ��� + �ַ���������'\0' */
    /*lint -e961*/
    ulMsgLength = sizeof(TAF_MNTN_LOG_PRINT_STRU) - 4 + ulDataLength + 1;
    /*lint +e961*/

    /* ������Ϣ */
    pstMsg = (TAF_MNTN_LOG_PRINT_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                WUEPS_PID_TAF,
                                ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               ulMsgLength - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ulMsgName       = MN_CALLBACK_LOG_PRINT;

    PS_MEM_CPY(pstMsg->acLog, pcData, ulDataLength);
    pstMsg->acLog[ulDataLength] = '\0';

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);
    if (VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MNTN_SndLogMsg:ERROR:Snd Msg Fail.");
    }
    return;
}


/*lint -esym(960,69)*/
VOS_VOID NAS_MNTN_LogPrintf(VOS_CHAR *pcFmt, ...)
{
    VOS_CHAR                            acBuf[NAS_TRACE_BUF_LEN] = {0};
    VOS_UINT32                          ulPrintLength = 0;

    /* ��ʽ�����BUFFER */
    /*lint -e530 -e830*/
    NAS_MNTN_LOG_FORMAT(ulPrintLength, acBuf, NAS_TRACE_BUF_LEN, pcFmt);
    /*lint +e530 +e830*/

    /* ѡ�����ASEHLL��CSHELL */
    if (NAS_TRACE_OUTPUT_ASHELL == (NAS_TRACE_OUTPUT_ASHELL & g_ulNasTraceOutput))
    {
        NAS_MNTN_SndLogMsg(acBuf, ulPrintLength);
    }

    if (NAS_TRACE_OUTPUT_CSHELL == (NAS_TRACE_OUTPUT_CSHELL & g_ulNasTraceOutput))
    {
        vos_printf("%s", acBuf);
    }

    return;
}
/*lint +esym(960,69)*/


VOS_VOID NAS_MNTN_SetTraceLevel(VOS_UINT32 ulLvl)
{
    g_ulNasTraceLevle = (ulLvl >= NAS_TRACE_LEVEL_TOP) ? NAS_TRACE_LEVEL_TOP : ulLvl;
    return;
}


VOS_VOID NAS_MNTN_SetTraceOutput(VOS_UINT32 ulOutput)
{
    g_ulNasTraceOutput = (ulOutput >= NAS_TRACE_OUTPUT_ALL) ? NAS_TRACE_LEVEL_TOP : ulOutput;
    return;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

