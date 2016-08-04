#include "product_config.h"
#include "osl_common.h"
#include "bsp_memmap.h"
#include "bsp_version.h"
#include "hi_syssc_interface.h"

/*****************************************************************************
* ����	: bsp_get_board_mode_type
* ����	: get board type(GUL or LTE)
* ����	: void
* ���	: void
* ����	: BOARD_TYPE_E
*****************************************************************************/
BOARD_TYPE_E bsp_get_board_mode_type(void)
{
#if(defined(FEATURE_MULTIMODE_GUL))
	return BOARD_TYPE_GUL;
#else
	return BOARD_TYPE_LTE_ONLY;
#endif
}

/*****************************************************************************
* ����	: bsp_board_type_is_gutl
* ����	: get board type is GUTL
* ����	: void
* ���	: void
* ����	: BOARD_TYPE_E
*****************************************************************************/
bool bsp_board_type_is_gutl(void)
{
	return (bool)(BOARD_TYPE_GUL == bsp_get_board_mode_type() ? 1 : 0);
}

/*****************************************************************************
* ����	: bsp_get_board_chip_type
* ����	: get board type and chip type
* ����	: void
* ���	: void
* ����	: BOARD_TYPE_E
*****************************************************************************/
u32 bsp_version_get_board_chip_type(void)
{
    unsigned int type = 0xffffffff;
	type = (u32)bsp_version_get_hwversion_index();

	if(HW_VER_INVALID==type){
		ver_print_error("[bsp_get_board_chip_type]:get hw version failed!hw_ver:0x%x\n",type);
		return type;
	}

	/*��Ϊudp��ֻ����UDPӲ���汾�ţ�������Ƶ�۰���Ϣ*/
	if(HW_VER_UDP_MASK==(type & HW_VER_UDP_MASK)){
		return HW_VER_PRODUCT_UDP;
	}

	/*��Ϊk3v3UDP,ֻ����UDPӲ���汾��*/
	if(HW_VER_K3V3_UDP_MASK == (type & HW_VER_K3V3_UDP_MASK)){
		return HW_VER_K3V3_UDP;
	}

	/*��Ϊk3v3FPGA,ֻ����FPGAӲ���汾��*/
	if(HW_VER_K3V3_FPGA_MASK == (type & HW_VER_K3V3_FPGA_MASK)){
		return HW_VER_K3V3_FPGA;
	}

	
	/*��Ϊk3v3 plus,ֻ����UDPӲ���汾��*/
	if(HW_VER_K3V3_PLUS_UDP_MASK == (type & HW_VER_K3V3_PLUS_UDP_MASK)){
		return HW_VER_K3V3_UDP;/*��ʱ���䣬����ɾ��*/
	}

	if(HW_VER_V711_UDP_MASK == (type & HW_VER_V711_UDP_MASK)){
		return HW_VER_V711_UDP;
	}

	return type;
}
u32 bsp_version_get_chip_type(void)
{
	return get_hi_version_id_version_id();
}
/*****************************************************************************
* ����	: bsp_get_board_actual_type
* ����	: get board actual type 
* ����	: void
* ���	: void
* ����	: BOARD_ACTUAL_TYPE_E       BBIT/SFT/ASIC
*
* ����       : ��
*
*****************************************************************************/
BOARD_ACTUAL_TYPE_E bsp_get_board_actual_type(void)
{
	u32 chip_ver = 0;

	chip_ver = bsp_version_get_chip_type();

	switch(chip_ver){
		case CHIP_VER_P531_ASIC:
		case CHIP_VER_P532_ASIC:
			return BOARD_TYPE_BBIT;

		case CHIP_VER_HI6950_ASIC:			
		case CHIP_VER_HI3630_ASIC:
		case CHIP_VER_HI6921_ASIC:
		case CHIP_VER_HI6930_ASIC:
		case CHIP_VER_HI3635_ASIC:
			return BOARD_TYPE_ASIC;

		case CHIP_VER_HI6950_SFT:
		case CHIP_VER_HI3635_SFT:
			return BOARD_TYPE_SFT;

		default:
			return BOARD_TYPE_MAX;		
	}
}
