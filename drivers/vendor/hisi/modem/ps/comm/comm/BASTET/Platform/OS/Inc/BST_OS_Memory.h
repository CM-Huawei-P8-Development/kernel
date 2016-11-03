

#ifndef __BST_OS_MEMORY_H__
#define __BST_OS_MEMORY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_PAL_Memory.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_OS_GetTableLength(Tbl)      ( BST_OS_SIZEOF(Tbl)/BST_OS_SIZEOF(Tbl[0]) )
#define BST_OS_SIZEOF( datatype )       ( BST_OS_PalSizeof( datatype ) )

#if (BST_VER_TYPE != BST_UT_VER )
#define BST_OS_MALLOC( ulSize )         ( BST_OS_PalMalloc( ulSize ) )
#endif

#define BST_OS_FREE( pData )    \
    {\
        BST_OS_PalFree( pData );\
        pData                           = BST_NULL_PTR;\
    }
#define BST_OS_MEMSET( buf, val, n )    ( BST_OS_Memset( buf, val, n ) )
#define BST_OS_MEMCMP( buf1, buf2, n )  ( BST_OS_Memcmp( buf1, buf2, n ) )
#define BST_OS_MEMCPY( dest, src, n)    ( BST_OS_Memcpy( dest, src, n ) )
#define BST_OS_MEMMOVE( dest, src, n )  ( BST_OS_Memmove( dest, src, n ) )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_VOID    BST_OS_MemInit( BST_VOID );

BST_VOID    BST_OS_Memset(
    BST_VOID           *pData,
    BST_INT32           lValue,
    BST_OS_MEMSIZE_T    ulSize );

BST_INT8    BST_OS_Memcmp(
    const BST_VOID     *pData1,
    const BST_VOID     *pData2,
    BST_OS_MEMSIZE_T    ulSize );

BST_VOID    BST_OS_Memcpy(
    BST_VOID           *pDst,
    const BST_VOID     *pSrc,
    BST_OS_MEMSIZE_T    ulSize );

BST_VOID    BST_OS_Memmove(
    BST_VOID           *pDst,
    BST_VOID           *pSrc,
    BST_OS_MEMSIZE_T    ulSize );
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
