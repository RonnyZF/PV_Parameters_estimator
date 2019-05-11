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

	double param_1=0;
	double param_2=0;
	uint32_t gpio_mask = (AP_START);

	int init_alpha = to_fixed(0.55);
	int init_beta = to_fixed(-13);
	int gamma11 = to_fixed(0.1);
	int gamma12 = to_fixed(0);
	int gamma21 = to_fixed(0);
	int gamma22 = to_fixed(100);
	int ig = to_fixed(10);
	int i_scale_f = to_fixed(1);
	int v_scale_f = to_fixed(1);


	XGpio_DiscreteWrite(&Igpio_1,1,gpio_mask);

//	XWrapper_fixed_estimator_Set_INIT_ALPHA_V(&estimator, INT2U32(init_alpha));
//	XWrapper_fixed_estimator_Set_INIT_BETA_V(&estimator, INT2U32(init_beta));
//	XWrapper_fixed_estimator_Set_GAMMA11_V(&estimator, INT2U32(gamma11));
//	XWrapper_fixed_estimator_Set_GAMMA12_V(&estimator, INT2U32(gamma12));
//	XWrapper_fixed_estimator_Set_GAMMA21_V(&estimator, INT2U32(gamma21));
//	XWrapper_fixed_estimator_Set_GAMMA22_V(&estimator, INT2U32(gamma22));
//	XWrapper_fixed_estimator_Set_Ig_V(&estimator, INT2U32(ig));
//	XWrapper_fixed_estimator_Set_I_scale_factor_V(&estimator, INT2U32(i_scale_f));
//	XWrapper_fixed_estimator_Set_V_scale_factor_V(&estimator, INT2U32(v_scale_f));

	printf("Alpha= %lu\n",XWrapper_fixed_estimator_Get_INIT_ALPHA_V(&estimator));
	printf("Beta= %lu\n",XWrapper_fixed_estimator_Get_INIT_BETA_V(&estimator));
	printf("Gamma11= %lu\n",XWrapper_fixed_estimator_Get_GAMMA11_V(&estimator));
	printf("Gamma12= %lu\n",XWrapper_fixed_estimator_Get_GAMMA12_V(&estimator));
	printf("Gamma21= %lu\n",XWrapper_fixed_estimator_Get_GAMMA21_V(&estimator));
	printf("Gamma22= %lu\n",XWrapper_fixed_estimator_Get_GAMMA22_V(&estimator));
	printf("Ig= %lu\n",XWrapper_fixed_estimator_Get_Ig_V(&estimator));
	printf("I scale factor= %lu\n",XWrapper_fixed_estimator_Get_I_scale_factor_V(&estimator));
	printf("V scale factor= %lu\n",XWrapper_fixed_estimator_Get_V_scale_factor_V(&estimator));

	printf("Inicia prueba\n");
//	int f = 0;
//	while(f==0){
	for(int i=0;i<5;i++){
		param_1 = XWrapper_fixed_estimator_Get_interface_param_apprx_1_V_vld(&estimator);
		param_2 = XWrapper_fixed_estimator_Get_interface_param_apprx_2_V_vld(&estimator);
		printf("P_1 = %lf\t P_2 = %lf\n\r",param_1,param_2);
	}
	printf("Fin prueba\n\n\n");

}

