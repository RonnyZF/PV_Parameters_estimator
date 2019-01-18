#include "estimador.hpp"

// THIS IS THE TOP LEVEL DESIGN THAT WILL BE SYNTHESIZED

int precision_change_vector_to_vector(hls::stream<data_vector<est_precision > > &in, hls::stream<data_vector<log_precision > > &out){
	data_vector<est_precision> sample_in_log=in.read();
	data_vector<log_precision> aux = {0,0};
	aux._v=sample_in_log._v;
	aux._i=sample_in_log._i;
	out.write(aux);
	return 0;
}

int precision_change_log_to_vector(hls::stream<log_data<log_precision > > &in, hls::stream<data_vector<est_precision > > &out){
	log_data<log_precision> sample_in_log=in.read();
	data_vector<est_precision> aux = {0,0};
	aux._v=sample_in_log.adc_v;
	aux._i=sample_in_log.log;
	out.write(aux);
	return 0;
}

int fixed_estimador(hls::stream<data_vector<est_precision > > &in, hls::stream<param_t<est_precision > > &out){
# pragma HLS DATAFLOW

	hls::stream<data_vector<est_precision> > out_real;
	hls::stream<data_vector<log_precision> > in_log;
	hls::stream<log_data<log_precision> > out_log;
	hls::stream<data_vector<est_precision> > in_est;

	template_adc_to_real_value<est_precision>(in,out_real);

	precision_change_vector_to_vector(out_real,in_log);

	template_fixed_log<data_vector<est_precision>,log_precision>(in_log,out_log);

	precision_change_log_to_vector(out_log,in_est);

	template_estimador<est_precision > (in_est,out);
	return 0;
}




