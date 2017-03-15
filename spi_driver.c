#include "samd20.h"
#include "spi_driver.h"
#include "integer.h"

void spi_init (void)
{
	#if SD_CARD_SPI_SERCOM1
	
	PORT->Group[0].PINCFG[16].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].PINCFG[18].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].PINCFG[19].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].DIRSET.reg = PORT_PA17;
	
	PORT->Group[0].PMUX[8].reg = PORT_PMUX_PMUXE_C;
	PORT->Group[0].PMUX[9].reg = PORT_PMUX_PMUXE_C | PORT_PMUX_PMUXO_C;
	
		/* spi init */
	//SERCOM1->SPI.INTENSET.reg = SERCOM_USART_INTENSET_RXS | SERCOM_USART_INTENSET_RXC;
	SERCOM1->SPI.BAUD.reg = SERCOM_SPI_BAUD_BAUD(100);
	SERCOM1->SPI.CTRLB.reg = SERCOM_SPI_CTRLB_RXEN;
	SERCOM1->SPI.CTRLA.reg = SERCOM_SPI_CTRLA_MODE(0x3) | SERCOM_SPI_CTRLA_DOPO(0x3) |
													 SERCOM_SPI_CTRLA_DIPO(0x2) | SERCOM_SPI_CTRLA_ENABLE;
	

	
	#endif
	
	#if ACC_SPI_SERCOM0
	
	PORT->Group[0].PINCFG[4].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].PINCFG[6].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].PINCFG[7].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].DIRSET.reg = PORT_PA05;
	PORT->Group[0].OUTSET.reg = PORT_PA05;
	
	PORT->Group[0].PMUX[2].reg = PORT_PMUX_PMUXE_D;
	PORT->Group[0].PMUX[3].reg = PORT_PMUX_PMUXE_D | PORT_PMUX_PMUXO_D;
	
		/* spi init */
	//SERCOM1->SPI.INTENSET.reg = SERCOM_USART_INTENSET_RXS | SERCOM_USART_INTENSET_RXC;
	SERCOM0->SPI.BAUD.reg = SERCOM_SPI_BAUD_BAUD(100);
	SERCOM0->SPI.CTRLB.reg = SERCOM_SPI_CTRLB_RXEN;
	SERCOM0->SPI.CTRLA.reg = SERCOM_SPI_CTRLA_MODE(0x3) | SERCOM_SPI_CTRLA_DOPO(0x1) |
													 SERCOM_SPI_CTRLA_DIPO(0x0) | SERCOM_SPI_CTRLA_CPOL | 
													 SERCOM_SPI_CTRLA_CPHA | SERCOM_SPI_CTRLA_ENABLE;
													 
													 
	#endif
}
BOOL set_out (PortGroup * GROUPx)
{

}
/******************************* spi write read function ******************************/
BOOL spi_rw (Sercom * SERCOMx, BYTE *w_buff, BYTE *r_buff, UINT32 lenght)
{
	int i=0;
	BYTE dummy;
	
	if (SERCOMx == NULL){
		return FALSE;
	}

	for(i=0;i<lenght;i++){
	
		if(w_buff != NULL){
			SERCOMx->SPI.DATA.reg = w_buff[i];
		}
		else{
			SERCOMx->SPI.DATA.reg = 0xFF;
		}
		
		/* Wait until data is sent */
		while (!(SERCOMx->SPI.INTFLAG.reg & SERCOM_SPI_INTFLAG_TXC));
		while (!(SERCOMx->SPI.INTFLAG.reg & SERCOM_SPI_INTFLAG_RXC));
		
		if(r_buff != NULL){
			r_buff[i] = SERCOMx->SPI.DATA.reg;
		}
		else
		{
			dummy = SERCOMx->SPI.DATA.reg;
		}

	}

	return TRUE;
}

BOOL spi_acc_rw (Sercom * SERCOMx, BYTE *w_buff, BYTE *r_buff, UINT32 lenght)
{
	int i=0;
	
	PORT->Group[0].OUTCLR.reg = PORT_PA05;
	
	if (SERCOMx == NULL){
		return FALSE;
	}
		
	for(i=0;i<lenght;i++){
		SERCOMx->SPI.DATA.reg = w_buff[i];
		/* Wait until data is sent */
		while (!(SERCOMx->SPI.INTFLAG.reg & SERCOM_SPI_INTFLAG_TXC));
		while (!(SERCOMx->SPI.INTFLAG.reg & SERCOM_SPI_INTFLAG_RXC));
		
		r_buff[i] = SERCOMx->SPI.DATA.reg;

	}
	
	PORT->Group[0].OUTSET.reg = PORT_PA05;
	
	return TRUE;
}


