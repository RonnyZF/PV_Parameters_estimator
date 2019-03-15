/*
 * estimado_app.c
 *
 *  Created on: 14 mar. 2019
 *      Author: Ronny Zárate Ferreto
 */

#include"monitor.h"


#define AP_DONE 0x1
#define AP_START 0x2
#define AP_READY 0x4
#define AP_IDLE 0x8
#define AP_CONTINUE 0x10

int main(void){

	XWrapper_fixed_estimator estimator;
	XGpio Igpio;

	uint32_t gpio_mask = (AP_START|AP_CONTINUE);

	uint32_t param_1=0;
	uint32_t param_2=0;

	double init_alpha = 9227468.8;  //0.55 x 2^24
	double init_beta = -218103808;	//-13 x 2^24
	double gamma11 = 1677721.6;		//0.1 x 2^24
	double gamma12 = 0;				//0 x 2^24
	double gamma21 = 0;				//0 x 2^24
	double gamma22 = 1677721600;	//100 x 2^24
	double ig = 167772160;			//10 x 2^24
	double i_scale_f = 16777216;	//1 x 2^24
	double v_scale_f = 16777216;	//1 x 2^24

	XWrapper_fixed_estimator_Initialize(&estimator,XPAR_WRAPPER_FIXED_ESTIMATOR_0_DEVICE_ID);
	XGpio_Initialize(&Igpio, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_DiscreteWrite(&Igpio, XPAR_AXI_GPIO_0_DEVICE_ID, gpio_mask);

	//set initial values
	XWrapper_fixed_estimator_Set_INIT_ALPHA_V(&estimator, INT2U32(init_alpha));
	XWrapper_fixed_estimator_Set_INIT_BETA_V(&estimator, INT2U32(init_beta));
	XWrapper_fixed_estimator_Set_GAMMA11_V(&estimator, INT2U32(gamma11));
	XWrapper_fixed_estimator_Set_GAMMA12_V(&estimator, INT2U32(gamma12));
	XWrapper_fixed_estimator_Set_GAMMA21_V(&estimator, INT2U32(gamma21));
	XWrapper_fixed_estimator_Set_GAMMA22_V(&estimator, INT2U32(gamma22));
	XWrapper_fixed_estimator_Set_Ig_V(&estimator, INT2U32(ig));
	XWrapper_fixed_estimator_Set_I_scale_factor_V(&estimator, INT2U32(i_scale_f));
	XWrapper_fixed_estimator_Set_V_scale_factor_V(&estimator, INT2U32(v_scale_f));


	printf("Test project\n\r");
	for(int i=0;i<1000;i++){
	param_1 = XWrapper_fixed_estimator_Get_interface_param_apprx_1_V_vld(&estimator);
	param_2 = XWrapper_fixed_estimator_Get_interface_param_apprx_2_V_vld(&estimator);
	printf("Parameter 1 = %lu\t Parameter 2 = %lu\n\r",param_1,param_2);
	}

	printf("test done\n");

	return 0;

}
