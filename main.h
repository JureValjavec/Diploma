#ifndef _MAIN_H_
#define _MAIN_H_

#include "types.h"

typedef struct captured_data
{
	char gps_read_buff[300];
	char gps_read;
	UINT32 gps_read_pos;
	UINT8 write_data;
	UINT32 int_cnt;
}T_CAPTURED_DATA;

//static void Delay (UINT32 dlyTicks);
void Delay (UINT32 dlyTicks);


#endif /*_MAIN_H_*/
