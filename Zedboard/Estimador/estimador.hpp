#include <iostream>

#include <hls_stream.h>
#include <ap_fixed.h>
#include <hls_math.h>
#include <stdint.h>
#include <fstream>
#include <stdlib.h>
#include "../Library/xadc_stream.hpp"

typedef ap_fixed<32,8> est_precision;
typedef ap_fixed<18,7> log_precision;

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
					est_precision I_scale_factor,
					est_precision V_scale_factor,
					est_precision Ig,
					est_precision GAMMA11,
					est_precision GAMMA12,
					est_precision GAMMA21,
					est_precision GAMMA22,
					est_precision INIT_ALPHA,
					est_precision INIT_BETA
					);

int wrapper_fixed_estimator(hls::stream<xadc_stream_interface> &seq_in_xadc,
							param_t<est_precision> &interface_param_apprx,
							est_precision I_scale_factor,
							est_precision V_scale_factor,
							est_precision Ig,
							est_precision GAMMA11,
							est_precision GAMMA12,
							est_precision GAMMA21,
							est_precision GAMMA22,
							est_precision INIT_ALPHA,
							est_precision INIT_BETA
							);

template<typename T>
int parameters_estimator(hls::stream<data_vector<T > > &in, hls::stream<param_t<T > > &out,
						  T GAMMA11 = 0.1,
						  T GAMMA12 =0,
						  T GAMMA21 =0,
						  T GAMMA22 = 100,
						  T INIT_ALPHA = 0.55,
						  T INIT_BETA = -13.0){

 	const T T_SAMPLING = 1e-6;

 	data_vector<T> sample_in=in.read(); // read fifo sample
 	static param_t<T> theta = {0,0}; // init theta register
 	static param_t<T> theta_v_l = {INIT_ALPHA,INIT_BETA}; // init past theta register
 	T aux = 0.0;

	aux = -sample_in._v;
	aux *= theta_v_l._1;
	aux += -theta_v_l._2;
	aux += sample_in._i;

	param_t<T> tuple_for_operations={GAMMA11*sample_in._v,GAMMA21*sample_in._v};
	tuple_for_operations._1+=GAMMA12;
	tuple_for_operations._2+=GAMMA22;

	tuple_for_operations._1*=aux;
	tuple_for_operations._2*=aux;

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
	data_vector<T> samples;
	samples._i=0;
	samples._v=0;

	float t;
	float current;
	float volt;

	std::cout<<"n = "<<n<<std::endl;

	std::ifstream data("/home/local/ESTUDIANTES/rzarate/python_code/DATA.CSV");
	std::string time;
	std::string column_c;
	std::string column_v;
	if(!data.is_open()) std::cout << "ERROR: File open"<<std::endl;

	for(int a=1; a<=n;a++){
		getline(data,time,',');
		getline(data,column_c,',');
		getline(data,column_v,'\n');
		t=std::stof((time).c_str(),0);
		current=std::stof((column_c).c_str(),0);
		volt=std::stof((column_v).c_str(),0);
	}
	std::cout<<"line: "<<n<<" tiempo: "<<t<<" corriente: "<<current<<" volt: "<<volt<<std::endl;
	samples._i= current;
	samples._v=volt;
	in.write(samples);
	return 0;
}
// --------------------------------------------------------
template<typename T>
int adc_to_real_value(hls::stream<data_vector<T > > &in,
					  hls::stream<data_vector<T > > &out,
					  T I_scale_factor = 5,
					  T V_scale_factor = 22,
					  T Ig = 3.99){

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


