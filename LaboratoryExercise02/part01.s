		.text 
		.global 	_start
_start:
	  	ldw		r9, TEST_NUM(r0)	/*Load the data into r9*/
	 	  mov		r10, r0				/*r10	will hold the result*/
LOOP:	beq		r9, r0, END			/*Loop until r9 contrains no more 1s*/
	  	srli	r11, r9, 0x01		/*Count the 1s by shifting the number and*/
	  	and 	r9, r9, r11			/*Increment the counter*/
	  	addi 	r10, r10, 0x01
	  	br		LOOP				

END:	br		END					/*Wait here*/
TEST_NUM: .word	0x3fabedef			/*The number to be tested*/
		  .end
