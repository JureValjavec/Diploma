#include "samd20.h"
#include "clock_driver.h"


/***************************************************************
Init and enable clock to all peripherals.

GEN0 = main clock = 48MHz
GEN1 = 32kHz
GEN3 = 1MHZ = source for EIC, UART, TC
****************************************************************/

void main_clock_init (void)
{
	#if GCLK_0

	/* enable the xosc32k and set the start up time */
	SYSCTRL->XOSC32K.reg = SYSCTRL_XOSC32K_STARTUP(0x6) | SYSCTRL_XOSC32K_EN32K |
												 SYSCTRL_XOSC32K_XTALEN | SYSCTRL_XOSC32K_ENABLE;
	
	while (!SYSCTRL->PCLKSR.bit.XOSC32KRDY){}
	
	/* enable the generic clock GEN1 and configure the XOSC32K as clock source for it */
	GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK1 | GCLK_GENCTRL_SRC_XOSC32K | 
											GCLK_GENCTRL_GENEN | GCLK_GENCTRL_IDC | GCLK_GENCTRL_OE;
	
	while (GCLK->STATUS.bit.SYNCBUSY){}
		
	/* Enable the DFLL and set the operation mode as closed loop */
  SYSCTRL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_ENABLE | SYSCTRL_DFLLCTRL_MODE;
  
  while(!SYSCTRL->PCLKSR.bit.DFLLRDY){}
		
  /* Load the Multiply factor, Coarse Step and fine Step for DFLL */
  SYSCTRL->DFLLMUL.reg = SYSCTRL_DFLLMUL_CSTEP(0x1F/4) | SYSCTRL_DFLLMUL_FSTEP(0xFF/4) |  
												  SYSCTRL_DFLLMUL_MUL(1465);
		
  /* Enable the Generic Clock GEN 1 as DFLL48 as Reference */ 
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK1 | GCLK_CLKCTRL_ID(0);
		
  /* wait for fine lock */
  while(!SYSCTRL->PCLKSR.bit.DFLLLCKF){}
		
  /* Set the NVM Read Wait States to 1, Since the operating frequency 48 MHz */
  NVMCTRL->CTRLB.bit.RWS = 1;
		
  /* Enable the Generic Clock 0 and Configure the DFLL as Clock Source for it*/
  GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK0 | GCLK_GENCTRL_SRC_DFLL48M |  GCLK_GENCTRL_GENEN | 
											GCLK_GENCTRL_IDC | GCLK_GENCTRL_OE;
  
  while(GCLK->STATUS.bit.SYNCBUSY){}

	#endif /* GCLK_0 */
		
	#if GCLK_3
		
	SYSCTRL->OSC8M.reg = SYSCTRL_OSC8M_FRANGE(0x2U) | SYSCTRL_OSC8M_PRESC(0x3U) | 
											 SYSCTRL_OSC8M_CALIB_Msk | SYSCTRL_OSC8M_ONDEMAND | SYSCTRL_OSC8M_ENABLE;
		
	/* enable the generic clock GEN3 and configure OSC8M as clock source for it */
	GCLK->GENCTRL.reg = GCLK_GENCTRL_ID_GCLK3 | GCLK_GENCTRL_SRC_OSC8M | 
											GCLK_GENCTRL_GENEN | GCLK_GENCTRL_IDC | GCLK_GENCTRL_OE;
	
	while (GCLK->STATUS.bit.SYNCBUSY){}
		
	#endif /* GLCK_3 */
		
	#if EIC_CLOCK
		
	/* enable the generic clock 3 as source for EIC module */
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_ID_EIC;		
		
	#endif /* EIC_CLOCK */
		
	#if TC_CLOCK
		
	/* enable power clock to TC0 and TC1 module and generic clock 3 as source */
	PM->APBCMASK.reg = PM_APBCMASK_TC0 | PM_APBCMASK_TC1;
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_ID_TC0_TC1;
		
	#endif /* TC_CLOCK */
		
	#if RF_CLOCK
		
	/* enable power clocl for sercom4 */
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM4;
	
	/* enable generic clock for sercom */
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_ID_SERCOM4_CORE;
	
	#endif /* RF_CLOCK */
	
	#if GPS_CLOCK
	
	/* enable power clocl for sercom5 */
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM5;
	
	/* enable generic clock for sercom */
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_ID_SERCOM5_CORE;
	
	#endif /* GPS_CLOCK */
	
	#if SPI_M_CLOCK
	
	/* enable power clock for sercom1 */
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM1;
	/* enable power clock for sercom0 */
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;
	
	/* enable generic clock for sercom1 */
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_SERCOM1_CORE;
	/* enable generic clock for sercom0 */
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_SERCOM0_CORE;
	
	#endif /* SPI_CLOCK */
		
	#if GCLK_0_OE /* PA14 */
		
	PORT->Group[0].PINCFG[14].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].PMUX[7].reg |= PORT_PMUX_PMUXE_H;
	
	#endif /* GCLK_0_OE */
	
	#if GCLK_1_OE /* PA15 */
		
	PORT->Group[0].PINCFG[15].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[0].PMUX[7].reg |= PORT_PMUX_PMUXO_H;
	
	#endif /* GCLK_1_OE */
	
	#if GCLK_3_OE /* PB17 */
		
	PORT->Group[1].PINCFG[17].reg = PORT_PINCFG_PMUXEN;
	PORT->Group[1].PMUX[8].reg = PORT_PMUX_PMUXO_H;
	
	#endif /* GCLK_1_OE */
}

