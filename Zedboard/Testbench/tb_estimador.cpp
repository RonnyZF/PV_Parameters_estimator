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

	float error_theta_1=0;
	float error_theta_2=0;
	float theta_1_float=0;
	float theta_2_float=0;

	for (int i=0;i<50000;i++){
		float_samples_generator(in_float,i);
		fixed_samples_generator(in_fixed,i);
		float_estimador(in_float,out_float);
		fixed_estimador(in_fixed,out_fixed);

		param_t<float> result_float = out_float.read();
		param_t<fixed_32> result_fixed = out_fixed.read();

		//calculos de error
		theta_1_float = result_fixed._1;
		theta_2_float = result_fixed._2;

		error_theta_1 = ((theta_1_float-result_float._1)/result_float._1);
		error_theta_2 = ((theta_2_float-result_float._2)/result_float._2);
		//...
		std::cout << "theta 1 obtained: " << result_fixed._1 << "\t expected: " << result_float._1 << "\t % error: " << error_theta_1 << "\n";
		std::cout << "theta 2 obtained: " << result_fixed._2 << "\t expected: " << result_float._2 << "\t % error: " << error_theta_2 << "\n\n";
	}
	return 0;
}
// --------------------------------------------------------
int float_estimador(hls::stream<adc_data<float > > &in, hls::stream<param_t<float > > &out){

	template_estimador<float>(in,out);
	return 0;
}
// --------------------------------------------------------
int float_samples_generator(hls::stream<adc_data<float > > &in, int n){

	template_samples_generator<float>(in,n);
	return 0;
}

// --------------------------------------------------------
int fixed_samples_generator(hls::stream<adc_data<fixed_32 > > &in, int n){

	template_samples_generator<fixed_32>(in, n);
	return 0;
}




