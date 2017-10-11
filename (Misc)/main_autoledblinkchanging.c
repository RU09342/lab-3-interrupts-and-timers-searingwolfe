#include <msp430g2553.h>
int main(void)
{
  unsigned int i=0,j=0;                            // Declare unsigned variables
  WDTCTL = WDTPW + WDTHOLD;                        // Stop watchdog timer
  P1DIR=0x01;                                      // Set P1.0 to output direction
  while(1)
  {
    BCSCTL1 &= ~(BIT1 + BIT2);                          // set to DCO(9,5)
    BCSCTL1 |= BIT0 + BIT3;
    DCOCTL &= ~BIT6;
    DCOCTL |= BIT5 + BIT7;
   for (j=0;j<=5;j++)                                  // Blink LEd 5 times at dco(9,5)
   {
   P1OUT ^= 0x01;                                      // Toggle P1.0 using exclusive-OR
     for(i=0;i<60000;i++){                            //Necessary delay
            }
   }
    BCSCTL1 &= ~(BIT0 + BIT2 + BIT3);                 // set to DCO(2,6)
    BCSCTL1 |= BIT1;
    DCOCTL &= ~BIT5;
    DCOCTL |= BIT6 + BIT7;
             for (j=0;j<=5;j++)                       // Blink led 5 times with dco(2,6)
             {
                 P1OUT ^= 0x01;                       // Toggle P1.0 using exclusive-OR
                 for(i=0;i<60000;i++)
                 {                                    //Necessary delay
                        }
  }
}
}