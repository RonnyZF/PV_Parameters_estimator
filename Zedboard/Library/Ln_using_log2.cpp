#include "Ln_using_log2.hpp"
#include "Ln_using_log2_templates.cpp"


int fixed_log(hls::stream<data_vector<log_precision> > &in, hls::stream<log_data<log_precision> > &out){
	fixed_log_calculation<data_vector<log_precision >,log_precision>(in,out);
	return 0;
}