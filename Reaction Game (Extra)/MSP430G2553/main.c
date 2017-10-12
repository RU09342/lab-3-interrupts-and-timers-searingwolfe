#include <msp430g2553.h>

int main(void) 
{
    volatile int d,e,f,g,h,i,j,k;
    volatile int a;
    volatile int s,t,u,v,w,x,y,z;
    volatile int lost;
 
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR |= BIT0 + BIT4 + BIT5 + BIT6; //make P1.0 the output pin, automatically assigns P1.1, P1.2, etc as inputs
    P1OUT &= BIT0 + BIT4 + BIT5 + BIT6;
    P2DIR |= BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
    P2OUT &= BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
    P1REN = BIT3; //internal resistor is enabled, P1.3 connects to either Vcc (3.6V) or ground
    P1OUT = BIT3; //P1.3 is an input pin; this line defines internal resistor to connect to 3.6V
    P2REN = BIT0;
    P2OUT = BIT0;
     
    // loop forever
    a = 32000; //At 10000, 4 cycles per second, or 250ms delay. 4000 cycles = 100ms or 10Hz delay.
    s = 0; t = 1; u = 1; v = 1; w = 1; x = 1; y = 1; z = 1;
    lost = 0;
    for(;;) //loop forever
    {
        if((P1IN & BIT3)==BIT3 & lost==0) //if buttons are not pressed
        {
            if(s < 1 & lost==0) {
                d = 0;
                P1OUT ^= BIT0; //two LEDs
                while(d < a) { //delays LED blinking until while-loop is complete.
                    d++; }
                s++; t--;
                if((P1IN & BIT3)!=BIT3) {
                    P1OUT ^= BIT4; P1OUT ^= BIT0;
                    lost = 1; }
            }
            if(t < 1 & lost==0) {
                e = 0;
                P1OUT ^= BIT6; P1OUT ^= BIT0; //two LEDs
                while(e < a) { //delays LED blinking until while-loop is complete.
                    e++; }
                t++; u--;
                if((P1IN & BIT3)!=BIT3) {
                    P1OUT ^= BIT4; P1OUT ^= BIT6;
                    lost = 1; } 
            }
            if(u < 1 & lost==0) {
                f = 0;
                P1OUT ^= BIT5; P1OUT ^= BIT6;;  //two LEDs
                while(f < a) { //delays LED blinking until while-loop is complete.
                    f++; }
                u++; v--;
                if((P1IN & BIT3)!=BIT3) {
                    P1OUT ^= BIT4; P1OUT ^= BIT5;
                    lost = 1; } 
            }
            if(v < 1 & lost==0) {
                g = 0;
                P2OUT ^= BIT1; P1OUT ^= BIT5; //two LEDs
                while(g < a) { //delays LED blinking until while-loop is complete.
                    g++; }
                v++; w--;
                if((P1IN & BIT3)!=BIT3) {
                    P1OUT ^= BIT4; P2OUT ^= BIT1;
                    lost = 1; } 
            }
            if(w < 1 & lost==0) {
                h = 0;
                P2OUT ^= BIT2; P2OUT ^= BIT1; //two LEDs
                while(h < a) { //delays LED blinking until while-loop is complete.
                    h++; }
                w++; x--;
                if((P1IN & BIT3)!=BIT3) {
                    P1OUT ^= BIT4; P2OUT ^= BIT2;
                    lost = 1; } 
            }
            if(x < 1 & lost==0) {
                i = 0;
                P2OUT ^= BIT3; P2OUT ^= BIT2; //two LEDs
                while(i < a) { //delays LED blinking until while-loop is complete.
                    i++; }
                x++; y--;
                if((P1IN & BIT3)!=BIT3) {
                    P1OUT ^= BIT4; P2OUT ^= BIT3;
                    lost = 1; } 
            }
            if(y < 1 & lost==0) {
                j = 0;
                P2OUT ^= BIT4; P2OUT ^= BIT3; //two LEDs
                while(j < a) { //delays LED blinking until while-loop is complete.
                    j++; }
                y++; z--;
                if((P1IN & BIT3)!=BIT3) {
                    P1OUT ^= BIT4; P2OUT ^= BIT4;
                    lost = 1; }
            }
            if(z < 1 & lost==0) {
                k = 0;
                P2OUT ^= BIT5; P2OUT ^= BIT4; //two LEDs
                while(k < a) { //delays LED blinking until while-loop is complete.
                    k++; }
                z++; 
                
                if(z == 1) {
                    s = 0; t = 1; u = 1; v = 1; w = 1; x = 1; y = 1; z = 1;
                    P2OUT ^= BIT5; 
                    
                    if((P1IN & BIT3)!=BIT3) {
                        a = a - 2000;
                    }
                }
            }
        }
        else if((P2IN & BIT0)!=BIT0 & lost == 1) { //if button reset is pressed
                a = 30000;
                s = 0; t = 1; u = 1; v = 1; w = 1; x = 1; y = 1; z = 1;
                lost = 0; P1OUT ^= BIT4;
        }
    }
}