TITLE lab1                (lab1.ASM)
INCLUDE Irvine32.inc

main          EQU start@0
.data

.code
main PROC
    mov al, 72
    mov ah, 71
    mov ax, 0a0bh
    mov dx, 0eeah
    sub dx, ax
    exit
main ENDP
END main