#include <hls_stream.h>
#include "ap_fixed.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef ap_fixed<32,8,AP_RND,AP_SAT> fixed_32;

// --------------------------------------------------------
template<typename T>
struct adc_data{
	T adc_v;
	T adc_i;
};

template<typename T>
struct param_t{
	T _1;
	T _2;
};

/* ****************************** C++ TEMPLATES ***************************************/

int fixed_estimador(hls::stream<adc_data<fixed_32 > > &in, hls::stream<param_t<fixed_32 > > &out);

template<typename T>
 int template_estimador(hls::stream<adc_data<T > > &in, hls::stream<param_t<T > > &out){
 	const T GAMMA11 = (0.1);
 	const T GAMMA22 = (100);
 	const T INIT_ALPHA = 0.55;
 	const T INIT_BETA = -13.0;
 	const T T_SAMPLING = 1e-6;

 	adc_data<T> sample_in=in.read(); // read fifo sample
 	static param_t<T> theta = {0,0}; // init theta register
 	static param_t<T> theta_v_l = {INIT_ALPHA,INIT_BETA}; // init past theta register
 	T aux = 0.0;

	aux = -sample_in.adc_v * theta_v_l._1;
	aux += -theta_v_l._2;
	aux += sample_in.adc_i;

	theta._1 = (GAMMA11*aux*sample_in.adc_v)*T_SAMPLING + theta_v_l._1;
	theta._2 = (GAMMA22*aux)*T_SAMPLING+theta_v_l._2;
	theta_v_l._1=theta._1;
	theta_v_l._2=theta._2;
	out.write(theta);
	return 0;
}

// --------------------------------------------------------
template<typename T>
int template_samples_generator(hls::stream< adc_data<T > > &in, int n){
	const float ALPHA = 0.625;
	const float F_SAMPLING = 1e6;
	const float V_CTE = 16.69;
	const float MM_PI = 3.14159265358979323846;
	const float PVG_F = 1000;
	const float K = 0.3;
	const float I_G = 5.1387085e-6; //(b=-12.1787)
	float b=(float) log(I_G);

	adc_data<T> samples;
	samples.adc_i=0;
	samples.adc_v=0;
	float volt;
	float current;
	static int i = 0;
	volt = V_CTE+K*V_CTE*sin(2*MM_PI*PVG_F*i/F_SAMPLING);
	current = ALPHA*volt +b;
	samples.adc_i=current;
	samples.adc_v=volt;
	i=n;
	//std::cout << "volt: " << samples.adc_v << "\t current: " << samples.adc_i << std::endl;
	in.write(samples);
	return 0;
}

