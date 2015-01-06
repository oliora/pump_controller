#include "msp430.h"
#include "stdio.h"
#include "uart.h"
#include "pump.h"
#include "temperature.h"
#include <legacymsp430.h>



pump mainPump(10);
temperature temp(true);

int main(void)
{
    WDTCTL  = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    P1OUT = 0;
    P1DIR |= LED_RED + PUMP_RELAY;
    P1OUT |= LED_RED;

    uart_init();

    

    TACCR0 = 62500 - 1;
    TACCTL0 = CCIE;
    TACTL = TASSEL_2 + ID_3 + MC_1 + TACLR;
    _BIS_SR(GIE);

    uart_putsln("\n\rProgram started ...");

    mainPump.startPump();

    _BIS_SR(LPM1_bits + GIE);

    return 0;
}

interrupt(TIMER0_A0_VECTOR) CCR0_ISR(void) {
    if (mainPump.isPumpWorking()) {
        mainPump.blinkGreen();
        if (++mainPump.pumpWorkTime == (mainPump.pumpMaxWorkTime * 2)) {
            mainPump.pumpWorkTime = 0;
            mainPump.stopPump();
        }
    }
    if (temp.isCheckTemp()) {
        uart_putsln(temp.getString());
    }
}



