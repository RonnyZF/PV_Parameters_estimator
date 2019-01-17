#include "estimador.hpp"

// THIS IS THE TOP LEVEL DESIGN THAT WILL BE SYNTHESIZED


int fixed_estimador(hls::stream<adc_data<fixed_32 > > &in, hls::stream<param_t<fixed_32 > > &out){
# pragma HLS DATAFLOW
	hls::stream<adc_data<fixed_log_pres> > in_log;
	adc_data<fixed_32> sample_in_log=in.read();
	adc_data<fixed_log_pres> aux = {0,0};
	aux.adc_v=sample_in_log.adc_v;
	aux.adc_i=sample_in_log.adc_i;
	in_log.write(aux);
	std::cout<<"aux_v="<<aux.adc_v<< " in_log_v="<<sample_in_log.adc_v<<std::endl;
	std::cout<<"aux_i="<<aux.adc_i<< " in_log_i="<<sample_in_log.adc_i<<std::endl;


	hls::stream<log_data<fixed_log_pres> > out_log;

	template_fixed_log<Scaling,fixed_log_pres>(in_log,out_log);

	hls::stream<adc_data<fixed_32> > in_est;

	log_data<fixed_log_pres> sample_in_est=out_log.read();
	std::cout<<"sample_in_est_v="<<sample_in_est.adc_v<<std::endl;
	std::cout<<"sample_in_est_i="<<sample_in_est.log<<std::endl;
	adc_data<fixed_32> aux2;
	aux2.adc_v=sample_in_est.adc_v;
	aux2.adc_i=sample_in_est.log;
	in_est.write(aux2);

	template_estimador<fixed_32 > (in_est,out);
	return 0;
}







