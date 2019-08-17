#include <hls_stream.h>
#include <ap_fixed.h>


typedef struct xadc_stream_interface{
	ap_fixed<16,0,AP_RND,AP_SAT> tdata;
	ap_uint<5> tid;
} xadc_stream_interface;

#define XADC_CHANNEL_1_ID (0x10)

#define XADC_CHANNEL_2_ID (0x18)
