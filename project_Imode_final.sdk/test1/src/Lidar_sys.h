/*
 * Lidar_sys.h
 *
 *  Created on: 2016Äê11ÔÂ12ÈÕ
 *      Author: lin.zheng
 */

#ifndef SRC_LIDAR_SYS_H_
#define SRC_LIDAR_SYS_H_

#define printf xil_printf



int System_ReadReg(int regNum);
int TDC_GetRegOffset(int regNum);

#endif /* SRC_LIDAR_SYS_H_ */
