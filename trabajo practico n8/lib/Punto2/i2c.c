#include "i2c.h"

void i2c_init(I2C_TypeDef *I2Cx) {
    I2Cx->CR2 = 8;        // 8 MHz PCLK1
    I2Cx->CCR = 40;       // 100kHz estándar
    I2Cx->TRISE = 9;
    I2Cx->CR1 |= I2C_CR1_PE;
}

void i2c_start(I2C_TypeDef *I2Cx) {
    I2Cx->CR1 |= I2C_CR1_START;
    while(!(I2Cx->SR1 & I2C_SR1_SB));
}

void i2c_stop(I2C_TypeDef *I2Cx) {
    I2Cx->CR1 |= I2C_CR1_STOP;
}

void i2c_send_direccion(I2C_TypeDef *I2Cx, char addr) {
    I2Cx->DR = addr;
    while(!(I2Cx->SR1 & I2C_SR1_ADDR));
    (void)I2Cx->SR2; // leer SR2 limpia flag
}

void i2c_send_byte(I2C_TypeDef *I2Cx, char data) {
    while(!(I2Cx->SR1 & I2C_SR1_TXE));
    I2Cx->DR = data;
    while(!(I2Cx->SR1 & I2C_SR1_BTF));
}

char i2c_recibir_byte_ack(I2C_TypeDef *I2Cx) {
    I2Cx->CR1 |= I2C_CR1_ACK;
    while(!(I2Cx->SR1 & I2C_SR1_RXNE));
    return I2Cx->DR;
}

char i2c_recibir_byte_nack(I2C_TypeDef *I2Cx) {
    I2Cx->CR1 &= ~I2C_CR1_ACK;
    while(!(I2Cx->SR1 & I2C_SR1_RXNE));
    return I2Cx->DR;
}
