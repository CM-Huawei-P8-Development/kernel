

#ifndef __BST_IP_LWIP_API_H__
#define __BST_IP_LWIP_API_H__


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "lwip/def.h"
#include "BST_Platform.h"
#include "BST_IP_Define.h"
#include "BST_IP_SocketClone.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#ifdef BST_SSL_SUPPORT
#define BST_IP_SOCKET_FUNCTION_TABLE \
/*                  |       Socket      |        Connect      |       Clone      |       Send       |      Receive     |       Bind      |     Close       |*/ \
/* TYPE_BSD      */ {  BST_IP_BsdSocket, BST_IP_BsdConnect,    BST_IP_BsdTcpClone, BST_IP_BsdSend,    BST_IP_BsdReceive, BST_IP_BsdBind,    BST_IP_BsdClose}, \
/* TYPE_SSL      */ {  BST_IP_SslSocket, BST_IP_SslConnect,    BST_NULL_PTR,       BST_IP_SslSend,    BST_IP_SslReceive, BST_IP_SslBind,    BST_IP_SslClose}, \
/* RAW_TCP       */ {  BST_IP_RawSocket, BST_IP_RawTcpConnect, BST_IP_RawTcpClone, BST_IP_RawTcpSend, BST_NULL_PTR,      BST_IP_RawTcpBind, BST_IP_RawTcpClose}, \
/* RAW_UDP       */ {  BST_IP_RawSocket, BST_IP_RawUdpConnect, BST_NULL_PTR,       BST_IP_RawUdpSend, BST_NULL_PTR,      BST_IP_RawUdpBind, BST_IP_RawUdpClose}
#else
#define BST_IP_SOCKET_FUNCTION_TABLE \
/*                  |       Socket      |        Connect      |       Clone      |       Send       |      Receive     |       Bind      |     Close       |*/ \
/* TYPE_BSD      */ {  BST_IP_BsdSocket, BST_IP_BsdConnect,    BST_IP_BsdTcpClone, BST_IP_BsdSend,    BST_IP_BsdReceive, BST_IP_BsdBind,    BST_IP_BsdClose}, \
/* TYPE_SSL      */ {  BST_NULL_PTR,     BST_NULL_PTR,         BST_NULL_PTR,       BST_NULL_PTR,      BST_NULL_PTR,      BST_NULL_PTR,      BST_NULL_PTR }, \
/* RAW_TCP       */ {  BST_IP_RawSocket, BST_IP_RawTcpConnect, BST_IP_RawTcpClone, BST_IP_RawTcpSend, BST_NULL_PTR,      BST_IP_RawTcpBind, BST_IP_RawTcpClose}, \
/* RAW_UDP       */ {  BST_IP_RawSocket, BST_IP_RawUdpConnect, BST_NULL_PTR,       BST_IP_RawUdpSend, BST_NULL_PTR,      BST_IP_RawUdpBind, BST_IP_RawUdpClose}
#endif
#define BST_IP_SOCKET_SUPPORT_TABLE \
    BST_SCKT_TYPE_BSD,                /* ��׼������BSD�ӿ� */ \
    BST_SCKT_TYPE_SSL,                /* SSL�ӿ�*/\
    BST_SCKT_TYPE_RAW_TCP,            /* LWIP �����õ�RAW-TCP�ӿڣ�֧��ʵ��Connect, ֧��Seq��/�� */ \
    BST_SCKT_TYPE_RAW_UDP             /* LWIP �����õ�RAW-UDP�ӿڣ�֧������ֵ��ѯ*/ \

#define BST_IP_SocketSupportTblHead()   ( &g_BST_IP_SocketSupportTable[0] ) 
#define BST_IP_SocketFunTblHead()       ( &g_BST_IP_SocketFunTable[0] )
#define BST_IP_GetSocketFunGrp(s_type)  ( &g_BST_IP_SocketFunTable[s_type])

/* for Pc-lint error 801: goto */
#define BST_IP_TCP_RCVAPI_FREE()                            \
    q                                   = p;                \
    for(;;)                                                 \
    {                                                       \
        if( BST_IP_IsLwipNull(q) )                          \
        {                                                   \
            break;                                          \
        }                                                   \
        BST_IP_ApiUnRegistPacket( ( BST_IP_PKT_ID_T ) q );  \
        q                               = q->next;          \
    }                                                       \
    pbuf_free( p );                                         \
    BST_OS_ThreadUnLock( tThreadLockCnt );                  \
    return( ucErrMsg )

#define BST_IP_UDP_RCVAPI_FREE()                            \
    q                                   = p;                \
    for(;;)                                                 \
    {                                                       \
        if( BST_IP_IsLwipNull(q) )                          \
        {                                                   \
            break;                                          \
        }                                                   \
        BST_IP_ApiUnRegistPacket( ( BST_IP_PKT_ID_T ) q );  \
        q                               = q->next;          \
    }                                                       \
    pbuf_free( p );                                         \
    BST_OS_ThreadUnLock( tThreadLockCnt );                  \
    return

typedef BST_IP_ERR_T (*BST_IP_API_SOKT_T)( BST_FD_T                *pfd,
                                           BST_ARG_T               *Arg,
                                           BST_UINT16               usProtocol );
typedef BST_IP_ERR_T (*BST_IP_API_CONN_T)( BST_FD_T                 fd,
                                           BST_ARG_T                Arg,
                                           BST_IP_SOCKET_ADD_T     *pAdd );
typedef BST_IP_ERR_T (*BST_IP_API_CLON_T)( BST_FD_T                 fd,
                                           BST_IP_SOCKET_ADD_T     *pAdd );
typedef BST_IP_ERR_T (*BST_IP_API_SEND_T)( BST_FD_T                 fd,
                                           BST_UINT8               *pData,
                                           BST_UINT16               usLength );
typedef BST_IP_ERR_T (*BST_IP_API_RECV_T)( BST_FD_T                 fd,
                                           BST_UINT8               *pData,
                                           BST_UINT16               usLength );
typedef BST_IP_ERR_T (*BST_IP_API_BIND_T)( BST_FD_T                 fd,
                                           BST_UINT16               usPort );
typedef BST_IP_ERR_T (*BST_IP_API_CLSE_T)( BST_FD_T                 fd,
                                           BST_ARG_T                Arg );

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  5 �ṹ����
*****************************************************************************/
typedef struct{
    BST_IP_API_SOKT_T                   pfSocket;
    BST_IP_API_CONN_T                   pfConnect;
    BST_IP_API_CLON_T                   pfClone;
    BST_IP_API_SEND_T                   pfSend;
    BST_IP_API_RECV_T                   pfReceive;
    BST_IP_API_BIND_T                   pfBind;
    BST_IP_API_CLSE_T                   pfClose;
}BST_IP_SOCKET_FUN_LUT_STRU;

/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/
extern const BST_IP_SOCKET_FUN_LUT_STRU  g_BST_IP_SocketFunTable[ BST_SCKT_TYPE_NUMBER ];

/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_IP_ERR_T BST_IP_CheckSocketSupport( BST_SCKT_TYPE_ENUM_UINT32 stSocketType );

/* RAW API��ؽӿ� */
BST_IP_ERR_T BST_IP_RawSocket       ( BST_FD_T                 *pfd,
                                      BST_ARG_T                *Arg,
                                      BST_UINT16                usProtocol );

BST_IP_ERR_T BST_IP_RawTcpSocket    ( BST_FD_T                 *pfd );
BST_IP_ERR_T BST_IP_RawTcpConnect   ( BST_FD_T                  fd,
                                      BST_ARG_T                 Arg,
                                      BST_IP_SOCKET_ADD_T      *pAdd );
BST_IP_ERR_T BST_IP_RawTcpClone     ( BST_FD_T                  fd,
                                      BST_IP_SOCKET_ADD_T      *pAdd );
BST_IP_ERR_T BST_IP_RawTcpSend      ( BST_FD_T                  fd,
                                      BST_UINT8                *pData,
                                      BST_UINT16                usLength );
BST_IP_ERR_T BST_IP_RawTcpBind      ( BST_FD_T                  fd,
                                      BST_UINT16                usPort );
BST_IP_ERR_T BST_IP_RawTcpClose     ( BST_FD_T                  fd,
                                      BST_ARG_T                 Arg );
BST_IP_ERR_T BST_IP_RawUdpSocket    ( BST_FD_T                 *pfd );
BST_IP_ERR_T BST_IP_RawUdpConnect   ( BST_FD_T                  fd,
                                      BST_ARG_T                 Arg,
                                      BST_IP_SOCKET_ADD_T      *pAdd );
BST_IP_ERR_T BST_IP_RawUdpSend      ( BST_FD_T                  fd,
                                      BST_UINT8                *pData,
                                      BST_UINT16                usLength );
BST_IP_ERR_T BST_IP_RawUdpBind      ( BST_FD_T                  fd,
                                      BST_UINT16                usPort );
BST_IP_ERR_T BST_IP_RawUdpClose     ( BST_FD_T                  fd,
                                      BST_ARG_T                 Arg );
BST_VOID BST_IP_CallBackEntry       ( BST_IP_EVENT_STRU        *pstEvent );

/* BSD��׼�����ͽӿ� */
BST_IP_ERR_T BST_IP_BsdSocket       ( BST_FD_T                 *pfd,
                                      BST_ARG_T                *Arg,
                                      BST_UINT16                usProtocol );
BST_IP_ERR_T BST_IP_BsdConnect      ( BST_FD_T                  fd,
                                      BST_ARG_T                 Arg,
                                      BST_IP_SOCKET_ADD_T      *pAdd );
BST_IP_ERR_T BST_IP_BsdTcpClone     ( BST_FD_T fd,
                                      BST_IP_SOCKET_ADD_T      *pAdd );
BST_IP_ERR_T BST_IP_BsdSend         ( BST_FD_T                  fd,
                                      BST_UINT8                *pData,
                                      BST_UINT16                usLength );
BST_IP_ERR_T BST_IP_BsdReceive      ( BST_FD_T                  fd,
                                      BST_UINT8                *pData,
                                      BST_UINT16                usLength );
BST_IP_ERR_T BST_IP_BsdBind         ( BST_FD_T                  fd,
                                      BST_UINT16                usPort );
BST_IP_ERR_T BST_IP_BsdClose        ( BST_FD_T                  fd,
                                      BST_ARG_T                 Arg );
#ifdef BST_SSL_SUPPORT
/*SSL�ӿ�*/
BST_IP_ERR_T BST_IP_SslSocket       ( BST_FD_T                 *pfd,
                                      BST_ARG_T                *Arg,
                                      BST_UINT16                usProtocol );
BST_IP_ERR_T BST_IP_SslConnect      ( BST_FD_T                  fd,
                                      BST_ARG_T                 Arg,
                                      BST_IP_SOCKET_ADD_T      *pAdd );
BST_IP_ERR_T BST_IP_SslTcpClone     ( BST_FD_T                  fd,
                                      BST_IP_SOCKET_ADD_T      *pAddr,
                                      BST_IP_SKT_PROPTY_STRU   *pstProperty );
BST_IP_ERR_T BST_IP_SslSend         ( BST_FD_T                  fd,
                                      BST_UINT8                *pData,
                                      BST_UINT16                usLength );
BST_IP_ERR_T BST_IP_SslReceive      ( BST_FD_T                  fd,
                                      BST_UINT8                *pData,
                                      BST_UINT16                usLength );
BST_IP_ERR_T BST_IP_SslBind         ( BST_FD_T                  fd,
                                      BST_UINT16                usPort );
BST_IP_ERR_T BST_IP_SslClose        ( BST_FD_T                  fd,
                                      BST_ARG_T                 Arg );
#endif
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#endif
