#include <hls_stream.h>
#include <hls_math.h>
#include "ap_fixed.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

 typedef ap_fixed<18,5,AP_RND,AP_SAT> log_precision;

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
 
 int Fixed_ln_taylor_series(hls::stream<data_vector<log_precision> > &in, hls::stream<log_data<log_precision> > &out);
