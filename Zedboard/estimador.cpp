#include "estimador.hpp"

// THIS IS THE TOP LEVEL DESIGN THAT WILL BE SYNTHESIZED

data_t<data_t<fixed_32>>;

int fixed_estimador(hls::stream<data_t<fixed_32>> &in, hls::stream<param_t<fixed_32>> &out){

	t_estimador <fixed_32> (hls::stream<data_t> &in, hls::stream<param_t> &out);
}




/*
int estimador(hls::stream<data_t> &in, hls::stream<param_t> &out){
	const fixed_32 GAMMA11 = 0.1;
	const fixed_32 GAMMA22 = 100;
	const fixed_32 INIT_ALPHA = 0.55;
	const fixed_32 INIT_BETA = -13.0;
	const fixed_32 T_SAMPLING = 1e-6;

	data_t sample_in=in.read(); // read fifo sample
	//std::cout << "tamaño dentro: " << in.size() << std::endl;
	static param_t theta = {0,0}; // init theta register
	static param_t theta_v_l = {INIT_ALPHA,INIT_BETA}; // init past theta register
	fixed_32 aux = 0.0;
	//std::cout << "ALPHA: " << theta_v_l._1 << "\t BETA: " << theta_v_l._2 << std::endl;

	aux = -sample_in.adc_v * theta_v_l._1;
	//std::coestimador<fixed_32>(in,out);ut << "1: " << theta_v_l._1 << std::endl;
	aux += -theta_v_l._2;
	//std::cout << "2: " << aux << std::endl;
	aux += sample_in.adc_i;
	//std::cout << "3: " << sample_in.adc_i << std::endl;
	//aux *= ;//-----------------------------------ERROR
	//std::cout << "4: " << F_SAMPLING << std::endl;
	theta._1 = (GAMMA11*aux*sample_in.adc_v)*T_SAMPLING + theta_v_l._1;
	theta._2 = (GAMMA22*aux)*T_SAMPLING+theta_v_l._2;
	theta_v_l._1=theta._1;
	theta_v_l._2=theta._2;
	out.write(theta);
	return 0;
}
*/


