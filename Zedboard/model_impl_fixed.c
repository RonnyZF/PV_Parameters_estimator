#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define INIT_ALPHA (0.55) // (alpha->kT)
#define INIT_BETA (-13.0) // (b=ln(Is))

#define ALPHA 0.625

#define GAMMA_11 0.1
#define GAMMA_22 100
#define F_SAMPLING 1e6
#define V_CTE 16.69

#define PVG_F 1000

#define I_G 5.1387085e-6 //(b=-12.1787)

#define STOP_TIME 0.1 //  (100ms)

#define TOTAL_BITS 64

#define Q_SIZE 24

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

struct ADC_data{
	int64_t *samp;
	size_t len;
};


extern inline int64_t float_to_fixed(float var){
	 return (int64_t) round(var*pow(2,Q_SIZE));
}

int64_t mult(int64_t a, int64_t b){
	__int128_t m=((__int128_t)a*(__int128_t)b);
	__int128_t out=(m>>Q_SIZE);
	if(out>INT32_MAX){

		return INT32_MAX;}
	if(out<INT32_MIN){

		return INT32_MIN;}
	if(((m>>Q_SIZE-1)&&1)==1){
		return (int64_t) out+1;}
	else{
		return (int64_t) out;}
}	

int64_t add(int64_t a, int64_t b){
	__int128_t out = ((__int128_t)a+(__int128_t)b);
//	printf("%ld",out);
	if(out>INT32_MAX)
		return INT32_MAX;
	if(out<INT32_MIN)
		return INT32_MIN;
	return (int64_t) out;
}

int main(int argc, char **argv){
	struct ADC_data adc_v;
	struct ADC_data adc_i_linear;
	int64_t theta_v[2]={0,0};
	int64_t theta_v_1[2]={float_to_fixed(INIT_ALPHA), float_to_fixed(INIT_BETA)};
	float b=log(I_G);

	size_t len = (size_t) round(STOP_TIME*F_SAMPLING);
	adc_v.len = len;
	adc_i_linear.len = len;
	adc_v.samp = (int64_t *) malloc(sizeof(int64_t)*len);
	adc_i_linear.samp = (int64_t *) malloc(sizeof(int64_t)*len);
	float aux=0;
	for(int i=0; i<len; i++){
		aux = V_CTE+0.3*V_CTE*sin(2*M_PI*PVG_F*i/F_SAMPLING);
		adc_v.samp[i] = float_to_fixed(aux);
		adc_i_linear.samp[i] = float_to_fixed((ALPHA*aux+b));
		//printf("V: %8f\tI: %8f\n",adc_v.samp[i],adc_i_linear.samp[i]);
	}

	
	int64_t g11=float_to_fixed(GAMMA_11);
	int64_t g22=float_to_fixed(GAMMA_22);
	int64_t acc=0;
	int64_t h_step=float_to_fixed(1/F_SAMPLING);

	for(int i=0; i<len; i++){


		acc=mult(-adc_v.samp[i],theta_v_1[0]);
//		printf("1 %8f  ",((float)acc)/pow(2,Q_SIZE));
		acc=add(acc,-theta_v_1[1]);
//		printf("2 %8f  ",((float)acc)/pow(2,Q_SIZE));
		acc=add(acc,adc_i_linear.samp[i]);
//		printf("3 %8f  ",((float)acc)/pow(2,Q_SIZE));
		acc=mult(acc,h_step);
//		printf("4 %8f\n",((float)acc)/pow(2,Q_SIZE));
		//aux=(adc_i_linear.samp[i]-adc_v.samp[i]*theta_v_1[0]-theta_v_1[1])/F_SAMPLING;
		//theta_v[0]=g11*aux*adc_v.samp[i]+theta_v_1[0];
		theta_v[0]=add(mult(g11,mult(acc,adc_v.samp[i])),theta_v_1[0]);
		theta_v[1]=add(mult(g22,acc),theta_v_1[1]);
		//theta_v[1]=g22*aux+theta_v_1[1];
		printf("%8f\t%8f\n",((float)theta_v_1[0])/pow(2,Q_SIZE),((float)theta_v_1[1])/pow(2,Q_SIZE));
		theta_v_1[0]=theta_v[0];
		theta_v_1[1]=theta_v[1];
		acc=0;
		
	}

	free(adc_v.samp);
	free(adc_i_linear.samp);

	return 0;
}


