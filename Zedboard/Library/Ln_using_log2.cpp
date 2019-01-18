
#include "log_calc.hpp"

struct Scaling{
	fixed_32 x;
	fixed_32 y;
 };

int fixed_log(hls::stream<ADC_data<fixed_32 >> &in, hls::stream<log_data<fixed_32 >> &out){
	template_fixed_log<Scaling,fixed_32>(in,out);
	return 0;
}