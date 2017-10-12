#include <msp430fr5994.h>
//Button Based Delay
int main(void) 
{
    volatile int i; //counter in between blinks
    volatile int a; //blink rate. smaller number means faster blinking.
 
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog
    PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings
    P1DIR |= BIT0; //make two leds blink
    P1OUT &= BIT0;
    P1DIR |= BIT1;
    P1OUT &= BIT1;
    P2REN = BIT5; //wiring the slow-down button
    P2OUT = BIT5;
    P4REN = BIT3; //wiring the resetting button
    P4OUT = BIT3;
                    //any bitwise functions on lines without + breaks the code for an unknown reason
    // loop forever
    a = 4000; //At 10000, 4 cycles per second, or 250ms delay. 4000 cycles = 100ms or 10Hz delay.
    for(;;) //loop forever
    {
        if(((P2IN & BIT5)==BIT5) & ((P4IN & BIT3)==BIT3)) //if buttons are not pressed
        {
            i = 0; //reset blink counter
            P1OUT ^= BIT0; //two LEDs
            P1OUT ^= BIT1;
            while(i < a) //delays LED blinking until while-loop is complete.
            {
                i = i + 1; //count from 0 to 3999
            }
        }
        else if((P2IN & BIT5)!=BIT5) //if button 1 is pressed
        {
            i = 0;
            P1OUT ^= BIT0; //two LEDs
            P1OUT ^= BIT1;
            a = a + 200; //incrementally slow down the blink rate while button is held
            while(i < a) //delays LED blinking until while-loop is complete.
            {
                i = i + 1;
            }  
        }
        else if((P4IN & BIT3)!=BIT3) //if button reset is pressed
        {
            a = 4000; //reset the a variable back to default speed
        }
    }
}