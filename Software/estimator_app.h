/*
 * estimador.h
 *
 *  Created on: Sep 6, 2019
 *      Author: ESTUDIANTES\rzarate
 */

#ifndef SRC_ESTIMADOR_H_
#define SRC_ESTIMADOR_H_



#endif /* SRC_ESTIMADOR_H_ */

#include<stdio.h>
#include"xparameters.h"
#include"xgpio.h"
#include"xil_io.h"




#define AP_START 0x1
#define AP_DONE 0x2
#define AP_READY 0x4
#define AP_IDLE 0x8
#define AP_CONTINUE 0x10
#define SIZE 1500

#define INT2U32(x) *(u32*)&x

int to_fixed(double a){
	a=a*pow(2,21);
	return (int)a;
}

