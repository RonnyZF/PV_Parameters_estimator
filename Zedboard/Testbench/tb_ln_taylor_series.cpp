#include <iostream>
#include "../Library/Ln_taylor_series.hpp"


int gen_samples(hls::stream<data_vector<log_precision> > &in);

int main(){
	hls::stream<data_vector<log_precision> > in;
	hls::stream<log_data<log_precision> > out;
	gen_samples(in);
	float a = 0.02;
	for (int i=1;i<500;i++){
		Fixed_ln_taylor_series(in,out);
		float comp = log(a);
		log_data<log_precision> resultado = out.read();
		//calculos de error
		float log_float = resultado.log;
		float error = ((log_float-comp)/comp);
		std::cout << "log("<<resultado.adc_v<<"): \t Resultado obtenido: "<< resultado.log << "\t esperado: " << comp << "\t %error: "<<error<<std::endl;
		//std::cout << a<<","<<resultado.log << "," << comp<<std::endl;
		a=a+0.02;
	}
	return 0;
}

 int gen_samples(hls::stream<data_vector<log_precision> > &in){
	data_vector<log_precision> samples;
	samples._i=0;
	samples._v=0;
	log_precision a=0.02;
	log_precision b=0.02;
	for (int i=1;i<500;i++){
		samples._v += a;
		samples._i += b;
		in.write(samples);
	}
	return 0;
 }
