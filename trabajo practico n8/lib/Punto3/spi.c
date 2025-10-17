#include "spi.h"

void spi_init(SPI_TypeDef *SPIx) {
    SPIx->CR1 = SPI_CR1_MSTR     // master
              | SPI_CR1_SSM      // software slave management
              | SPI_CR1_SSI
              | SPI_CR1_BR_1     // baudrate prescaler
              | SPI_CR1_SPE;     // habilitar SPI
}

void spi_ss(GPIO_TypeDef *port, int pin) {
    port->BRR = (1 << pin); // poner SS en 0
}

void spi_ds(GPIO_TypeDef *port, int pin) {
    port->BSRR = (1 << pin); // poner SS en 1
}

char spi_rw_byte(SPI_TypeDef *SPIx, char data) {
    while(!(SPIx->SR & SPI_SR_TXE));
    SPIx->DR = data;
    while(!(SPIx->SR & SPI_SR_RXNE));
    return (char)SPIx->DR;
}