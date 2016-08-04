/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : SCMProc.h
  �� �� ��      : ����
  ��    ��      : zhuli
  ��������      : 2012��8��3��
  ����޸�      :
  ��������      : ��ͷ�ļ�ΪSOCP API��ͷ�ļ�����Ҫ�ṩ���ⲿ����ʹ��
  �����б�      :
  �޸���ʷ      :
  1.��    ��    : 2012��8��3��
    ��    ��    : zhuli
    �޸�����    : �����ļ�

******************************************************************************/
#ifndef _SCM_PROC_H_
#define _SCM_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "DrvInterface.h"
#include "vos.h"

#if(VOS_OS_VER == VOS_LINUX)
#include <asm/dma-mapping.h>
#include <linux/dma-mapping.h>
#include <asm/io.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#endif

#if(VOS_OS_VER == VOS_VXWORKS)
#include "cacheLib.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#if (FEATURE_OFF == FEATURE_MERGE_OM_CHAN)
/**************************************************************************
  2 �궨��
**************************************************************************/

//#define OM_DEBUG_PRINT

/* ����꿪�� */
#if (VOS_OS_VER == VOS_WIN32)
#define SCM_ACORE
#define SCM_CCORE
#else

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#define SCM_ACORE
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#define SCM_CCORE
#endif

#endif    /*(VOS_OS_VER == VOS_WIN32)*/

/* ͨ���������ݺ����ݳ��� */
typedef VOS_VOID (*SCM_CODERDESTFUCN)(SOCP_CODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT8 *pucPHYData, VOS_UINT32 ulSize);

/* ͨ���������ݡ����ݳ��ȡ��ؾ����ݡ��ؾ����ݳ��� */
typedef VOS_VOID (*SCM_DECODERDESTFUCN)(SOCP_DECODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT32 ulSize, VOS_UINT8 *pucRBData, VOS_UINT32 ulRBSize);

#if (VOS_OS_VER == VOS_WIN32)               /*PC Stub*/
#define SCM_CODER_SRC_NUM           (4)       /* ����Դͨ������ */
#define SCM_CODER_DST_NUM           (3)       /* ����Ŀ��ͨ������ */
#define SCM_DECODER_SRC_NUM         (1)       /* ����Դͨ������ */
#define SCM_DECODER_DST_NUM         (1)       /* ����Ŀ��ͨ������ */

#else
#if (OSA_CPU_CCPU == VOS_OSA_CPU)

#if (RAT_MODE != RAT_GU)                /* Mutil Mode */
#define SCM_CODER_SRC_NUM           (4)       /* ����Դͨ������ */
#else                                       /* GU Single Mode */
#define SCM_CODER_SRC_NUM           (1)       /* ����Դͨ������ */
#endif  /* (RAT_MODE != RAT_GU) */

#endif  /* (OSA_CPU_CCPU == VOS_OSA_CPU) */

#if (OSA_CPU_ACPU == VOS_OSA_CPU)

#if (RAT_MODE != RAT_GU)                /* Mutil Mode */
#define SCM_CODER_SRC_NUM           (3)       /* ����Դͨ������ */
#define SCM_CODER_DST_NUM           (3)       /* ����Ŀ��ͨ������ */
#define SCM_DECODER_SRC_NUM         (1)       /* ����Դͨ������ */
#define SCM_DECODER_DST_NUM         (1)       /* ����Ŀ��ͨ������ */
#else                                       /* GU Single Mode */
#define SCM_CODER_SRC_NUM           (1)       /* ����Դͨ������ */
#define SCM_CODER_DST_NUM           (1)       /* ����Ŀ��ͨ������ */
#endif  /* (RAT_MODE != RAT_GU) */

#endif  /* (OSA_CPU_ACPU == VOS_OSA_CPU) */

#endif /*(VOS_OS_VER == VOS_WIN32)*/


#define SCM_CODER_SRC_MAX_LEN       (16*1024)       /* ����ͨ����������ݳ���  */

#define SCM_DECODER_SRC_SIZE        (8*1024)        /* ����Դͨ���ռ��С */
#define SCM_DECODER_DST_SIZE        (8*1024)        /* ����Ŀ��ͨ���ռ��С */
#define SCM_CODER_DST_IND_SIZE      (80*1024)       /* �����ϱ�����Ŀ��ͨ���ռ��С */
#define SCM_CODER_DST_CNF_SIZE      (16*1024)       /* ����ظ�����Ŀ��ͨ���ռ��С */

#define SCM_CODER_DST_IND_SD_SIZE   (1024*1229)     /* SD�������ϱ�����Ŀ��ͨ���ռ��С 1.2M */

#define SCM_CODE_SRC_BD_NUM         (4*1024)        /* ��ʽͨ��BD�ĸ��� */
#define SCM_CODE_SRC_RD_NUM         (4*1024)        /* ��ʽͨ��RD�ĸ��� */

#define SCM_CODER_SRC_BDSIZE        (sizeof(SOCP_BD_DATA_STRU)*SCM_CODE_SRC_BD_NUM)   /* ��ʽͨ����BD�ռ� */
#define SCM_CODER_SRC_RDSIZE        (sizeof(SOCP_RD_DATA_STRU)*SCM_CODE_SRC_RD_NUM)   /* ��ʽͨ����RD�ռ� */

#define SCM_CODER_DST_THRESHOLD_GU  (4)             /* GU����Ŀ��ͨ����ֵ����λKB */

#define SCM_CODER_DST_THRESHOLD_L   (4)             /* L����Ŀ��ͨ����ֵ����λKB */

#define SCM_CODER_DST_GTHRESHOLD    ((4*1024)+8)    /* ����Դͨ���ٲ���ֵ */

#define SCM_DECODER_DST_THRESHOLD   (1)             /* ����Ŀ��ͨ����ֵ, ��λHDLC֡ */

#define SCM_CODER_SRC_RD_THRESHOLD  (0)             /* ����Դͨ��RD��ֵ */

#define SCM_DATA_SAVE_TAG           (0x5A)          /* SOCP�������ݵļ����� */

#if (VOS_OS_VER == VOS_WIN32)

#ifdef OAM_UT_DEBUG        /*only for UT test*/
#define SCM_MALLOC(ulBytes)         V_MemAlloc(0, 0, ulBytes, 0, 0, 0)
#else                     /*for ST test*/
#define SCM_MALLOC(ulBytes)         malloc(ulBytes)
#endif /* OAM_UT_DEBUG */
#endif /*(VOS_OS_VER == VOS_WIN32)*/

#if((VOS_OS_VER == VOS_WIN32) || (VOS_RTOSCK == VOS_OS_VER))
#define SCM_FLUSH_CACHE(ptr, size)
#define SCM_INVALID_CACHE(ptr, size)
#elif(VOS_OS_VER == VOS_VXWORKS)
#define SCM_FLUSH_CACHE(ptr, size)      cacheFlush(DATA_CACHE, ptr, size)
#define SCM_INVALID_CACHE(ptr, size)    cacheInvalidate(DATA_CACHE, ptr, size);
#elif (VOS_OS_VER == VOS_LINUX)
extern unsigned long long g_astScmDmaMask;
#define SCM_FLUSH_CACHE(ptr, size)                      \
    do{                                                 \
        struct device dev;                              \
        memset(&dev,0,sizeof(struct device));           \
        dev.dma_mask = (unsigned long long *)(&g_astScmDmaMask);    \
        dma_map_single(&dev, ptr, size, DMA_TO_DEVICE);  \
    }while(0)
#define SCM_INVALID_CACHE(ptr, size)                    \
    do{                                                 \
        struct device dev;                              \
        memset(&dev,0,sizeof(struct device));           \
        dev.dma_mask = (unsigned long long *)(&g_astScmDmaMask);    \
        dma_map_single(&dev, ptr, size, DMA_FROM_DEVICE);  \
    }while(0)
#endif


#define SCM_MALLOC_MAX_SIZE     0x200000
#define SCM_MALLOC_MAX_INDEX    9           /*page_size Ϊ4K*/
#define SCM_PAGE_SIZE      		0x1000

/**************************************************************************
  3 ö�ٶ���
**************************************************************************/
enum  SCM_CHANNEL_INIT_ENUM
{
    SCM_CHANNEL_UNINIT = 0,             /* δ��ʼ�� */
    SCM_CHANNEL_INIT_SUCC,              /* ��ʼ���ɹ� */
    SCM_CHANNEL_MEM_FAIL,               /* ��ʼ�������ڴ���� */
    SCM_CHANNEL_CFG_FAIL,               /* ��ʼ��ͨ������ */
    SCM_CHANNEL_START_FAIL,             /* ͨ���������� */
    SCM_CHANNEL_INIT_BUTT
};
typedef VOS_UINT32 SCM_CHANNEL_INIT_ENUM_U32;

enum SOCP_SOFT_DECODE_CB_ENUM
{
    SOCP_DECODER_DST_CB_TL_OM,
    SOCP_DECODER_DST_CB_GU_OM,
    SOCP_DECODER_DST_CB_GU_CBT,
    SOCP_DECODER_DST_CB_BUTT
};
typedef VOS_UINT32 SOCP_SOFT_DECODE_CB_ENUM_U32;
/**************************************************************************
  4 �ṹ�嶨��
**************************************************************************/
typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ��ʼ��״̬ */
    VOS_UINT32                  ulChannelID;    /* ͨ��ID */
}SCM_CHANNEL_CFG_HEAD;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_CODER_SRC_ENUM_U32     enChannelID;    /* ����Դͨ��ID���̶����� */
    SOCP_CODER_DST_ENUM_U32     enDstCHID;      /* ����Ŀ��ͨ��ID */
    SOCP_DATA_TYPE_ENUM_UIN32            enDataType;     /* ������Դ���� */
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32       enCHMode;       /* ͨ������ */
    SOCP_CHAN_PRIORITY_ENUM_UIN32        enCHLevel;      /* ͨ�����ȼ� */
    VOS_UINT32                      ulSrcBufLen;    /* ����Դͨ�����ݿռ��С */
    VOS_UINT32                      ulRDBufLen;     /* ����Դͨ��RD���ݿռ��С */
    VOS_UINT8                   *pucSrcBuf;     /* ����Դͨ�����ݿռ��ڴ�ָ�� */
    VOS_UINT8                   *pucSrcPHY;
    VOS_UINT8                   *pucRDBuf;      /* ����Դͨ��RD���ݿռ��ڴ�ָ�� */
    VOS_UINT8                   *pucRDPHY;
}SCM_CODER_SRC_CFG_STRU;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_CODER_DST_ENUM_U32     enChannelID;    /* ����Ŀ��ͨ��ID���̶����� */
    VOS_UINT32                  ulBufLen;       /* ����Ŀ��ͨ�����ݿռ��С */
    VOS_UINT32                  ulThreshold;    /* ����Ŀ��ͨ����ֵ */
    VOS_UINT8                   *pucBuf;        /* ����Ŀ��ͨ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucBufPHY;
    SCM_CODERDESTFUCN           pfunc;          /* ����Ŀ��ͨ�����ݴ���ص����� */
}SCM_CODER_DEST_CFG_STRU;


typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_DECODER_SRC_ENUM_U32   enChannelID;    /* ����Դͨ��ID���̶����� */
    VOS_UINT32                  ulSrcBufLen;    /* ����Դͨ�����ݿռ��С */
    VOS_UINT32                  ulRfu;
    VOS_UINT8                   *pucSrcBuf;     /* ����Դͨ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucSrcPHY;
}SCM_DECODER_SRC_CFG_STRU;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_DECODER_DST_ENUM_U32   enChannelID;    /* ����Ŀ��ͨ��ID���̶����� */
    SOCP_DECODER_SRC_ENUM_U32   enSrcCHID;      /* ����Դͨ��ID */
    SOCP_DATA_TYPE_ENUM_UIN32            enDataType;     /* ����������Դ���� */
    VOS_UINT32                  ulBufLen;       /* ����Ŀ�����ݿռ��С */
    VOS_UINT32                  ulThreshold;    /* ����Ŀ��ͨ����ֵ */
    VOS_UINT8                   *pucBuf;        /* ����Ŀ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucBufPHY;
    SCM_DECODERDESTFUCN         pfunc;          /* ����Ŀ��ͨ�����ݴ���ص����� */
}SCM_DECODER_DEST_CFG_STRU;

#define INNER_LOG_DATA_MAX                   0x40

typedef struct
{
    VOS_UINT32                  ulSlice;
    VOS_UINT32                  ulFileNO;
    VOS_INT32                   lLineNO;
    VOS_UINT32                  ulP1;
    VOS_UINT32                  ulP2;
}INNER_LOG_RECORD_STRU;

typedef struct
{
    VOS_UINT32                  ulCnt;
    INNER_LOG_RECORD_STRU       astLogData[INNER_LOG_DATA_MAX];
}INNER_LOG_DATA_STRU;

typedef struct
{
    VOS_UINT32                  aulBDUsedMax[SCM_CODER_SRC_NUM];    /* ��¼�ϲ���õķ���Դͨ��BDʹ�����ֵ */
    VOS_UINT32                  aulRDUsedMax[SCM_CODER_SRC_NUM];    /* ��¼�ϲ���õķ���ԴRDʹ�����ֵ */
    INNER_LOG_DATA_STRU         stCoderSrcLog;                      /* ��¼�ϲ���õķ��ͽӿ�log */
    INNER_LOG_DATA_STRU         stCoderSrcRDLog;                    /* ��¼�ϲ���õ��ͷ�RD�ӿ�log */
    /*INNER_LOG_DATA_STRU         stCoderSrcReset;*/                /* ��¼�ϲ���õĸ�λ�ӿ�log,�ݲ�ʹ�� */
    INNER_LOG_DATA_STRU         stCoderSrcErr;                      /* ��¼����Դͨ���ص�����Log */
#ifdef SCM_ACORE
    INNER_LOG_DATA_STRU         stCoderDstLog;                      /* ��¼�ص��ϲ�ı���Ŀ��ͨ������Log */
    INNER_LOG_DATA_STRU         stCoderDstErr;                      /* ��¼����Ŀ��ͨ���ص�����Log */
    /*INNER_LOG_DATA_STRU         stDoderSrcLog;*/                  /* ��¼�ϲ���õĽ���Դͨ��Log,�ݲ�ʹ�� */
    /*INNER_LOG_DATA_STRU         stDecoderDstLog;*/                /* ��¼�ص��ϲ�Ľ���Ŀ��ͨ������Log,�ݲ�ʹ�� */
    /*INNER_LOG_DATA_STRU         stDecoderDstErr;*/                /* ��¼����Ŀ��ͨ���ص�����Log,�ݲ�ʹ�� */
    /*INNER_LOG_DATA_STRU         stDecoderSrcErr;*/                /* ��¼����Դͨ���ص�����Log,�ݲ�ʹ�� */
#endif
}SCM_INFODATA_STRU;


/**************************************************************************
  5 Log��������
**************************************************************************/
extern VOS_VOID OM_Inner_Log(VOS_CHAR *pucStr, VOS_UINT32 ulP1, VOS_UINT32 ulP2,
                          INNER_LOG_DATA_STRU *pstLogData ,VOS_UINT32 ulFileID, VOS_INT32 lLineNo);

#define SCM_CODER_SRC_LOG(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcLog, VOS_FILE_ID, __LINE__)

#define SCM_CODER_SRCRD_LOG(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcRDLog, VOS_FILE_ID, __LINE__)

#define SCM_CODER_SRCRESET_LOG(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcReset, VOS_FILE_ID, __LINE__)*/

#define SCM_CODER_SRC_ERR(pucStr, ulP1, ulP2)\
	vos_printf("%s, %ul, %ul.\n", pucStr, ulP1, ulP2)
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcErr, VOS_FILE_ID, __LINE__)*/

#ifdef SCM_ACORE
#define SCM_CODER_DST_ERR(pucStr, ulP1, ulP2)\
	printk("%s, %ul, %ul.\n", pucStr, ulP1, ulP2)
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderDstErr, VOS_FILE_ID, __LINE__)*/

#define SCM_DECODER_SRC_LOG(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDoderSrcLog, VOS_FILE_ID, __LINE__)*/

#define SCM_CODER_DST_LOG(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderDstLog, VOS_FILE_ID, __LINE__)

#define SCM_DECODER_DST_LOG(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDecoderDstLog, VOS_FILE_ID, __LINE__)*/

#define SCM_DECODER_DST_ERR(pucStr, ulP1, ulP2)\
	printk("%s, %ul, %ul.\n", pucStr, ulP1, ulP2)
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDecoderDstErr, VOS_FILE_ID, __LINE__)*/

#define SCM_DECODER_SRC_ERR(pucStr, ulP1, ulP2)\
	printk("%s, %ul, %ul.\n", pucStr, ulP1, ulP2)
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDecoderSrcErr, VOS_FILE_ID, __LINE__)*/
#endif

extern SCM_INFODATA_STRU           g_stSCMInfoData;    /* ���ڱ���log��Ϣ */

/**************************************************************************
  6 ��������
**************************************************************************/

extern VOS_UINT32 OM_GetSlice(VOS_VOID);

extern VOS_UINT8* SCM_VirtMemAlloc(VOS_UINT32 ulSize,VOS_UINT_PTR *pulRealAddr);

extern VOS_UINT_PTR SCM_MemVirtToPhy(VOS_UINT8 *pucCurVirtAddr, VOS_UINT8 *pucPhyStart, VOS_UINT8 *pucVirtStart, VOS_UINT32 ulBufLen);

extern VOS_UINT_PTR SCM_MemPhyToVirt(VOS_UINT8 *pucCurPhyAddr, VOS_UINT8 *pucPhyStart, VOS_UINT8 *pucVirtStart, VOS_UINT32 ulBufLen);

extern VOS_UINT32 SCM_RlsSrcRDAll(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT_PTR *pulDataAddr, VOS_UINT32 *pulDataLen);

extern VOS_UINT32 SCM_RlsSrcRDFirst(SOCP_CODER_SRC_ENUM_U32 enChanlID,VOS_UINT_PTR *pulDataAddr,VOS_UINT32 *pulDataLen);

extern VOS_UINT32 SCM_GetBDFreeNum(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT32 *pulBDNum);

extern VOS_UINT32 SCM_SendCoderSrc(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT8 *pucSendData, VOS_UINT32 ulSendLen);

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT32 SCM_RlsDestBuf(VOS_UINT32 ulChanlID, VOS_UINT32 ulReadSize);

extern VOS_UINT32 SCM_RegCoderDestProc(SOCP_CODER_DST_ENUM_U32 enChanlID,SCM_CODERDESTFUCN func);

extern VOS_UINT32 SCM_RegDecoderDestProc(SOCP_DECODER_DST_ENUM_U32 enChanlID,SCM_DECODERDESTFUCN func);

extern VOS_UINT32 SCM_SendDecoderSrc(SOCP_DECODER_SRC_ENUM_U32 enChanlID, VOS_UINT8 *pucSendData, VOS_UINT32 ulSendLen);


#endif

#else


/**************************************************************************
  2 �궨��
**************************************************************************/
/* ����꿪�� */
#if (VOS_OS_VER == VOS_WIN32)
#define SCM_ACORE
#define SCM_CCORE
#define SCM_SNCHECK
#else

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#define SCM_ACORE
#define SCM_SNCHECK
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#define SCM_CCORE
#endif

#endif    /*(VOS_OS_VER == VOS_WIN32)*/

/* ͨ���������ݺ����ݳ��� */
typedef VOS_VOID (*SCM_CODERDESTFUCN)(SOCP_CODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT8 *pucPHYData, VOS_UINT32 ulSize);

/* ͨ���������ݡ����ݳ��ȡ��ؾ����ݡ��ؾ����ݳ��� */
typedef VOS_VOID (*SCM_DECODERDESTFUCN)(SOCP_DECODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT32 ulSize, VOS_UINT8 *pucRBData, VOS_UINT32 ulRBSize);

#if (VOS_OS_VER == VOS_WIN32)               /*PC Stub*/
#define SCM_CODER_SRC_NUM           (6)       /* ����Դͨ������ */
#define SCM_CODER_DST_NUM           (2)       /* ����Ŀ��ͨ������ */
#define SCM_DECODER_SRC_NUM         (1)       /* ����Դͨ������ */
#define SCM_DECODER_DST_NUM         (1)       /* ����Ŀ��ͨ������ */

#else
#if (OSA_CPU_CCPU == VOS_OSA_CPU)

#if (RAT_MODE != RAT_GU)                /* Mutil Mode */
#define SCM_CODER_SRC_NUM           (5)       /* ����Դͨ������ */
#else                                       /* GU Single Mode */
#define SCM_CODER_SRC_NUM           (2)       /* ����Դͨ������ */
#endif  /* (RAT_MODE != RAT_GU) */

#endif  /* (OSA_CPU_CCPU == VOS_OSA_CPU) */

#if (OSA_CPU_ACPU == VOS_OSA_CPU)

#if (RAT_MODE != RAT_GU)                /* Mutil Mode */
#define SCM_CODER_SRC_NUM           (4)       /* ����Դͨ������ */
#define SCM_CODER_DST_NUM           (2)       /* ����Ŀ��ͨ������ */
#define SCM_DECODER_SRC_NUM         (1)       /* ����Դͨ������ */
#define SCM_DECODER_DST_NUM         (1)       /* ����Ŀ��ͨ������ */
#else                                       /* GU Single Mode */
#define SCM_CODER_SRC_NUM           (2)       /* ����Դͨ������ */
#define SCM_CODER_DST_NUM           (2)       /* ����Ŀ��ͨ������ */
#endif  /* (RAT_MODE != RAT_GU) */

#endif  /* (OSA_CPU_ACPU == VOS_OSA_CPU) */

#endif /*(VOS_OS_VER == VOS_WIN32)*/


#define SCM_CODER_SRC_MAX_LEN       (16*1024)       /* ����ͨ����������ݳ���  */

#define SCM_DECODER_SRC_SIZE        (8*1024)        /* ����Դͨ���ռ��С */
#define SCM_DECODER_DST_SIZE        (8*1024)        /* ����Ŀ��ͨ���ռ��С */
#define SCM_CODER_DST_IND_SIZE      (80*1024)       /* �����ϱ�����Ŀ��ͨ���ռ��С */
#define SCM_CODER_DST_CNF_SIZE      (16*1024)       /* ����ظ�����Ŀ��ͨ���ռ��С */

#define SCM_CODER_DST_IND_SD_SIZE   (1024*1229)     /* LOG3.5�ӳ��ϱ�����Ŀ��ͨ���ռ��С 1.2M */

#define SCM_CODE_SRC_BD_NUM         (4*1024)        /* ��ʽͨ��BD�ĸ��� */
#define SCM_CODE_SRC_RD_NUM         (4*1024)        /* ��ʽͨ��RD�ĸ��� */

#define SCM_CODER_SRC_BDSIZE        (sizeof(SOCP_BD_DATA_STRU)*SCM_CODE_SRC_BD_NUM)   /* ��ʽͨ����BD�ռ� */
#define SCM_CODER_SRC_RDSIZE        (sizeof(SOCP_RD_DATA_STRU)*SCM_CODE_SRC_RD_NUM)   /* ��ʽͨ����RD�ռ� */

#define SCM_CODER_DST_THRESHOLD     (4)             /* ����Ŀ��ͨ����ֵ����λKB */

#define SCM_CODER_DST_GTHRESHOLD    ((4*1024) + 8 + 128)    /* ����Դͨ���ٲ���ֵ + DMAһ����С�����ֽ� */

#define SCM_DECDOER_DST_THRESHOLD   (1)             /* ����Ŀ��ͨ����ֵ, ��λHDLC֡ */

#define SCM_CODER_SRC_RD_THRESHOLD  (0)             /* ����Դͨ��RD��ֵ */

#define SCM_DATA_SAVE_TAG           (0x5A)          /* SOCP�������ݵļ����� */

#define INNER_LOG_DATA_MAX                   0x40

#if (VOS_OS_VER == VOS_WIN32)

#ifdef OAM_UT_DEBUG        /*only for UT test*/
#define SCM_MALLOC(ulBytes)         V_MemAlloc(0, 0, ulBytes, 0, 0, 0)
#else                     /*for ST test*/
#define SCM_MALLOC(ulBytes)         malloc(ulBytes)
#endif /* OAM_UT_DEBUG */
#endif /*(VOS_OS_VER == VOS_WIN32)*/

#if((VOS_OS_VER == VOS_WIN32) || (VOS_RTOSCK == VOS_OS_VER))
#define SCM_FLUSH_CACHE(ptr, size)
#define SCM_INVALID_CACHE(ptr, size)
#elif(VOS_OS_VER == VOS_VXWORKS)
#define SCM_FLUSH_CACHE(ptr, size)      cacheFlush(DATA_CACHE, ptr, size)
#define SCM_INVALID_CACHE(ptr, size)    cacheInvalidate(DATA_CACHE, ptr, size);
#elif (VOS_OS_VER == VOS_LINUX)
extern unsigned long long g_astScmDmaMask;
#define SCM_FLUSH_CACHE(ptr, size)                      \
    do{                                                 \
        struct device dev;                              \
        memset(&dev,0,sizeof(struct device));           \
        dev.dma_mask = (unsigned long long *)(&g_astScmDmaMask);    \
        dma_map_single(&dev, ptr, size, DMA_TO_DEVICE);  \
    }while(0)
#define SCM_INVALID_CACHE(ptr, size)                    \
    do{                                                 \
        struct device dev;                              \
        memset(&dev,0,sizeof(struct device));           \
        dev.dma_mask = (unsigned long long *)(&g_astScmDmaMask);    \
        dma_map_single(&dev, ptr, size, DMA_FROM_DEVICE);  \
    }while(0)
#endif

/**************************************************************************
  3 ö�ٶ���
**************************************************************************/
enum  SCM_CHANNEL_INIT_ENUM
{
    SCM_CHANNEL_UNINIT = 0,             /* δ��ʼ�� */
    SCM_CHANNEL_INIT_SUCC,              /* ��ʼ���ɹ� */
    SCM_CHANNEL_MEM_FAIL,               /* ��ʼ�������ڴ���� */
    SCM_CHANNEL_CFG_FAIL,               /* ��ʼ��ͨ������ */
    SCM_CHANNEL_START_FAIL,             /* ͨ���������� */
    SCM_CHANNEL_INIT_BUTT
};
typedef VOS_UINT32 SCM_CHANNEL_INIT_ENUM_U32;

enum SOCP_SOFT_DECODE_CB_ENUM
{
    SOCP_DECODER_DST_CB_TL_OM,
    SOCP_DECODER_DST_CB_GU_OM,
    SOCP_DECODER_DST_CB_GU_CBT,
    SOCP_DECODER_DST_CB_BUTT
};

typedef VOS_UINT32 SOCP_SOFT_DECODE_CB_ENUM_U32;
/**************************************************************************
  4 �ṹ�嶨��
**************************************************************************/
typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ��ʼ��״̬ */
    VOS_UINT32                  ulChannelID;    /* ͨ��ID */
}SCM_CHANNEL_CFG_HEAD;

typedef struct
{
    VOS_UINT32                  ulSlice;
    VOS_UINT32                  ulFileNO;
    VOS_INT32                   lLineNO;
    VOS_UINT32                  ulP1;
    VOS_UINT32                  ulP2;
}INNER_LOG_RECORD_STRU;

typedef struct
{
    VOS_UINT32                  ulCnt;
    INNER_LOG_RECORD_STRU       astLogData[INNER_LOG_DATA_MAX];
}INNER_LOG_DATA_STRU;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32       enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_CODER_SRC_ENUM_U32         enChannelID;    /* ����Դͨ��ID���̶����� */
    SOCP_CODER_DST_ENUM_U32         enDstCHID;      /* ����Ŀ��ͨ��ID */
    SOCP_DATA_TYPE_ENUM_UIN32       enDataType;     /* ������Դ���� */
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32  enCHMode;       /* ͨ������ */
    SOCP_CHAN_PRIORITY_ENUM_UIN32   enCHLevel;      /* ͨ�����ȼ� */
    VOS_UINT32                      ulSrcBufLen;    /* ����Դͨ�����ݿռ��С */
    VOS_UINT32                      ulRDBufLen;     /* ����Դͨ��RD���ݿռ��С */
    VOS_UINT8                       *pucSrcBuf;     /* ����Դͨ�����ݿռ��ڴ�ָ�� */
    VOS_UINT8                       *pucSrcPHY;
    VOS_UINT8                       *pucRDBuf;      /* ����Դͨ��RD���ݿռ��ڴ�ָ�� */
    VOS_UINT8                       *pucRDPHY;
}SCM_CODER_SRC_CFG_STRU;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_CODER_DST_ENUM_U32     enChannelID;    /* ����Ŀ��ͨ��ID���̶����� */
    VOS_UINT32                  ulBufLen;       /* ����Ŀ��ͨ�����ݿռ��С */
    VOS_UINT32                  ulThreshold;    /* ����Ŀ��ͨ����ֵ */
    VOS_UINT8                   *pucBuf;        /* ����Ŀ��ͨ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucBufPHY;
    SCM_CODERDESTFUCN           pfunc;          /* ����Ŀ��ͨ�����ݴ���ص����� */
}SCM_CODER_DEST_CFG_STRU;


typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_DECODER_SRC_ENUM_U32   enChannelID;    /* ����Դͨ��ID���̶����� */
    VOS_UINT32                  ulSrcBufLen;    /* ����Դͨ�����ݿռ��С */
    VOS_UINT32                  ulRfu;
    VOS_UINT8                   *pucSrcBuf;     /* ����Դͨ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucSrcPHY;
}SCM_DECODER_SRC_CFG_STRU;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_DECODER_DST_ENUM_U32   enChannelID;    /* ����Ŀ��ͨ��ID���̶����� */
    SOCP_DECODER_SRC_ENUM_U32   enSrcCHID;      /* ����Դͨ��ID */
    SOCP_DATA_TYPE_ENUM_UIN32   enDataType;     /* ����������Դ���� */
    VOS_UINT32                  ulBufLen;       /* ����Ŀ�����ݿռ��С */
    VOS_UINT32                  ulThreshold;    /* ����Ŀ��ͨ����ֵ */
    VOS_UINT8                   *pucBuf;        /* ����Ŀ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucBufPHY;
    SCM_DECODERDESTFUCN         pfunc;          /* ����Ŀ��ͨ�����ݴ���ص����� */
}SCM_DECODER_DEST_CFG_STRU;


typedef struct
{
    VOS_UINT32                  aulBDUsedMax[SCM_CODER_SRC_NUM];    /* ��¼�ϲ���õķ���Դͨ��BDʹ�����ֵ */
    VOS_UINT32                  aulRDUsedMax[SCM_CODER_SRC_NUM];    /* ��¼�ϲ���õķ���ԴRDʹ�����ֵ */
    INNER_LOG_DATA_STRU         stCoderSrcLog;                      /* ��¼�ϲ���õķ��ͽӿ�log */
    INNER_LOG_DATA_STRU         stCoderSrcRDLog;                    /* ��¼�ϲ���õ��ͷ�RD�ӿ�log */
    /*INNER_LOG_DATA_STRU         stCoderSrcReset;*/                /* ��¼�ϲ���õĸ�λ�ӿ�log,�ݲ�ʹ�� */
    INNER_LOG_DATA_STRU         stCoderSrcErr;                      /* ��¼����Դͨ���ص�����Log */
#ifdef SCM_ACORE
    INNER_LOG_DATA_STRU         stCoderDstLog;                      /* ��¼�ص��ϲ�ı���Ŀ��ͨ������Log */
    INNER_LOG_DATA_STRU         stCoderDstErr;                      /* ��¼����Ŀ��ͨ���ص�����Log */
    /*INNER_LOG_DATA_STRU         stDoderSrcLog;*/                  /* ��¼�ϲ���õĽ���Դͨ��Log,�ݲ�ʹ�� */
    /*INNER_LOG_DATA_STRU         stDecoderDstLog;*/                /* ��¼�ص��ϲ�Ľ���Ŀ��ͨ������Log,�ݲ�ʹ�� */
    /*INNER_LOG_DATA_STRU         stDecoderDstErr;*/                /* ��¼����Ŀ��ͨ���ص�����Log,�ݲ�ʹ�� */
    /*INNER_LOG_DATA_STRU         stDecoderSrcErr;*/                /* ��¼����Դͨ���ص�����Log,�ݲ�ʹ�� */
#endif
}SCM_INFODATA_STRU;

#ifdef SCM_ACORE
#ifdef SCM_SNCHECK
#define  SCM_SN_RECORD_BUF_SIZE           (500)
#define  SCM_SN_CHECK_THRESHOLD_VALUE     (400)
#define  SCM_SN_CHECK_FLAG                (0x5a5a)

typedef struct
{
    VOS_UINT32                  aulSnBuf[SCM_SN_RECORD_BUF_SIZE];   /* ����SN�� */
    VOS_UINT32                  ulCount;                            /* ��������� */
}SCM_SN_CHECK_STRU;

typedef struct
{
    VOS_UINT32                          ulDataLen;                  /* �������ݳ��� */
    VOS_UINT32                          ulNum;                      /* ��������֡���� */
}SCM_SN_CHECK_MNTN_INFO_STRU;

extern VOS_UINT32                              g_ulSnErrCount;
extern SCM_SN_CHECK_STRU                       g_stSnCheck;
extern VOS_UINT16                              g_usSnCheckFlag;
extern VOS_SPINLOCK                            g_stSnCheckSpinLock;

VOS_VOID SCM_MaoPao(VOS_UINT32 *pulDataBuf, VOS_UINT32 ulBufLen);
VOS_VOID SCM_CheckSn(VOS_VOID);
VOS_VOID SCM_SnCheckShow(VOS_VOID);

#endif
#endif
#define SCM_CODER_SRC_LOG(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcLog, VOS_FILE_ID, __LINE__)

#define SCM_CODER_SRCRD_LOG(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcRDLog, VOS_FILE_ID, __LINE__)

#define SCM_CODER_SRCRESET_LOG(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcReset, VOS_FILE_ID, __LINE__)*/

#define SCM_CODER_SRC_ERR(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcErr, VOS_FILE_ID, __LINE__)

#define SCM_CODER_DST_ERR(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderDstErr, VOS_FILE_ID, __LINE__)

#ifdef SCM_ACORE
#define SCM_DECODER_SRC_LOG(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDoderSrcLog, VOS_FILE_ID, __LINE__)*/

#define SCM_CODER_DST_LOG(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderDstLog, VOS_FILE_ID, __LINE__)

#define SCM_DECODER_DST_LOG(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDecoderDstLog, VOS_FILE_ID, __LINE__)*/
#if 0
#define SCM_CODER_DST_ERR(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderDstErr, VOS_FILE_ID, __LINE__)
#endif

#define SCM_DECODER_DST_ERR(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDecoderDstErr, VOS_FILE_ID, __LINE__)*/

#define SCM_DECODER_SRC_ERR(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDecoderSrcErr, VOS_FILE_ID, __LINE__)*/
#endif

extern SCM_INFODATA_STRU           g_stSCMInfoData;    /* ���ڱ���log��Ϣ */

extern SCM_DECODERDESTFUCN         g_astSCMDecoderCbFunc[SOCP_DECODER_DST_CB_BUTT];
/**************************************************************************
  6 ��������
**************************************************************************/
extern VOS_UINT32  SCM_FindChannelCfg(VOS_UINT32 ulChannelID, VOS_UINT32 ulChMax, SCM_CHANNEL_CFG_HEAD *pstCfg, VOS_UINT32 ulStruLen, VOS_UINT32 *pulNum);

extern VOS_UINT32 SCM_CoderSrcChannelCfg(SCM_CODER_SRC_CFG_STRU *pstCfg);

extern VOS_UINT32 SCM_ResetCoderSrcChan(SOCP_CODER_SRC_ENUM_U32 enChID);

extern VOS_UINT32 SCM_CoderSrcChannelInit(VOS_VOID);

extern VOS_UINT32 SCM_RlsSrcRDAll(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT_PTR *pDataPhyAddr, VOS_UINT32 *pulDataLen);

extern VOS_UINT32 SCM_RlsSrcRDFirst(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT_PTR *pDataPhyAddr, VOS_UINT32 *pulDataLen);

extern VOS_UINT32 SCM_GetBDFreeNum(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT32 *pulBDNum);

extern VOS_UINT32 SCM_SendCoderSrc(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT8 *pucSendData, VOS_UINT32 ulSendLen);

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT32 SCM_RlsDestBuf(VOS_UINT32 ulChanlID, VOS_UINT32 ulReadSize);

extern VOS_UINT32 SCM_RegCoderDestProc(SOCP_CODER_DST_ENUM_U32 enChanlID,SCM_CODERDESTFUCN func);

extern VOS_UINT32 SCM_RegDecoderDestProc(SOCP_DECODER_DST_ENUM_U32 enChanlID,SCM_DECODERDESTFUCN func);
extern VOS_UINT8* SCM_CoderDestMemVirtToPhy(VOS_UINT32 ulDstChID, VOS_UINT8 *pucVirtAddr);

extern VOS_UINT32 COMM_Init(VOS_VOID);

VOS_VOID SCM_MsgSnRecord(SOCP_CODER_DST_ENUM_U32 enChanID, VOS_UINT8 *pucData, VOS_UINT32 ulLen);

#endif
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


