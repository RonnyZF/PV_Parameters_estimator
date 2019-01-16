#include <hls_stream.h>
#include <hls_math.h>
#include "ap_fixed.h"

 typedef ap_fixed<32,14,AP_RND,AP_SAT> fixed_32;

 typedef ap_fixed<32,14,AP_RND,AP_SAT> fixed_ln_taylor_series;

 
 struct ADC_data{
	fixed_32 adc_v;
	fixed_32 adc_i;
};

 struct log_data{
	fixed_32 adc_v;
	fixed_32 log;
};
 typedef struct ADC_data data_t;
 
 int Ln_taylor_series(hls::stream<ADC_data> &in, hls::stream<log_data> &out);
