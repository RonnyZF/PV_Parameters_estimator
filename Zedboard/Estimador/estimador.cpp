#include "estimador.hpp"
#include "../Library/Ln_using_log2_templates.cpp"


// THIS IS THE TOP LEVEL DESIGN THAT WILL BE SYNTHESIZED
int pop_xadc_stream(hls::stream<xadc_stream_interface> &seq_in_xadc,
					hls::stream<data_vector<est_precision > > &vector_in){

	data_vector<est_precision> parallel_packed_samples;
	// read pair of samples
	for(int i = 0; i<2; i++){
		xadc_stream_interface holder_sample = seq_in_xadc.read();
		est_precision converter = holder_sample.tdata;
		if(holder_sample.tid==XADC_CHANNEL_1_ID){
			parallel_packed_samples._v = converter;
		}else if(holder_sample.tid==XADC_CHANNEL_2_ID){
			parallel_packed_samples._i = converter;
		}
	}
	vector_in.write(parallel_packed_samples);
	return 0;
}

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
					){

	static hls::stream<data_vector<est_precision > > vector_in;
	static hls::stream<data_vector<est_precision> > out_real;
	static hls::stream<data_vector<est_precision> > raw_out_real;
	static hls::stream<data_vector<log_precision> > in_log;
	static hls::stream<log_data<log_precision> > out_log;
	static hls::stream<data_vector<est_precision> > in_est;

#pragma HLS dataflow
	//POP ADC data
	pop_xadc_stream(seq_in_xadc,vector_in);
	// Stage 1 - ADC samples to V/A units
	adc_to_real_value<est_precision>(vector_in,out_real,raw_out_real,I_scale_factor,V_scale_factor, Ig);
	// Stage 2 - Precision change for logarithm calculation
	precision_change_vector_to_log<est_precision,log_precision>(out_real,in_log);
	// Stage 3 - Logarithm calculation
	fixed_log_calculation<scale_struct<est_precision>,log_precision>(in_log,out_log);
	// Stage 4 - Precision change for estimator
	precision_change_log_to_vector<log_precision,est_precision>(out_log,in_est);
	// Stage 5 - Parameters estimator
	parameters_estimator<est_precision > (in_est,out,raw_out_real,raw_out,GAMMA11,GAMMA12,GAMMA21,GAMMA22,INIT_ALPHA,INIT_BETA,T_SAMPLING,SET_FLAG);
	return 0;
}

int wrapper_fixed_estimator(
			hls::stream<xadc_stream_interface> &seq_in_xadc,
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
			est_precision SET_FLAG)
			{

#pragma HLS INTERFACE ap_ctrl_hs port=return
#pragma HLS INTERFACE axis register both port=seq_in_xadc
#pragma HLS INTERFACE s_axilite register port=I_scale_factor
#pragma HLS INTERFACE s_axilite register port=V_scale_factor
#pragma HLS INTERFACE s_axilite register port=Ig
#pragma HLS INTERFACE s_axilite register port=GAMMA11
#pragma HLS INTERFACE s_axilite register port=GAMMA12
#pragma HLS INTERFACE s_axilite register port=GAMMA21
#pragma HLS INTERFACE s_axilite register port=GAMMA22
#pragma HLS INTERFACE s_axilite register port=INIT_ALPHA
#pragma HLS INTERFACE s_axilite register port=INIT_BETA
#pragma HLS INTERFACE s_axilite register port=T_SAMPLING
#pragma HLS INTERFACE s_axilite register port=SET_FLAG
#pragma HLS INTERFACE s_axilite port=interface_param_apprx
#pragma HLS INTERFACE s_axilite port=raw_out

	static hls::stream<param_t<est_precision > > vector_out;
	static hls::stream<data_vector<est_precision > > raw_vector_out;

	param_t<est_precision> result;
	data_vector<est_precision> raw_result;
#pragma HLS dataflow
	fixed_estimator(seq_in_xadc,vector_out,raw_vector_out,I_scale_factor,V_scale_factor,Ig,GAMMA11,GAMMA12,GAMMA21,GAMMA22,INIT_ALPHA,INIT_BETA,T_SAMPLING,SET_FLAG);
	vector_out.read(result);
	raw_vector_out.read(raw_result);
	interface_param_apprx=result;
	raw_out=raw_result;
	return 0;
}


