

/*****************************************************************************
  1 ͷ�ļ�����
**************************************************************************** */
#include "CbtCpm.h"
#include "cpm.h"
#include "SCMSoftDecode.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* lint -e767  */
#define    THIS_FILE_ID        PS_FILE_ID_CBT_CPM_C
/* lint +e767  */

/* ****************************************************************************
  2 ȫ�ֱ�������
**************************************************************************** */
CBTCPM_RCV_FUNC                g_pCbtRcvFunc = VOS_NULL_PTR;
CBTCPM_SEND_FUNC               g_pCbtSndFunc = VOS_NULL_PTR;

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/

extern VOS_UINT32 CBTSCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/


VOS_VOID CBTCPM_PortRcvReg(CBTCPM_RCV_FUNC pRcvFunc)
{
    g_pCbtRcvFunc = pRcvFunc;

    return;
}


VOS_VOID CBTCPM_PortSndReg(CBTCPM_SEND_FUNC pSndFunc)
{
    g_pCbtSndFunc = pSndFunc;

    return;
}


CBTCPM_RCV_FUNC CBTCPM_GetRcvFunc(VOS_VOID)
{
    return g_pCbtRcvFunc;
}


CBTCPM_SEND_FUNC CBTCPM_GetSndFunc(VOS_VOID)
{
    return g_pCbtSndFunc;
}


VOS_UINT32 CBTCPM_NotifyChangePort(AT_PHY_PORT_ENUM_UINT32 enPhyPort)
{
    /* NAS��UART����У׼ */
    if (CPM_IND_PORT > enPhyPort)
    {
        /* ��AT��÷������ݵĺ���ָ�� */
        CBTCPM_PortSndReg(AT_QuerySndFunc(enPhyPort));

        /* ��AT�Ķ˿���У׼������USB��VCOM�������� */
        CBTCPM_PortRcvReg(VOS_NULL_PTR);

        /* ��У׼ͨ���Ľ��պ�����ATģ�� */
        AT_RcvFuncReg(enPhyPort, CBTSCM_SoftDecodeDataRcv);

        return VOS_OK;
    }

    return VOS_ERR;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif




