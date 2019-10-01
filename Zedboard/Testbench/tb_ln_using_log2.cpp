#include <iostream>
#include <fstream>
#include "../Library/Ln_using_log2.hpp"


int gen_samples(hls::stream<data_vector<log_precision >> &in);


int main(){
	hls::stream<data_vector<log_precision >> in;
	hls::stream<log_data<log_precision >> out;
	gen_samples(in);
	float a = 0.001;

	std::ofstream csv_log;
	csv_log.open("/home/local/ESTUDIANTES/rzarate/vivadoprjs/PV_Parameters_estimator/Software/python_code/HLS_LOG2.CSV");

	for (int i=1;i<10000;i++){
		fixed_log(in,out);
		float comp = log(a);
		log_data<log_precision > resultado = out.read();
		//calculos de error
		float log_float = resultado.log;
		float error = abs((comp-log_float)/comp)*100;

		csv_log <<resultado.adc_v<<","<<resultado.log<<","<<comp<<"\n";
		std::cout << "log("<<resultado.adc_v<<"): \t Resultado obtenido: "<< resultado.log << "\t esperado: " << comp << "\t %error: "<<error<<std::endl;
		a=a+0.001;
	}
	return 0;
}

 int gen_samples(hls::stream<data_vector<log_precision >> &in){
	 data_vector<log_precision> samples;
	samples._i=0;
	samples._v=0;
	log_precision a=0.001;
	log_precision b=0.001;
	for (int i=1;i<10000;i++){
		samples._v += a;
		samples._i += b;
		in.write(samples);
	}
	return 0;
 }
