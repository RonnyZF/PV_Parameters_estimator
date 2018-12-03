#include <iostream>
#include <hls_stream.h>
#include "estimador.hpp"

int fill_stream(hls::stream<data_t> &in);

int main(){
	hls::stream<data_t> in;
	hls::stream<param_t> out;
	//while(out.size() > 0){
	for (int i=0;i<25;i++){
		fill_stream(in);
		estimador(in,out);
		param_t resultado = out.read();
		std::cout << "theta_1: " << resultado._1 << "\t theta_2: " << resultado._2 << std::endl;
	}
	return 0;
}

int fill_stream(hls::stream<data_t> &in){
	const fixed_32 ALPHA = 0.625;
	const fixed_32 F_SAMPLING = 1e6;
	const fixed_32 V_CTE = 16.69;
	const fixed_32 MM_PI = 3.14159265358979323846;
	const fixed_32 PVG_F = 1000;
	const fixed_32 K = 0.3;


	data_t samples;
	samples.adc_i=0;
	samples.adc_v=0;
	fixed_32 a=2.9;
	fixed_32 b=4.5;
	//in.write(samples);
	for (int i=0;i<25;i++){
		samples.adc_v = V_CTE+K*V_CTE*sin(2*MM_PI*PVG_F*i/F_SAMPLING);
		samples.adc_i = ALPHA*samples.adc_v +b;
		in.write(samples);
	}
	return 0;
}
/*
int fill_stream(hls::stream<data_t> &in){
	data_t samples;
	samples.adc_i=0;
	samples.adc_v=0;
	fixed_32 a=2.9;
	fixed_32 b=4.5;
	//in.write(samples);
	for (int i=0;i<25;i++){
		samples.adc_v += a;
		samples.adc_i += b;
		in.write(samples);
	}
	return 0;
}*/
