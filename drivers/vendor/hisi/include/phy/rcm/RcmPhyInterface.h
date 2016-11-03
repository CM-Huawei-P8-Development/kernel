

#ifndef __RCMPHYINTERFACE_H__
#define __RCMPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"

#ifndef LPS_RTT
#include "vos.h"
#include "phyoaminterface.h"
#else
#define VOS_MSG_HEADER
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*���֧�ֵ�RF��Ŀ*/
#define RCM_RF_SUPPORT_NUM                      ( RCM_RF_ID_BUTT )

/*���֧�ֵ�PHY mode��Ŀ*/
#define RCM_MODE_SUPPORT_NUM                    ( RCM_MODE_ID_BUTT )

/*���֧�ֵ�MODEM��Ŀ*/
#define RCM_MODEM_SUPPORT_NUM                   ( RCM_MODEM_ID_BUTT )

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : RCM_PHY_MSG_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : RCM <-> PHY �ӿ���ϢID
*****************************************************************************/
enum RCM_PHY_MSG_ID_ENUM
{
    ID_PHY_RCM_START_TAS_CNF                = 0x180e,                           /* _H2ASN_MsgChoice PHY_RCM_START_TAS_CNF_STRU */
    ID_PHY_RCM_STOP_TAS_CNF                 = 0x180f,                           /* _H2ASN_MsgChoice PHY_RCM_STOP_TAS_CNF_STRU */
    ID_PHY_RCM_SET_DPDT_CNF                 = 0x1810,                           /* _H2ASN_MsgChoice PHY_RCM_SET_DPDT_CNF_STRU */
    ID_PHY_RCM_TX_BLANKING_IND              = 0x1811,                           /* _H2ASN_MsgChoice PHY_RCM_TX_BLANKING_IND_STRU */
    ID_PHY_RCM_RATMODE_IND                  = 0x1812,                           /* _H2ASN_MsgChoice PHY_RCM_RATMODE_IND_STRU */
    ID_MSP_RCM_MAILBOX_READ_IND             = 0x1813,                           /* _H2ASN_MsgChoice RCM_PHY_MSG_HEADER_STRU */
    ID_PHY_RCM_ACCESS_STATE_IND             = 0x1814,                           /* _H2ASN_MsgChoice PHY_RCM_ACCESS_STATE_IND_STRU */
    ID_PHY_RCM_SEARCHING_STATE_IND          = 0x1815,                           /* _H2ASN_MsgChoice PHY_RCM_SEARCHING_STATE_IND_STRU */
    ID_PHY_RCM_SIGNAL_STATE_IND             = 0x1816,                           /* _H2ASN_MsgChoice PHY_RCM_SIGNAL_STATE_IND_STRU */
    ID_PHY_RCM_IDLE_HAPPY_IND               = 0x1817,                           /* _H2ASN_MsgChoice PHY_RCM_IDLE_HAPPY_IND_STRU */
                                                                                /* 0x1818�Ѿ������MTC -> RCM messageʹ�� */
    ID_PHY_RCM_VOICE_CALL_STATE_IND         = 0x1819,                           /* _H2ASN_MsgChoice PHY_RCM_VOICE_CALL_STATE_IND_STRU */
    ID_PHY_RCM_SEARCHING_STATE_REQ          = 0x181a,                           /* _H2ASN_MsgChoice PHY_RCM_SEARCHING_STATE_REQ_STRU */
                                                                                /* 0x181b,0x181c�Ѿ������CMMCA -> RCM messageʹ�� */
    ID_PHY_RCM_AGENT_SET_DPDT_CNF           = 0x181d,                           /* _H2ASN_MsgChoice PHY_RCM_AGENTC_SET_DPDT_CNF_STRU */

    ID_RCM_PHY_START_TAS_REQ                = 0x188e,                           /* _H2ASN_MsgChoice RCM_PHY_START_TAS_REQ_STRU */
    ID_RCM_PHY_STOP_TAS_REQ                 = 0x188f,                           /* _H2ASN_MsgChoice RCM_PHY_STOP_TAS_REQ_STRU */
    ID_RCM_PHY_SET_DPDT_REQ                 = 0x1890,                           /* _H2ASN_MsgChoice RCM_PHY_SET_DPDT_REQ_STRU */
    ID_RCM_PHY_TX_BLANKING_IND              = 0x1891,                           /* _H2ASN_MsgChoice RCM_PHY_TX_BLANKING_IND */
    ID_RCM_PHY_SEARCHING_STATE_CNF          = 0x1892,                           /* _H2ASN_MsgChoice RCM_PHY_SEARCHING_STATE_CNF_STRU */
    ID_RCM_PHY_AGENT_SET_DPDT_REQ           = 0x1893,                           /* _H2ASN_MsgChoice RCM_PHY_AGENTC_SET_DPDT_REQ_STRU */

    ID_RCM_PHY_MSG_BUTT

};
typedef VOS_UINT16 RCM_PHY_MSG_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_MODE_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �����ģʽ��ʾ ���д����У׼����һ��
*****************************************************************************/
enum RCM_MODE_ID_ENUM
{
    RCM_LTE                             = 0,                                    /* LTE */
    RCM_WCDMA                           = 1,                                    /* WCDMA */
    RCM_1X                              = 2,                                    /* 1X */
    RCM_HRPD                            = 3,                                    /* HRPD */
    RCM_TD                              = 4,                                    /* TD */
    RCM_G0                              = 5,                                    /* G0 */
    RCM_G1                              = 6,                                    /* G1 */
    RCM_G2                              = 7,                                    /* G2 */
    RCM_MODE_ID_BUTT
};
typedef VOS_UINT16  RCM_MODE_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_MODEM_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : MODEM ID
*****************************************************************************/
enum RCM_MODEM_ID_ENUM
{
    RCM_MODEM_1                         = 0,                                    /* MODEM0 */
    RCM_MODEM_2                         = 1,                                    /* MODEM1 */
    RCM_MODEM_3                         = 2,                                    /* MODEM2 */
    RCM_MODEM_ID_BUTT
};
typedef VOS_UINT16  RCM_MODEM_ID_ENUM_UINT16;


/*****************************************************************************
 ö����    : RCM_STOP_TAS_TYPE_ENUM_UINT16
 ö��˵��  : RCMȡ�������TAS��Ȩ��ʽ
             0:�ر�TAS���������л�PHYĬ��̬
             1:��ͣTAS�������߱����ڵ�ǰ״̬
*****************************************************************************/
enum RCM_STOP_TAS_TYPE_ENUM
{
    RCM_STOP_TAS_TYPE_STOP                = 0,
    RCM_STOP_TAS_TYPE_KEEP                = 1,
    RCM_STOP_TAS_TYPE_BUTT
};
typedef VOS_UINT16 RCM_STOP_TAS_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_CONNECT_STATE_ENUM_UINT16
 ö��˵��  : modemҵ������״̬
             0:������״̬
             1:����״̬
*****************************************************************************/
enum RCM_TAS_CONNECT_STATE_ENUM
{
    RCM_TAS_CONNECT_NO_EXIST             = 0,
    RCM_TAS_CONNECT_EXIST                = 1,
    RCM_TAS_CONNECT_BUTT
};
typedef VOS_UINT16 RCM_TAS_CONNECT_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_POWER_STATE_ENUM_UINT16
 ö��˵��  : modem_power���µ�״̬���Ƿ��ڷ���ģʽ
             0:�µ缴����ģʽ
             1:�ϵ缴�Ƿ���ģʽ
*****************************************************************************/
enum RCM_TAS_POWER_STATE_ENUM
{
    RCM_TAS_POWER_STATE_OFF           = 0,
    RCM_TAS_POWER_STATE_ON            = 1,
    RCM_TAS_POWER_STATE_BUTT
};
typedef VOS_UINT16 RCM_TAS_POWER_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_ACCESS_STATE_ENUM_UINT16
 ö��˵��  : modem����״̬
             0:�ǽ���״̬
             1:����״̬
*****************************************************************************/
enum RCM_ACCESS_STATE_ENUM
{
    RCM_ACCESS_STATE_NON_ACCESS   = 0,
    RCM_ACCESS_STATE_ACCESS       = 1,
    RCM_ACCESS_STATE_UNHAPPY      = 2,
    RCM_ACCESS_STATE_BUTT
};
typedef VOS_UINT16 RCM_ACCESS_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_SEARCHING_STATE_ENUM_UINT16
 ö��˵��  : modem��Ѱ״̬
             0:����Ѱ״̬
             1:��Ѱ״̬
*****************************************************************************/
enum RCM_SEARCHING_STATE_ENUM
{
    RCM_SEARCHING_STATE_NON_SEARCH    = 0,
    RCM_SEARCHING_STATE_SEARCH        = 1,
    RCM_SEARCHING_STATE_BUTT
};
typedef VOS_UINT16 RCM_SEARCHING_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_SIGNAL_STATE_ENUM_UINT16
 ö��˵��  : modemѶ��״̬
             0:Ѷ��POOR״̬
             1:Ѷ��GOOD״̬
*****************************************************************************/
enum RCM_SIGNAL_STATE_ENUM
{
    RCM_SIGNAL_STATE_POOR         = 0,
    RCM_SIGNAL_STATE_GOOD         = 1,
    RCM_SIGNAL_STATE_BUTT
};
typedef VOS_UINT16 RCM_SIGNAL_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_IDLE_HAPPY_ENUM_UINT16
 ö��˵��  : modem Idle Happy״̬
             0:Idle Unhappy״̬
             1:Idle Happy״̬
*****************************************************************************/
enum RCM_IDLE_HAPPY_ENUM
{
    RCM_IDLE_HAPPY_UNHAPPY        = 0,
    RCM_IDLE_HAPPY_HAPPY          = 1,
    RCM_IDLE_HAPPY_BUTT
};
typedef VOS_UINT16 RCM_IDLE_HAPPY_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_VOICE_CALL_STATE_ENUM_UINT16
 ö��˵��  : modem Background or Active Call״̬
             0:Active Call״̬
             1:Background Call״̬
*****************************************************************************/
enum RCM_VOICE_CALL_STATE_ENUM
{
    RCM_VOICE_CALL_ACTIVE           = 0,
    RCM_VOICE_CALL_BACKGROUND       = 1,
    RCM_VOICE_CALL_BUTT
};
typedef VOS_UINT16 RCM_VOICE_CALL_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_DPDT_CONTROL_ENUM_UINT16
 ö��˵��  : DPDT�����Ӧ����ģʽ
             0:ֱͨ
             1:����
*****************************************************************************/
enum RCM_TAS_DPDT_CONTROL_ENUM
{
    RCM_TAS_DPDT_PASS_THROUGH         = 0,
    RCM_TAS_DPDT_SWAP                 = 1,
    RCM_TAS_DPDT_BUTT
};
typedef VOS_UINT16 RCM_TAS_DPDT_CONTROL_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_SEARCH_METHOD_ENUM_UINT16
 ö��˵��  : ������������ʽ
             0:����ԭ����������
             1:TASר����������
*****************************************************************************/
enum RCM_TAS_SEARCH_METHOD_ENUM
{
    RCM_TAS_SEARCH_METHOD_ORIGINAL          = 0,
    RCM_TAS_SEARCH_METHOD_TAS               = 1,
    RCM_TAS_SEARCH_METHOD_BUTT
};
typedef VOS_UINT16 RCM_TAS_SEARCH_METHOD_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_AGENTC_DPDT_DELAY_CTRL_ENUM_UINT16
 ö��˵��  : DPDT�ӳ��л�����ָʾ:
             0:�յ�ȡ����Ȩ��Ϣ��ֹͣһ��dpdt����
             1:ȡ��DPDT�ӳ��л�
             2:����DPDT�ӳ��л�
             3:��������DPDTֵ
             4:ȡ��DPDT�����л�
             5:����DPDT�����л�
             6:��������̬���㷨�л�����
*****************************************************************************/
enum RCM_AGENTC_DPDT_CTRL_ENUM
{
    RCM_AGENTC_DPDT_CTRL_STOP                  = 0,
    RCM_AGENTC_DPDT_DELAY_CTRL_STOP            = 1,
    RCM_AGENTC_DPDT_DELAY_CTRL_START           = 2,
    RCM_AGENTC_DPDT_DELAY_CTRL_UPDATE          = 3,
    RCM_AGENTC_DPDT_DIRECT_CTRL_STOP           = 4,
    RCM_AGENTC_DPDT_DIRECT_CTRL_START          = 5,
    RCM_AGENTC_DPDT_DIRECT_CTRL_UPDATE         = 6,
    RCM_AGENTC_DPDT_CTRL_BUTT
};
typedef VOS_UINT16 RCM_AGENTC_DPDT_CTRL_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_INHERIT_STATE_ENUM_UINT16
 ö��˵��  : ����ģ����������
             0:������ģ�������
             1:����ģ�������
*****************************************************************************/
enum RCM_TAS_INHERIT_STATE_ENUM
{
    RCM_TAS_INHERIT_NONEXIST        = 0,
    RCM_TAS_INHERIT_EXIST           = 1,
    RCM_TAS_INHERIT_BUTT
};
typedef VOS_UINT16 RCM_TAS_INHERIT_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : RCM_TAS_AUTHORIZE_PHY_STATE_ENUM_UINT16
 ö��˵��  : ������Ƿ�����Ȩ
             0:����Ȩ
             1:����Ȩ
*****************************************************************************/
enum RCM_TAS_AUTHORIZE_PHY_STATE_ENUM
{
    RCM_TAS_AUTHORIZE_DISABLE        = 0,
    RCM_TAS_AUTHORIZE_ENABLE         = 1,
    RCM_TAS_AUTHORIZE_BUTT
};
typedef VOS_UINT16 RCM_TAS_AUTHORIZE_PHY_STATE_ENUM_UINT16;

#ifdef LPS_RTT
/*****************************************************************************
 ö����    :VOS_RATMODE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  :˯�߻���ʱ,����ģʽ����
            ע�⣻˫��˫����ö��ֵ������Э��ջ��DRVЭ��ΪGULT;
            ��Ҫ��DrvInterface.h�е�PWC_COMM_MODE_E����һ��

*****************************************************************************/
enum VOS_RATMODE_ENUM
{
    VOS_RATMODE_GSM                         = 0,
    VOS_RATMODE_WCDMA                       = 1,
    VOS_RATMODE_LTE                         = 2,
    VOS_RATMODE_TDS                         = 3,
    VOS_RATMODE_BUTT
};
typedef VOS_UINT32 VOS_RATMODE_ENUM_UINT32;

#define VOS_VOID void
#endif
/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : RCM_PHY_START_TAS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY��ȨTAS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enMasterDpdt;                   /* ԭ��ģdpdt״̬ */
    RCM_TAS_INHERIT_STATE_ENUM_UINT16           enInheritCtrl;                  /* ����ģ����������� */
}RCM_PHY_START_TAS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_START_TAS_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM��Ȩ���ָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enMasterDpdt;                   /* ԭ��ģdpdt״̬ */
    RCM_TAS_INHERIT_STATE_ENUM_UINT16           enInheritCtrl;                  /* ����ģ����������� */
}PHY_RCM_START_TAS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_STOP_TAS_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHYȡ����ȨTAS
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_STOP_TAS_TYPE_ENUM_UINT16               enStopTasType;                  /* ȡ��TAS��Ȩ��ʽ */
    VOS_UINT16                                  usRsv2;                         /* �����ֶ� */
}RCM_PHY_STOP_TAS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_STOP_TAS_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCMȡ����Ȩ���ָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_STOP_TAS_TYPE_ENUM_UINT16               enStopTasType;                  /* ȡ��TAS��Ȩ��ʽ */
}PHY_RCM_STOP_TAS_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_SET_DPDT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY����DPDT������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enDpdtValue;                    /* DPDT�����֣�0:ֱͨ��1:���� */
    VOS_UINT16                                  usRsv2;                          /* �����ֶ� */
}RCM_PHY_SET_DPDT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_SET_DPDT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM����DPDT���������ָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}PHY_RCM_SET_DPDT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_TX_BLANKING_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨ����modem TX_BLANKING��ʼʱ�����ֹʱ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  ulStartSlice;                   /* ��ʼslice */
    VOS_UINT32                                  ulStopSlice;                    /* ��ֹslice */
}RCM_PHY_TX_BLANKING_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_TX_BLANKING_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM����modem TX_BLANKING��ʼʱ�����ֹʱ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_UINT32                                  ulStartSlice;                   /* ��ʼslice */
    VOS_UINT32                                  ulStopSlice;                    /* ��ֹslice */
    VOS_UINT16                                  usDpdtStatus;                   /* �л���dpdt��״̬ */
    VOS_UINT16                                  usRsv2;                         /* �����ֶ� */
}PHY_RCM_TX_BLANKING_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_RATMODE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHY֪ͨRCM��ǰmodem������ģģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    VOS_RATMODE_ENUM_UINT32                     enMasterMode;                   /* ��ģģʽ */
    VOS_RATMODE_ENUM_UINT32                     enSlaveMode;                    /* ��ģģʽ */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enMasterDpdt;                   /* ԭ��ģdpdt״̬ */
    RCM_TAS_AUTHORIZE_PHY_STATE_ENUM_UINT16     enPhyAuthorizeFlg;              /* ԭ��ģ��Ȩ״̬ */
}PHY_RCM_RATMODE_IND_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_MSG_HEADER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RCM������㽻����Ϣ�ṹͷ���壬����ȷ��rcm����phy����Ϣ�ṹ���¶��壬
             ��ֵʱӦ��usRsv��Ϊ0����Ϊmsp����Ĵ洢����Ϣ����һ�����ֽ�Ϊ��Ϣid��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
}RCM_PHY_MSG_HEADER_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_ACCESS_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY Access ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_ACCESS_STATE_ENUM_UINT16                enAccessState;                  /* Access State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_ACCESS_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_SEARCHING_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY Searching ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_SEARCHING_STATE_ENUM_UINT16             enSearchingState;               /* Searching State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_SEARCHING_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_SIGNAL_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY Signal ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_SIGNAL_STATE_ENUM_UINT16                enSignalState;                  /* Signal State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_SIGNAL_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_IDLE_HAPPY_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY Signal ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_IDLE_HAPPY_ENUM_UINT16                  enIdleHappy;                    /* Idle Happy State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_IDLE_HAPPY_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_VOICE_CALL_STATE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM Voice Call ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_VOICE_CALL_STATE_ENUM_UINT16            enVoiceCallState;               /* Voice Call State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_VOICE_CALL_STATE_IND_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_SEARCHING_STATE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨRCM PHY Searching ״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_SEARCHING_STATE_ENUM_UINT16             enSearchingState;               /* Searching State */
    VOS_UINT16                                  usRsv2;
}PHY_RCM_SEARCHING_STATE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_SEARCHING_STATE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨPHY����ִ��Searching���ú��ַ�ʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_TAS_SEARCH_METHOD_ENUM_UINT16           enSearchMethod;                 /* PHY Search Method */
    VOS_UINT16                                  usRsv2;
}RCM_PHY_SEARCHING_STATE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RCM_PHY_AGENTC_SET_DPDT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֪ͨ����PHY�л�DPDT���������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_AGENTC_DPDT_CTRL_ENUM_UINT16            enTaskCtrl;                     /* DPDT�л�������� */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enDpdtValue;                    /* DPDT�����֣�0:ֱͨ��1:���� */
}RCM_PHY_AGENTC_SET_DPDT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PHY_RCM_AGENTC_SET_DPDT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PHY���л�DPDT�������������Ϣ�Ļظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_PHY_MSG_ID_ENUM_UINT16                  enMsgID;                        /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* �����ֶ� */
    VOS_UINT16                                  usOPID;                         /* ������ʶ */
    VOS_UINT16                                  usRsv1;                         /* �����ֶ� */
    RCM_MODE_ID_ENUM_UINT16                     enModeID;                       /* ģʽID */
    RCM_MODEM_ID_ENUM_UINT16                    enModemID;                      /* modem ID */
    RCM_AGENTC_DPDT_CTRL_ENUM_UINT16            enTaskCtrl;                     /* DPDT�л�������� */
    RCM_TAS_DPDT_CONTROL_ENUM_UINT16            enDpdtValue;                    /* DPDT�����֣�0:ֱͨ��1:���� */
}PHY_RCM_AGENTC_SET_DPDT_CNF_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of RcmPhyInterface.h */



