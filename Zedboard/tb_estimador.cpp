#include <iostream>
#include <hls_stream.h>
#include <hls_math.h>
#include "estimador.hpp"


// function prototypes
int float_samples_generator(hls::stream<adc_data<float > > &in, int n);
int fixed_samples_generator(hls::stream<adc_data<fixed_32 > > &in, int n);
int float_estimador(hls::stream<adc_data<float > > &in, hls::stream<param_t<float > > &out);

int main(){
	hls::stream<adc_data<float > > in_float;
	hls::stream<adc_data<fixed_32> > in_fixed;
	hls::stream<param_t<float > > out_float;
	hls::stream<param_t<fixed_32 > > out_fixed;
	//std::cout << "tamaño: " << in.size() << std::endl;

	for (int i=0;i<50000;i++){
		float_samples_generator(in_float,i);
		fixed_samples_generator(in_fixed,i);
		float_estimador(in_float,out_float);
		fixed_estimador(in_fixed,out_fixed);
		param_t<float> resultado_float = out_float.read();
		param_t<fixed_32> resultado_fixed = out_fixed.read();
		//calculos de error
		//...
		std::cout << "theta_1: " << resultado_float._1 << "\t theta_2: " << resultado_float._2 << "\n";
		std::cout << "theta_1: " << resultado_fixed._1 << "\t theta_2: " << resultado_fixed._2 << "\n";
	}
	return 0;
}
// --------------------------------------------------------
int float_estimador(hls::stream<adc_data<float > > &in, hls::stream<param_t<float > > &out){

	t_estimador<float>(in,out);
	return 0;
}
// --------------------------------------------------------
int float_samples_generator(hls::stream<adc_data<float > > &in, int n){

	t_gen_samples<float>(in,n);
	return 0;
}

// --------------------------------------------------------
int fixed_samples_generator(hls::stream<adc_data<fixed_32 > > &in, int n){

	t_gen_samples<fixed_32>(in, n);
	return 0;
}

/*
int fill_stream(hls::stream<data_t> &in, int n){
	const float ALPHA = 0.625;
	const float F_SAMPLING = 1e6;
	const float V_CTE = 16.69;
	const float MM_PI = 3.14159265358979323846;
	const float PVG_F = 1000;
	const float K = 0.3;
	const float I_G = 5.1387085e-6; //(b=-12.1787)
	float b=(float) log(I_G);

	data_t samples;
	samples.adc_i=0;
	samples.adc_v=0;
	float volt;
	float current;
	static int i = 0;
	volt = V_CTE+K*V_CTE*sin(2*MM_PI*PVG_F*i/F_SAMPLING);
	current = ALPHA*volt +b;
	samples.adc_i=current;
	samples.adc_v=volt;
	i=n;
	//std::cout << "volt: " << samples.adc_v << "\t current: " << samples.adc_i << std::endl;
	in.write(samples);
	return 0;
}
*/
/*
int fill_stream(hls::stream<data_t> &in){
	const float ALPHA = 0.625;
	const float F_SAMPLING = 1e6;
	const float V_CTE = 16.69;
	const float MM_PI = 3.14159265358979323846;
	const float PVG_F = 1000;
	const float K = 0.3;
	const float I_G = 5.1387085e-6; //(b=-12.1787)
	float b=(float) log(I_G);

	data_t samples;
	samples.adc_i=0;
	samples.adc_v=0;
	float volt;
	float current;
	for (int i=0;i<50000;i++){
		volt = V_CTE+K*V_CTE*sin(2*MM_PI*PVG_F*i/F_SAMPLING);
		current = ALPHA*volt +b;
		samples.adc_i=current;
		samples.adc_v=volt;
		//std::cout << "volt: " << samples.adc_v << "\t current: " << samples.adc_i << std::endl;
		in.write(samples);
	}
	return 0;
}
*/

