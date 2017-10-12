#include <msp430f5529.h>

//Timer A Blink
char i=0;
void main(void) 
{
	WDTCTL = WDTPW + WDTHOLD;    // disable watchdog
    //PM5CTL0 &= ~LOCKLPM5; // Disable GPIO power-on default high-impedance mode to activate configured port settings
	P1DIR = BIT2 + BIT3 + BIT4 + BIT5;
	P1OUT = BIT2 + BIT3 + BIT4 + BIT5;    // set the 4 gpio pins as outputs

	//BCSCTL1 = CALBC1_1MHZ;    // Set DCO to calibrated 1 MHz.
	//DCOCTL = CALDCO_1MHZ;     // LED blink time delay = TACCR0 / DC0CTL, or time delay = 62500-1 / 1 MHz = 0.062499 seconds.
    //change TACCR0 to TA0CCRO
	TA0CCR0 = 62500 - 1;    // A period of 62,500 cycles is 0 to 62,499. TACCR0 = 1500-1 is about as fast as it can be, visually.
	TA0CCTL0 = CCIE;        // Enable interrupts for CCR0.
	TA0CTL = TASSEL_2 + ID_3 + MC_2 + TACLR;  // SMCLK, multiply time delay by 2^3=8, continuous mode, timer reset. multiply by 8 achieved by ID_3.
	                                         // clear timer. ID_1 placed there as a reminder that it exists, likewise for TACLR.
	_enable_interrupt();                     // MC_1 = up mode. MC_2 = continuous mode. MC_3 = up/down mode. MC_3 multiplies time delay by 2.
                                             // The max cycles value is 65536, thus for slower speeds an ID_# multiplier is needed.
                                             // Thus, 0.062499 seconds * 8 = 0.499992 seconds, or about half-second cycles.
    //for(;;) {    // Do nothing while waiting for interrupts. Commented out since it is unnecessary.
    //	}            
} // main
/*  Interrupt Service Routines  */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void CCR0_ISR(void) 
{
	if (++i == 1) { //essentially multiplies TACCR0 value by i. example: if TACCR0 = 6250-1 and ++i==10, then TACCR0 = 62500-1
		P1OUT ^= BIT2 + BIT3 + BIT4 + BIT5;
		i=0;
	}
} // CCR0_ISR