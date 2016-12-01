/*
 * Lidar_sys.c
 *
 *  Created on: 2016Äê11ÔÂ12ÈÕ
 *      Author: lin.zheng
 */
#include <stdio.h>
#include "platform.h"
#include "myImode.h"
#include "sleep.h"
#include "xparameters.h"	/* SDK generated parameters */
#include "xsdps.h"		/* SD device driver */
#include "xil_printf.h"
#include "ff.h"
#include "xil_cache.h"
#include "xplatform_info.h"


#include "tdc.h"
#include "Lidar_sys.h"

int System_ReadReg(int regNum){
	int readData = 0;
	int regOffset = 0;

	regOffset = TDC_GetRegOffset(regNum);
	readData = MYIMODE_mReadReg(TDC_BASEADDR, regOffset);
	return readData;
}

int TDC_GetRegOffset(int regNum){
	switch(regNum){
		case REG_CSN:					return MYIMODE_S00_AXI_SLV_REG0_OFFSET;
//		case REG_CSN:					return MYIMODE_S00_AXI_SLV_REG0_OFFSET;
		case REG_RDN:					return MYIMODE_S00_AXI_SLV_REG2_OFFSET;
		case REG_ADDR:					return MYIMODE_S00_AXI_SLV_REG3_OFFSET;
		case REG_DATA:					return MYIMODE_S00_AXI_SLV_REG4_OFFSET;
		case REG_EF1:					return MYIMODE_S00_AXI_SLV_REG5_OFFSET;
		case REG_EF2:					return MYIMODE_S00_AXI_SLV_REG6_OFFSET;
		case REG_STOPDIS:				return MYIMODE_S00_AXI_SLV_REG7_OFFSET;
		case REG_RECV_FLAG:				return MYIMODE_S00_AXI_SLV_REG20_OFFSET;
		case REG_START_TRI_COUNTTER:	return MYIMODE_S00_AXI_SLV_REG2_OFFSET;
		case REG_IRFLAG:				return MYIMODE_S00_AXI_SLV_REG8_OFFSET;
		case REG_ERRFLAG:				return MYIMODE_S00_AXI_SLV_REG12_OFFSET;
		default	:	return	-1;
	}
}
