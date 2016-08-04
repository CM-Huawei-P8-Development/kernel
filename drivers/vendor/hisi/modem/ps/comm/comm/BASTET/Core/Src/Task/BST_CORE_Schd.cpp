

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_CORE_Schd.h"
#include "BST_OS_Thread.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_TaskMng.h"
#include "BST_DRV_As.h"
#include "BST_DSPP_Define.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_CORE_SCHD_CPP
/*lint +e767*/
/*****************************************************************************
  2 ��������
*****************************************************************************/
extern "C" BST_VOID BST_SRV_InitAppThreads ( BST_VOID );
/******************************************************************************
   4 ˽�ж���
******************************************************************************/

/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/
BST_UINT16  g_ucAppInitCnt;
LIST        g_stPTaskList;

/******************************************************************************
   6 ����ʵ��
******************************************************************************/


/*lint -e429*/
BST_VOID BST_CTaskSchdler::Attach ( BST_CORE_CPTask *pC_PTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( !BST_OS_IsTimerValid (m_ulTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::Attach m_ulTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }
    if ( BST_NULL_PTR == pC_PTask )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Attach pC_PTask=NULL" );
        return;
    }
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if( pstPtaskNode->pcTask == pC_PTask )
        {
            return;
        }
    }
    /*
     * ��������ڵ���Դ�����ڴ洢����
     */
    pstPtaskNode                = ( BST_CORE_PTASK_NODE_STRU *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF( BST_CORE_PTASK_NODE_STRU ) );
    if( BST_NULL_PTR == pstPtaskNode )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Attach pstPtaskNode=NULL" );
        return;
    }
    /*
     * ��ʼ���������ݣ�����������б�
     */
    pC_PTask->m_ulSuspCounter   = 0;
    pstPtaskNode->pcTask        = pC_PTask;
    lstAdd( &g_stPTaskList, (NODE *)pstPtaskNode );
    /*
     * �����ʱϵͳTICK��ʱ�Ѿ��رգ���PS�����״̬��������ô��Ҫ�ٴ�������ʱ
     */
    if(  BST_TRUE == BST_OS_TimerIsStop( m_ulTimerId ) )
    {
        m_ulSystemTick          = 0;
        BST_OS_TimerStart ( m_ulTimerId, BST_TASK_SYS_BASE_TIMELEN );
        BST_DBG_LOG1( "BST_CTaskSchdler::Attach Start Scheduler Timer:%u",
                      BST_TASK_SYS_BASE_TIMELEN );
    }
}
/*lint +e429*/

/*lint -e438*/
BST_VOID BST_CTaskSchdler::Detach ( BST_CORE_CPTask *pC_PTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( !BST_OS_IsTimerValid (m_ulTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::Detach m_ulTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }
    if ( BST_NULL_PTR == pC_PTask )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Detach pC_PTask=NULL" );
        return;
    }
    /*
     * �����б��ҵ�pctask��������񣬴�����ɾ�����ͷ���Դ
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if( pstPtaskNode->pcTask != pC_PTask )
        {
            continue;
        }
        lstDelete( &g_stPTaskList, (NODE *)pstPtaskNode );
        BST_OS_FREE( pstPtaskNode );
        break;
    }
    /*
     * ע���������Ϊ�б�Ϊ�գ���ֱ�ӹرն�ʱ�����������κε���
     */
    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        BST_DBG_LOG( "BST_CTaskSchdler::Detach Stop Scheduler Timer" );
        BST_OS_TimerStop ( m_ulTimerId );
    }
}
/*lint +e438*/

BST_VOID BST_CTaskSchdler::Suspend ( BST_VOID )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::Suspend g_stPTaskList count=0" );
        return;
    }
    /*
     * ����������ҵ�������������й���
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        if ( BST_TASK_STATE_START == pstPtaskNode->pcTask->GetState () )
        {
            pstPtaskNode->pcTask->Suspend();
        }
    }
}


BST_CTaskSchdler* BST_CTaskSchdler::GetInstance ( BST_VOID )
{
    static BST_CTaskSchdler    *pTaskScheduler = BST_NULL_PTR;

    if ( BST_NULL_PTR == pTaskScheduler )
    {
        pTaskScheduler          = new BST_CTaskSchdler;
    }
    return pTaskScheduler;
}


BST_CTaskSchdler::BST_CTaskSchdler ( BST_VOID )
{
#if( 0 != BST_BLOCKED_THREAD_NUM )
    BST_UINT32              ulCnt;
    BST_CHAR                cThreadName[BST_BLOCKED_THREAD_LEN];
    BST_OS_MEMSET( cThreadName, 0, BST_OS_SIZEOF( cThreadName ) );
#endif
    m_ulTimerId             = BST_OS_TimerCreateCpp ( this, BST_NULL_PTR );
    m_ulSystemTick          = 0;
    m_ulBlockInfo           = BST_AS_BLOCKED_BY_NO_SERVICE;
    m_bTaskMissExec         = BST_FALSE;
    g_ucAppInitCnt          = 0;
    lstInit( &g_stPTaskList );
#ifdef BST_UNBLOCKED_OWN_THREAD
    /*
     * �����������Ӧ�����Լ��Ķ����̣߳��򴴽�����߳�
     */
    BST_OS_CreateThread ( (BST_INT8 *)"Bastet UnBlocked Thread",
                          (BST_OS_THREAD_T)AppThread,
                          &m_pstUnBlockTaskMbx,
                           BST_OS_STACK_SIZE_XL,
                           BST_OS_PRIO_LOW );
#endif
#if( 0 != BST_BLOCKED_THREAD_NUM )
    /*
     * ���������Ӧ�ý��̲�Ϊ0�����ʼ�������̣߳���������������ָ��
     */
    for ( ulCnt = 0; ulCnt < BST_BLOCKED_THREAD_NUM; ulCnt ++ )
    {
        m_pastBlockTaskMbx[ ulCnt ]     = BST_NULL_PTR;

        snprintf( cThreadName, BST_OS_SIZEOF( cThreadName ), "Bastet %d Blocked Thread", ulCnt );
        BST_OS_CreateThread ( (BST_INT8 *)cThreadName,
                              (BST_OS_THREAD_T)BST_CTaskSchdler::AppThread,
                              &m_pastBlockTaskMbx[ulCnt],
                               BST_OS_STACK_SIZE_XL,
                               BST_OS_PRIO_HIGH );
        BST_DBG_LOG2 ( "BST_CTaskSchdler::BST_CTaskSchdler Blocked Task %u Create, MailBoxId=%p ",
                       ulCnt, &m_pastBlockTaskMbx[ulCnt] );
    }
#endif
    RegAsNotice( BST_AS_EVT_L3_RRC_STATE );
    RegAsNotice( BST_AS_EVT_L3_BLOCK_INFO );
}


BST_CTaskSchdler::~BST_CTaskSchdler ( BST_VOID )
{
#ifdef BST_UNBLOCKED_OWN_THREAD
    m_pstUnBlockTaskMbx = BST_NULL_PTR;
#endif
}


BST_VOID BST_CTaskSchdler::TimerExpired(
    BST_OS_TIMERID_T    ulId,
    BST_VOID           *pvPara)
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNodeNext;

    if ( !BST_OS_IsTimerValid (m_ulTimerId) )
    {
        BST_RLS_LOG1( "BST_CTaskSchdler::TimerExpired m_ulTimerId=%u is invalid",
                      m_ulTimerId );
        return;
    }
    if ( ulId != m_ulTimerId )
    {
        BST_RLS_LOG2( "BST_CTaskSchdler::TimerExpired ulId=%u,m_ulTimerId=%u",
                      ulId, m_ulTimerId );
        return;
    }
    /*
     * ���û��������ֱ�ӷ��أ������κβ���
     */
    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::TimerExpired g_stPTaskList count=0" );
        return;
    }

    /*
     * ����ϵͳTICKֵ
     */
    m_ulSystemTick         += BST_TASK_SYS_TICKS;
    BST_DBG_LOG1 ( "BST_CTaskSchdler::TimerExpired Scheduler TimeOut, Tick=%d ",
                   m_ulSystemTick );

    /*
     * ���������б���ȡ���񲢽�����Ӧ����
     */
    for ( pstPtaskNode = ( BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = pstPtaskNodeNext )
    {
        pstPtaskNodeNext    = ( BST_CORE_PTASK_NODE_STRU *)
                              lstNext((NODE *)pstPtaskNode);
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        /*
         * �������Ϊ�գ������״̬���е���
         */
        ScheduleTask ( pstPtaskNode->pcTask );
    }
    /*
     * �ٴ�����ϵͳTICK��ʱ��
     */
    BST_OS_TimerStart ( m_ulTimerId, BST_TASK_SYS_BASE_TIMELEN );
}

BST_BOOL BST_CTaskSchdler::TryTaskExist ( BST_VOID )
{
    BST_UINT32                  ulNextTick;
    BST_TASK_STATE_ENUM_UINT8   enTaskState;
    BST_SRV_CTaskMng           *pcTaskManager;
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    ulNextTick                  = 0;
    pcTaskManager               = BST_SRV_CTaskMng::GetInstance ();
    BST_ASSERT_NULL_RTN( pcTaskManager, BST_FALSE );
    /*
     * �ڵ�ǰϵͳֵ��һ��TICK��λ�������һʱ��TICKֵ
     */
    ulNextTick                  = m_ulSystemTick + BST_TASK_SYS_TICKS;

    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode ) )
    {
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        /*
         * �������û��ִ����ɣ����ڷ�æ״̬������������
         */
        if ( BST_TRUE == pstPtaskNode->pcTask->IsBusy () )
        {
            continue;
        }
       /*
        * ���TICKֵ�ܹ�����������������˵�����˸���������
        */
        if ( 0 == ( ulNextTick % pstPtaskNode->pcTask->m_ulCycle ) )
        {
            enTaskState         = pstPtaskNode->pcTask->GetState ();
            if ( BST_TASK_STATE_START == enTaskState )
            {
                return BST_TRUE;
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }
    }
    return BST_FALSE;
}


BST_VOID BST_CTaskSchdler::Execute( BST_CORE_CPTask *pC_PTask )
{
    BST_RUN_MODE_ENUM_UINT8     enTaskRunMode;
#if( 0 != BST_BLOCKED_THREAD_NUM )
    BST_STATIC BST_UINT32       ulUnblkedCnt = 0;
#endif

    enTaskRunMode               = pC_PTask->GetRunMode ();
    pC_PTask->m_ulSuspCounter   = 0;
    /*
     * ������������ģʽ������ִ���������
     */
    switch ( enTaskRunMode )
    {
        /*
         * ���������������û�е����̣߳���ֱ��ִ�У�������������ʼ�
         * ��ͬ������ulUnblkedCntͳһ���䣬ƽ�����߳����񸺺�
         */
        case BST_TASK_RUN_BLOCKED:
#if( 0 != BST_BLOCKED_THREAD_NUM )
            if ( ulUnblkedCnt >= BST_BLOCKED_THREAD_NUM )
            {
                ulUnblkedCnt    = 0;
            }
            if ( BST_NULL_PTR == m_pastBlockTaskMbx[ulUnblkedCnt] )
            {
                BST_RLS_LOG1 ( "BST_CTaskSchdler::Execute Blocked Thread %d is not ready",
                               ulUnblkedCnt );
                return;
            }
            BST_OS_SendMail ( m_pastBlockTaskMbx[ulUnblkedCnt], pC_PTask );
            ulUnblkedCnt++;
#else
            pC_PTask->PEntry();
#endif
            break;
        /*
         * �����������������û�е����̣߳���ֱ��ִ�У�������������ʼ�
         */
        case BST_TASK_RUN_UNBLOCKED:
#ifdef BST_UNBLOCKED_OWN_THREAD
            if ( BST_NULL_PTR == m_pstUnBlockTaskMbx )
            {
                BST_RLS_LOG ( "BST_CTaskSchdler::Execute UnBlocked Thread is not ready" );
                return;
            }
            BST_OS_SendMail ( m_pstUnBlockTaskMbx, pC_PTask );
#else
            pC_PTask->PEntry();
#endif
            break;

        default:
            break;
    }
}


BST_VOID    BST_CTaskSchdler::ScheduleTask( BST_CORE_CPTask *pC_PTask )
{
    BST_SRV_CTaskMng           *pcTaskManager;
    BST_TASK_STATE_ENUM_UINT8   enTaskState;

    pcTaskManager               = BST_SRV_CTaskMng::GetInstance ();
    BST_ASSERT_NULL( pcTaskManager );

    /*
     * ��ڼ��
     */
    if ( BST_NULL_PTR == pC_PTask )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::ScheduleTask pC_PTask=NULL" );
        return;
    }
    /*
     * ����ϴ�ִ�е��¼���δ��ɣ����β�����
     */
    if ( BST_TRUE == pC_PTask->IsBusy () )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::ScheduleTask pC_PTask Is Busy" );
        return;
    }
    /*
     * ���ϵͳTICK���Ա���������������˵����������������ʱ��
     */
    if ( 0 != m_ulSystemTick%pC_PTask->m_ulCycle )
    {
        return;
    }
    enTaskState                 = pC_PTask->GetState ();

    BST_DBG_LOG3( "BST_CTaskSchdler::ScheduleTask enTaskState:%d,m_ulTaskBlockState:%d,m_ulBlockInfo:%d",
                 enTaskState, pC_PTask->m_ulTaskBlockState,m_ulBlockInfo);
    switch ( enTaskState )
    {
        /*
         * �������ֹͣ��ֻ����suspendCounterΪ0�������κ�����
         */
        case BST_TASK_STATE_STOPED:
            pC_PTask->m_ulSuspCounter    = 0;
            break;

        /*
         * ���������𳬹�����޶ȣ�������ɾ��֮
         */
        case BST_TASK_STATE_SUSPEND:
            pC_PTask->m_ulSuspCounter ++;
            if ( pC_PTask->m_ulSuspCounter >= BST_TASK_MAX_SYSPEND )
            {
                pcTaskManager->Remove ( pC_PTask->m_usProcId, pC_PTask->m_usTaskId );
            }
            break;
        /*
         * �����Ϊ��������̬�������ִ��
         */
        case BST_TASK_STATE_START:
            switch(pC_PTask->m_ulTaskBlockState)
            {
                /*��ǰ����normal״̬�������ڵ�������ʱ�������ǰΪunblock״̬����ִ������
                               �������õ�ǰtask������״̬Ϊexpired
                            */
                case BST_TASK_BLOCK_STATE_NORMAL:
                    if( BST_AS_UNBLOCKED == m_ulBlockInfo )
                    {
                        Execute( pC_PTask );
                    }
                    else
                    {
                        pC_PTask->m_ulTaskBlockState = BST_TASK_BLOCK_STATE_EXPIRED;
                        m_bTaskMissExec              = BST_TRUE;
                    }
                    break;
                /*��ǰ����EXPIRED״̬������ָ�unblock״̬��ֱ�ӵ��ȣ��÷�֧Ϊ�쳣������֧*/
                case BST_TASK_BLOCK_STATE_EXPIRED:
                    if( BST_AS_UNBLOCKED == m_ulBlockInfo )
                    {
                        Execute( pC_PTask );
                        pC_PTask->m_ulTaskBlockState = BST_TASK_BLOCK_STATE_NORMAL;
                    }
                    break;
                 default:
                    break;

            }
            break;
        default:
            break;
    }

    if(BST_TASK_BLOCK_STATE_IGNORE == pC_PTask->m_ulTaskBlockState)
    {
        pC_PTask->m_ulTaskBlockState = BST_TASK_BLOCK_STATE_NORMAL;
    }
}
BST_VOID BST_CTaskSchdler::AsEventCallback(
    BST_AS_EVT_ENUM_UINT32    enEvent,
    BST_UINT32                ulLength,
    BST_VOID                 *pvData )
{
    BST_UINT32          ulPara;

    switch( enEvent )
    {
        /*
         * ������RRC״̬��Ϣ����RRC���ӳɹ�ʱ���鿴��ǰʣ��ʱ���Ƿ񿿽�
         */
        case BST_AS_EVT_L3_RRC_STATE:
            if ( BST_OS_SIZEOF(ulPara) != ulLength )
            {
                break;
            }
            if ( BST_NULL_PTR == pvData )
            {
                break;
            }
            BST_OS_MEMCPY( &ulPara, pvData, ulLength );
            if( BST_AS_RRC_CONNECTED == ulPara )
            {
                ulPara      = BST_OS_TimerIsStop( m_ulTimerId );
                if ( BST_TRUE == ulPara )
                {
                    break;
                }
                ulPara      = BST_OS_TimeGetRemain( m_ulTimerId );
                if ( 0 == ulPara )
                {
                    break;
                }
                ulPara      = NearRrcTrig ( ulPara );
                BST_OS_TimerStart( m_ulTimerId, ulPara );
            }
            break;

        case BST_AS_EVT_L3_BLOCK_INFO:
            if ( BST_OS_SIZEOF(BST_UINT32) != ulLength )
            {
                BST_RLS_LOG1("BST_CTaskSchdler::AsEventCallback Error blockinfo Length = %u:", ulLength );
                break;
            }

            UtranBlockInfoChgProc( (BST_UINT32 *)pvData );
            break;
        default:
            break;
    }
}


BST_UINT32 BST_CTaskSchdler::NearRrcTrig ( BST_UINT32 const ulSysTimerRemainMs )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_UINT32                  ulNextSysTick;
    BST_UINT32                  ulNextLongCycle;

    ulNextLongCycle             = 0;
    ulNextSysTick               = m_ulSystemTick + BST_TASK_SYS_TICKS;
    /*
     * ���������б��ҳ�������Ч����
     */
    for( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
         pstPtaskNode!= BST_NULL_PTR;
         pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        if( 0 == pstPtaskNode->pcTask->m_ulCycle )
        {
            continue;
        }
        if( BST_TRUE == pstPtaskNode->pcTask->IsBusy () )
        {
            continue;
        }
        if( BST_TASK_STATE_START != pstPtaskNode->pcTask->GetState () )
        {
            continue;
        }
        /*
         * �鿴�Ƿ�������������Tick������������ڵ���
         */
        if( 0 == ( ulNextSysTick % pstPtaskNode->pcTask->m_ulCycle ) )
        {
            if( pstPtaskNode->pcTask->m_ulCycle > ulNextLongCycle )
            {
                ulNextLongCycle = pstPtaskNode->pcTask->m_ulCycle;
            }
        }
    }
    /*
     * ��ȡ��ǰϵͳ���ڣ���ȡ���������ʣ��ʱ����ڸ�ֵ����˵���㹻����
     */
    ulNextLongCycle             = BST_CORE_GetCycleToMs( ulNextLongCycle );
    if( BST_TASK_IsNearEnough( ulSysTimerRemainMs, ulNextLongCycle ) )
    {
        BST_RLS_LOG("BST_CTaskSchdler::NearRrcTrig Closing To RRC Enough, Periodic Runing after 200Ms");
        return BST_TASK_RRC_SEND_TIMER;
    }
    else
    {
        return ulSysTimerRemainMs;
    }
}


BST_UINT32 BST_CTaskSchdler::ChkTaskExist ( BST_CORE_CPTask *pC_PTask )
{
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;

    if ( BST_NULL_PTR == pC_PTask )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::ChkTaskExist pC_PTask=NULL" );
        return BST_FALSE;
    }

    if ( 0 == lstCount( &g_stPTaskList ) )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::ChkTaskExist g_stPTaskList count=0" );
        return BST_FALSE;
    }

    /*
     * ����������Ա�pcPtask����ȵļ�Ϊ�ҵ�
     */
    for ( pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
          pstPtaskNode!= BST_NULL_PTR;
          pstPtaskNode = (BST_CORE_PTASK_NODE_STRU *)lstNext((NODE *)pstPtaskNode) )
    {
        if ( BST_NULL_PTR == pstPtaskNode->pcTask )
        {
            continue;
        }
        if ( pC_PTask == pstPtaskNode->pcTask )
        {
            return BST_TRUE;
        }
    }
    return BST_FALSE;
}


BST_VOID BST_CTaskSchdler::AppThread ( BST_VOID* arg )
{
    BST_CORE_CPTask    *pcTask;
    BST_OS_MBX_T      **pstMailBox;
    BST_OS_LOCKCNT_T    tThreadLockCnt;
    BST_UINT32          ulRtnVal;

    if ( BST_NULL_PTR == arg )
    {
        return;
    }
    /*
     * �̲߳�����ʼ�����������䣬���б�ʶ
     */
    tThreadLockCnt      = BST_OS_ThreadLock ();
    pstMailBox          = (BST_OS_MBX_T **)arg;
   *pstMailBox          = BST_OS_CreateMbx
                        ( BST_OS_GetCurrentThreadId (), BST_MAX_APP_NUMBER );
    BST_SetThreadInitFlag ( BST_APP_THREAD_FLAG << g_ucAppInitCnt );
    g_ucAppInitCnt++;
    BST_OS_ThreadUnLock ( tThreadLockCnt );

    /*
     * �����߳���ѭ�����ȴ��ʼ����ʼ�����Ϊ����ִ�е�����
     */
    for(;;)
    {
        ulRtnVal        = BST_OS_RecvMail
                       ( *pstMailBox, (BST_VOID **)&pcTask, BST_OS_SYS_FOREVER );
        BST_ASSERT_NORM( BST_OS_SYS_TIMEOUT == ulRtnVal );
        if ( BST_NULL_PTR == pcTask )
        {
            continue;
        }
        if ( BST_FALSE == ChkTaskExist (pcTask) )
        {
            continue;
        }
        if ( BST_TRUE == pcTask->IsBusy () )
        {
            continue;
        }
        pcTask->PEntry ();
    }
}

BST_VOID BST_CTaskSchdler::UtranBlockInfoChgProc( BST_UINT32 *pulBlockInfo )
{
    BST_INT32                   lTaskCnt;
    BST_UINT32                  ulNextTickRemainTime;
    BST_UINT32                  ulBlockInfo;
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNode;
    BST_CORE_PTASK_NODE_STRU   *pstPtaskNodeNext;
    BST_BOOL                    bTimerStop;

    if( BST_NULL_PTR == pulBlockInfo)
    {
        return;
    }
    ulBlockInfo     = (BST_UINT32 )*pulBlockInfo;
    BST_DBG_LOG2( "BST_CTaskSchdler::UtranBlockInfoChgProc blockold=u%, blockNew=u%",
                  m_ulBlockInfo,ulBlockInfo);

    if ( m_ulBlockInfo == ulBlockInfo )
    {
        return;
    }
    m_ulBlockInfo           = ulBlockInfo;

    if ( BST_AS_UNBLOCKED == m_ulBlockInfo )
    {

        BST_DBG_LOG1( "BST_CTaskSchdler::UtranBlockInfoChgProc :%d", m_bTaskMissExec );
        if(BST_FALSE == m_bTaskMissExec)
        {
            return;
        }
        lTaskCnt            = lstCount( &g_stPTaskList );

        BST_DBG_LOG1( "BST_CTaskSchdler::UtranBlockInfoChgProc TaskNum=u%", lTaskCnt );

        if ( 0 == lTaskCnt )
        {
            return;
        }
        ulNextTickRemainTime = 0;
        bTimerStop      = BST_OS_TimerIsStop( m_ulTimerId );
        if ( BST_FALSE == bTimerStop )
        {
            ulNextTickRemainTime      = BST_OS_TimeGetRemain( m_ulTimerId );
            BST_OS_TimerStop ( m_ulTimerId );
        }

        BST_DBG_LOG2( "BST_CTaskSchdler::UtranBlockInfoChgProc stop:%d,timerremain=u%", bTimerStop,ulNextTickRemainTime );
        /*
         * ���������б���ȡ���񲢽�����Ӧ����
         */
        for ( pstPtaskNode = ( BST_CORE_PTASK_NODE_STRU *)lstFirst( &g_stPTaskList );
              pstPtaskNode!= BST_NULL_PTR;
              pstPtaskNode = pstPtaskNodeNext )
        {
            pstPtaskNodeNext    = ( BST_CORE_PTASK_NODE_STRU *)
                                  lstNext((NODE *)pstPtaskNode);
            if ( BST_NULL_PTR == pstPtaskNode->pcTask )
            {
                continue;
            }
            /*
             * �������Ϊ�գ������״̬���е���
             */
            TrigScheduleTask ( pstPtaskNode->pcTask);
        }

        if((0 == ulNextTickRemainTime) || (ulNextTickRemainTime > BST_TASK_SYS_BASE_TIMELEN))
        {
            ulNextTickRemainTime = BST_TASK_SYS_BASE_TIMELEN;
        }

        BST_OS_TimerStart ( m_ulTimerId, ulNextTickRemainTime );

    }

}



BST_VOID    BST_CTaskSchdler::TrigScheduleTask( BST_CORE_CPTask *pC_PTask)
{
    BST_SRV_CTaskMng           *pcTaskManager;
    BST_TASK_STATE_ENUM_UINT8   enTaskState;
    BST_UINT32                  ulRemainTickNum;

    pcTaskManager               = BST_SRV_CTaskMng::GetInstance ();
    BST_ASSERT_NULL( pcTaskManager );

    /*
     * ��ڼ��
     */
    if ( BST_NULL_PTR == pC_PTask )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::TrigScheduleTask pC_PTask=NULL" );
        return;
    }
    /*
     * ����ϴ�ִ�е��¼���δ��ɣ����β�����
     */
    if ( BST_TRUE == pC_PTask->IsBusy () )
    {
        BST_RLS_LOG( "BST_CTaskSchdler::TrigScheduleTask pC_PTask Is Busy" );
        return;
    }
    /*
     * ���ϵͳTICK���Ա���������������˵����������������ʱ��
     */
    enTaskState                 = pC_PTask->GetState ();

    BST_DBG_LOG2( "BST_CTaskSchdler::TrigScheduleTask enTaskState:%d,m_ulTaskBlockState:%d",
                       enTaskState,pC_PTask->m_ulTaskBlockState );

    switch ( enTaskState )
    {
        case BST_TASK_STATE_START:
            if( BST_TASK_BLOCK_STATE_EXPIRED ==  pC_PTask->m_ulTaskBlockState )
            {
                Execute( pC_PTask );
                ulRemainTickNum = pC_PTask->m_ulCycle - (m_ulSystemTick % pC_PTask->m_ulCycle);
                if( ulRemainTickNum > BST_TASK_SYS_TICKS )
                {
                    pC_PTask->m_ulTaskBlockState    = BST_TASK_BLOCK_STATE_NORMAL;
                }
                else
                {
                    pC_PTask->m_ulTaskBlockState    = BST_TASK_BLOCK_STATE_IGNORE;
                }
                m_bTaskMissExec                     = BST_FALSE;
            }
            return;
        default:
            break;
    }
}



BST_VOID BST_SRV_InitAppThreads ( BST_VOID )
{
    BST_CTaskSchdler::GetInstance ();
}
