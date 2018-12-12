#include <iostream>
#include <hls_stream.h>
#include "log_calc.hpp"


int gen_samples(hls::stream<ADC_data> &in);

int main(){
	hls::stream<ADC_data> in;
	hls::stream<log_data> out;
	gen_samples(in);
	float a = 0.02;
	for (int i=1;i<500;i++){
		fixed_log(in,out);
		float comp = log(a);
		log_data resultado = out.read();
		//calculos de error
		float log_float = resultado.log;
		float error = ((log_float-comp)/comp);
		//std::cout << "log("<<resultado.adc_v<<"): \t Resultado obtenido: "<< resultado.log << "\t esperado: " << comp << "\t %error: "<<error<<std::endl;
		std::cout << a<<","<<resultado.log << "," << comp<<std::endl;
		a=a+0.02;
	}
	return 0;
}

 int gen_samples(hls::stream<ADC_data> &in){
	 ADC_data samples;
	samples.adc_i=0;
	samples.adc_v=0;
	fixed_32 a=0.02;
	fixed_32 b=0.02;
	for (int i=1;i<500;i++){
		samples.adc_v += a;
		samples.adc_i += b;
		in.write(samples);
	}
	return 0;
 }
