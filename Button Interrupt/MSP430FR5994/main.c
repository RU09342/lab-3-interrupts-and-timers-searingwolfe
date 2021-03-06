#include <msp430fr5994.h>

#define LED0 BIT0
#define LED1 BIT1 
#define BUTTON BIT6
//simply set the bit values here for a different microprocessor
//P1DIR, P1OUT, P1REN, etc will still have to be changed

//Button Interrupt
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;   // Disable GPIO power-on default high-impedance mode, for MSP430FR boards
    P1DIR |= LED0 + LED1; // Set P1.0 to output direction
    P3DIR |= BIT4 + BIT5 + BIT6 + BIT7;

    // P1.3 must stay at input
    P1OUT &= ~(LED0 + LED1); // set P1.0 to 0 (LED OFF)
    P3OUT &= ~(BIT4 + BIT5 + BIT6 + BIT7); //GPIO pins
    P5REN = BUTTON; //can only use P1 for interrupts.
    P5IE |= BUTTON; // P1.3 interrupt enabled

    P5IFG &= ~BUTTON; // P1.3 IFG cleared

    __enable_interrupt(); // enable all interrupts
    //for(;;)
    //{} //unnecessary loop
}


// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR //change port value to match button interrupt input
__interrupt void Port_1(void)
{
    P1OUT ^= LED0 + LED1; // P1.0 = toggle
    P3OUT ^= BIT4 + BIT5 + BIT6 + BIT7;
    P5IFG &= ~BUTTON; // P1.3 IFG cleared
    P5IES ^= BUTTON; // toggle the interrupt edge
}
