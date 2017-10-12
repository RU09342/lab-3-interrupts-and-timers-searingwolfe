#include <msp430fr2311.h>
//Button Based Delay
int main(void) 
{
    volatile int i; //counter in between blinks
    volatile int a; //blink rate. smaller number means faster blinking.
 
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog
    PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings
    P1DIR |= BIT0; //make two leds blink
    P1OUT &= BIT0;
    P2DIR |= BIT0;
    P2OUT &= BIT0;
    P2REN = BIT6 + BIT7; //wiring the slow-down button
    P2OUT = BIT6 + BIT7; //wiring the resetting button
                    //any bitwise functions on lines without + breaks the code for an unknown reason
    // loop forever
    a = 4000; //At 10000, 4 cycles per second, or 250ms delay. 4000 cycles = 100ms or 10Hz delay.
    for(;;) //loop forever
    {
        if(((P2IN & BIT6)==BIT6) & ((P2IN & BIT7)==BIT7)) //if buttons are not pressed
        {
            i = 0; //reset blink counter
            P1OUT ^= BIT0; //two LEDs
            P2OUT ^= BIT0;
            while(i < a) //delays LED blinking until while-loop is complete.
            {
                i = i + 1; //count from 0 to 3999
            }
        }
        else if((P2IN & BIT6)!=BIT6) //if button 1 is pressed
        {
            i = 0;
            P1OUT ^= BIT0; //two LEDs
            P2OUT ^= BIT0;
            a = a + 200; //incrementally slow down the blink rate while button is held
            while(i < a) //delays LED blinking until while-loop is complete.
            {
                i = i + 1;
            }  
        }
        else if((P2IN & BIT7)!=BIT7) //if button reset is pressed
        {
            a = 4000; //reset the a variable back to default speed
        }
    }
}