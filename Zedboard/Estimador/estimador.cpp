#include "estimador.hpp"

// THIS IS THE TOP LEVEL DESIGN THAT WILL BE SYNTHESIZED



int fixed_estimador(hls::stream<data_vector<est_precision > > &in, hls::stream<param_t<est_precision > > &out){
# pragma HLS DATAFLOW

	hls::stream<data_vector<est_precision> > out_real;

	template_adc_to_real_value<est_precision>(in,out_real);

	hls::stream<data_vector<log_precision> > in_log;
	data_vector<est_precision> sample_in_log=out_real.read();
	data_vector<log_precision> aux = {0,0};
	aux._v=sample_in_log._v;
	aux._i=sample_in_log._i;
	in_log.write(aux);
	std::cout<<"aux_v="<<aux._v<< " in_log_v="<<sample_in_log._v<<std::endl;
	std::cout<<"aux_i="<<aux._i<< " in_log_i="<<sample_in_log._i<<std::endl;


	hls::stream<log_data<log_precision> > out_log;

	template_fixed_log<data_vector<est_precision>,log_precision>(in_log,out_log);

	hls::stream<data_vector<est_precision> > in_est;

	log_data<log_precision> sample_in_est=out_log.read();
	std::cout<<"sample_in_est_v="<<sample_in_est.adc_v<<std::endl;
	std::cout<<"sample_in_est_i="<<sample_in_est.log<<std::endl;
	data_vector<est_precision> aux2;
	aux2._v=sample_in_est.adc_v;
	aux2._i=sample_in_est.log;
	in_est.write(aux2);

	template_estimador<est_precision > (in_est,out);
	return 0;
}




