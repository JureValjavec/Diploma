#ifndef _CLOCK_H_
#define _CLOCK_H_

#define GCLK_0					1
#define GCLK_3					1
#define EIC_CLOCK				1
#define RF_CLOCK				1
#define GPS_CLOCK				1
#define SPI_M_CLOCK			1
#define TC_CLOCK				0

#define GCLK_0_OE				0
#define GCLK_1_OE				0
#define GCLK_2_OE				0
#define GCLK_3_OE				0

void main_clock_init (void); 

#endif /* _CLOCK_H_ */
