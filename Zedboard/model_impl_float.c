#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#define INIT_ALPHA 0.55 // (alpha->kT)
#define INIT_BETA -13.0 // (b=ln(Is))

#define ALPHA 0.625

#define GAMMA_11 0.1
#define GAMMA_22 100
#define F_SAMPLING 1e6
#define V_CTE 16.69

#define PVG_F 1000

#define I_G 5.1387085e-6 //(b=-12.1787)

#define STOP_TIME 4 //  (100ms)

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

struct ADC_data{
	float *samp;
	size_t len;
};


int main(int argc, char **argv){
	struct ADC_data adc_v;
	struct ADC_data adc_i_linear;
	float theta_v[2]={0,0};
	float theta_v_1[2]={INIT_ALPHA, INIT_BETA};
	float b=log(I_G);

	size_t len = (size_t) round(STOP_TIME*F_SAMPLING);
	adc_v.len = len;
	adc_i_linear.len = len;
	adc_v.samp = (float *) malloc(sizeof(float)*len);
	adc_i_linear.samp = (float *) malloc(sizeof(float)*len);
	
	for(int i=0; i<len; i++){
		adc_v.samp[i] = V_CTE+0.3*V_CTE*sin(2*M_PI*PVG_F*i/F_SAMPLING);
		adc_i_linear.samp[i] = ALPHA*adc_v.samp[i]+b;
		//printf("V: %8f\tI: %8f\n",adc_v.samp[i],adc_i_linear.samp[i]);
	}

	float aux=0;
	for(int i=0; i<len; i++){
		aux = -adc_v.samp[i]*theta_v_1[0];
//		printf("1 %f  ",aux);
		aux += -theta_v_1[1];
//		printf("2 %f  ",aux);
		aux += adc_i_linear.samp[i];
//		printf("3 %f  ",aux);
		aux /= F_SAMPLING;
//		printf("4 %f\n",aux);
		theta_v[0]=GAMMA_11*aux*adc_v.samp[i]+theta_v_1[0];
		theta_v[1]=GAMMA_22*aux+theta_v_1[1];
		theta_v_1[0]=theta_v[0];
		theta_v_1[1]=theta_v[1];
		printf("%8f\t%8f\n",theta_v_1[0],theta_v_1[1]);
	}

	free(adc_v.samp);
	free(adc_i_linear.samp);

	return 0;
}


