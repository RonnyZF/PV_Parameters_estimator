/*
 * prueba_xadc.c
 *
 *  Created on: 31 mar. 2019
 *      Author: thor
 */

#include<stdio.h>
#include <unistd.h>
#include<time.h>
#include <math.h>
#include"xparameters.h"
#include"xgpio.h"
#include"estimador_app.h"


int main(void){

	XGpio Igpio_0;
	XGpio Igpio_1;

	XGpio_Initialize(&Igpio_0, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_Initialize(&Igpio_1, XPAR_AXI_GPIO_1_DEVICE_ID);

	double param_1=0;
	double param_2=0;

	printf("Inicia prueba");
	int f = 0;
	double a=0,b=7,q=0,w=0;
	while(f==0){
		param_1 = (double)XGpio_DiscreteRead(&Igpio_1,1)/pow(2,24);
		param_2 = (double)XGpio_DiscreteRead(&Igpio_1,2)/pow(2,24);
		printf("Parameter 1 = %lf\t Parameter 2 = %lf\n\r",param_1,param_2);
		
		q = pow(2.0,a);
		w = pow(2.0,b);
		XGpio_DiscreteWrite(&Igpio_0, 1, q+w);
		q=0;w=0;a++;b--;
		usleep(100000);
		XGpio_DiscreteWrite(&Igpio_0, 1, 0);
		if(a==7){a=0;b=7;}
	}



}
