#ifndef _UART_DRIVER_H_
#define _UART_DRIVER_H_

#include "types.h"


#define TRP868_SERCOM4	1
#define GPR_SERCOM5			1

#define	UART_READ_BUFF_SIZE		100
#define UART_WRITE_BUFF_SIZE 	100

/******* data struct *******/

/*
typedef struct uart_data_struct
{
	//char uart5_read_buff[UART_READ_BUFF_SIZE];
	char uart4_read_buff[UART_READ_BUFF_SIZE];
	char uart_write_buff[UART_WRITE_BUFF_SIZE];
	//UINT32 read5_pos;
	UINT32 read4_pos;
	UINT8 new_data;
	
}T_UART_DATA;
*/

/***************************/

void uart_init (void);
void gps_write (char * buff, UINT32 lenght);
void set_baud (UINT8 uart_port, UINT32 baud_rate);
void uart_write (UINT8 uart_port, char * buff,  UINT32 lenght);

#endif /* _UART_DRIVER_H */
