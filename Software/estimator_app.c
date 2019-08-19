/*
 * estimador_app.c
 *
 *  Created on: Apr 25, 2019
 *      Author: ESTUDIANTES\rzarate
 */


#include<stdio.h>
#include <unistd.h>
#include<time.h>
#include <math.h>
#include"xparameters.h"
#include"xgpio.h"
#include"xwrapper_fixed_estimator.h"
#include"estimador_app.h"


int main(void){

	XGpio Igpio_1;
	XWrapper_fixed_estimator estimator;

	XGpio_Initialize(&Igpio_1, XPAR_AXI_GPIO_1_DEVICE_ID);
	XWrapper_fixed_estimator_Initialize(&estimator,XPAR_XWRAPPER_FIXED_ESTIMATOR_0_DEVICE_ID);

	float param_1=0;
	float param_2=0;

	int p_1=0;
	int p_2=0;

	int init_alpha = to_fixed(0.55);
	int init_beta = to_fixed(-13);
	int gamma11 = to_fixed(0.1);
	int gamma12 = to_fixed(0);
	int gamma21 = to_fixed(0);
	int gamma22 = to_fixed(100);
	int ig = to_fixed(10);
	int i_scale_f = to_fixed(1);
	int v_scale_f = to_fixed(1);

	XWrapper_fixed_estimator_Set_INIT_ALPHA_V(&estimator, INT2U32(init_alpha));
	XWrapper_fixed_estimator_Set_INIT_BETA_V(&estimator, INT2U32(init_beta));
	XWrapper_fixed_estimator_Set_GAMMA11_V(&estimator, INT2U32(gamma11));
	XWrapper_fixed_estimator_Set_GAMMA12_V(&estimator, INT2U32(gamma12));
	XWrapper_fixed_estimator_Set_GAMMA21_V(&estimator, INT2U32(gamma21));
	XWrapper_fixed_estimator_Set_GAMMA22_V(&estimator, INT2U32(gamma22));
	XWrapper_fixed_estimator_Set_Ig_V(&estimator, INT2U32(ig));
	XWrapper_fixed_estimator_Set_I_scale_factor_V(&estimator, INT2U32(i_scale_f));
	XWrapper_fixed_estimator_Set_V_scale_factor_V(&estimator, INT2U32(v_scale_f));

	printf("Alpha= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_INIT_ALPHA_V(&estimator))/pow(2,24)));
	printf("Beta= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_INIT_BETA_V(&estimator))/pow(2,24)));
	printf("Gamma11= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_GAMMA11_V(&estimator))/pow(2,24)));
	printf("Gamma12= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_GAMMA12_V(&estimator))/pow(2,24)));
	printf("Gamma21= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_GAMMA21_V(&estimator))/pow(2,24)));
	printf("Gamma22= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_GAMMA22_V(&estimator))/pow(2,24)));
	printf("Ig= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_Ig_V(&estimator))/pow(2,24)));
	printf("I scale factor= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_I_scale_factor_V(&estimator))/pow(2,24)));
	printf("V scale factor= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_V_scale_factor_V(&estimator))/pow(2,24)));

	printf("Inicia prueba\n");
	int f = 0;
	while(f==0){
//	for(int i=0;i<2;i++){
		p_1 = (int)XWrapper_fixed_estimator_Get_interface_param_apprx_1_V(&estimator);
		p_2 = (int)XWrapper_fixed_estimator_Get_interface_param_apprx_2_V(&estimator);

		param_1 = (float)p_1/pow(2,24);
		param_2 = (float)p_2/pow(2,24);

		printf("P_1 = %f\t P_2 = %f\n\r",param_1,param_2);
	}
	printf("Fin prueba\n\n\n");

}

