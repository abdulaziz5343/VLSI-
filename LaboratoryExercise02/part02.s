.text
.global _start 
ONES: 	 		addi		sp, sp, -8
	    		stw		r10, 0(sp)
		     	stw		ra, 4(sp)
		     	movi		r2, 0
ONES_CONT:		beq	 	r4, r0, ONES_END
			srli		r10, r4, 0x01
		    	and		r4, r4, r10
		    	addi		r2, r2, 0x01
		    	br 		ONES_CONT
ONES_END:		ldw		ra, 4(sp)
		    	ldw		r10, 0(sp)
		    	addi		sp, sp, 8
		    	ret		
_start:
	    		movia		r3, TEST_NUM
	    		mov 		r10, r0
LOOP:		  	ldw		r4, 0(r3)
	    		beq		r4, r0, END	
		    	call	 	ONES
	    		blt		r2, r10, NEXT
			mov		r10, r2
NEXT:	  		addi		r3, r3, 4
		    	br 		LOOP	
END:	  		br 		END
TEST_NUM:		.word	0x12345678, 0xFF134567, 0x0
			.end
