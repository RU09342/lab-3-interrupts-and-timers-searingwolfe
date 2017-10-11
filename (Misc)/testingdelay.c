#include <msp430g2553.h>

#define GPIO (BIT0 + BIT1 + BIT2 + BIT3)
#define LED0 BIT0
#define LED1 BIT6
#define BUTTON BIT7

int a = 111111-1;
int x = 0;
void main(void) 
{
	WDTCTL = WDTPW + WDTHOLD;    // disable watchdog
    P1DIR |= LED0 + LED1;
    P1OUT |= LED0 + LED1;
	P2DIR |= GPIO;
	P2OUT |= GPIO;    // set the 4 gpio pins as outputs
	
	P1REN = BUTTON;
	P1OUT &= BUTTON;
	BCSCTL1 = CALBC1_1MHZ;    // Set DCO to calibrated 1 MHz.
    DCOCTL = CALDCO_1MHZ;     // LED blink time delay = TACCR0 / DC0CTL, or time delay = 62500-1 / 1 MHz = 0.062499 seconds.
	TACCTL0 = CCIE;        // Enable interrupts for CCR0.
	TACTL = TASSEL_2 + ID_1 + MC_1 + TACLR;  // SMCLK, multiply time delay by 2^3=8, continuous mode, timer reset. multiply by 8 achieved by ID_3
	
	while(1) //loop indefinitely
    {
        if(((P1IN & BUTTON)==BUTTON) & x==0) //logic AND. P1IN and BIT3 must be 1 for output to be 1
        {
	        TACCR0 = a;    // A period of 62,500 cycles is 0 to 62,499. TACCR0 = 1500-1 is about as fast as it can be, visually.
	        x = 1;
        }
        else if(((P1IN & BUTTON)==BUTTON) & x==1)
        { 
	        TACCR0 = a+10000;    // A period of 62,500 cycles is 0 to 62,499. TACCR0 = 1500-1 is about as fast as it can be, visually.
	        x = 0;
        }
    }
	//_enable_interrupt(); 
} // main
#pragma vector = TIMER0_A0_VECTOR
__interrupt void CCR0_ISR(void) 
{
	P1OUT ^= LED0 + LED1;
	P2OUT ^= GPIO;
	TACTL &= ~BIT0;
} // CCR0_ISR

