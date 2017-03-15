#include "samd20.h"
#include "extin_driver.h"
#include "types.h"


/* config pin PB02 for button interrupt */

void ext_int_conf (void)
{
	PORT->Group[1].PINCFG[2].reg = PORT_PINCFG_PULLEN | PORT_PINCFG_PMUXEN;
	PORT->Group[1].PMUX[1].reg = PORT_PMUX_PMUXE_A; 
}
