#include "estimador.hpp"

/*
int estimador(hls::stream<data_t> &in, hls::stream<param_t> &out){
	const ap_fixed<32,14,AP_RND,AP_SAT> GAMMA11 = (1,234);
	data_t sample_in;
	param_t theta;
	in.read(sample_in);
	theta._1 = sample_in.adc_v + sample_in.adc_i;
	theta._2 = sample_in.adc_v - sample_in.adc_i;
	out.write(theta);
	return 0;
}
*/
int estimador(hls::stream<data_t> &in, hls::stream<param_t> &out){
	const fixed_32 GAMMA11 = (0.1);
	const fixed_32 GAMMA22 = (100);
	const fixed_32 INIT_ALPHA = 0.55;
	const fixed_32 INIT_BETA = -13.0;

	data_t sample_in;
	param_t theta;
	param_t theta_v_l;
	theta_v_l._1=INIT_ALPHA;
	theta_v_l._2=INIT_BETA;
	fixed_32 aux = 0.0;
	in.read(sample_in);
	aux = -sample_in.adc_v * theta_v_l._1;
	aux += theta_v_l._2;
	aux += sample_in.adc_i;
	theta._1 = GAMMA11*aux*sample_in.adc_v + theta_v_l._1;
	theta._2 = GAMMA22*aux*theta_v_l._2;
	theta_v_l._1=theta._1;
	theta_v_l._2=theta._2;
	out.write(theta);
	return 0;
}

