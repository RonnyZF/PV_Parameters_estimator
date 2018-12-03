#include <hls_stream.h>
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
struct param_t{
	fixed_32 _1;
	fixed_32 _2;
};

typedef struct ADC_data data_t;
typedef struct param_t param_t;

int estimador(hls::stream<data_t> &in, hls::stream<param_t> &out);

