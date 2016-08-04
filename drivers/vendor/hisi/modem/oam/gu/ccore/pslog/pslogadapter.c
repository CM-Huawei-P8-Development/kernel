
/******************************************************************************

                ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : PsLogAdapter.c
  �� �� ��   : ����
  ��    ��   : ���� 47350
  ��������   : 2008��7��16��
  ����޸�   :
  ��������   : PsLogAdapter���ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��7��16��
    ��    ��   : ���� 47350
    �޸�����   : �����ļ�

*****************************************************************************/
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



#include "pslogadapter.h"
#include "om.h"

/*****************************************************************************
 �� �� ��  : LOG_RegisterDrv
 ��������  : LOG����ӿڣ����ڷ�VxWorksƽ̨��Ч
 �������  : fptr      - ָ���ӡLOG��Ϣ�ĺ���ָ��
 �������  : ��
 �� �� ֵ  : LOG_ERR - ����ʧ��
             LOG_OK  - �����ɹ�

 �޸���ʷ      :
  1.��    ��   : 2008��7��17��
    ��    ��   : ���� 47350
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 LOG_RegisterDrv(LOG_PFUN fptr, LOG_PFUN fptr1, LOG_PFUN fptr2,
                                  LOG_PFUN fptr3, LOG_PFUN fptr4)
{
#if((VOS_OS_VER == VOS_VXWORKS)||(VOS_OS_VER == VOS_RTOSCK))
    return (VOS_UINT32)DRV_LOG_INSTALL((VOIDFUNCPTR)fptr, (VOIDFUNCPTR)fptr1,
             (VOIDFUNCPTR)fptr2, (VOIDFUNCPTR)fptr3, (VOIDFUNCPTR)fptr4);
#else
    return LOG_OK;
#endif
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

