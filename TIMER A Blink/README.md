MSP430 Microprocessors (5 boards):
------------------------------------------
MSP430F5529
MSP430FR2311
MSP430FR5994
MSP430FR6989
MSP430G2553
------------------------------------------

Timer A Blink

------------------------------------------

The code begins outside the main block by declaring a character i=0 for counting in between LED blinks). Inside the main block, the first line turns off the on-board watchdog timer control. Four GPIO pins are set as directional pins, and then set as outputs. Two lines are commented out for simplicity, but they can be used to calibrate the on-board timer to a desired frequency (1MHz by default). The capture/compare register (TACCR0) is set to a value of 62500-1 (actually counts from 0 to 62499, which is 62500 counts). Interrupts are enabled for the capture/compare control register. The timer control register is configured to continuous mode (MC_2), and its value is multiplied by 8 (ID_3) since the capture/compare control register cannot be larger than 65536. In the last line in the main block, all interrupt blocks are enabled. Before the interrupt block, the #pragma vector line is equal to TIMER0_A0_VECTOR, which reads any interrupts coming from TIMER0 (TACCTL0). Within the interrupt block, the four GPIO outputs are toggled only during an interrupt event after the capture/compare register has counted up to its declared value. A single if-statement is used to multiply TACCR0's value by the number that ++i is equal to and slow down the LED's blink rate overall (if ++i == 10 then TACCR0's value would essentially be 625000-1). The final line, also in the if-statement, is i=0 for resetting the if-statement's counter.

This code is almost identical for every board, with the exception found in three of them. The MSP430FR boards require one extra line to implement the same code for blinking an LED, which disables the GPIO power-on default high-impedance mode for activating the configured In/Out port settings (PM5CTL0 &= ~LOCKLPM5). Also, some boards reqire changing lines such as TACCR0 (TAC...generally) to TA0CCR0 or TB0CCR0, depending on the board's specific timer register declarations. And the #pragma vector value is changed accordingly, from TIMER0_A0 to TIMER0_B0 or similar.

------------------------------------------
