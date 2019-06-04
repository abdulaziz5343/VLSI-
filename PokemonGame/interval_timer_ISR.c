#include "address_map_nios2.h"

extern volatile int timeout;
extern volatile int count;
/*****************************************************************************
 * Interval timer interrupt service routine
 *                                                                          
 * Controls refresh of the VGA screen
 * 
******************************************************************************/
void interval_timer_ISR( )
{
	volatile int * interval_timer_ptr = (int *) TIMER_BASE;
  	volatile char * LCD_display_ptr = (char *) CHAR_LCD_BASE;

	*(interval_timer_ptr) = 0; 						// clear the interrupt
	timeout = 1;									// set global variable
	count++;
	/* shift the LCD display to the left */
	*(LCD_display_ptr) = 0x18;						// instruction = shift left 

	return;
}
