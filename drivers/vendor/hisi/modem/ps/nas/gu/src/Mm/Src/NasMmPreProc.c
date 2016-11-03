

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MM_Ext.h"
#include "NasMmlCtx.h"







#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MM_PREPORC_C

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_CsNotSupport_PreProc( VOS_VOID )
{
    /* ϵͳ��Ϣ��ָʾCS��֧�֣�MM��idle̬��״̬Ǩ�Ƶ�No cell available */
    if ((MM_IDLE_NORMAL_SERVICE         == g_MmGlobalInfo.ucState)
     || (MM_IDLE_ATTEMPTING_TO_UPDATE   == g_MmGlobalInfo.ucState)
     || (MM_IDLE_LIMITED_SERVICE        == g_MmGlobalInfo.ucState)
     || (MM_IDLE_PLMN_SEARCH            == g_MmGlobalInfo.ucState)
     || (MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState))
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);
    }

    /* �ظ�MMCMM_ATTACH_CNF�Ĳ���,����ȴ�ATTACH�����־λ */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }

    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);


    return;
}


VOS_UINT8 NAS_MM_IsNeedDiscardMmcMmSysInfoInd( VOS_VOID )
{
    /* MM��TC״̬����������MMC��ϵͳ��Ϣ��
       GMM����Gmm_MsgDistribute_GMM_TC_ACTIVE ������������ */
    if (TEST_CONTROL_ACTIVE == g_MmGlobalInfo.ucState)
    {
        return VOS_TRUE;
    }

    /* ͨ���͵ȴ��������̣�������ϵͳ��Ϣ��ת���������ȴ��µ�ϵͳ��Ϣ */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        if ((WAIT_FOR_OUTGOING_MM_CONNECTION            == g_MmGlobalInfo.ucState)
         || (WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucState)
         || (MM_CONNECTION_ACTIVE                       == g_MmGlobalInfo.ucState))
        {
            if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
            {
                Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);

                /* ֪ͨMMC HO SUCC */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE, MM_MMC_LU_RESULT_SUCCESS, NAS_MML_REG_FAIL_CAUSE_HO_SUCC);
            }

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MM_ProcMmcMmSysInfoInd_NoImsi_PreProc( VOS_VOID )
{
    g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS);

    /* �ǿ���̬,������CS����Ч */
    if (VOS_TRUE == NAS_MM_IsIdleState())
    {
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
        g_MmGlobalInfo.ucPreState       = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(MM_IDLE_NO_IMSI);
    }

    Mm_ComCheckDelayMmConn(MM_FALSE);

    return;
}
VOS_UINT8   NAS_MM_RcvMmcMmSysInfoInd_PreProc(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucEventID;

    ucEventID       = 5;

    NAS_MM_LogMmCtxInfo();

    /* ͣMM_TIMER_HO_WAIT_SYSINFO��MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO�Ĵ�����ԭ����ͬ:
       ֻ����CSFB��־����ʱ����ͣ��ʱ��. �����Ҫ��LAU���ȴ�LAU���;�������Ҫ��LAU, MM��ע�������
       ��������²�ͣ��ʱ�����ȶ�ʱ����ʱ */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);

        /* ֪ͨMMC HO SUCC */
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE, MM_MMC_LU_RESULT_SUCCESS, NAS_MML_REG_FAIL_CAUSE_HO_SUCC);
    }

    /* �Ƿ���Ҫ����ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MM_IsNeedDiscardMmcMmSysInfoInd())
    {
        return MM_EVENT_ID_INVALID;
    }

    /* ���ϵͳ��Ϣ�ĺϷ��� */
    if (VOS_FALSE == NAS_MM_CheckMmcMmSysInfoIE(pRcvMsg))
    {
        return MM_EVENT_ID_INVALID;
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        NAS_MM_UpdateNetworkInfo_GasSysInfo(pRcvMsg);
    }
    else
    {
        NAS_MM_UpdateNetworkInfo_WasSysInfo(pRcvMsg);
    }

    if (VOS_TRUE == NAS_MM_IsCsNotSupport(pRcvMsg))
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsNotSupport_PreProc();

        return MM_EVENT_ID_INVALID;
    }

    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_MM_ProcMmcMmSysInfoInd_NoImsi_PreProc();

        return MM_EVENT_ID_INVALID;
    }


    return ucEventID;
}
VOS_UINT8 NAS_MM_RcvMmcCoverageLostInd_PreProc(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucEventID;

    ucEventID       = 21;

    /* ͣMM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO��MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO�Ĵ�����ԭ����ͬ:
       ֻ����CSFB��־����ʱ����ͣ��ʱ��. �����Ҫ��LAU���ȴ�LAU���;�������Ҫ��LAU, MM��ע�������
       ��������²�ͣ��ʱ�����ȶ�ʱ����ʱ */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);
    }

    return ucEventID;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

