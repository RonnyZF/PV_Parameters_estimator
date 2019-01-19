#include <hls_stream.h>
#include <hls_math.h>
#include "ap_fixed.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

 typedef ap_fixed<32,14,AP_RND,AP_SAT> log_precision;

template<typename T>
 struct data_vector{
 	T _v;
 	T _i;
 };

 template<typename T>
 struct log_data{
	T adc_v;
	T log;
};

 
 int fixed_log(hls::stream<data_vector<log_precision > > &in, hls::stream<log_data<log_precision > > &out);
