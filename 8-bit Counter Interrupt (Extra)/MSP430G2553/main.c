
#include<msp430g2553.h> 
#include<stdint.h> // for uint16_t
#define BUTTON BIT3 //push button P1.3

void main (void) 
{
    WDTCTL = WDTPW | WDTHOLD; //watchdog off
    P2OUT &= 0x3F; //outputs P2.0 - P2.5
    P2DIR |= 0x3F; //pins P2.0 - P2.5
    P1OUT &= 0xC0; //outputs P1.6 - P1.7
    P1DIR |= 0xC0; //pins P1.6 - P1.7
    TACCR0 = 10000-1; // A period of 50000 cycles is 0 to 49999. Controls counting speed.
    TACTL = TASSEL_2 | ID_3 | MC_1 | TACLR; // SMCLK, multiply time delay by 2^3=8, up mode, timer reset. multiply by 8 achieved by ID_3.
    TACCTL0 = CCIE; // Enable interrupts for CCR0.
    P1DIR &= ~BUTTON; // set Button to input
    BCSCTL1 = CALBC1_1MHZ;// Set DCO to calibrated 1 MHz.
	DCOCTL = CALDCO_1MHZ; // LED blink time delay = TACCR0 / DC0CTL, or time delay = 62500-1 / 1 MHz = 0.062499 seconds.

    __enable_interrupt(); // enable all interrupts
    
} // Port 1 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR //change port value to match button interrupt input
__interrupt void CCR0_ISR(void)
{
    int i;
    i=0;
    for(;;)
    {
       while ((P1IN & BUTTON) == 0)
       { // while button is pressed
           while ((TACTL & TAIFG) == 0)
           { // waiting for timer to overflow
           }
           TACTL &= ~TAIFG; // reset overflow
           i++; // increase counter i variable
           P2OUT = pattern(i); // set counter to output
           P1OUT = pattern(P2OUT);
           if (i == 255)
           { // max outcome is 11111111 bits, so 255 counts until counter reset
                i=0; // set counter back to zero
           }
       }
       i=0;
    }
    
} 
int pattern (int value)  
{ // set pattern
    uint16_t patterntest; // unsigned 16 bit integer for binairy pattern
    int i; // for loop integer i
    patterntest = 0;
 
    for (i=7;i>=0;i--){ // loop with bit shifting
        if (value >= power(i)){ // decide if value higher is then 2^5-0
            patterntest |= BIT0;
            value = value - power(i);
        }
        else {
            patterntest &= ~BIT0; // if not, then 0
        }
        if (i != 0){
        patterntest <<= 1; // shift bit 1 to the left
        }
    }
  return  patterntest; // set output
}
int power (int n) // raise 2 to the power n
{
    int p;
    int i;
    p = 1;
        for (i=1;i<=n;i++){
            p=p*2; // loop 2*p until n
        }
    return p; // return outcome
}