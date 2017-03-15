#include "samd20.h"
#include "main.h"

#include "clock_driver.h"
#include "port_driver.h"
#include "uart_driver.h"
#include "spi_driver.h"
#include "gps.h"
#include "ff.h"

#include <stdio.h> 
#include <string.h>
#include <math.h>


/******************* FILE SYSTEM AND STRUCTS *********************************/
FATFS FatFs;
FIL fil;
FRESULT fr;
T_CAPTURED_DATA data;
/*****************************************************************************/

/***************************** DELAY FUNCTION ********************************/
volatile UINT32 msTicks;

void SysTick_Handler(void)
{
	msTicks++;
}

void Delay (UINT32 dlyTicks)
{
	uint32_t curTicks;
	
	curTicks = msTicks;
	while ((msTicks - curTicks) < dlyTicks);
}
/*****************************************************************************/

/*********************** INTERUPT HANDLERS **********************************/
void SERCOM5_Handler (void)
{
	data.write_data = 1;
	data.int_cnt++;
	if (SERCOM5->USART.INTFLAG.bit.RXC)
	{
		data.gps_read_buff[data.gps_read_pos] = SERCOM5->USART.DATA.reg;
		data.gps_read_pos++;
	}
	
}
/*****************************************************************************/

/********************** LOCAL FUNCTIONS **************************************/
/*****************************************************************************/

/******************* MAIN FUNCTION ENTRY *************************************/
int main(void)
{
	UINT bw;

	SystemCoreClockUpdate();
	main_clock_init();
	SysTick_Config(SystemCoreClock/1000);
	uart_init();
	spi_init();

	gps_set_output_data();
	
	Delay(1000);

	f_mount(&FatFs, "", 0);
	f_open(&fil, "Gps_data.txt", FA_WRITE | FA_CREATE_ALWAYS);
	
	Delay(100);
	
	memset(&data, 0, sizeof(data));
	
	NVIC_EnableIRQ(SERCOM5_IRQn);
		
	while(1)
	{
		if(data.gps_read_buff[data.gps_read_pos-6] == 0x4E
			|| data.gps_read_buff[data.gps_read_pos-6] == 0x41
			|| data.gps_read_buff[data.gps_read_pos-6] == 0x44
			|| data.gps_read_buff[data.gps_read_pos-6] == 0x45
			|| data.gps_read_buff[data.gps_read_pos-6] == 0x52
			|| data.gps_read_buff[data.gps_read_pos-6] == 0x53)
		{
			if (data.gps_read_buff[data.gps_read_pos-5] == 0x2A)
			{
				f_write(&fil, data.gps_read_buff, strlen(data.gps_read_buff), &bw);
				f_sync(&fil);
				memset(&data, 0, sizeof(data));	
			}
		}
	}
	
}

