TITLE lab6                (lab6.ASM) ; TODO:
INCLUDE Irvine32.inc

.data
ninenine BYTE 81 DUP(?)

.code
writeNinenine Proc uses ecx

writeNinenine ENDP

main EQU start@0
main PROC
    mov ecx, 9
    mov al, 0
    mov ax, 9

L1:
    add al, 1
    call writeNinenine



    exit
main ENDP
END main