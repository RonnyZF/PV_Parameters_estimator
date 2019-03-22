/*
 * estimador_app.h
 *
 *  Created on: 14 mar. 2019
 *      Author: Ronny Zárate Ferreto
 */
#include<stdio.h>
#include"xparameters.h"
#include"xgpio.h"
#include"xil_io.h"
#include"xwrapper_fixed_estimator.h"


#define AP_DONE 0x1
#define AP_START 0x2
#define AP_READY 0x4
#define AP_IDLE 0x8
#define AP_CONTINUE 0x10

#define INT2U32(x) *(u32*)&x
