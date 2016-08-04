

#ifndef  __BBP_PMU_H__
#define  __BBP_PMU_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <linux/types.h>

enum ADPPOWER_OM_TYPE
{
    ADPPOWER_LOG_ERROR,/*����*/
    ADPPOWER_LOG_ACTUAL/*ʵ�ʲ����˸�ģ���ӵ�*/
}BBP_LOG_TYPE_E;
enum ADPPOWER_OM_OPS
{
    ADPPOWER_POWERON = 0,
    ADPPOWER_POWEROFF,
    ADPPOWER_BBPCLKON,
    ADPPOWER_BBPCLKOFF,
    ADPPOWER_PLLON,
    ADPPOWER_PLLOFF,
    ADPPOWER_OTHERS
};
enum ADPPOWER_OM_DEV
{
    ADPPOWER_PA = 0,
    ADPPOWER_RFIC,
    ADPPOWER_IRMBBP,
    ADPPOWER_G1BBP,
    ADPPOWER_G2BBP,
    ADPPOWER_TBBP,
    ADPPOWER_WBBP,
    ADPPOWER_TWBBP,
    ADPPOWER_BBPPLL,
    ADPPOWER_BBEPLL,
    ADPPOWER_ABBCH0G,
    ADPPOWER_ABBCH0LWT,
    ADPPOWER_ABBCH1G,
    ADPPOWER_ABBCH1LWT,
    DEV_OTHERS
};
enum ADPPOWER_OM_ERR
{
    ADPPOWER_PARAERR = 0,
    ADPPOWER_OPSERR,
    ADPPOWER_DEVERR,
    APPPERR_OTHERS
};
struct adp_power_errlog
{
    int ops_id;
    unsigned int   info_mode;       /*��¼ʵ�ֿ��ز�����ģ*/
    unsigned int   info_module;       /*��¼ʵ�ֿ��ز��������*/
    unsigned int   info_modem;       /*��¼ʵ�ֿ��ز����Ŀ�(�������Ǹ���)*/
    unsigned int   err_id;           /*�����֧*/
    int   task_id;
};
struct adp_power_actlog
{
    int ops_id;
    int dev_id;
    u32 vote_lock; /*��ǰͶƱ���*/
    unsigned int   act_mode;       /*��¼ʵ�ֿ��ز�����ģ*/
    unsigned int   act_module;       /*��¼ʵ�ֿ��ز��������*/
    unsigned int   act_modem;       /*��¼ʵ�ֿ��ز����Ŀ�(�������Ǹ���)*/
    int   task_id;
};

int adppower_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif   /* __BBP_PMU_H__ */