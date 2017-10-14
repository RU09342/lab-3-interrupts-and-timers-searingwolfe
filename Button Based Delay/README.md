MSP430 Microprocessors (5 boards):
------------------------------------------
MSP430F5529
MSP430FR2311
MSP430FR5994
MSP430FR6989
MSP430G2553
------------------------------------------

Button Based Delay

------------------------------------------

The code begins in the main block with declaring two volatile integers, i (for counting between LED blinks) and a (for setting the blink rate, smaller means faster). The next line turns off the on-board watchdog timer control. The two LEDs are set as directional pins, and then these LEDs are set as outputs (blinking on startup). Two buttons are used, one for holding down to slow down the blink rate over time, and the other for resetting the blink rate back to default. The two BUTTONs are coded to internal resistors and set as outputs. The variable a=4000 (100ms or 10Hz) outside of the for-loop, serving as a global variable. Within the for-loop, three if-statements read the current conditions of the two BUTTONs. If both BUTTONs are not pressed, then i=0 (resetting the counter between blinks). The two LEDs are toggled on-or-off. A while-loop controls how long the LEDs take to blink by performing i=i+1 until i is no longer less than a, counting from 0 to 3999 per LED toggling. Once the while-loop ends, the if-statement essentially restarts its code. The second if-statement does not occur until the first BUTTON is pressed. The code inside this second if-statement is almost identical to the first if-statement, except for one extra line. The line a=a+200, outside of the while-loop, increases the total blink rate frequency by causing the while-loop to take longer to count to a. After every while-loop is completed, another a=a+200 is performed, further increasing the blink rate frequency. The code inside the last if-statement is only run when the second button is pressed. In here, a=4000 (last line of code) for resetting the global variable a back to its default startup value.

This code is almost identical for every board, with the exception found in three of them. The MSP430FR boards require one extra line to implement the same code for blinking an LED, which disables the GPIO power-on default high-impedance mode for activating the configured In/Out port settings (PM5CTL0 &= ~LOCKLPM5).

------------------------------------------
