#include <hls_stream.h>
#include <hls_math.h>
#include "ap_fixed.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

 typedef ap_fixed<32,14,AP_RND,AP_SAT> fixed_32;
 
 struct ADC_data{
	fixed_32 adc_v;
	fixed_32 adc_i;
};

 struct log_data{
	fixed_32 adc_v;
	fixed_32 log;
};
 typedef struct ADC_data data_t;
 
 int fixed_log(hls::stream<ADC_data> &in, hls::stream<log_data> &out);
