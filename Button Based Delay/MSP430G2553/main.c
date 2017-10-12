#include <msp430g2553.h>

//Button Based Delay
int main(void) 
{
    volatile int i; //counter in between blinks
    volatile int a; //blink rate. smaller number means faster blinking.
 
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog
    //PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings
    P1DIR |= BIT0 + BIT6; //make two leds blink
    P1OUT &= BIT0 + BIT6;
    P1REN = BIT3; //wiring the slow-down button
    P1OUT = BIT3; 
    P2REN = BIT0; //any bitwise functions on lines without + breaks the code for an unknown reason
    P2OUT = BIT0; //wiring the resetting button
     
    // loop forever
    a = 4000; //At 10000, 4 cycles per second, or 250ms delay. 4000 cycles = 100ms or 10Hz delay.
    for(;;) //loop forever
    {
        if(((P1IN & BIT3)==BIT3) & ((P2IN & BIT0)==BIT0)) //if buttons are not pressed
        {
            i = 0; //reset blink counter
            P1OUT ^= BIT0 + BIT6; //two LEDs
            while(i < a) //delays LED blinking until while-loop is complete.
            {
                i = i + 1; //count from 0 to 3999
            }
        }
        else if((P1IN & BIT3)!=BIT3) //if button 1 is pressed
        {
            i = 0;
            P1OUT ^= BIT0 + BIT6; //two LEDs
            a = a + 200; //incrementally slow down the blink rate while button is held
            while(i < a) //delays LED blinking until while-loop is complete.
            {
                i = i + 1;
            }  
        }
        else if((P2IN & BIT0)!=BIT0) //if button reset is pressed
        {
            a = 4000; //reset the a variable back to default speed
        }
    }
}