#include <msp430f5529.h>
//Button Based Delay
int main(void) 
{
    volatile int i; //counter in between blinks
    volatile int a; //blink rate. smaller number means faster blinking.
 
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog
    //PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings
    P1DIR |= BIT0; //make two leds blink
    P1OUT &= BIT0;
    P4DIR |= BIT7;
    P4OUT &= BIT7;
    P2REN = BIT4; //wiring the slow-down button
    P2OUT = BIT4;
    P1REN = BIT5; //wiring the resetting button
    P1OUT = BIT5;
                    //any bitwise functions on lines without + breaks the code for an unknown reason
    // loop forever
    a = 4000; //At 10000, 4 cycles per second, or 250ms delay. 4000 cycles = 100ms or 10Hz delay.
    for(;;) //loop forever
    {
        if(((P2IN & BIT4)==BIT4) & ((P1IN & BIT5)==BIT5)) //if buttons are not pressed
        {
            i = 0; //reset blink counter
            P1OUT ^= BIT0; //two LEDs
            P4OUT ^= BIT7;
            while(i < a) //delays LED blinking until while-loop is complete.
            {
                i = i + 1; //count from 0 to 3999
            }
        }
        else if((P2IN & BIT4)!=BIT4) //if button 1 is pressed
        {
            i = 0;
            P1OUT ^= BIT0; //two LEDs
            P4OUT ^= BIT7;
            a = a + 200; //incrementally slow down the blink rate while button is held
            while(i < a) //delays LED blinking until while-loop is complete.
            {
                i = i + 1;
            }  
        }
        else if((P1IN & BIT5)!=BIT5) //if button reset is pressed
        {
            a = 4000; //reset the a variable back to default speed
        }
    }
}