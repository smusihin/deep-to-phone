.text
.globl _start
_start: 
    .code 32
        add r3,pc,#1
        bx r3
    .code 16
	    ldr	r0, [sp, #8]
	    add r1, sp, #8
	    eor r2, r2
	    mov r7, #11
        svc #1



