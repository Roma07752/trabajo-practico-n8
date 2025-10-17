#include "usart.h"

void usart_init(USART_TypeDef *USARTx, int baudrate) {
    // Ejemplo: suponer clock a 8 MHz
    int uartdiv = 8000000 / baudrate;
    USARTx->BRR = uartdiv;

    USARTx->CR1 |= USART_CR1_TE | USART_CR1_RE; // habilitar TX y RX
    USARTx->CR1 |= USART_CR1_UE;                // habilitar USART
}

void usart_send_char(USART_TypeDef *USARTx, char c) {
    while(!(USARTx->SR & USART_SR_TXE)); // espera buffer vacío
    USARTx->DR = c;
}

void usart_send_string(USART_TypeDef *USARTx, char *str) {
    while(*str) {
        usart_send_char(USARTx, *str++);
    }
}

char usart_recibir_char(USART_TypeDef *USARTx) {
    while(!(USARTx->SR & USART_SR_RXNE)); // espera dato
    return (char)(USARTx->DR & 0xFF);
}
