MSP430 Microprocessors (5 boards):
------------------------------------------
MSP430F5529
MSP430FR2311
MSP430FR5994
MSP430FR6989
MSP430G2553
------------------------------------------

Button Interrupt

------------------------------------------

Three definitions are declared for LED0, LED1, and BUTTON, for simplification. The code begins in the main block with turning off the on-board watchdog timer control. The two LEDs are set as directional pins, and then these LEDs are set as the NOT outputs (off on startup). The BUTTON is coded to an internal resistor. An interrupt register is enabled for this BUTTON. This same BUTTON's interrupt flag is then cleared using ~BUTTON (NOT BUTTON). The last line in the main block then enables all subsequent interrupt blocks. Before the interrupt block, the #pragma vector line is equal to PORT1_VECTOR, which reads any interrupts coming from PORT1 (the BUTTON is wired to P1.3). Within the interrupt block, the two LEDs' outputs are toggled from off-to-on only during an interrupt event from the BUTTON. The next line clears the NOT BUTTON's interupt flag again. The final line toggles the interrupt edge of the BUTTON (high-to-low or low-to-high).

This code is almost identical for every board, with the exception found in three of them. The MSP430FR boards require one extra line to implement the same code for blinking an LED, which disables the GPIO power-on default high-impedance mode for activating the configured In/Out port settings (PM5CTL0 &= ~LOCKLPM5).

------------------------------------------
