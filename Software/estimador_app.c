/*
 * estimador.c
 *
 *  Created on: 13 mar. 2019
 *      Author: thor
 */

#include<stdio.h>
#include"xil_io.h"

#define ESTIMATOR_BASEADDR 0x43C00000
#define DATA_PARAM_1_OFFSET 0x10	//read only
#define CTRL_PARAM_1_OFFSET 0x14 	//read only
#define DATA_PARAM_2_OFFSET 0x18 	//read only
#define CTRL_PARAM_2_OFFSET 0x1C 	//read only
#define I_SCALE_OFFSET 0x20 		//write only
#define V_SCALE_OFFSET 0x28 		//write only
#define IG_OFFSET 0x30 				//write only
#define GAMMA11_OFFSET 0x38 		//write only
#define GAMMA12_OFFSET 0x40 		//write only
#define GAMMA21_OFFSET 0x48 		//write only
#define GAMMA22_OFFSET 0x50 		//write only
#define INIT_ALPHA_OFFSET 0x58 		//write only
#define INIT_BETA_OFFSET 0x60 		//write only

void set_register(int baseaddr, int offset, int32_t value){
	Xil_Out32(baseaddr + offset, value);
}

int get_register(int baseaddr, int offset){
	int temp = 0;
	Xil_In32(baseaddr + offset);
	return (temp);
}

int main(void){

	float param_1;
	float param_2;

	printf("Test project\n\r");
	//set initial values
	double init_alpha = 9227468.8;  //0.55 x 2^24
	double init_beta = -218103808;	//-13 x 2^24
	double gamma11 = 1677721.6;		//0.1 x 2^24
	double gamma12 = 0;				//0 x 2^24
	double gamma21 = 0;				//0 x 2^24
	double gamma22 = 1677721600;	//100 x 2^24
	double ig = 167772160;			//10 x 2^24
	double i_scale_f = 16777216;	//1 x 2^24
	double v_scale_f = 16777216;	//1 x 2^24

	int32_t alpha_fixed = (int32_t) init_alpha;
	int32_t beta_fixed = (int32_t) init_beta;
	int32_t gamma11_fixed = (int32_t) gamma11;
	int32_t gamma12_fixed = (int32_t) gamma12;
	int32_t gamma21_fixed = (int32_t) gamma21;
	int32_t gamma22_fixed = (int32_t) gamma22;
	int32_t ig_fixed = (int32_t) ig;
	int32_t i_scale_fixed = (int32_t) i_scale_f;
	int32_t v_scale_fixed = (int32_t) v_scale_f;

	set_register(ESTIMATOR_BASEADDR,INIT_ALPHA_OFFSET,alpha_fixed);
	set_register(ESTIMATOR_BASEADDR,INIT_BETA_OFFSET,beta_fixed);
	set_register(ESTIMATOR_BASEADDR,GAMMA11_OFFSET,gamma11_fixed);
	set_register(ESTIMATOR_BASEADDR,GAMMA12_OFFSET,gamma12_fixed);
	set_register(ESTIMATOR_BASEADDR,GAMMA21_OFFSET,gamma21_fixed);
	set_register(ESTIMATOR_BASEADDR,GAMMA22_OFFSET,gamma22_fixed);
	set_register(ESTIMATOR_BASEADDR,IG_OFFSET,ig_fixed);
	set_register(ESTIMATOR_BASEADDR,I_SCALE_OFFSET,i_scale_fixed);
	set_register(ESTIMATOR_BASEADDR,V_SCALE_OFFSET,v_scale_fixed);

	param_1 = get_register(ESTIMATOR_BASEADDR,DATA_PARAM_1_OFFSET);
	param_2 = get_register(ESTIMATOR_BASEADDR,DATA_PARAM_2_OFFSET);

	printf("Parameter 1 = %f\t Parameter 2 = %f\n\r",param_1,param_2);

	printf("test done\n");

	return 0;

}
