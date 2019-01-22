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
}



int fixed_estimator(hls::stream<data_vector<est_precision > > &vector_in, hls::stream<param_t<est_precision > > &out){
# pragma HLS DATAFLOW

	hls::stream<data_vector<est_precision> > out_real;
	hls::stream<data_vector<log_precision> > in_log;
	hls::stream<log_data<log_precision> > out_log;
	hls::stream<data_vector<est_precision> > in_est;

	// Stage 1 - Pop ADC samples
	//pop_xadc_stream(in,vector_in);
	// Stage 2 - ADC samples to V/A units
	adc_to_real_value<est_precision>(vector_in,out_real);
	// Stage 3 - Precision change for logarithm calculation
	precision_change_vector_to_vector<est_precision,log_precision>(out_real,in_log);
	// Stage 4 - Logarithm calculation
	fixed_log_calculation<data_vector<est_precision>,log_precision>(in_log,out_log);
	// Stage 5 - Precision change for estimator
	precision_change_log_to_vector<log_precision,est_precision>(out_log,in_est);
	// Stage 6 - Parameters estimator
	parameters_estimator<est_precision > (in_est,out);

	return 0;
}




