#include "estimador.hpp"

// THIS IS THE TOP LEVEL DESIGN THAT WILL BE SYNTHESIZED


int fixed_estimador(hls::stream<adc_data<fixed_32 > > &in, hls::stream<param_t<fixed_32 > > &out){
# pragma HLS DATAFLOW
	template_estimador<fixed_32 > (in,out);
	return 0;
}




