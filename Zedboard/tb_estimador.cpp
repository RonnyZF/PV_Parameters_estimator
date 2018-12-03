#include <iostream>
#include <hls_stream.h>
#include "estimador.hpp"

int fill_stream(hls::stream<data_t> &in);

int main(){
	hls::stream<data_t> in;
	hls::stream<param_t> out;
	fill_stream(in);
	std::cout << "tamaño: " << in.size() << std::endl;

	for (int i=0;i<25;i++){
		estimador(in,out);
		param_t resultado = out.read();
		std::cout << "theta_1: " << resultado._1 << "\t theta_2: " << resultado._2 << std::endl;
	}
	return 0;
}

int fill_stream(hls::stream<data_t> &in){
	const float ALPHA = 0.625;
	const float F_SAMPLING = 1e6;
	const float V_CTE = 16.69;
	const float MM_PI = 3.14159265358979323846;
	const float PVG_F = 1000;
	const float K = 0.3;
	const float I_G = 5.1387085e-6; //(b=-12.1787)
	float b=log(I_G);

	data_t samples;
	samples.adc_i=0;
	samples.adc_v=0;
	float volt;
	float current;
	for (int i=0;i<25;i++){
		volt = V_CTE+K*V_CTE*sin(2*MM_PI*PVG_F*i/F_SAMPLING);
		current = ALPHA*volt +b;
		samples.adc_i=current;
		samples.adc_v=volt;
		std::cout << "volt: " << samples.adc_v << "\t current: " << samples.adc_i << std::endl;
		in.write(samples);
	}
	return 0;
}

