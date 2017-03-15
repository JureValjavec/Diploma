#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_

#include "types.h"
#include "samd20.h"
#include "integer.h"

#define SD_CARD_SPI_SERCOM1	1
#define ACC_SPI_SERCOM0 0

#define spi_r(SERCOMx, r_buff, lenght) spi_rw(SERCOMx, NULL, r_buff, lenght)
#define spi_w(SERCOMx, w_buff, lenght) spi_rw(SERCOMx, w_buff, NULL, lenght)

typedef struct spi_data_struct
{
	char spi1_read_buff[100];
	char spi1_write_buff[100];

}T_SPI_DATA;

void spi_init (void);
BOOL spi_rw (Sercom * SERCOMx, BYTE *w_buff, BYTE *r_buff, UINT32 lenght);
BOOL spi_acc_rw (Sercom * SERCOMx, BYTE *w_buff, BYTE *r_buff, UINT32 lenght);

#endif /* _SPI_DRIVER_H_*/
