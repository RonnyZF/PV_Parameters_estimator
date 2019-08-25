#include <iostream>
#include <fstream>
#include <hls_stream.h>
#include <hls_math.h>
#include "../Estimador/estimador.hpp"
#include "../Library/Ln_using_log2_templates.cpp"


// function prototypes
int float_samples_generator(hls::stream<data_vector<float > > &in, int n);
int fixed_samples_generator(hls::stream<data_vector<est_precision > > &in, int n);
int float_estimator(hls::stream<data_vector<float > > &in, hls::stream<param_t<float > > &out);
int xadc_interface_adapter(hls::stream<data_vector<est_precision > > &in,hls::stream<xadc_stream_interface> &seq_in_xadc);

int main(){
	hls::stream<data_vector<float > > in_float;
	hls::stream<data_vector<est_precision> > in_fixed;
	hls::stream<param_t<float > > out_float;
	hls::stream<param_t<est_precision > > out_fixed;
	hls::stream<xadc_stream_interface> seq_in_xadc;
	param_t<est_precision> interface_param_apprx;

	est_precision I_scale_factor=5;
	est_precision V_scale_factor=22;
	est_precision Ig=3.99;
	est_precision GAMMA11=0.1;
	est_precision GAMMA12=0;
	est_precision GAMMA21=0;
	est_precision GAMMA22=100;
	est_precision INIT_ALPHA = 0.55;
	est_precision INIT_BETA = -13.0;

	float error_theta_1=0;
	float error_theta_2=0;
	float theta_1_float=0;
	float theta_2_float=0;

	std::ofstream csvfloat;
	csvfloat.open("/home/thor/Escritorio/tutoriales/HLS_float.CSV");
	std::ofstream csvfixed;
	csvfixed.open("/home/thor/Escritorio/tutoriales/HLS_fixed.CSV");

	for (int i=1;i<250;i++){
// SW reference
		std::cout<<"              cálculo float "<<std::endl;
		float_samples_generator(in_float,i);
		float_estimator(in_float,out_float);
// HW reference
		std::cout<<"              cálculo fixed "<<std::endl;
		fixed_samples_generator(in_fixed,i);
		//fixed_estimator(in_fixed,out_fixed);
		xadc_interface_adapter(in_fixed,seq_in_xadc);
		wrapper_fixed_estimator(seq_in_xadc,interface_param_apprx,I_scale_factor,V_scale_factor,Ig,GAMMA11,GAMMA12,GAMMA21,GAMMA22,INIT_ALPHA,INIT_BETA);
		out_fixed.write(interface_param_apprx);

		param_t<float> result_float = out_float.read();
		param_t<est_precision> result_fixed = out_fixed.read();

		//calculos de error
		theta_1_float = result_fixed._1;
		theta_2_float = result_fixed._2;

		error_theta_1 = abs(((theta_1_float-result_float._1)/result_float._1)*100);
		error_theta_2 = ((theta_2_float-result_float._2)/result_float._2)*100;
		//...
		csvfloat <<result_float._1<<","<<result_float._2<<"\n";
		csvfixed <<result_fixed._1<<","<<result_fixed._2<<"\n";

		std::cout << "i obtained: " << result_fixed._1 << "\t expected: " << result_float._1 << "\t % error: " << error_theta_1 << "\n";
		std::cout << "v obtained: " << result_fixed._2 << "\t expected: " << result_float._2 << "\t % error: " << error_theta_2 << "\n\n";
	}
	return 0;
}
// --------------------------------------------------------
int float_estimator(hls::stream<data_vector<float > > &in, hls::stream<param_t<float > > &out){

	hls::stream<data_vector<float> > out_real;
	hls::stream<data_vector<float> > in_log;
	hls::stream<log_data<float> > out_log;
	hls::stream<data_vector<float> > in_est;

	adc_to_real_value<float>(in,out_real,5,22,3.99);

	precision_change_vector_to_vector<float,float>(out_real,in_log);

	fixed_log_calculation<scale_struct<float>,float>(in_log,out_log);

	precision_change_log_to_vector<float,float>(out_log,in_est);

	parameters_estimator<float > (in_est,out);
	return 0;
}
// --------------------------------------------------------
int float_samples_generator(hls::stream<data_vector<float > > &in, int n){

	samples_generator<float>(in,n);
	return 0;
}

// --------------------------------------------------------
int fixed_samples_generator(hls::stream<data_vector<est_precision > > &in, int n){
	samples_generator<est_precision>(in, n);
	return 0;
}

int xadc_interface_adapter(
			hls::stream<data_vector<est_precision > > &in,
			hls::stream<xadc_stream_interface> &seq_in_xadc
){
	xadc_stream_interface xadc_stream;
	data_vector<est_precision> holder_vector = in.read();
	// voltage channel
	xadc_stream.tid = XADC_CHANNEL_1_ID;
	xadc_stream.tdata = holder_vector._v;
	seq_in_xadc.write(xadc_stream);
	// current channel
	xadc_stream.tid = XADC_CHANNEL_2_ID;
	xadc_stream.tdata = holder_vector._i;
	std::cout<<"c int: "<<holder_vector._i<<" v int: "<<holder_vector._v<<std::endl;
	seq_in_xadc.write(xadc_stream);
	return 0;
}
