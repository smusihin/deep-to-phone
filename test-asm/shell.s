.data

.section .rodata

command:
        .string "/system/bin/sh"

arg0:  
        .string "/system/bin/sh"

args:  
        .word arg0
        .word 0

.text

.globl _start

_start:
        .code 32
        add r3, pc, #1
        bx r3
 
        .code 16
        mov r7, #11
        ldr r0, =command
        ldr r1, =args
        eor r2, r2
        svc #0
