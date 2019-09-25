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
#include"estimador.h"


int main(void){

	XGpio Igpio_1;
	XWrapper_fixed_estimator estimator;

	XGpio_Initialize(&Igpio_1, XPAR_AXI_GPIO_1_DEVICE_ID);
	XWrapper_fixed_estimator_Initialize(&estimator,XPAR_XWRAPPER_FIXED_ESTIMATOR_0_DEVICE_ID);

	float param_1=0;
	float param_2=0;
	float f_vpv=0;
	float f_ipv=0;
	int p_1=0;
	int p_2=0;
	int vpv=0;
	int ipv=0;
	float vpv_out[SIZE];
	float ipv_out[SIZE];
	float theta1_out[SIZE];
	float theta2_out[SIZE];

	int set_flag=to_fixed(1);
	int init_alpha = to_fixed(0.55);
	int init_beta = to_fixed(-13);
	int gamma11 = to_fixed(0.1);
	int gamma12 = to_fixed(0);
	int gamma21 = to_fixed(0);
	int gamma22 = to_fixed(100);
	int ig = to_fixed(3.99);
	int i_scale_f = to_fixed(5.1248);
	int v_scale_f = to_fixed(22.1248);
	int t_sampling = to_fixed(1e-6);

	XWrapper_fixed_estimator_Set_SET_FLAG_V(&estimator, INT2U32(set_flag));
	XWrapper_fixed_estimator_Set_GAMMA11_V(&estimator, INT2U32(gamma11));
	XWrapper_fixed_estimator_Set_GAMMA12_V(&estimator, INT2U32(gamma12));
	XWrapper_fixed_estimator_Set_GAMMA21_V(&estimator, INT2U32(gamma21));
	XWrapper_fixed_estimator_Set_GAMMA22_V(&estimator, INT2U32(gamma22));
	XWrapper_fixed_estimator_Set_Ig_V(&estimator, INT2U32(ig));
	XWrapper_fixed_estimator_Set_I_scale_factor_V(&estimator, INT2U32(i_scale_f));
	XWrapper_fixed_estimator_Set_V_scale_factor_V(&estimator, INT2U32(v_scale_f));
	XWrapper_fixed_estimator_Set_T_SAMPLING_V(&estimator, INT2U32(t_sampling));
	XWrapper_fixed_estimator_Set_INIT_ALPHA_V(&estimator, INT2U32(init_alpha));
	XWrapper_fixed_estimator_Set_INIT_BETA_V(&estimator, INT2U32(init_beta));

	printf("set flag= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_SET_FLAG_V(&estimator))/pow(2,21)));
	printf("Alpha= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_INIT_ALPHA_V(&estimator))/pow(2,21)));
	printf("Beta= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_INIT_BETA_V(&estimator))/pow(2,21)));
	printf("Gamma11= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_GAMMA11_V(&estimator))/pow(2,21)));
	printf("Gamma12= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_GAMMA12_V(&estimator))/pow(2,21)));
	printf("Gamma21= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_GAMMA21_V(&estimator))/pow(2,21)));
	printf("Gamma22= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_GAMMA22_V(&estimator))/pow(2,21)));
	printf("Ig= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_Ig_V(&estimator))/pow(2,21)));
	printf("I scale factor= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_I_scale_factor_V(&estimator))/pow(2,21)));
	printf("V scale factor= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_V_scale_factor_V(&estimator))/pow(2,21)));
	printf("T sampling= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_T_SAMPLING_V(&estimator))/pow(2,21)));

	set_flag=to_fixed(0);
	XWrapper_fixed_estimator_Set_SET_FLAG_V(&estimator, INT2U32(set_flag));
	printf("set flag= %f\n", (float)(((int)XWrapper_fixed_estimator_Get_SET_FLAG_V(&estimator))/pow(2,21)));

	//printf("Inicia prueba\n");
	unsigned int microseconds=10000;

	for(int i=0;i<SIZE;i++){
//	for(int i=0;i<1000000;i++){
		vpv = (int)XWrapper_fixed_estimator_Get_raw_out_v_V(&estimator);
		ipv = (int)XWrapper_fixed_estimator_Get_raw_out_i_V(&estimator);
		p_1 = (int)XWrapper_fixed_estimator_Get_interface_param_apprx_1_V(&estimator);
		p_2 = (int)XWrapper_fixed_estimator_Get_interface_param_apprx_2_V(&estimator);

		f_vpv = (float)vpv/pow(2,21);
		f_ipv = (float)ipv/pow(2,21);
		param_1 = (float)p_1/pow(2,21);
		param_2 = (float)p_2/pow(2,21);

//		printf("theta1 = %f\t theta2 = %f\n\r",param_1,param_2);
		vpv_out[i]=f_vpv;
		ipv_out[i]=f_ipv;
		theta1_out[i]=param_1;
		theta2_out[i]=param_2;
		usleep(microseconds);

	}
//
	for(int i=0;i<SIZE;i++){
		//printf("i= %i\t vpv = %f\t ipv = %f\t theta1 = %f\t theta2 = %f\n\r",i,vpv_out[i],ipv_out[i],theta1_out[i],theta2_out[i]);
		printf("\n%i,%f,%f,%f,%f",i,vpv_out[i],ipv_out[i],theta1_out[i],theta2_out[i]);
	}

	//printf("\nFin prueba\n\n");

}


