#include "log_calc.hpp"

fixed_32 mapVariable(fixed_32 noMapped){
	return (noMapped-1)/(noMapped+1);
}

fixed_32 approxLog(fixed_32 mapped){
	fixed_32 A[] =
	{0.935484,0.931035,0.925926,0.920000,
	 0.913043,0.904762,0.894737,0.882353,
	 0.866667,0.846154,0.818182,0.777778,
	 0.714286,0.600000,0.333333};
	fixed_32 K = mapped*mapped;
	fixed_32 aux=K*A[0] + 1;
	for(int stageIdx=1;stageIdx<15;stageIdx++){
		aux=aux*A[stageIdx]*K + 1;
	}
	return aux*mapped*2;
}

int fixed_log(hls::stream<ADC_data> &in, hls::stream<log_data> &out){
#pragma HLS DATAFLOW
	ADC_data sample_in;
	log_data sample_out;
	sample_in=in.read();
	fixed_32 mapped = mapVariable(sample_in.adc_i);//56 ciclos
	sample_out.log = approxLog(mapped);
	sample_out.adc_v = sample_in.adc_v;
	out.write(sample_out);
	return 0;
}

