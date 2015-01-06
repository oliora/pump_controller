#include "msp430.h"
#include "stdio.h"
#include "temperature.h"

temperature::temperature() {
  this->checkTemp = false;
}

temperature::temperature(bool checkTemp = false) {
  this->checkTemp = checkTemp;
}

int temperature::getInt() {
  ADC10CTL0 = SREF_1 + REFON + ADC10ON + ADC10SHT_3;
  ADC10CTL1 = INCH_10 + ADC10DIV_3;
  int t = 0;
  __delay_cycles(1000);
  ADC10CTL0 |= ENC + ADC10SC;
  while (ADC10CTL1 & BUSY);
  t = ADC10MEM;
  ADC10CTL0 &= ~ENC;
  return(int) ((t * 27069L - 18169625L) >> 16);
}

char *temperature::getString() {
  int temp = getInt();
  sprintf(currentTemp, "%d", temp);
  return currentTemp;
}

bool temperature::isCheckTemp() {
  return checkTemp;
}