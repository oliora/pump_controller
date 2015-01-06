#include "msp430.h"
#include "uart.h"

#define RXD  BIT1 // линии порта P1
#define TXD  BIT2 // задействованные под UART

/**
 * Callback handler for receive
 */
 void (*uart_rx_isr_ptr)(unsigned char c);

 void uart_init(void)
 {
 	uart_set_rx_isr_ptr(0L);

 	P1SEL  = RXD + TXD;      // настраиваем линии порта                 
 	P1SEL2 = RXD + TXD;                       
 	UCA0CTL1 |= UCSSEL_2;  // Источник тактирования UART --- SMCLK
 	UCA0BR0 = 104;         // Настраиваем скорость 1MHz 9600
 	UCA0BR1 = 0;           // 1MHz 9600
 	UCA0MCTL = UCBRS0;     // Модуляция UCBRSx = 1
 	UCA0CTL1 &= ~UCSWRST;  // Инициализируем модуль USCI
 	IE2 |= UCA0RXIE;       // Разрешаем прерывания от UART.
}

void uart_set_rx_isr_ptr(void (*isr_ptr)(unsigned char c))  
// Назначает обработчик прерывания от UART
{
	uart_rx_isr_ptr = isr_ptr; 
}

unsigned char uart_getc()
{
	while (!(IFG2&UCA0RXIFG));  // Буфер приёмника USCI_A0 готов?
	return UCA0RXBUF;
}

void uart_putc(unsigned char c)
{
	while (!(IFG2&UCA0TXIFG)); // Буфер передатчика готов
	UCA0TXBUF = c;  // TX
}

void uart_puts(const char *str)
{
	while(*str) uart_putc(*str++);
}

void uart_putsln(const char *str)
{
	uart_puts(str);
	uart_puts("\n\r");
}
void usci0rx_isr(void) __attribute((interrupt(USCIAB0RX_VECTOR)));

void usci0rx_isr(void)
{
	if(uart_rx_isr_ptr != 0L) { // Если пришёл символ 
		(uart_rx_isr_ptr)(UCA0RXBUF); // то вызывам обработчик
	}
}
