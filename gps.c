#include "samd20.h"
#include "gps.h"
#include "types.h"
#include "uart_driver.h"

#include <string.h>

void gps_set_output_data (void)
{
	char gps_set_output[43] = {"$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0*28\r\n"};
	//char gps_set_baud[19] = {"$PMTK251,57600*2C\r\n"};
	
	uart_write(5, gps_set_output, strlen(gps_set_output));
	//gps_write(gps_set_baud, strlen(gps_set_baud));
	
	//set_baud(5, 57600);
}
