

#include "mailbox.h"
#include "mailbox_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*lint -save -e717*/
/*lint -save -e958*/
/*****************************************************************************
 Prototype      : BSP_MailBox_SpULMsgHeadInit
 Description    : ר�У�Special Mailbox�������������Ϣͷ��ʼ���ӿ�
                  (��ʼ����������ÿ��ԭ�����Ϣͷ���ṩ��Э��ջ����Ҫ���ö��
                  �ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          : 
                ulAddr : ר������ĵ�ַ
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                ucData : ��ʼֵ
 Return Value   None
*****************************************************************************/
void BSP_MailBox_SpULMsgHeadInit(u32 ulAddr,
                                 u32 ulSize,
                                 u8 ucData)
{
    unsigned long key;

    local_irq_save(key);
    memset((void*)ulAddr, ucData, ulSize);
    local_irq_restore(key);
}

/*****************************************************************************
 Prototype      : BSP_MailBox_SpDLMsgHeadInit
 Description    : ר�У�Special Mailbox�������������Ϣͷ��ʼ���ӿ�
                  (��ʼ����������ÿ��ԭ�����Ϣͷ���ṩ��Э��ջ����Ҫ���ö��
                  �ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          : 
                ulAddr : ר������ĵ�ַ
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                ucData : ��ʼֵ
 Return Value   None
*****************************************************************************/
void BSP_MailBox_SpDLMsgHeadInit(u32 ulAddr,
                                 u32 ulSize,
                                 u8 ucData)
{
    unsigned long key;

    local_irq_save(key);
    memset((u8*)ulAddr, ucData, ulSize);
    local_irq_restore(key);
}
/*lint -restore*/

/*****************************************************************************
 Prototype      : MailBox_SpMsgWrite
 Description    : ר������д�ӿڷ�װ
 Input          : 
                ulAddr : ר������ĵ�ַ
                ulSize : ��������С(���ֽ�Ϊ��λ)
                pData  : ������ָ��(��������Ϣͷ��Ϣ)
 Return Value   : 
                0: ��ʾ�����ɹ�
                ����: ��ʾ����ʧ��
*****************************************************************************/
u32 MailBox_SpMsgWrite(u32 ulAddr,
                           u32 ulSize,
                           void* pData)
{
    u32 ret = BSP_OK;
    unsigned long key;

    local_irq_save(key);
    if(*((u32*)ulAddr))
    {
        /* ����Ϊ������ */
        *((u32*)ulAddr) = 0;

        ret = ERR_MAILBOX_COVER;
    }

    memcpy(((u8*)ulAddr + 4), pData, ulSize);

    /* ����ΪDSP���Զ� */
    *((u32*)ulAddr) = 1;

    local_irq_restore(key);

    return ret;
}

/*****************************************************************************
 Prototype      : BSP_MailBox_SpMsgWrite
 Description    : ר�����䣨Special Mailbox����д�ӿ�
                  (�ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          : 
                ulAddr : ר�������ƫ�Ƶ�ַ������Ϣͷ��ʼ�ĵ�ַ��
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                pData  : ������Ϣ(��������Ϣͷ��Ϣ)
 Return Value   : 
                BSP_OK: ��ʾ�����ɹ�
                ERR_MAILBOX_COVER: ��ʾǰһ��ԭ��δ�����ߣ�����
                ERR_MAILBOX_WRITE_FAILED: дʧ��
                ERR_MAILBOX_NOT_INIT: ����δ��ʼ��
                ERR_MAILBOX_PARAM_INCORRECT: ��������
*****************************************************************************/
u32 BSP_MailBox_SpMsgWrite(u32 ulAddr,
                               u32 ulSize,
                               void* pData)
{
    unsigned long key = 0;
    u32 ret = 0;

    if(!(g_stMbxCtrl.bMbxInit))
    {
        g_stMbxMntn.stAbnormal.ulNInitSlic = BSP_GetSliceValue();
        return ERR_MAILBOX_NOT_INIT;
    }

    if((BSP_NULL == pData) || (0 == ulSize))
    {
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    local_irq_save(key);

    ret = MailBox_SpMsgWrite(ulAddr, ulSize, pData);

    local_irq_restore(key);

    return ret;
}


/*****************************************************************************
 Prototype      : MailBox_SpMsgWrite
 Description    : ר��������ӿڷ�װ
 Input          : 
                ulAddr : ר�������ƫ�Ƶ�ַ������Ϣͷ��ʼ�ĵ�ַ��
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                pData  : ������Ϣ(��������Ϣͷ��Ϣ)
 Return Value   : 
                0: ��ʾ�����ɹ�
                ����: ��ʾ����ʧ��
*****************************************************************************/
u32 MailBox_SpMsgRead(u32 ulAddr,
                          u32 ulSize,
                          void* pData)
{
    unsigned long key;

    local_irq_save(key);

    /* ���DSP��˯�ߣ���ʾ������������ */
    /* ���DSPû˯�ߣ������жϱ�֤�����ȵ͹���ģ���DSP���µ紦�� */
    if(BSP_TRUE == BSP_MailBox_IsDspSleep()) /*lint !e746*/
    {
        local_irq_restore(key);
        return ERR_MAILBOX_READ_NULL;
    }

    /* �жϵ�ǰ��Ϣ�Ƿ��Ѷ��� */
    if(0 == *((u32*)ulAddr))
    {
        local_irq_restore(key);
        return ERR_MAILBOX_READ_NULL;
    }

    memcpy(pData, ((u8*)ulAddr + 4), ulSize);

    /* ���ÿ���DSP���Զ� */
    *((u32*)ulAddr) = 0;

    local_irq_restore(key);

    return BSP_OK;
}

/*****************************************************************************
 Prototype      : BSP_MailBox_SpMsgRead
 Description    : ר�����䣨Special Mailbox���Ķ��ӿ�
                  (�ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          : 
                ulAddr : ר�������ƫ�Ƶ�ַ������Ϣͷ��ʼ�ĵ�ַ��
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                pData  : ������Ϣ(��������Ϣͷ��Ϣ)
 Return Value   : 
                BSP_OK: ��ȡ�ɹ�
                ERR_MAILBOX_READ_NULL: ������
                ERR_MAILBOX_NOT_INIT: ����δ��ʼ��
                ERR_MAILBOX_PARAM_INCORRECT: ��������
*****************************************************************************/
u32 BSP_MailBox_SpMsgRead(u32 ulAddr,
                              u32 ulSize,
                              void* pData)
{
    unsigned long key = 0;
    u32 ret = 0;

    if(!(g_stMbxCtrl.bMbxInit))
    {
        g_stMbxMntn.stAbnormal.ulNInitSlic = BSP_GetSliceValue();
        return ERR_MAILBOX_NOT_INIT;
    }

    if((BSP_NULL == pData) || (0 == ulSize))
    {
        return ERR_MAILBOX_PARAM_INCORRECT;
    }

    local_irq_save(key);

    ret = MailBox_SpMsgRead(ulAddr, ulSize, pData);

    local_irq_restore(key);

    return ret;
}

/*****************************************************************************
 Prototype       : BSP_MailBox_SpNotifyReg
 Description     : ר���������ݵ���֪ͨע��ӿ�
 param           : pFun             �������ݵ��ﴦ����
 Return Value    : BSP_OK: �ɹ�
                   ����: ʧ��
*****************************************************************************/
u32 BSP_MailBox_SpNotifyReg(BSP_MBX_NOTIFY_FUNC pFun)
{
    g_stMbxCtrl.pfnSpNotifyProc = pFun;

    return BSP_OK;
}

/*****************************************************************************
 Prototype       : BSP_MailBox_SpNotifyEnable
 Description     : ר���������ݵ���֪ͨ�ж�ʹ�ܽӿ�
 param           : None
 Return Value    : void
*****************************************************************************/
void BSP_MailBox_SpNotifyEnable(void)
{
    if(BSP_OK != BSP_IPC_IntConnect(IPC_INT_DSP_PS_MAC_MBX, (VOIDFUNCPTR)Mbx_SpIntProc, 0))
    {
        Mbx_Printf("BSP_IPC_IntConnect failed.\n");
    }

    if(BSP_OK != BSP_IPC_IntEnable(IPC_INT_DSP_PS_MAC_MBX))
    {
        Mbx_Printf("BSP_IPC_IntEnable failed.\n");
    }
}

/*****************************************************************************
 Prototype       : BSP_MailBox_SpNotifyDisable
 Description     : ר���������ݵ���֪ͨ�ж�ȥʹ�ܽӿ�
 param           : None
 Return Value    : void
*****************************************************************************/
void BSP_MailBox_SpNotifyDisable(void)
{
    if(BSP_OK != BSP_IPC_IntDisable(IPC_INT_DSP_PS_MAC_MBX))
    {
        Mbx_Printf("BSP_IPC_IntDisable failed.\n");
    }

    if(BSP_OK != BSP_IPC_IntDisonnect(IPC_INT_DSP_PS_MAC_MBX, NULL, 0))
    {
        Mbx_Printf("BSP_IPC_IntDisonnect failed.\n");
    }
}


/*****************************************************************************
 Prototype       : Mbx_SpIntProc
 Description     : ר�������жϴ�����
                   (���DSPд�����ͨ�������ж�֪ͨARM��DSPӦ��֤��ARMδ��������ǰ������)
 param           : None
 Return Value    : None
*****************************************************************************/
void Mbx_SpIntProc(void)
{
    MAILBOX_INT_TYPE_E enType;
    
    g_stMbxMntn.stNumber.ulSpIntNum++;

    if(g_stMbxCtrl.pfnSpNotifyProc)
    {
        enType = g_stMbxCtrl.bIsSubFrameInt ? EN_MAILBOX_INT_SUBFRAME : EN_MAILBOX_INT_SP_IPC;
        g_stMbxCtrl.pfnSpNotifyProc(enType);
    }

    return ;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

/* end C file*/
