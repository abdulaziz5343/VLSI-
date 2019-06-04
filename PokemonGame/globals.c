#include "globals.h"

/* global variables */
volatile int record, play, buffer_index;	// audio variables
volatile int left_buffer[BUF_SIZE];			// audio buffer
volatile int right_buffer[BUF_SIZE]; 		// audio buffer

volatile int JPSOUND, BGSOUND, DEADSOUND;	//인덱스들을 VOLATILE INT 형식으로 선언.
volatile int GUNGSOUND;

volatile char byte1, byte2, byte3;			// PS/2 variables

volatile int timeout;						// used to synchronize with the timer
volatile int count;
volatile int KEY;
volatile int Rhythm_KEY;
volatile int Rhythm_Check;
volatile int Rhythm_Color;
volatile int Rhythm_Check_Count[10];
volatile int Count_num;
volatile int Correct;
volatile int First_Rhythm_Check_Count;
volatile int game_over;
volatile int left_buffer[BUF_SIZE];			// audio buffer
volatile int right_buffer[BUF_SIZE];
volatile int complete;
