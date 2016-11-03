#!/bin/bash 
set -e

ANDROID_ROOT_DIR=$1
ANDROID_PRODUCT_NAME=$2
ANDROID_VERSION_MODE=$3
ANDROID_ARCH=$4
ANDROID_MAKE_GOALS="$5 $6 $7 $8 $9"


cd ${ANDROID_ROOT_DIR}

. build/envsetup.sh

if [ "${ANDROID_ARCH}" = "arm64" ]; then
    choosecombo release ${ANDROID_PRODUCT_NAME} eng normal fullAP arm64
else
    choosecombo release ${ANDROID_PRODUCT_NAME} eng normal 
fi

if [ "${ANDROID_VERSION_MODE}" = "K3_ANDROID" ]; then
	
	if [ "${tiny}" = "true" ]; then
		android_pkgs="bootimage fastboot.img"
	elif [ -z "${ANDROID_MAKE_GOALS}" ]; then
		android_pkgs=""
	else
		android_pkgs=${ANDROID_MAKE_GOALS}
	fi

	if [ "${separate}" = "true" ]; then
		echo "sprara=true"
	else
		if [ -d vendor/huawei/modem/commril/ ] ;then
			cp -rf vendor/huawei/modem/commril/* hardware/ril/libril/
			rm hardware/ril/libril/Android.mk
			mv hardware/ril/libril/Android.mk.ril hardware/ril/libril/Android.mk
			cp -rf vendor/huawei/modem/commril/rild/* hardware/ril/rild/
			rm -rf hardware/ril/libril/rild
		fi
	fi

	if [ "${UPDATE_API}" != "false" ]; then
	    echo "make update-api -j "
	    make update-api -j 
    fi

	echo "make  -j   ${android_pkgs} CFG_BALONG_MODEM=true"
	make -j  ${android_pkgs} CFG_BALONG_MODEM=true

else
	if [ -z "${ANDROID_MAKE_GOALS}" ]; then
		android_pkgs="fastboot.img onchip.img adbd netcfg opcontrol oprofiled linker btools ecall lrz lsz adb ash debuggerd crasher logcat logwrapper run-as sdcard strace libfuse libexfat mount.exfat dumpexfat exfat.label mkfs.exfat yaffs_test nanddump nandwrite flashcp flash_erase mtd_debug lcdtest"
	else
		android_pkgs=${ANDROID_MAKE_GOALS}
	fi

	echo "make  -j  " ${android_pkgs}
	make  -j  ${android_pkgs}

	echo "make  BUILD_TINY_ANDROID=true -j "
	make  BUILD_TINY_ANDROID=true -j

	echo "make USE_MINGW=y fastboot"
	make USE_MINGW=y fastboot

fi

exit $?
