#include "address_map_nios2.h"
#include <stdio.h>
#include "globals.h"

extern volatile int buffer_index;
extern volatile int KEY;
extern volatile int Rhythm_KEY;
extern volatile int Rhythm_Check;
extern volatile int Rhythm_Check_Count[10];
extern volatile int Count_num;
extern volatile int Correct;
extern volatile int First_Rhythm_Check_Count;


//extern volatile int timeout;
//extern volatile int count;
void Key_Rhythm_Check();
/*******************************************************************************
 * Pushbutton - Interrupt Service Routine
 *
 * This ISR checks which KEY has been pressed. If KEY0, then it enables audio-in
 * interrupts (recording). If KEY1, it enables audio-out interrupts (playback).
 ******************************************************************************/
void pushbutton_ISR( void )
{
	volatile int * KEY_ptr = (int *) KEY_BASE;
	
	int KEY_value;


	KEY_value = *(KEY_ptr + 3);			// read the pushbutton interrupt register
	*(KEY_ptr + 3) = KEY_value; 		// Clear the interrupt

	if (KEY_value == 0x1)				// check KEY0
	{
		KEY=0;
		Key_Rhythm_Check();
	}
	else if (KEY_value == 0x2)			// check KEY1
	{
		KEY=1;
		Key_Rhythm_Check();
	}
	else if (KEY_value == 0x4)			// check KEY1
	{
		KEY=2;
		Key_Rhythm_Check();
	}
	else if (KEY_value == 0x8)			// check KEY1
	{
		KEY=3;
		Key_Rhythm_Check();			
	}
	return;
}
void Key_Rhythm_Check(){	//PushButtonÀÔ·Â°ú ³ëÆ®ÀÇ TypeÀÌ ÀÏÄ¡ÇÏ´ÂÁö ÆÇ´Ü.
	if(Rhythm_KEY==KEY){	//ÀÏÄ¡ÇÏ´Â °æ¿ì
		Rhythm_Check=0;		//CheckµÈ ³ëÆ®Ç¥½Ã¸¦ À§ÇØ Rhythm[j].Check_SW¿¡ 0À» ³Ñ°ÜÁÜ.
		Rhythm_Check_Count[Count_num]--;	//ÆÇ´ÜÇÒ ³ëÆ®ÀÇ ¼ö¸¦ 1°¨¼Ò.
		if(Rhythm_Check_Count[Count_num]==0){	/*¸ðµç ³ëÆ®¸¦ ÆÇ´ÜÇÑ °æ¿ì ´ÙÀ½ ³ëÆ®±×·ìÀÇ
												³ëÆ® °³¼ö¸¦ °¡¸®Å´.*/
			Count_num++;
			if(Count_num==10)	Count_num=0;
			Correct = 1;			//¸ðµç ³ëÆ®¸¦ Á¤È®È÷ ÆÇ´ÜÇßÀ½.
		}
	}
	else{
		Correct = 2;				//Àß¸øµÈ PushButtonÀÔ·Â.
	}
}
