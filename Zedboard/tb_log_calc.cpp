#include <iostream>
#include <hls_stream.h>
#include "log_calc.hpp"


int gen_samples(hls::stream<ADC_data> &in);

int main(){
	hls::stream<ADC_data> in;
	hls::stream<log_data> out;
	gen_samples(in);
	for (int i=1;i<25;i++){
		fixed_log(in,out);
		float comp = log(i);
		log_data resultado = out.read();

		//calculos de error
		float log_float = resultado.log;
		float error = ((log_float-comp)/comp);

		std::cout << "log("<<i<<"): \t Resultado obtenido: "<< resultado.log << "\t esperado: " << comp << "\t %error: "<<error<<std::endl;
	}
	return 0;
}

 int gen_samples(hls::stream<ADC_data> &in){
	 ADC_data samples;
	samples.adc_i=0;
	samples.adc_v=0;
	fixed_32 a=1;
	fixed_32 b=1;
	for (int i=1;i<25;i++){
		samples.adc_v += a;
		samples.adc_i += b;
		in.write(samples);
	}
	return 0;
 }
