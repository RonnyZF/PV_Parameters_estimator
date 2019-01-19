#include <hls_stream.h>
#include "ap_fixed.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef ap_fixed<32,8,AP_RND,AP_SAT> est_precision;
typedef ap_fixed<32,14,AP_RND,AP_SAT> log_precision;

// --------------------------------------------------------
template<typename T>
struct data_vector{
	T _v;
	T _i;
};

template<typename T>
struct param_t{
	T _1;
	T _2;
};

template<typename T>
struct log_data{
	T adc_v;
	T log;
};

/* ****************************** C++ TEMPLATES ***************************************/

int fixed_estimator(hls::stream<data_vector<est_precision > > &in, hls::stream<param_t<est_precision > > &out);


template<typename T>
 int parameters_estimator(hls::stream<data_vector<T > > &in, hls::stream<param_t<T > > &out){
 	const T GAMMA11 = (0.1);
 	const T GAMMA22 = (100);
 	const T INIT_ALPHA = 0.55;
 	const T INIT_BETA = -13.0;
 	const T T_SAMPLING = 1e-6;

 	data_vector<T> sample_in=in.read(); // read fifo sample
 	static param_t<T> theta = {0,0}; // init theta register
 	static param_t<T> theta_v_l = {INIT_ALPHA,INIT_BETA}; // init past theta register
 	T aux = 0.0;

	aux = -sample_in._v * theta_v_l._1;
	aux += -theta_v_l._2;
	aux += sample_in._i;

	param_t<T> tuple_for_operations={GAMMA11*aux,GAMMA22*aux};
	tuple_for_operations._1*=sample_in._v;

	theta._1 = tuple_for_operations._1*T_SAMPLING + theta_v_l._1;
	theta._2 = tuple_for_operations._2*T_SAMPLING + theta_v_l._2;

	theta_v_l._1=theta._1;
	theta_v_l._2=theta._2;
	out.write(theta);
	return 0;
}

// --------------------------------------------------------
template<typename T>
int samples_generator(hls::stream< data_vector<T > > &in, int n){
	const float ALPHA = 0.625;
	const float F_SAMPLING = 1e6;
	const float V_CTE = 16.69;
	const float MM_PI = 3.14159265358979323846;
	const float PVG_F = 1000;
	const float K = 0.3;
	const float I_G = 5.1387085e-6; //(b=-12.1787)
	float b=(float) log(I_G);

	data_vector<T> samples;
	samples._i=0;
	samples._v=0;
	float volt;
	float current;
	static int i = 0;
	volt = V_CTE+K*V_CTE*sin(2*MM_PI*PVG_F*i/F_SAMPLING);
	current = ALPHA*volt +b;


	samples._i= current;//(current<1) ?current*-1: current;
	samples._v=volt;
	i=n;

	in.write(samples);
	return 0;
}

// --------------------------------------------------------
template<typename T>
int adc_to_real_value(hls::stream<data_vector<T > > &in, hls::stream<data_vector<T > > &out){
	const T I_scale_factor = 1;
	const T V_scale_factor = 1;
	const T Ig = 10;
	const T min_current = 0.002;

	data_vector<T> sample_in=in.read();
	sample_in._i = sample_in._i * I_scale_factor;
	sample_in._v = sample_in._v * V_scale_factor;
	T aux = Ig-sample_in._i;
	sample_in._i = (Ig>=sample_in._i) ?aux: min_current;
	out.write(sample_in);
	return 0;
}

template<typename type_in, typename type_out>
int precision_change_vector_to_vector(hls::stream<data_vector<type_in > > &in, hls::stream<data_vector<type_out > > &out){
	data_vector<type_in> sample_in_log=in.read();
	data_vector<type_out> aux = {0,0};
	aux._v=sample_in_log._v;
	aux._i=sample_in_log._i;
	out.write(aux);
	return 0;
}

template<typename type_in, typename type_out>
int precision_change_log_to_vector(hls::stream<log_data<type_in > > &in, hls::stream<data_vector<type_out > > &out){
	log_data<type_in> sample_in_log=in.read();
	data_vector<type_out> aux = {0,0};
	aux._v=sample_in_log.adc_v;
	aux._i=sample_in_log.log;
	out.write(aux);
	return 0;
}
