#include "Ln_taylor_series.hpp"
#include <stdint.h>


template<typename ArbPrec>
ArbPrec mapVariable(ArbPrec noMapped){
	return (noMapped-1)/(noMapped+1);
}

template<typename ArbPrec>
ArbPrec approxLn(ArbPrec mapped){
	ArbPrec A[] =
	{0.333333,0.600000,0.714286,
	 0.777778,0.818182,0.846154,
	 0.866667,0.882353,0.894737,
	 0.904762,0.913043,0.920000,
	 0.925926,0.931035,0.935484};
	ArbPrec K = mapped*mapped;
	ArbPrec aux=K*A[0] + 1;
	for(int8_t stageIdx=14;stageIdx>-1;stageIdx--){
		aux=aux*A[stageIdx]*K + 1;
	}
	return aux*mapped*2;
}

int Ln_taylor_series(hls::stream<ADC_data> &in, hls::stream<log_data> &out){
#pragma HLS DATAFLOW
	ADC_data sample_in;
	log_data sample_out;
	sample_in=in.read();
	fixed_ln_taylor_series mapped = mapVariable<fixed_ln_taylor_series>(sample_in.adc_i);//56 ciclos
	sample_out.log = approxLn<fixed_ln_taylor_series>(mapped);
	sample_out.adc_v = sample_in.adc_v;
	out.write(sample_out);
	return 0;
}

