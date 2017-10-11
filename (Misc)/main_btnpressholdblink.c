#include <msp430g2553.h>

#define LED0 BIT0 
#define LED1 BIT6
#define BUTTON BIT3
unsigned int blink = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //stop watchdog timer
    P1DIR |= (LED0 + LED1); //set P1.0 and P1.6 as output
    P1OUT &= ~(LED0 + LED1); //set LEDs off
    P1REN |= BUTTON; //wires resistor to pin
    P1OUT |= BUTTON; //resistor pullup, "1" at pin
    //P1IES |= BUTTON; //Triggers when button PRESS
    P1IES &= ~BUTTON; //Triggers when button RELEASE
    P1IE |= BUTTON; //generate interrupts

    __enable_interrupt(); //interrupt enabler
    for (;;) //for anything while not interrupting
    {
        if(blink > 0) //begins as true
        {
            P1OUT ^= (LED0 + LED1); //Toggle P1.0 and P1.6 using exclusive-OR
            __delay_cycles(111111); //10 Hz = 0.1s = 0.9*10^-6 * 111111 cycles
        }
    }
} 
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    blink ^= 0x01;
    P1IFG &= ~BUTTON; // P1.3 IFG cleared
    P1OUT &= ~(LED0 + LED1); // Clear the LEDs so they start in OFF state
    
}