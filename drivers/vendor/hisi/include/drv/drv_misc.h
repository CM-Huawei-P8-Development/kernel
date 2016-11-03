
#ifndef _DRV_MISC_H_
#define _DRV_MISC_H_

/*lint -save -e537*/
#include "drv_comm.h"
/*lint -restore +e537*/

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
* �� �� ��  : mdrv_misc_scbackup_ext_write
*
* ��������  : ���ӿ����ڱ������������ļ�
*
* �������  : pRamAddr Դ�ļ���ַ
*             len  д�볤��
*
* �������  : ��
*
* �� �� ֵ  : OK  д��ɹ� ����ʧ��
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
int mdrv_misc_scbackup_ext_write(unsigned char* pRamAddr, unsigned int len);

/*****************************************************************************
* �� �� ��  : mdrv_misc_scbackup_ext_read
*
* ��������  : ���ӿ����ڻָ����������ļ�
*
* �������  : pRamAddr ���������ļ��ĵ�ַ
*             len  ��������
*
* �������  : ��
*
* �� �� ֵ  : OK  �����ɹ� ����ʧ��
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
int mdrv_misc_scbackup_ext_read(unsigned char* pRamAddr, unsigned int len);




#ifdef __cplusplus
}
#endif

#endif  /*_DRV_MISC_H_*/




