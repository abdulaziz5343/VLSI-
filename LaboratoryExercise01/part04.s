.text
.global _start
_start:
			movia	r4, N
			addi	r8, r4, 4
			ldw		r4, (r4)	

LOOP:		call 	DIVIDE
			mov		r4, r3
			stb		r2, 0(r8)
			beq		r4, r0, END
			addi	r8, r8, 1
			bne		r6, r8, LOOP
END:		br 		END
/*Subroutine to perform  the integer division r4/10.
*Returns quotient in r3, and remainder in r2*/
DIVIDE:		mov		r2, r4		#r2 will be remainder
			movi	r5, 10		#divisor
			movi	r3, 0		#r3 will be the quotient
CONT:		blt		r2, r5, DIV_END
			sub		r2, r2, r5 	#subtract the divisor, and...
			addi	r3, r3, 1	#increment the quotient
			br 		CONT
DIV_END:	ret					#quotient is in r3, remainder in r2

N:			.word	76			
Digits:		.space	4			
			.end
