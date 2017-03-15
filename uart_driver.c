#include "samd20.h"
#include "uart_driver.h"
#include "types.h"

void uart_init (void)
{
		/* UART SERCOM4 PB08 and PB09 MUXD */
	
		/* mux enable on PB08 and PB09 */
	PORT->Group[1].PINCFG[8].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[1].PINCFG[9].reg = PORT_PINCFG_PMUXEN;
	
		/* select peripheral function D for PB08 and PB09 */
	PORT->Group[1].PMUX[4].reg = PORT_PMUX_PMUXE_D | PORT_PMUX_PMUXO_D;
	
	/* UART SERCOM5 PA24 and PA25 MUXD */
	
		/* mux enable ob PA24 and PA25 */
	PORT->Group[0].PINCFG[24].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].PINCFG[25].reg = PORT_PINCFG_PMUXEN;
	
		/* select peripheral function D for PA24 and PA25 */
	PORT->Group[0].PMUX[12].reg = PORT_PMUX_PMUXE_D | PORT_PMUX_PMUXO_D;
	
	#if TRP868_SERCOM4 /* for trp868 */
	
		/*  sercom init */
	SERCOM4->USART.CTRLB.reg = SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_RXEN;
	
		/* current BAUDRATE 9600 */
	SERCOM4->USART.BAUD.reg =  SERCOM_USART_BAUD_BAUD(60003);
	SERCOM4->USART.INTENSET.reg = SERCOM_USART_INTENSET_RXS | SERCOM_USART_INTENSET_RXC;
	SERCOM4->USART.CTRLA.reg = SERCOM_USART_CTRLA_MODE_USART_INT_CLK | SERCOM_USART_CTRLA_ENABLE | 
														 SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_RXPO(0x1);
	
	#endif /* TRP868_SERCOM4 */

	#if GPR_SERCOM5 	
	
		/*  sercom init */
	SERCOM5->USART.CTRLB.reg = SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_RXEN;
	
			/* current BAUDRATE 9600 */
	SERCOM5->USART.BAUD.reg =  SERCOM_USART_BAUD_BAUD(60003); //60503
	SERCOM5->USART.INTENSET.reg = SERCOM_USART_INTENSET_RXS | SERCOM_USART_INTENSET_RXC;
	SERCOM5->USART.CTRLA.reg = SERCOM_USART_CTRLA_MODE_USART_INT_CLK | SERCOM_USART_CTRLA_ENABLE | 
														 SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_RXPO(0x3) | SERCOM_USART_CTRLA_TXPO_PAD2;
														 
	#endif /* GPR_SERCOM5 */
 
}

void set_baud (UINT8 uart_port, UINT32 baud_rate)
{
	UINT32 baud_value;
	UINT32 f_baud;
	double multiplier;
	
	f_baud = (baud_rate / 2);
	
	multiplier = ( 1000 - ((16 * f_baud) / 1000 ));
	
	baud_value = ( (65536 * multiplier) / 1000 ); 
	
	/* disable UART_PORT first, so you can write to BAUD register */
	
	switch (uart_port)
	{
		case 4:
			SERCOM4->USART.CTRLA.bit.ENABLE = 0;
			SERCOM4->USART.BAUD.reg =  SERCOM_USART_BAUD_BAUD(baud_value);
			SERCOM4->USART.CTRLA.bit.ENABLE = 1;
		break;
		
		case 5:
			SERCOM5->USART.CTRLA.bit.ENABLE = 0;
			SERCOM5->USART.BAUD.reg =  SERCOM_USART_BAUD_BAUD(baud_value);
			SERCOM5->USART.CTRLA.bit.ENABLE = 1;
		break;
		
		default:
			break;
	}
	
}

void gps_write (char * buff, UINT32 lenght)
{
	int pos = 0;
	while (lenght)
	{
		SERCOM5->USART.DATA.reg = buff[pos];
		while (!(SERCOM5->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_TXC)) 
		{
			/* Wait until data is sent */
		}
		pos++;
		lenght--;
	}
}

void uart_write (UINT8 uart_port, char * buff,  UINT32 lenght)
{
	int pos = 0;
	
	switch (uart_port)
	{
		case 4:
			
			while (lenght)
			{
				SERCOM4->USART.DATA.reg = buff[pos];
				while (!(SERCOM4->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_TXC)) 
				{
					/* Wait until data is sent */
				}
				pos++;
				lenght--;
			}
			break;
			
		case 5:
			
			while (lenght)
			{
				SERCOM5->USART.DATA.reg = buff[pos];
				while (!(SERCOM5->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_TXC)) 
				{
					/* Wait until data is sent */
				}
				pos++;
				lenght--;
			}
			break;
			
		default:
			break;
	}
}

/* read uart over the interrupt */

/*
void SERCOM4_Handler (void)
{
	if (SERCOM4->USART.INTFLAG.bit.RXC)
	{
		uart_data.uart4_read_buff[uart_data.read4_pos] = SERCOM5->USART.DATA.reg;
		uart_data.read4_pos++;
	}
}*/


