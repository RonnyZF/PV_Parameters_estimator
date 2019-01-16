#include <hls_stream.h>
#include <hls_math.h>
#include "ap_fixed.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

 typedef ap_fixed<32,14,AP_RND,AP_SAT> fixed_32;

 template<typename T>
 struct ADC_data{
	T adc_v;
	T adc_i;
};

 template<typename T>
 struct log_data{
	T adc_v;
	T log;
};

 //typedef struct ADC_data data_t;
 
 int fixed_log(hls::stream<ADC_data<fixed_32 >> &in, hls::stream<log_data<fixed_32 >> &out);

 template<typename T>
 T template_approxLn(T log2_result){
 	const T log2_e=1.442695041;
 	return log2_result/log2_e;
 }

 template<typename P, typename T>
 P template_escalamiento(T x){
 	T y = 0;
 	bool not_finished_scaling = true;
 	while (not_finished_scaling){
 #pragma HLS loop_tripcount min=1 max=3 avg=2
 		if (x<1){
 			x=2*x;
 			y=y-1;
 		}
 		else if(x>=2){
 			x=x/2;
 			y=y+1;
 		}
 		else{
 			not_finished_scaling = false;
 		}
 	}
 	P result = {x, y};
 	return result;

 }

 template<typename T>
 T template_approxLog2(T x, T y){
 	T b=0.5;
 		for (int i = 0; i < 15; ++i){
 			x=x*x;
 			if (x>=2){
 				x=x/2;
 				y=y+b;
 			}
 			b=b/2;
 		}
 	return y;
 }

 template<typename P, typename T>
 int template_fixed_log(hls::stream<ADC_data<T>> &in, hls::stream<log_data<T>> &out){
 #pragma HLS DATAFLOW
 	ADC_data<T> sample_in;
 	log_data<T> sample_out;
 	sample_in=in.read();
 	P aux = template_escalamiento<P,T>(sample_in.adc_i);
 	T aux2 = template_approxLog2<T>(aux.x,aux.y);
 	sample_out.log = template_approxLn<T>(aux2);
 	sample_out.adc_v = sample_in.adc_v;
 	out.write(sample_out);
 	return 0;
 }
