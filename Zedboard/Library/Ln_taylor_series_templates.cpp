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

template<typename T>
int Ln_taylor_series_calculation(hls::stream<data_vector<T> > &in, hls::stream<log_data<T> > &out){
#pragma HLS DATAFLOW
	data_vector<T> sample_in;
	log_data<T> sample_out;
	sample_in=in.read();
	T mapped = mapVariable<T>(sample_in._i);
	sample_out.log = approxLn<T>(mapped);
	sample_out.adc_v = sample_in._v;
	out.write(sample_out);
	return 0;
}
