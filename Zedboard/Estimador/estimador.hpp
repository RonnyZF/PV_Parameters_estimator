#include <iostream>

#include <hls_stream.h>
#include <ap_fixed.h>
#include <hls_math.h>
#include <stdint.h>
#include <fstream>
#include <stdlib.h>
#include "../Library/xadc_stream.hpp"

typedef ap_fixed<32,11> est_precision;
typedef ap_fixed<18,5> log_precision;

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

template<typename T>
struct scale_struct{
	T _x;
	T _y;
};

/******************************** C++ TEMPLATES ***************************************/

int fixed_estimator(hls::stream<xadc_stream_interface> &seq_in_xadc,
					hls::stream<param_t<est_precision > > &out,
					hls::stream<data_vector<est_precision > > &raw_out,
					est_precision I_scale_factor,
					est_precision V_scale_factor,
					est_precision Ig,
					est_precision GAMMA11,
					est_precision GAMMA12,
					est_precision GAMMA21,
					est_precision GAMMA22,
					est_precision INIT_ALPHA,
					est_precision INIT_BETA,
					est_precision T_SAMPLING,
					est_precision SET_FLAG
					);

int wrapper_fixed_estimator(hls::stream<xadc_stream_interface> &seq_in_xadc,
							param_t<est_precision> &interface_param_apprx,
							data_vector<est_precision> &raw_out,
							est_precision I_scale_factor,
							est_precision V_scale_factor,
							est_precision Ig,
							est_precision GAMMA11,
							est_precision GAMMA12,
							est_precision GAMMA21,
							est_precision GAMMA22,
							est_precision INIT_ALPHA,
							est_precision INIT_BETA,
							est_precision T_SAMPLING,
							est_precision SET_FLAG
							);

template<typename T>
int parameters_estimator(hls::stream<data_vector<T > > &in, hls::stream<param_t<T > > &out,
						 hls::stream<data_vector<T > > &raw_in, hls::stream<data_vector<T > > &raw_out,
						  T GAMMA11,
						  T GAMMA12,
						  T GAMMA21,
						  T GAMMA22,
						  T INIT_ALPHA,
						  T INIT_BETA,
						  T T_SAMPLING,
						  T SET_FLAG){

	data_vector<T> input=raw_in.read();
	data_vector<T> output = {0,0};
 	data_vector<T> sample_in=in.read(); // read fifo sample
 	static param_t<T> theta = {0,0}; // init theta register
 	static T init_cond_1 = 0;
	static T init_cond_2 = 0;
 	if(SET_FLAG){
 		init_cond_1 = INIT_ALPHA;
 		init_cond_2 = INIT_BETA;
 	}
	output._v=input._v;
	output._i=input._i;
	raw_out.write(output);
 	T aux = 0;
	aux = -input._v;
	aux *= init_cond_1;
	aux -= init_cond_2;
	aux += sample_in._i;

	param_t<T> tuple_for_operations={GAMMA11*input._v,GAMMA21*input._v};
	tuple_for_operations._1+=GAMMA12;
	tuple_for_operations._2+=GAMMA22;

	tuple_for_operations._1*=aux;
	tuple_for_operations._2*=aux;

	theta._1 = tuple_for_operations._1*T_SAMPLING + init_cond_1;
	theta._2 = tuple_for_operations._2*T_SAMPLING + init_cond_2;

	init_cond_1=theta._1;
	init_cond_2=theta._2;

	out.write(theta);
	return 0;
}

// --------------------------------------------------------

template<typename T>
int samples_generator(hls::stream< data_vector<T > > &in, int n){
	data_vector<T> samples;
	samples._i=0;
	samples._v=0;

	float t;
	float current;
	float volt;

	std::ifstream data("/home/local/ESTUDIANTES/rzarate/vivadoprjs/PV_Parameters_estimator/Software/python_code/DATA.CSV");
	std::string time;
	std::string column_c;
	std::string column_v;
	if(!data.is_open()) std::cout << "ERROR: can't open file"<<std::endl;

	for(int a=1; a<=n;a++){
		getline(data,time,',');
		getline(data,column_c,',');
		getline(data,column_v,'\n');
		t=std::stof((time).c_str(),0);
		current=std::stof((column_c).c_str(),0);
		volt=std::stof((column_v).c_str(),0);
	}
//	volt = 17.125732/22;//0.126;
//	current = 2.903137/5;//0.125;
	samples._i= current;
	samples._v=volt;
	in.write(samples);
	return 0;
}
// --------------------------------------------------------
template<typename T>
int adc_to_real_value(hls::stream<data_vector<T > > &in,
					  hls::stream<data_vector<T > > &out,
					  hls::stream<data_vector<T > > &raw_out,
					  T I_scale_factor = 5,
					  T V_scale_factor = 22,
					  T Ig = 3.99){

	const T min_current = 0.00001;

	data_vector<T> sample_in=in.read();
	sample_in._i = sample_in._i * I_scale_factor;
	sample_in._v = sample_in._v * V_scale_factor;
	raw_out.write(sample_in);
	T aux = Ig-sample_in._i;
	sample_in._i = (Ig>=sample_in._i) ?aux: min_current;
	out.write(sample_in);

	return 0;
}

template<typename type_in, typename type_out>
int precision_change_vector_to_log(hls::stream<data_vector<type_in > > &in, hls::stream<data_vector<type_out > > &out){
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
