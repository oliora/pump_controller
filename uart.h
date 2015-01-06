#pragma once

//Инициализация UART
void uart_init(void);

//Установить обработчик прерывания по приёму данных на UART
void uart_set_rx_isr_ptr(void (*isr_ptr)(unsigned char c));

//Считать один символ с UART
unsigned char uart_getc();

//Переслать один символ по UART
void uart_putc(unsigned char c);

//Переслать строку на UART
void uart_puts(const char *str);

//Переслать строку на UART
void uart_putsln(const char *str);
