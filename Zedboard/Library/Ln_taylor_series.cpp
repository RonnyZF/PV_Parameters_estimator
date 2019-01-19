#include "Ln_taylor_series.hpp"
#include "Ln_taylor_series_templates.hpp"


int Ln_taylor_series(hls::stream<data_vector<log_precision> > &in, hls::stream<log_data<log_precision> > &out){
	Ln_taylor_series_calculation<log_precision>(in,out);
	return 0;
}

