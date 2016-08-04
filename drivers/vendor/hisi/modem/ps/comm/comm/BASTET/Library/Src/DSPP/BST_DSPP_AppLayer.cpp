

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_DSPP_AppLayer.h"
#include "BST_DSPP_CtrLayer.h"
#include "BST_DSPP_TrsLayer.h"
#include "BST_DBG_MemLeak.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DSPP_APPLAYER_CPP
/*lint +e767*/

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_DSPP_HEAD_LENGTH            (  BST_DSPP_TPA_HEAD_LEN        \
                                         + BST_DSPP_TPA_FLAG_LEN        \
                                         + BST_DSPP_CP_HEAD_LEN )
#define BST_DSPP_AP_OFFSET_ADDR         (  BST_DSPP_TPA_HEAD_LEN        \
                                         + BST_DSPP_TPA_BEGIN_FLAG_LEN  \
                                         + BST_DSPP_CP_HEAD_LEN )

/*****************************************************************************
  3 ����ʵ��
******************************************************************************/


BST_DSPP_CAppDlVa::BST_DSPP_CAppDlVa( BST_VOID )
    : BST_DSPP_CDlLayerBase( BST_DSPP_LAYER_APP, BST_DSPP_VER_A )
{
    m_pcTaskManager = BST_SRV_CTaskMng::GetInstance ();
}


BST_DSPP_CAppDlVa::~BST_DSPP_CAppDlVa( BST_VOID )
{
    m_pcTaskManager                     = BST_NULL_PTR;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::ParseHeadInfo(
    BST_DSPP_HEAD_STRU   *const pstHead,
    BST_UINT8 const      *pucData,
    BST_UINT16            usLength )
{
    return BST_NO_ERROR_MSG;
}


BST_UINT16 BST_DSPP_CAppDlVa::ReadOut(
    BST_DSPP_OBJTADDR_T     usObjtAddr,
    BST_DSPP_OFSTADDR_T     usOfstAddr,
    BST_UINT8              *pucSrcBuff,
    BST_UINT8              *pucDstBuff,
    BST_UINT16              usSrcLen,
    BST_UINT16              usDstLen )
{

    BST_CORE_PID_LEN_T                  usParamLen;
    BST_CORE_PID_ENUM_UINT16            usParamId;
    BST_UINT16                          usLooper;
    BST_UINT16                          usResBufCnt;

    usResBufCnt                         = 0;
    for ( usLooper = 0;
          usLooper < usSrcLen;
          usLooper += BST_CORE_PID_LEN )
    {

        /*
         * ��ȡPID���
         */
        usParamId                       = BST_DSPP_AP_BYTE2PID
                                         ( pucSrcBuff[ usLooper ], pucSrcBuff[ usLooper + 1 ] );
        /*
         * ��ȡ�������泤��
         * |--PL(2 BYTE)--|--PID(2 BYTE)--|--Content( usParamLen���������)--|
         * ��ˣ����뻺�峤������ΪBST_OS_SIZEOF ( BST_CORE_PID_LEN_T )+BST_CORE_PID_LEN
         */
        usParamLen                      = m_pcTaskManager->Inquire
                                         ( usObjtAddr, usOfstAddr, usParamId,
                                         ( BST_UINT16 )( usDstLen - usResBufCnt
                                                       - BST_OS_SIZEOF ( BST_CORE_PID_LEN_T )
                                                       - BST_CORE_PID_LEN ),
                                                        pucDstBuff + usResBufCnt
                                                        + BST_OS_SIZEOF ( BST_CORE_PID_LEN_T )
                                                        + BST_CORE_PID_LEN );
        BST_DBG_LOG4( "DSPP Inquire: procid=%u, taskid=%u, pid=%u, plen=%u",
                      usObjtAddr, usOfstAddr, usParamId, usParamLen );

        /*
         * �������Ȼ�ȡ�ɹ��󣬸��ƻ���������
         */
        if ( 0 != usParamLen )
        {
            usParamLen                 += ( BST_OS_SIZEOF ( BST_CORE_PID_LEN_T ) + BST_CORE_PID_LEN );
            pucDstBuff[usResBufCnt]    = BST_DSPP_U16_TO_U8L ( usParamLen );
            pucDstBuff[usResBufCnt+1]  = BST_DSPP_U16_TO_U8H ( usParamLen );
            pucDstBuff[usResBufCnt+2]  = BST_DSPP_U16_TO_U8L ( usParamId );
            pucDstBuff[usResBufCnt+3]  = BST_DSPP_U16_TO_U8H ( usParamId );
            usResBufCnt               += usParamLen;
        }

        /*
         * ���������ȡ���ȳ��ޣ���ô���������β�����ȡ����
         */
        if ( usResBufCnt + BST_OS_SIZEOF ( BST_CORE_PID_LEN_T ) + BST_CORE_PID_LEN > usDstLen )
        {
            break;
        }
    }
    return usResBufCnt;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::Inquire(
    BST_DSPP_OBJTADDR_T    usObjtAddr,
    BST_DSPP_OFSTADDR_T    usOfstAddr,
    BST_DSPP_HEAD_STRU    *const pstRxHeadInfo )
{
    BST_CORE_PID_LEN_T          usParamLen;
    BST_CORE_PID_ENUM_UINT16    usParamId;
    BST_UINT16                  usLooper;
    BST_UINT16                  usResBufCnt;
    BST_UINT8                  *pucData;
    BST_UINT8                  *pcResBuffer;
    BST_UINT16                  usPktTotLen;

    usLooper                    = 0;
    usParamLen                  = 0;
    usPktTotLen                 = 0;
    usResBufCnt                 = 0;
    usParamId                   = BST_PID_INVALID;
    pcResBuffer                 = BST_NULL_PTR;
    pucData                     = pstRxHeadInfo->pucData;

    /*
     * ����������
     */
    if ( ( BST_NULL_PTR == m_pcTaskManager )
     || ( BST_NULL_PTR == pstRxHeadInfo ) )
    {
        return BST_ERR_INVALID_PTR;
    }

    if ( !BST_DSPP_IsObjIdValid (usObjtAddr) )
    {
        BST_RLS_LOG1( "BST_DSPP_CAppDlVa::Inquire usObjtAddr=%u",
                      usObjtAddr );
        return BST_ERR_UNKNOW_OBJ;
    }

    if ( ( BST_NULL_PTR == pucData )
     || ( BST_CORE_PID_LEN > pstRxHeadInfo->usLength ) )
    {
        return BST_ERR_PAR_LEN;
    }

    if ( ( pstRxHeadInfo->usLength % BST_CORE_PID_LEN ) != 0 )
    {
        BST_RLS_LOG1( "BST_DSPP_CAppDlVa::Inquire pstRxHeadInfo->usLength=%u",
                      pstRxHeadInfo->usLength );
        return BST_ERR_PAR_LEN;
    }

    /*
     * ���Ȼ�ȡԤ��ѯ�������ܳ���
     */
    for ( usLooper = 0;
          usLooper < pstRxHeadInfo->usLength;
          usLooper+= BST_CORE_PID_LEN )
    {
        usParamId               = BST_DSPP_AP_BYTE2PID
                                ( pucData[usLooper], pucData[usLooper + 1] );
        usParamLen              = m_pcTaskManager->GetLen
                                ( usObjtAddr, usOfstAddr, usParamId );

        if ( 0 != usParamLen )
        {
            usPktTotLen        += ( BST_OS_SIZEOF ( BST_CORE_PID_LEN_T )
                                  + BST_CORE_PID_LEN
                                  + usParamLen );
        }
    }
    if ( 0 == usPktTotLen )
    {
        return BST_ERR_PAR_UNKNOW;
    }
    /*
     * ����Ŀ�껺����Դ
     */
    pcResBuffer                 = ( BST_UINT8 * )BST_OS_MALLOC ( usPktTotLen );
    if ( BST_NULL_PTR == pcResBuffer )
    {
        return BST_ERR_NO_MEMORY;
    }

    /*
     * ��PID���ݿ����Ӧ�ó����ò�������
     */
    usResBufCnt                 = ReadOut( usObjtAddr, usOfstAddr, pucData, pcResBuffer,
                                           pstRxHeadInfo->usLength, usPktTotLen );
    /*
     * Memory Leak! If we malloc the space but copy none, We shoud release it here;
     */
    if ( 0 == usResBufCnt )
    {
        BST_OS_FREE ( pcResBuffer );
        pcResBuffer             = BST_NULL_PTR;
    }
    /*
     * �������û��������ݣ���Ӧ��ʹ��
     */
    pstRxHeadInfo->pucData      = pcResBuffer;
    pstRxHeadInfo->usLength     = usResBufCnt;
    return BST_NO_ERROR_MSG;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::Config(
    BST_DSPP_OBJTADDR_T usObjtAddr,
    BST_DSPP_OFSTADDR_T usOfstAddr,
    BST_DSPP_HEAD_STRU *const pstRxHeadInfo )
{
    BST_CORE_PID_LEN_T          usParamLen;
    BST_CORE_PID_ENUM_UINT16    usParamId;
    BST_UINT8                  *pcData;
    BST_UINT16                  usBufCnt;
    BST_ERR_ENUM_UINT8          ucRtnVal;

    if ( BST_NULL_PTR == pstRxHeadInfo )
    {
        return BST_ERR_INVALID_PTR;
    }
    usParamLen                  = 0;
    usBufCnt                    = 0;
    usParamId                   = BST_PID_INVALID;
    ucRtnVal                    = BST_NO_ERROR_MSG;
    pcData                      = pstRxHeadInfo->pucData;

    /*
     * ��ڼ��
     */
    if ( BST_NULL_PTR == m_pcTaskManager )
    {
        return ( BST_ERR_INVALID_PTR );
    }

    if ( !BST_DSPP_IsObjIdValid (usObjtAddr) )
    {
        BST_RLS_LOG1( "BST_DSPP_CAppDlVa::Config usObjtAddr=%u",
                      usObjtAddr );
        return ( BST_ERR_UNKNOW_OBJ );
    }

    if( BST_CORE_PID_LEN > pstRxHeadInfo->usLength )
    {
        return ( BST_ERR_PAR_LEN );
    }

    for (;;)
    {
        /*
         * ���ʣ�����ݳ����޷���ȡ��ЧPID��Ϣ����ôֱ���˳��򷵻�
         */
        if ( pstRxHeadInfo->usLength - usBufCnt <= BST_DSPP_AP_CMD_HEAD_LEN )
        {
            if ( pstRxHeadInfo->usLength == usBufCnt )
            {
                ucRtnVal        = BST_NO_ERROR_MSG;
            }
            else
            {
                ucRtnVal        = BST_ERR_PAR_LEN;
            }
            break;
        }
        /*
         * ��ȡPID���ȣ�PID���Ƶ���Ϣ
         */
        usParamLen              = ( BST_CORE_PID_LEN_T )BST_DSPP_U8_TO_U16
                                  ( pcData[BST_DSPP_AP_CMD_LEN_L],
                                    pcData[BST_DSPP_AP_CMD_LEN_H] )
                                   -BST_DSPP_AP_CMD_HEAD_LEN;
        usParamId               = BST_DSPP_AP_BYTE2PID
                                ( pcData[BST_DSPP_AP_CMD_ID_L],
                                  pcData[BST_DSPP_AP_CMD_ID_H] );
        pcData                 += BST_DSPP_AP_CMD_HEAD_LEN;
        usBufCnt               += BST_DSPP_AP_CMD_HEAD_LEN;

        /*
         * ���ʣ�����ݳ�����������Ľ�������ϣ����ȡʶ���޷���������
         */
        if ( ( pstRxHeadInfo->usLength - usBufCnt ) < usParamLen )
        {
            BST_RLS_LOG3( "BST_DSPP_CAppDlVa::Config usLength=%u,usBufCnt=%u,usParamLen=%u",
                          pstRxHeadInfo->usLength, usBufCnt, usParamLen );
            ucRtnVal            = BST_ERR_PAR_LEN;
            break;
        }
        /*
         * д�����ֵ
         */
        ucRtnVal                = m_pcTaskManager->Config
                                 ( usObjtAddr, usOfstAddr, usParamId,
                                   usParamLen, pcData );
        if ( BST_NO_ERROR_MSG == ucRtnVal )
        {
            pcData             += usParamLen;
            usBufCnt           += usParamLen;
        }
        else
        {
            break;
        }
    }
    return ( ucRtnVal );
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::Add(
    BST_DSPP_HEAD_STRU     *const pstRxHeadInfo,
    BST_DSPP_OFSTADDR_T    *const pusOfstAddr,
    BST_DSPP_OBJTADDR_T     usObjtAddr )
{
    BST_UINT16              usOfstAddr;
    BST_ERR_ENUM_UINT8      ucRtnVal;

    /*
     * ��ڼ��
     */
    if ( ( BST_NULL_PTR == m_pcTaskManager )
     || ( BST_NULL_PTR == pstRxHeadInfo )
     || ( BST_NULL_PTR == pusOfstAddr ) )
    {
        return ( BST_ERR_INVALID_PTR );
    }
   *pusOfstAddr             = BST_DSPP_INVALID_ADDR;
    /*
     * У��PID�Ƿ���Ч
     */
    if ( !BST_DSPP_IsObjIdValid (usObjtAddr) )
    {
        return ( BST_ERR_UNKNOW_OBJ );
    }

    /*
     * �������������ȡ�������ID���
     */
    usOfstAddr              = m_pcTaskManager->Add ( usObjtAddr );
    BST_DBG_LOG2( "DSPP Add: procid=%u, taskid=%u", usObjtAddr, usOfstAddr );
    if ( BST_DSPP_INVALID_ADDR == usOfstAddr )
    {
        return ( BST_ERR_NO_MEMORY );
    }
    /*
     * ���ֲ���ֵ�����
     */
   *pusOfstAddr             = usOfstAddr;
    pstRxHeadInfo->enApVer  = BST_DSPP_VER_VOID;
    switch ( pstRxHeadInfo->enCpVer )
    {
        case BST_DSPP_VER_A:
            pstRxHeadInfo->stCpVerA.usOfstAddr = usOfstAddr;
            break;

        case BST_DSPP_VER_B:
            pstRxHeadInfo->stCpVerA.usOfstAddr = usOfstAddr;
            break;

        default:
            break;
    }
    /*
     * �������ɺ���������ݣ���ô�ȼ���ò�����Ҫ����
     */
    if ( ( 0 != pstRxHeadInfo->usLength )
      && ( BST_NULL_PTR != pstRxHeadInfo->pucData ) )
    {
        ucRtnVal            = Config ( usObjtAddr, usOfstAddr, pstRxHeadInfo );
    }
    else
    {
        ucRtnVal            = BST_NO_ERROR_MSG;
    }
    return ( ucRtnVal );
}

BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::Remove(
    BST_DSPP_OBJTADDR_T usObjtAddr,
    BST_DSPP_OFSTADDR_T usOfstAddr )
{
    if ( BST_NULL_PTR == m_pcTaskManager )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_DSPP_INVALID_ADDR == usOfstAddr )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    BST_DBG_LOG2( "DSPP Remove: procid=%u, taskid=%u", usObjtAddr, usOfstAddr );
    return ( m_pcTaskManager->Remove ( usObjtAddr, usOfstAddr ) );
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::ProcAction(
    BST_DSPP_HEAD_STRU     *const pstRxHeadInfo,
    BST_DSPP_OFSTADDR_T    *pusOfstAddr,
    BST_DSPP_OBJTADDR_T     usObjtAddr )
{
    BST_ERR_ENUM_UINT8      enRtnVal;

    enRtnVal                = BST_ERR_UNKNOW_ACT;
    switch ( pstRxHeadInfo->stCpVerA.ucActType )
    {
        /*
         * ���������
         */
        case BST_ACTION_ADD:
            enRtnVal        = Add ( pstRxHeadInfo, pusOfstAddr, usObjtAddr );
            break;
        /*
         * ɾ������
         */
        case BST_ACTION_REMOVE:
            enRtnVal        = Remove ( usObjtAddr, *pusOfstAddr ) ;
            break;
        /*
         * ��ʼ��������в�����Ҫ�����ã�����������������
         */
        case BST_ACTION_START:
            if( ( 0 != pstRxHeadInfo->usLength )
             && ( BST_NULL_PTR != pstRxHeadInfo->pucData ) )
            {
                /*
                 * �������ʧ�ܣ���Start������������ϵͳ�쳣����˲�������
                 */
                if ( Config( usObjtAddr, *pusOfstAddr, pstRxHeadInfo )
                  != BST_NO_ERROR_MSG )
                {
                    break;
                }
            }
            enRtnVal        = m_pcTaskManager->Start ( usObjtAddr, *pusOfstAddr );
            break;
        /*
         * ֹͣ��������
         */
        case BST_ACTION_STOP:
            enRtnVal        = m_pcTaskManager->Stop ( usObjtAddr, *pusOfstAddr );
            break;

        /*
         * ��ѯ����
         */
        case BST_ACTION_INQUIRE:
            if ( BST_NULL_PTR == pstRxHeadInfo->pucData )
            {
                enRtnVal    = BST_ERR_LAYER_VER;
                break;
            }
            enRtnVal        = Inquire ( usObjtAddr, *pusOfstAddr, pstRxHeadInfo );
            break;
        /*
         * ���ò���
         */
        case BST_ACTION_CONFIG:
            if ( BST_NULL_PTR == pstRxHeadInfo->pucData )
            {
                enRtnVal    = BST_ERR_LAYER_VER;
                break;
            }
            enRtnVal        = Config ( usObjtAddr, *pusOfstAddr, pstRxHeadInfo ) ;
            break;

        default:
            enRtnVal        = BST_ERR_PAR_UNKNOW;
            BST_DBG_LOG ( "BST_DSPP_CAppDlVa::ProcAction Error, Unknow Action" );
            break;
    }
    return enRtnVal;
}

/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::UnpackInternal(
    BST_DSPP_HEAD_STRU         *const pstRxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const pstNextVer )
{
    BST_UINT8              *pucBackRx;
    BST_DSPP_CAppUlVa      *pcUlProc;
    BST_ERR_ENUM_UINT8      enRtnVal;

    pcUlProc                = BST_DSPP_CAppUlVa::GetInstance ();
    enRtnVal                = BST_ERR_UNKNOW_ACT;

    /*
     * ��ڼ��
     */
    BST_ASSERT_NULL_RTN ( pstRxHeadInfo, BST_ERR_INVALID_PTR);
    BST_ASSERT_NULL_RTN ( pcUlProc, BST_ERR_INVALID_PTR);
    if ( BST_NULL_PTR == m_pcTaskManager )
    {
        return ( pcUlProc->Response ( pstRxHeadInfo, BST_ERR_INVALID_PTR ) );
    }
    if ( BST_DSPP_VER_A != pstRxHeadInfo->enCpVer )
    {
        return ( pcUlProc->Response ( pstRxHeadInfo, BST_ERR_LAYER_VER ) );
    }
    /*
     * ���������0����ģʽ����ô����FREE����������ACOMM�����ָ�븳ֵΪ��
     */
    if ( BST_FALSE == pstRxHeadInfo->ulZeroCopy )
    {
        pucBackRx           = pstRxHeadInfo->pucData;
    }
    else
    {
        pucBackRx           = BST_NULL_PTR;
    }
    /*
     * ���ݲ�ͬACITON���ͣ������������
     */
    enRtnVal                = ProcAction( pstRxHeadInfo,
                             &pstRxHeadInfo->stCpVerA.usOfstAddr,
                              pstRxHeadInfo->stCpVerA.usObjtAddr );

    /*
     * ��INQUIRE-ACTION�£���Ϊ�л�Ӧֵ������PID���ݲ��գ�������FREE��ֻ�г������
     */
    if ( BST_ACTION_INQUIRE == pstRxHeadInfo->stCpVerA.ucActType )
    {
        if ( BST_NO_ERROR_MSG != enRtnVal )
        {
            pstRxHeadInfo->usLength = 0;
        }
    }
    else
    {
        pstRxHeadInfo->usLength     = 0;
    }
    /*
     * ���֮ǰ�б�������ָ�룬��FREE���ռ䣬�����ڴ�й©
     */
    if ( BST_NULL_PTR != pucBackRx )
    {
        BST_OS_FREE( pucBackRx );
    }
    /*
     * Ӧ��S��ACTION���
     */
    enRtnVal                        = pcUlProc->Response
                                    ( pstRxHeadInfo, enRtnVal );
    return enRtnVal;
}
/*lint +e438*/

BST_DSPP_CDlLayerBase *BST_DSPP_CAppDlVa::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    return BST_NULL_PTR;
}


BST_DSPP_CAppDlVa *BST_DSPP_CAppDlVa::GetInstance( BST_VOID )
{
    static BST_DSPP_CAppDlVa   *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance             = new BST_DSPP_CAppDlVa ();
    }
    return s_pInstance;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::Response(
    BST_DSPP_HEAD_STRU   *const pstOrigHeadInfo,
    BST_ERR_ENUM_UINT8    enErrMsg )
{
    BST_UINT8          *pucSdu;
    pucSdu             = BST_NULL_PTR;

    /*
     * �����
     */
    if ( BST_NULL_PTR == pstOrigHeadInfo )
    {
        return BST_ERR_UNREACHABLE;
    }

    /*
     * У��Э��汾�����Ƿ�Ϸ�
     */
    if ( !BST_DSPP_IsVersionValid ( pstOrigHeadInfo->enCpVer ) )
    {
        return BST_ERR_UNREACHABLE;
    }

    /*
     * ��дDSPP�ṹ�����ݣ�����ΪRESPONSE
     */
    pstOrigHeadInfo->enTpVer        = BST_DSPP_VER_VOID;
    pstOrigHeadInfo->enPrmvType     = BST_DSPP_PRMTV_RESPONSE;

    /*
     * ���ԴӦ�𻺳��������ݣ���ô����ռ�Ҳ����
     */
    if ( ( BST_NULL_PTR != pstOrigHeadInfo->pucData )
      && ( 0 != pstOrigHeadInfo->usLength ) )
    {
        pstOrigHeadInfo->enApVer= BST_DSPP_VER_A;
        pucSdu                  = ( BST_UINT8 * )BST_OS_MALLOC
                                  ( pstOrigHeadInfo->usLength+BST_DSPP_HEAD_LENGTH );
        if ( BST_NULL_PTR == pucSdu )
        {
            BST_OS_FREE( pstOrigHeadInfo->pucData );
            return BST_ERR_NO_MEMORY;
        }
        BST_OS_MEMCPY( &pucSdu[BST_DSPP_AP_OFFSET_ADDR],
                        pstOrigHeadInfo->pucData,
                        pstOrigHeadInfo->usLength );
        BST_OS_FREE( pstOrigHeadInfo->pucData );
        pstOrigHeadInfo->pucData    = pucSdu;
    }
    /*
     * ���Ӧ��Ϊ�հף�ֱ������DSPPͷ���ȼ���
     */
    else
    {
        pstOrigHeadInfo->enApVer    = BST_DSPP_VER_VOID;
        pstOrigHeadInfo->usLength   = 0;
        pstOrigHeadInfo->pucData    = ( BST_UINT8 * )
                                      BST_OS_MALLOC ( BST_DSPP_HEAD_LENGTH );
        if ( BST_NULL_PTR == pstOrigHeadInfo->pucData )
        {
            return BST_ERR_NO_MEMORY;
        }
    }

    switch ( pstOrigHeadInfo->enCpVer )
    {
        case BST_DSPP_VER_A:
            pstOrigHeadInfo->stCpVerA.ucActType
                                    = enErrMsg;
            break;

        case BST_DSPP_VER_B:
            pstOrigHeadInfo->stCpVerA.ucActType
                                    = enErrMsg;
            break;

        default:
            break;
    }
    /*
     * ������һ����з��
     */
    return ( Pack ( pstOrigHeadInfo ) );
}


BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::Report(
    BST_DSPP_OBJTADDR_T      usObjtAddr,
    BST_DSPP_OFSTADDR_T      usOfstAddr,
    BST_DSPP_CMDLEN_T        usCmdLen,
    BST_CORE_PID_ENUM_UINT16 enCmdId,
    BST_UINT8               *pucCmdData )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;
    BST_UINT8                          *pucSdu;

    pucSdu                             = BST_NULL_PTR;
    /*
     * ��ڼ��
     */
    if ( ( 0 == usCmdLen )
      || ( BST_NULL_PTR == pucCmdData ) )
    {
        return BST_ERR_INVALID_PTR;
    }
    /*
     * У�����͡���ֵַ�Ƿ���Ч
     */
    if ( (!BST_DSPP_IsObjIdValid ( usObjtAddr ) )
      || ( BST_DSPP_INVALID_ADDR == usOfstAddr ) )
    {
        return BST_ERR_UNREACHABLE;
    }

    /*
     * ��ȡ�ϱ�����
     */
    pucSdu                              = ( BST_UINT8 * )BST_OS_MALLOC ( usCmdLen
                                        + BST_DSPP_AP_CMD_HEAD_LEN + BST_DSPP_HEAD_LENGTH );
    if ( BST_NULL_PTR == pucSdu )
    {
        return BST_ERR_NO_MEMORY;
    }
    /*
     * ��дSDU-AP����Ϣ
     */
    stTxHeadInfo.pucData                = pucSdu;
    pucSdu                             += BST_DSPP_AP_OFFSET_ADDR;
    pucSdu[BST_DSPP_AP_CMD_LEN_L]       = BST_DSPP_U16_TO_U8L
                                        ( usCmdLen + BST_DSPP_AP_CMD_HEAD_LEN );
    pucSdu[BST_DSPP_AP_CMD_LEN_H]       = BST_DSPP_U16_TO_U8H
                                        ( usCmdLen + BST_DSPP_AP_CMD_HEAD_LEN );
    pucSdu[BST_DSPP_AP_CMD_ID_L]        = BST_DSPP_U16_TO_U8L ( enCmdId );
    pucSdu[BST_DSPP_AP_CMD_ID_H]        = BST_DSPP_U16_TO_U8H ( enCmdId );
    BST_OS_MEMCPY ( pucSdu + BST_DSPP_AP_CMD_HEAD_LEN, pucCmdData, usCmdLen );

    /*
     * ��дDSPP�ṹ�壬ѡ��Э��汾�����²�ʹ��
     */
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_VOID;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.usLength               = ( usCmdLen + BST_DSPP_AP_CMD_HEAD_LEN );
    stTxHeadInfo.stCpVerA.usObjtAddr    = usObjtAddr;
    stTxHeadInfo.stCpVerA.usOfstAddr    = usOfstAddr;
    stTxHeadInfo.stCpVerA.ucActType     = BST_ACTION_REPORT;

    return ( Pack ( &stTxHeadInfo ) );
}

BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::Report(
    BST_DSPP_OBJTADDR_T usObjtAddr,
    BST_DSPP_OFSTADDR_T usOfstAddr,
    BST_ERR_ENUM_UINT8  enErr )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;

    /*
     * ��ڼ��
     */
    if ( (!BST_DSPP_IsObjIdValid ( usObjtAddr ) )
      || ( BST_DSPP_INVALID_ADDR == usOfstAddr ) )
    {
        return BST_ERR_UNREACHABLE;
    }
    stTxHeadInfo.pucData                = ( BST_UINT8 * )
                                          BST_OS_MALLOC ( BST_DSPP_HEAD_LENGTH );
    if ( BST_NULL_PTR == stTxHeadInfo.pucData )
    {
        return BST_ERR_NO_MEMORY;
    }
    /*
     * ��дDSPP�ṹ�壬ѡ��Э��汾�����²�ʹ��
     */
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_VOID;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.usLength               = 0;
    stTxHeadInfo.stCpVerA.usObjtAddr    = usObjtAddr;
    stTxHeadInfo.stCpVerA.usOfstAddr    = usOfstAddr;
    stTxHeadInfo.stCpVerA.ucActType     = enErr;
    return ( Pack ( &stTxHeadInfo ) );
}


BST_DSPP_CAppUlVa *BST_DSPP_CAppUlVa::GetInstance ( BST_VOID )
{
    static BST_DSPP_CAppUlVa           *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance                     = new BST_DSPP_CAppUlVa ();
    }

    return s_pInstance;
}


BST_DSPP_CAppUlVa::BST_DSPP_CAppUlVa ( BST_VOID )
    : BST_DSPP_CUlLayerBase ( BST_DSPP_LAYER_APP, BST_DSPP_VER_A )
{

}

BST_DSPP_CAppUlVa::~BST_DSPP_CAppUlVa ( BST_VOID )
{

}

BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::PackInternal(
    BST_DSPP_HEAD_STRU         *const pstTxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const penNextVer )
{
    if ( BST_NULL_PTR == pstTxHeadInfo )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
   *penNextVer                          = pstTxHeadInfo->enCpVer;
    return BST_NO_ERROR_MSG;
}


BST_DSPP_CUlLayerBase *BST_DSPP_CAppUlVa::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    switch ( enNextVer )
    {
        case BST_DSPP_VER_A:
            return ( new BST_DSPP_CCtrUlVa () );

        default:
            break;
    }
    return BST_NULL_PTR;
}

