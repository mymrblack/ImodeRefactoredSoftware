/*
 * SD_Card.c
 *
 *  Created on: 2016��11��12��
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
#include "SD_Card.h"

/*****************************************************************************/
/**
*
* File system example using SD driver to write to and read from an SD card
* in polled mode. This example creates a new file on an
* SD card (which is previously formatted with FATFS), write data to the file
* and reads the same data back to verify.
*
* @param	None
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None
*
******************************************************************************/
//int FfsSdPolledExample(int *chandata)


int FfsSdPolledExample(int *pchandata)
{
	FRESULT Res;
	UINT NumBytesWritten;
	u32 BuffCnt;
	u32 FileSize = (10*1024*1024);
	TCHAR *Path = "0:/";
	unsigned int i=0,j=0;
	unsigned int count_per_page = FileSize / 72;
	unsigned int count_page = 0;
	Res = f_mount(&fatfs, Path, 0);

	if (Res != FR_OK) {
		return XST_FAILURE;
	}

	sprintf(FileName, "data%d.bin", indexFile++);
	SD_File = (char *)FileName;

	Res = f_open(&fil, SD_File, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	if (Res) {
		return XST_FAILURE;
	}

	Res = f_lseek(&fil, 0);
	if (Res) {
		return XST_FAILURE;
	}

	for(BuffCnt = 0; BuffCnt < FileSize; BuffCnt++){
		SourceAddress[BuffCnt] =  0;
	}

	do{
		if((*(pchandata+8*i+0))==0&&(*(pchandata+8*i+1)==0)&&
		   (*(pchandata+8*i+2))==0&&(*(pchandata+8*i+3)==0)&&
		   (*(pchandata+8*i+4))==0&&(*(pchandata+8*i+5)==0)&&
		   (*(pchandata+8*i+6))==0&&(*(pchandata+8*i+7)==0))
			{
				j++;
				i++;
				continue;
			}
		sprintf(SourceAddress + count_page * 72, "%8d\t%8d\t%8d\t%8d\t%8d\t%8d\t%8d\t%8d\n",
				*(pchandata+8*i+0),*(pchandata+8*i+1),*(pchandata+8*i+2),*(pchandata+8*i+3),
				*(pchandata+8*i+4),*(pchandata+8*i+5),*(pchandata+8*i+6),*(pchandata+8*i+7));
		i++;
		count_page++;
		if(count_page == count_per_page)
		{
			count_page = 0;

			Res = f_write(&fil, (const void*)SourceAddress, strlen(SourceAddress),&NumBytesWritten);
			printf("%d\r\n", strlen(SourceAddress));
			for(BuffCnt = 0; BuffCnt < FileSize; BuffCnt++){
				SourceAddress[BuffCnt] =  0;
			}
		}
	}while(i < MyFileSize);

	if(strlen(SourceAddress) != 0)
	{
		Res = f_write(&fil, (const void*)SourceAddress, strlen(SourceAddress),&NumBytesWritten);
		printf("%d\r\n", strlen(SourceAddress));
	}

	Res = f_close(&fil);
	printf("%d\r\n", j);
	if (Res) {
		return XST_FAILURE;
	}
	return XST_SUCCESS;

}



