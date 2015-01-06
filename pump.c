#include "uart.h"
#include "msp430.h"
#include "pump.h"

pump::pump() {
	pumpWorkTime = 0;
	pumpMaxWorkTime = 1;
	pumpIsWorking = false;
}

pump::pump(int pumpMaxWorkTime) {
	this->pumpWorkTime = 0;
	this->pumpMaxWorkTime = pumpMaxWorkTime;
	this->pumpIsWorking = false;
}

void pump::startPump() {
	P1OUT |= PUMP_RELAY;
   	uart_putsln("Pump started.");
   	pumpIsWorking = true;
}

void pump::stopPump() {
	P1OUT &= ~PUMP_RELAY;
   	uart_putsln("Pump stopped.");
   	pumpIsWorking = false;
}

bool pump::isPumpWorking() {
	return pumpIsWorking;
}

void pump::blinkGreen() {
	P1OUT ^= PUMP_RELAY;
}