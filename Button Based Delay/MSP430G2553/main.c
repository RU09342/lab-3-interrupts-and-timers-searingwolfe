#include <msp430g2553.h>

int main(void) 
{
    volatile int i;
    volatile int a;
 
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR = BIT0 + BIT6; //make P1.0 the output pin, automatically assigns P1.1, P1.2, etc as inputs
    P1OUT = BIT0 + BIT6;
    P1REN = BIT3; //internal resistor is enabled, P1.3 connects to either Vcc (3.6V) or ground
    P1OUT = BIT3; //P1.3 is an input pin; this line defines internal resistor to connect to 3.6V
    P2REN = BIT0 + BIT1;
    P2OUT = BIT0 + BIT1;
     
    // loop forever
    a = 4000; //At 10000, 4 cycles per second, or 250ms delay. 4000 cycles = 100ms or 10Hz delay.
    for(;;) //loop forever
    {
        if(((P1IN & BIT3)==BIT3) & ((P2IN & BIT0)==BIT0)) //if buttons are not pressed
        {
            i = 0;
            P1OUT ^= BIT0 + BIT6; //two LEDs
            while(i < a) //delays LED blinking until while-loop is complete.
            {
                i = i + 1;
            }
        }
        else if((P1IN & BIT3)!=BIT3) //if button 1 is pressed
        {
            i = 0;
            P1OUT ^= BIT0 + BIT6; //two LEDs
            a = a + 200;
            while(i < a) //delays LED blinking until while-loop is complete.
            {
                i = i + 1;
            }  
        }
        else if((P2IN & BIT0)!=BIT0) //if button reset is pressed
        {
            a = 4000;
        }
    }
}