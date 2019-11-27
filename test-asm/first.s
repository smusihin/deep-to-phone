.text           /*code section*/
.global main    /*'main' is emtry point and must be global*/
.func main      /*'main' is a function*/


main:
    mov r0, #2 
    bx lr       /*return from main*/

