#include <msp430g2553.h>

#define LED0 BIT0
#define LED1 BIT6 
#define BUTTON BIT3
//simply set the bit values here for a different microprocessor
//P1DIR, P1OUT, P1REN, etc will still have to be changed

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    //PM5CTL0 &= ~LOCKLPM5;   // Disable GPIO power-on default high-impedance mode, for MSP430FR boards
    P1DIR |= (LED0 + LED1); // Set P1.0 to output direction 
    // P1.3 must stay at input
    P1OUT &= ~(LED0 + LED1); // set P1.0 to 0 (LED OFF)
    P1REN = BUTTON;
    P1IE |= BUTTON; // P1.3 interrupt enabled

    P1IFG &= ~BUTTON; // P1.3 IFG cleared

    __enable_interrupt(); // enable all interrupts
    //for(;;)
    //{} //unnecessary loop
}


// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^= (LED0 + LED1); // P1.0 = toggle
    P1IFG &= ~BUTTON; // P1.3 IFG cleared
    P1IES ^= BUTTON; // toggle the interrupt edge
}