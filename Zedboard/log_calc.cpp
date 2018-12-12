#include "log_calc.hpp"
 
int fixed_log(hls::stream<ADC_data> &in, hls::stream<log_data> &out){
	
	ADC_data sample_in;
	log_data sample_out;
	in.read(sample_in);
	fixed_32 x = (sample_in.adc_i-1)/(sample_in.adc_i+1);//56 ciclos

	fixed_32 K = x*x;

	fixed_32 A = 0.971831; //69/71
	fixed_32 aux=K*A + 1;

	A = 0.971014; //67/69
	aux=aux*A*K + 1;
	A = 0.970149; //65/67
	aux=aux*A*K + 1;
	A = 0.969231; //63/65
	aux=aux*A*K + 1;
	A = 0.968254; //61/63
	aux=aux*A*K + 1;
	A = 0.967213; //59/61
	aux=aux*A*K + 1;
	A = 0.966102; //57/59
	aux=aux*A*K + 1;
	A = 0.964912; //55/57
	aux=aux*A*K + 1;
	A = 0.963636; //53/55
	aux=aux*A*K + 1;
	A = 0.962264; //51/53
	aux=aux*A*K + 1;
	A = 0.960784; //49/51
	aux=aux*A*K + 1;
	A = 0.959184; //47/49
	aux=aux*A*K + 1;
	A = 0.957447; //45/47
	aux=aux*A*K + 1;
	A = 0.955556; //43/45
	aux=aux*A*K + 1;
	A = 0.953488; //41/43
	aux=aux*A*K + 1;
	A = 0.951219; //39/41
	aux=aux*A*K + 1;
	A = 0.948718; //37/39
	aux=aux*A*K + 1;
	A = 0.945946; //35/37
	aux=aux*A*K + 1;
	A = 0.942857; //33/35
	aux=aux*A*K + 1;
	A = 0.939394; //31/33
	aux=aux*A*K + 1;
	A = 0.935484; //29/31
	aux=aux*A*K + 1;
	A = 0.931035; //27/29
	aux=aux*A*K + 1;
	A = 0.925926; //25/27
	aux=aux*A*K + 1;
	A = 0.920000; //23/25
	aux=aux*A*K + 1;
	A = 0.913043; //21/23
	aux=aux*A*K + 1;
	A = 0.904762; //19/21
	aux=aux*A*K + 1;
	A = 0.894737; //17/19
	aux=aux*A*K + 1;
	A = 0.882353; //15/17
	aux=aux*A*K + 1;
	A = 0.866667; //13/15
	aux=aux*A*K + 1;
	A = 0.846154; //11/13
	aux=aux*A*K + 1;
	A = 0.818182; //9/11
	aux=aux*A*K + 1;
	A = 0.777778; //7/9
	aux=aux*A*K + 1;
	A = 0.714286; //5/7
	aux=aux*A*K + 1;
	A = 0.600000; //3/5
	aux=aux*A*K + 1;
	A = 0.333333; //1/3
	aux=aux*A*K + 1;

	aux = aux*x*2;

	sample_out.adc_v = sample_in.adc_v;
	sample_out.log = aux;
	
	out.write(sample_out);
	return 0;
}

