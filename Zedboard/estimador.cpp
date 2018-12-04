#include "estimador.hpp"

int estimador(hls::stream<data_t> &in, hls::stream<param_t> &out){
	const fixed_32 GAMMA11 = 0.1;
	const fixed_32 GAMMA22 = 100;
	const fixed_32 INIT_ALPHA = 0.55;
	const fixed_32 INIT_BETA = -13.0;
	const fixed_32 F_SAMPLING = 1e6;

	data_t sample_in=in.read(); // read fifo sample
	//std::cout << "tamaño dentro: " << in.size() << std::endl;
	static param_t theta = {0,0}; // init theta register
	static param_t theta_v_l = {INIT_ALPHA,INIT_BETA}; // init past theta register
	fixed_32 aux = 0.0;
	//std::cout << "ALPHA: " << theta_v_l._1 << "\t BETA: " << theta_v_l._2 << std::endl;

	aux = -sample_in.adc_v * theta_v_l._1;
	aux += -theta_v_l._2;
	aux += sample_in.adc_i;
	aux /= F_SAMPLING;
	theta._1 = GAMMA11*aux*sample_in.adc_v + theta_v_l._1;
	theta._2 = GAMMA22*aux*theta_v_l._2;
	theta_v_l._1=theta._1;
	theta_v_l._2=theta._2;
	out.write(theta);
	return 0;
}

/*
template<typename T>
 int estimador(hls::stream<data_t(T)> &in, hls::stream<param_t(T)> &out){
 	const T GAMMA11 = (0.1);
 	const T GAMMA22 = (100);
 	const T INIT_ALPHA = 0.55;
 	const T INIT_BETA = -13.0;

 	data_t sample_in=in.read(); // read fifo sample
 	static param_t theta = {0,0}; // init theta register
 	static param_t theta_v_l = {INIT_ALPHA,INIT_BETA}; // init past theta register
 	T aux = 0.0;

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

estimador<float>(in,out);
estimador<fixed_32>(in,out);

*/