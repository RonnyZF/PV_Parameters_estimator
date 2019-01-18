
 template<typename T>
 T approxLn(T log2_result){
 	const T log2_e=1.442695041;
 	return log2_result/log2_e;
 }

 template<typename P, typename T>
 P escalamiento(T x){
 	T y = 0;
 	bool not_finished_scaling = true;
 	while (not_finished_scaling){
 #pragma HLS loop_tripcount min=1 max=3 avg=2
 		if (x<1){
 			x=2*x;
 			y=y-1;
 		}
 		else if(x>=2){
 			x=x/2;
 			y=y+1;
 		}
 		else{
 			not_finished_scaling = false;
 		}
 	}
 	P result = {x, y};
 	return result;

 }

 template<typename T>
 T approxLog2(T x, T y){
 	T b=0.5;
 		for (int i = 0; i < 15; ++i){
 			x=x*x;
 			if (x>=2){
 				x=x/2;
 				y=y+b;
 			}
 			b=b/2;
 		}
 	return y;
 }

 template<typename P, typename T>
 int fixed_log_calculation(hls::stream<data_vector<T>> &in, hls::stream<log_data<T>> &out){
 #pragma HLS DATAFLOW
 	data_vector<T> sample_in;
 	log_data<T> sample_out;
 	sample_in=in.read();
 	P aux = escalamiento<P,T>(sample_in._i);
 	T aux2 = approxLog2<T>(aux._v,aux._i);
 	sample_out.log = approxLn<T>(aux2);
 	sample_out.adc_v = sample_in._v;
 	out.write(sample_out);
 	return 0;
 }
