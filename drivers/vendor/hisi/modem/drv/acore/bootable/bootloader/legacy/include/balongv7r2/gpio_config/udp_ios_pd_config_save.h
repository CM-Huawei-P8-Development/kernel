/**************************************************************
CAUTION : This file is Auto Generated by VBA based on *.xls.
          So, don't modify this file manually!
***************************************************************/
#ifndef  UDP_IOS_PD_SAVE_H_
#define  UDP_IOS_PD_SAVE_H_

/*保存掉电域管脚复用关系、内部上下拉以及驱动能力*/
#define  UDP_IOS_PD_CONFIG_SAVE \
do{\
\
/*配置NANDFLASH(15个PIN)*/\
    /*gpio1[0]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL14);\
\
\
/*配置BOOT_MODE,JTAG_MODE(7个PIN）*/\
    /*antpa_sel[25]管脚复用配置保存*/\
    add_ios_list(IOS_PD_AF_CTRL1);\
    add_ios_list(IOS_PD_IOM_CTRL15);\
    /*antpa_sel[25]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL15);\
\
    /*antpa_sel[26]管脚复用配置保存*/\
    add_ios_list(IOS_PD_AF_CTRL1);\
    add_ios_list(IOS_PD_IOM_CTRL16);\
    /*antpa_sel[26]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL16);\
\
    /*antpa_sel[27]管脚复用配置保存*/\
    add_ios_list(IOS_PD_AF_CTRL1);\
    add_ios_list(IOS_PD_IOM_CTRL17);\
    /*antpa_sel[27]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL17);\
\
    /*antpa_sel[28]管脚复用配置保存*/\
    add_ios_list(IOS_PD_AF_CTRL1);\
    add_ios_list(IOS_PD_IOM_CTRL18);\
    /*antpa_sel[28]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL18);\
\
    /*antpa_sel[29]管脚复用配置保存*/\
    add_ios_list(IOS_PD_AF_CTRL1);\
    add_ios_list(IOS_PD_IOM_CTRL19);\
    /*antpa_sel[29]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL19);\
\
    /*antpa_sel[30]管脚复用配置保存*/\
    add_ios_list(IOS_PD_AF_CTRL1);\
    add_ios_list(IOS_PD_IOM_CTRL20);\
    /*antpa_sel[30]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL20);\
\
\
/*配置MMC0（6个PIN）（SD MASTER/SDIO SLAVE）*/\
    /*mmc0_clk管脚复用配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL21);\
    /*mmc0_clk管脚Drive电流配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL21);\
\
\
/*配置JTAG0（6个PIN）*/\
\
/*配置GPIO/GSBI_0(16PIN）*/\
    /*uart1_txd管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL4);\
    add_ios_list(IOS_PD_IOM_CTRL33);\
    /*uart1_txd管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL33);\
\
    /*uart1_rxd管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL4);\
    add_ios_list(IOS_PD_IOM_CTRL34);\
    /*uart1_rxd管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL34);\
\
    /*uart2_txd管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL4);\
    add_ios_list(IOS_PD_IOM_CTRL35);\
    /*uart2_txd管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL35);\
\
    /*uart2_rxd管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL4);\
    add_ios_list(IOS_PD_IOM_CTRL36);\
    /*uart2_rxd管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL36);\
\
    /*uart3_txd管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL4);\
    add_ios_list(IOS_PD_IOM_CTRL37);\
    /*uart3_txd管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL37);\
\
    /*uart3_rxd管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL4);\
    add_ios_list(IOS_PD_IOM_CTRL38);\
    /*uart3_rxd管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL38);\
\
    /*i2c0_sda管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL4);\
    /*i2c0_sda管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL39);\
\
    /*i2c0_scl管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL4);\
    /*i2c0_scl管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL40);\
\
    /*gpio2[24]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL41);\
\
    /*i2c1_sda管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL5);\
    /*i2c1_sda管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL43);\
\
    /*i2c1_scl管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL5);\
    /*i2c1_scl管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL44);\
\
    /*gpio2[29]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL46);\
\
    /*lte_tx_active管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL5);\
    add_ios_list(IOS_PD_IOM_CTRL47);\
    /*lte_tx_active管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL47);\
\
    /*gp_pwm2管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL3);\
    add_ios_list(IOS_PD_AF_CTRL5);\
    add_ios_list(IOS_PD_IOM_CTRL48);\
    /*gp_pwm2管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL48);\
\
\
/*配置GPIO/GSBI_1(7PIN）*/\
    /*antpa_sel[21]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL4);\
    add_ios_list(IOS_PD_AF_CTRL7);\
    add_ios_list(IOS_PD_IOM_CTRL49);\
    /*antpa_sel[21]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL49);\
\
    /*antpa_sel[22]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL4);\
    add_ios_list(IOS_PD_AF_CTRL7);\
    add_ios_list(IOS_PD_IOM_CTRL50);\
    /*antpa_sel[22]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL50);\
\
    /*antpa_sel[23]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL4);\
    add_ios_list(IOS_PD_AF_CTRL7);\
    add_ios_list(IOS_PD_IOM_CTRL51);\
    /*antpa_sel[23]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL51);\
\
    /*antpa_sel[24]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL4);\
    add_ios_list(IOS_PD_AF_CTRL7);\
    add_ios_list(IOS_PD_IOM_CTRL52);\
    /*antpa_sel[24]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL52);\
\
    /*lte_frame_sync管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL4);\
    add_ios_list(IOS_PD_AF_CTRL7);\
    add_ios_list(IOS_PD_IOM_CTRL53);\
    /*lte_frame_sync管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL53);\
\
    /*wlan_bt_rx_priority管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL4);\
    add_ios_list(IOS_PD_AF_CTRL7);\
    add_ios_list(IOS_PD_IOM_CTRL54);\
\
    /*lte_rx_active管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL4);\
    add_ios_list(IOS_PD_AF_CTRL7);\
    add_ios_list(IOS_PD_IOM_CTRL55);\
    /*lte_rx_active管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL55);\
\
\
/*配置RF线控：CH0 FEM(6PIN）*/\
    /*ch0_apt_pdm管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL5);\
    add_ios_list(IOS_PD_AF_CTRL9);\
    add_ios_list(IOS_PD_IOM_CTRL59);\
    /*ch0_apt_pdm管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL59);\
\
    /*ch0_mipi_clk管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL5);\
    add_ios_list(IOS_PD_AF_CTRL8);\
    add_ios_list(IOS_PD_IOM_CTRL60);\
    /*ch0_mipi_clk管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL60);\
\
    /*ch0_mipi_data管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL5);\
    add_ios_list(IOS_PD_AF_CTRL8);\
\
\
/*配置RF线控：CH1 FEM(6PIN）*/\
    /*ch1_apt_pdm管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL6);\
    add_ios_list(IOS_PD_AF_CTRL11);\
    add_ios_list(IOS_PD_IOM_CTRL65);\
    /*ch1_apt_pdm管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL65);\
\
    /*ch1_mipi_clk管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL6);\
    add_ios_list(IOS_PD_AF_CTRL10);\
    add_ios_list(IOS_PD_IOM_CTRL66);\
    /*ch1_mipi_clk管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL66);\
\
    /*ch1_mipi_data管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL6);\
    add_ios_list(IOS_PD_AF_CTRL10);\
\
\
/*配置TCXO PDM（2个PIN）*/\
\
/*配置RF线控：FEM(21个PIN）*/\
    /*antpa_sel[0]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL70);\
    /*antpa_sel[0]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL70);\
\
    /*antpa_sel[1]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL71);\
    /*antpa_sel[1]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL71);\
\
    /*antpa_sel[2]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL72);\
    /*antpa_sel[2]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL72);\
\
    /*antpa_sel[3]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL73);\
    /*antpa_sel[3]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL73);\
\
    /*antpa_sel[4]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL74);\
    /*antpa_sel[4]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL74);\
\
    /*antpa_sel[5]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL75);\
    /*antpa_sel[5]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL75);\
\
    /*antpa_sel[6]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL76);\
    /*antpa_sel[6]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL76);\
\
    /*antpa_sel[7]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL77);\
    /*antpa_sel[7]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL77);\
\
    /*antpa_sel[8]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL78);\
    /*antpa_sel[8]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL78);\
\
    /*antpa_sel[9]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL79);\
    /*antpa_sel[9]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL79);\
\
    /*antpa_sel[10]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL80);\
    /*antpa_sel[10]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL80);\
\
    /*antpa_sel[11]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL81);\
    /*antpa_sel[11]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL81);\
\
    /*antpa_sel[12]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL82);\
    /*antpa_sel[12]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL82);\
\
    /*antpa_sel[13]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL83);\
    /*antpa_sel[13]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL83);\
\
    /*antpa_sel[14]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL84);\
    /*antpa_sel[14]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL84);\
\
    /*antpa_sel[15]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL85);\
    /*antpa_sel[15]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL85);\
\
    /*antpa_sel[16]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL86);\
    /*antpa_sel[16]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL86);\
\
    /*antpa_sel[17]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL87);\
    /*antpa_sel[17]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL87);\
\
    /*antpa_sel[18]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL88);\
    /*antpa_sel[18]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL88);\
\
    /*antpa_sel[19]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL89);\
    /*antpa_sel[19]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL89);\
\
    /*antpa_sel[20]管脚复用配置保存*/\
    add_ios_list(IOS_PD_MF_CTRL8);\
    add_ios_list(IOS_PD_AF_CTRL14);\
    add_ios_list(IOS_PD_IOM_CTRL90);\
    /*antpa_sel[20]管脚上下拉配置保存*/\
    add_ios_list(IOS_PD_IOM_CTRL90);\
\
\
/*配置ABB信号（32个PIN）*/\
\
/*配置LPDDR2信号（65个PIN）：CA(19PIN)*/\
\
/*配置LPDDR2信号（65个PIN）：DQ(46PIN)*/\
\
/*配置USB3.0信号（10个PIN）*/\
\
/*配置PCIE（7个PIN）*/\
\
}while(0)

/*管脚配置宏for drv*/
#define  UDP_IOS_CONFIG_SAVE \
do{\
     UDP_IOS_AO_CONFIG_SAVE;\
     UDP_IOS_PD_CONFIG_SAVE;\
}while(0)

#endif

