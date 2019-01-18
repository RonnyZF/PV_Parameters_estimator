#include "estimador.hpp"

// THIS IS THE TOP LEVEL DESIGN THAT WILL BE SYNTHESIZED

int fixed_estimador(hls::stream<data_vector<est_precision > > &in, hls::stream<param_t<est_precision > > &out){
# pragma HLS DATAFLOW

	hls::stream<data_vector<est_precision> > out_real;
	hls::stream<data_vector<log_precision> > in_log;
	hls::stream<log_data<log_precision> > out_log;
	hls::stream<data_vector<est_precision> > in_est;

	template_adc_to_real_value<est_precision>(in,out_real);

	template_precision_change_vector_to_vector<est_precision,log_precision>(out_real,in_log);

	template_fixed_log<data_vector<est_precision>,log_precision>(in_log,out_log);

	template_precision_change_log_to_vector<log_precision,est_precision>(out_log,in_est);

	template_estimador<est_precision > (in_est,out);
	return 0;
}




