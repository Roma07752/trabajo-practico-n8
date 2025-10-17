#ifndef SPI_H
#define SPI_H

#include "stm32f103xb.h"

void spi_init(SPI_TypeDef *SPIx);
void spi_ss(GPIO_TypeDef *port, int pin);
void spi_ds(GPIO_TypeDef *port, int pin);
char spi_rw_byte(SPI_TypeDef *SPIx, char data);

#endif
