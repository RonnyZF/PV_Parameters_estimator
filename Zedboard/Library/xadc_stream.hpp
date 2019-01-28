#include <hls_stream.h>
#include <ap_fixed.h>


typedef struct xadc_stream_interface{
	ap_fixed<16,1,AP_RND,AP_SAT> tdata;
	int8_t tid;
} xadc_stream_interface;

#define XADC_CHANNEL_1_ID (0x3)

#define XADC_CHANNEL_2_ID (0x10)
