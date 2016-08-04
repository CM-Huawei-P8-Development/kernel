
#include <product_config.h>

#ifdef MODEM_MEM_REPAIR

#include <bsp_memmap.h>
#include <hi_base.h>
#include <hi_ap_sctrl.h>
#include <hi_syscrg.h>
#include <hi_syssc.h>

#include <bsp_om.h>
#include <bsp_shared_ddr.h>
#include <bsp_hardtimer.h>
#endif

#include <bsp_memrepair.h>
#include <memrepair_balong.h>

#ifdef MODEM_MEM_REPAIR

/*sram��������0x20���ֽ�*/
static unsigned int *mr_poweron_flag[MODEM_MEMREPAIR_BUTT] = {
	[MODEM_MEMREPAIR_DSP] =(unsigned int *)(SHM_MEM_MEMREPAIR_ADDR + 0),
	[MODEM_MEMREPAIR_IRM] =(unsigned int *)(SHM_MEM_MEMREPAIR_ADDR + MODEM_MEMREPAIR_IRM*4),
};

/*�ж��Ƿ���Ҫrepair*/
int bsp_modem_is_need_memrepair(modem_memrepair_ip module)
{
    int ret = 0;
    unsigned int bit;

    switch(module){
		case MODEM_MEMREPAIR_DSP:
			bit = MODEM_MEMREPAIR_DSP_BIT;
			break;
		case MODEM_MEMREPAIR_IRM:
			bit = MODEM_MEMREPAIR_IRM_BIT;
			break;
		default:
			ret = 0;
			return ret;/*Ĭ�ϲ���Ҫrepair*/
	}
    ret = (int)(get_hi_ap_sctrl_scbakdata14_bakdata() & (0x01UL<<bit));

    return ret;
}

int bsp_modem_memrepair(modem_memrepair_ip module)
{
	int ret = 0;
	unsigned int timestamp_busbusy;
    unsigned int timestamp_repairdone;
	unsigned int slicenew_busbusy = 0;
    unsigned int slicenew_repairdone = 0;
	unsigned int bus_stat,done_stat,err_flag = 0;
	unsigned int bit;


    if (!bsp_modem_is_need_memrepair(module))
        return 0;

	/*3.����SYSCTRL�е�SCPERCTRL3(0x20c) bit 3 bit4Ϊ0*/
	set_hi_ap_sctrl_scperctrl3_repair_frm_sram(0);
	set_hi_ap_sctrl_scperctrl3_repair_frm_efu(0);

    /*4.����SYSCTRL�е�SCPERCTRL2��0x208��(bit19:0)Ϊ1,�ȴ�1us*/
    set_hi_ap_sctrl_scperctrl2_repair_disable(0xfffff);

    udelay(1);

	switch(module){
		case MODEM_MEMREPAIR_DSP:
			bit = MODEM_MEMREPAIR_DSP_BIT;
			break;
		case MODEM_MEMREPAIR_IRM:
			bit = MODEM_MEMREPAIR_IRM_BIT;
			break;
		default:
			ret = -1;
			goto out;
	}

	/*5.ʹ�ܴ��޸�ģ�飬����SYSCTRL�е�SCPERCTRL2(0x208)bit14Ϊ0��
	����bitΪ1,[31:20] bit ���ֲ���*/
	set_hi_ap_sctrl_scperctrl2_repair_disable(~(1<<bit)&0xfffff);
	udelay(5);
	/*6.���״��ϵ磬������SYSCTRL�е�SCPERCTRL3 (0x20C) bit4Ϊ1,ָʾ�޸�������ԴEFUSE*/
	if(*mr_poweron_flag[module] == MR_POWERON_FLAG){
		set_hi_ap_sctrl_scperctrl3_repair_frm_efu(1);
		*mr_poweron_flag[module] = 0;
	}
	else if(*mr_poweron_flag[module] == 0){
	/*6.���״��ϵ磬������SYSCTRL�е�SCPERCTRL3 (0x20C)bit3Ϊ1,ָʾ�޸�������Դsram*/
		set_hi_ap_sctrl_scperctrl3_repair_frm_sram(1);
	}
	else{/*�ڴ汻��*/
		mr_print_error("shared ddr has trampled!module id is %d\n",module);/*�ڴ汻�ȣ��������̻�Ҫ��������?*/
	}

    /*k3v3+����*/
    /*8.��ȡSCTRL�е�repair done��SCPERSTATUS3��0x228��bit[14]�Ƿ�Ϊ1.���Ϊ1��ִ�У�9��������ִ�У�13��*/
    timestamp_repairdone = bsp_get_slice_value();
    do{
        done_stat = get_hi_ap_sctrl_scperstatus3_efusec_timeout_dbg_info() & (1<<bit);
        if(done_stat != 0)
        {
        	/*9.��ѯSYSCTRL�е�SCMRBBUSYSTAT��0x304��bit14�������Ϊ0����ӡ�޸����*/
            /*10.�ж�����Ƿ��Ѿ���������ʱ�����û���������������300us����ʱ������Ѿ����������벽�裨11��*/

        	timestamp_busbusy = bsp_get_slice_value();
        	do{
        		bus_stat = get_hi_ap_sctrl_scmrbbusystat_mrb_efuse_busy() & (1<<bit);/*304*/
        		slicenew_busbusy = bsp_get_slice_value();
        	}while((bus_stat != 0)&&(get_timer_slice_delta(timestamp_busbusy, slicenew_busbusy) < MEMRAIR_WAIT_TIMEOUT));
            /*11.����жϵ���ʱ�Ƿ�ʱ����û�г�ʱ�����벽�裨9����������ʱ��ʱ����ӡ�޸�ʱ�䲻����Ϣ�����벽�裨12��*/
        	if(bus_stat != 0){
        		mr_print_error("wait memrepair efuse busy bit timeout,wait slice is 0x%x\n",(slicenew_busbusy - timestamp_busbusy));
        		/* coverity[no_escape] */
        		for(;;) ;
        	}
            else
            {
                /*��ȡerrflag*/
                err_flag = get_hi_ap_sctrl_scperstatus1_err_flag();
                if(!err_flag)
                    goto done;
                else
                {
                    mr_print_error("memrepair has errflag,errflag is 0x%x\n",err_flag);
                    /* coverity[no_escape] */
                    for(;;) ;
                }
            }
        }
        slicenew_repairdone = bsp_get_slice_value();
    /*13.�ж��Ƿ��Ѿ�����30us����ʱ�����û���������������30us����ʱ��ִ�У�14��������Ѿ�������ִ�У�14��*/
    }while((done_stat == 0)&&(get_timer_slice_delta(timestamp_repairdone, slicenew_repairdone) < MEMRAIR_DONE_WAIT_TIMEOUT));
    /*14.�ж��Ƿ�ʱ�����û�г�ʱ��ִ�У�8���������ʱ����ӡ�޸�û�������������������ѭ��*/
    if(done_stat == 0)
    {
        mr_print_error("wait memrepair done bit timeout,wait slice is %x\n",(slicenew_repairdone - timestamp_repairdone));
        /* coverity[no_escape] */
        for(;;) ;
    }

done:
	/*12. ����SYSCTRL�е�SCPERCTRL3(0x20c)bit 3 bit4Ϊ0���˳��޸�����*/
	set_hi_ap_sctrl_scperctrl3_repair_frm_sram(0);/*bit 3*/
	set_hi_ap_sctrl_scperctrl3_repair_frm_efu(0);/*bit 4*/

out:
	return ret;
}

int bsp_get_memrepair_time(void)
{
    int need_flag;

    need_flag = bsp_modem_is_need_memrepair(MODEM_MEMREPAIR_DSP)||bsp_modem_is_need_memrepair(MODEM_MEMREPAIR_IRM);

    if (need_flag)
        return 900; /* us *//*��֤�����¹���*/
    else
        return 0;
}

#else

int bsp_modem_memrepair(modem_memrepair_ip module){
	return 0;
}

int bsp_get_memrepair_time(void)
{
    return 0;
}
#endif

