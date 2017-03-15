#ifndef _TRP_868_H_
#define _TRP_868_H_

#include "types.h"

BOOL trp868_write (char * buff,  UINT16 lenght );
BOOL trp868_read (char * buff);
BOOL gps_write (char * buff,  UINT16 lenght );

#endif /* _TRP868_UART_H_ */
