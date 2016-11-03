

#ifndef __CDS_BST_PROC_H__
#define __CDS_BST_PROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
#if (CDS_FEATURE_ON == CDS_FEATURE_BASTET)
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CDS_BST_HOOK_LEVEL_NONE         ( 0x00U )
#define CDS_BST_HOOK_LEVEL_HEAD         ( 0x01U )
#define CDS_BST_HOOK_LEVEL_FULL         ( 0x02U )
#define CDS_BST_HOOK_LEVEL_FLAGS        ( CDS_BST_HOOK_LEVEL_HEAD )

#define CDS_BST_HOOK_TYPE_NO            ( 0x00U )
#define CDS_BST_HOOK_TYPE_UL            ( 0x01U )
#define CDS_BST_HOOK_TYPE_DL            ( 0x02U )
#define CDS_BST_HOOK_TYPE_FW            ( 0x04U )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
   5 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : CDS_BST_IP_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS_BST_IP_INFO_STRU�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usProtocol;                 /*Э���*/
    VOS_UINT16                          usDstPort;                  /*Ŀ�Ķ˿ں�*/
}CDS_BST_IP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CDS_BST_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS_BST_ENTITY_STRU�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNvFlag;                   /*NV����״̬*/
    VOS_UINT8                           ucHookFlag;                 /*������������*/
    VOS_UINT8                           ucRabId;                    /*Ĭ�ϳ���RAB*/
    VOS_UINT8                           ucRptEnable;                /*�Ƿ������ϱ�����״̬*/
    VOS_UINT16                          usNetState;                 /*��ǰACORE����״̬*/
    VOS_UINT16                          usModemId;                  /*��ǰCDS����MODEM-ID*/
    CDS_BST_RECV_DL_DATA_FUNC           pfRcvDlPacket;              /*BASTET���հ��ص�����*/
    CDS_BST_PORT_CHECK_FUNC             pfPortCheck;                /*BASTETУ��˿�ֵ�ص�*/
}CDS_BST_ENTITY_STRU;

/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/
extern VOS_UINT32 CDS_IsBastetPacket    ( TTF_MEM_ST   *pstIpPkt );
extern VOS_UINT32 CDS_UlProcBastetData  ( VOS_VOID );
extern VOS_VOID   CDS_DlProcBastetData  ( TTF_MEM_ST   *pstSrc,
                                          VOS_UINT8     ucDeftRabId,
                                          VOS_UINT16    usModemId,
                                          VOS_UINT32    ulSduLen );

extern VOS_VOID   CDS_BstSendTxRxInd    ( VOS_VOID );
extern VOS_VOID   CDS_BST_MsgProc       ( MsgBlock *pstMsg );
extern PS_BOOL_ENUM_UINT8   CDS_GetBastetSupportFlag(VOS_VOID);
extern VOS_VOID             CDS_BstInit(VOS_VOID);

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
#endif

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

#endif

