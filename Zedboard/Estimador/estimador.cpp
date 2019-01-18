#include "estimador.hpp"
#include "../Library/Ln_using_log2_templates.cpp"

// THIS IS THE TOP LEVEL DESIGN THAT WILL BE SYNTHESIZED

int fixed_estimador(hls::stream<data_vector<est_precision > > &in, hls::stream<param_t<est_precision > > &out){
# pragma HLS DATAFLOW

	hls::stream<data_vector<est_precision> > out_real;
	hls::stream<data_vector<log_precision> > in_log;
	hls::stream<log_data<log_precision> > out_log;
	hls::stream<data_vector<est_precision> > in_est;

	// Stage 1 - ADC samples to V/A units
	adc_to_real_value<est_precision>(in,out_real);
	// Stage 2 - Precision change for logarithm calculation
	precision_change_vector_to_vector<est_precision,log_precision>(out_real,in_log);
	// Stage 3 - Logarithm calculation
	fixed_log_calculation<data_vector<est_precision>,log_precision>(in_log,out_log);
	// Stage 4 - Precision change for estimator
	precision_change_log_to_vector<log_precision,est_precision>(out_log,in_est);
	// Stage 5 - Parameters estimator
	parameters_estimador<est_precision > (in_est,out);

	return 0;
}




