	// file header
	.arch armv6           		// armv6 architecture
	.arm		      		// arm 32-bit instruction set
        .fpu vfp	      		// floating point co-processor
	.syntax unified	      		// modern syntax

        // constant values you want to use throughout the program
        // could go below like:
        // .equ ONE, 1

	// .data // uncomment if needed

	.text 				// start of text segment

	.global encrypt			// make encrypt global for linking to
	.type	encrypt, %function	// define encrypt to be a function
	.equ	FP_OFF, 4		// fp offset distance from sp

encrypt:
	// function prologue
	push	{fp, lr}		// stack frame register save
	add	fp, sp, FP_OFF		// set frame pointer to frame base
                                                                          
	// DO NOT EDIT LINES ABOVE 
	

        // your code here
	MOV R3, 0x0F			// R3 = 0x0F;
	AND R2, R0, R3			// R2 = (R0 & R3);
	LSL R3, R2, #4			// R3 = R2 << 4;
	MOV R2, 0xF0			// R2 = 0xF0
	AND R2, R0, R2			// R2 = (R0 & R2);
	LSR R2, R2, #4			// R2 = R2 >> 4;
	ORR R0, R3, R2			// R0 = (R3 | R2);
	EOR R2, R0, R1			// R2 = (R0 ^ R1);
	MOV R0, R2			// R0=R2
	

        // DO NOT EDIT LINES BELOW
	
	// function epilogue
	sub	sp, fp, FP_OFF		// restore stack frame top
	pop	{fp, lr}		// remove frame and restore registers
	bx	lr			// return to caller

	// function footer
	.size	encrypt, (. - encrypt)	// set size for function

	.global decrypt			// make encrypt global for linking to
	.type	decrypt, %function	// define encrypt to be a function
	.equ	FP_OFF, 4		// fp offset distance from sp

decrypt:
	// function prologue
	push	{fp, lr}		// stack frame register save
	add	fp, sp, FP_OFF		// set frame pointer to frame base

        // DO NOT EDIT LINES ABOVE


	// your code here
	EOR R2, R0, R1			// R2 = (R0 ^ R1);
	MOV R3, 0x0F			// R3 = 0x0F
	AND R1, R2, R3			// R1 = (R2 & R3);
	LSL R3, R1, #4			// R3 = R1 << 4;
	MOV R1, 0xF0			// R1 = 0xF0
	AND R1, R2, R1			// R1 = (R2 & R1);
	LSR R1, R1, #4			// R1 = R1 >> 4;
	ORR R0, R1, R3			// R0 = (R1 | R3);

	// DO NOT EDIT LINES BELOW
	
        // function epilogue
	sub	sp, fp, FP_OFF		// restore stack frame top
	pop	{fp, lr}		// remove frame and restore registers
	bx	lr			// return to caller

	// function footer
	.size	decrypt, (. - decrypt)	// set size for function

	// file footer
	.section .note.GNU-stack,"",%progbits // stack/data non-exec (linker)
.end
	Template is Arm Procedure Call Standard Compliant (for Linux)
