TITLE HW1 of 108502571                (hw1.ASM)
INCLUDE Irvine32.inc

.data
ChStrs  BYTE "  ****  "
        BYTE " *  **  "
        BYTE "    **  "
        BYTE "    **  "
        BYTE "    **  "
        BYTE "    **  "
        BYTE "    **  "
        BYTE " *******"
BitStrs BYTE 8 dup(?)

.code
print PROC USES esi ecx eax
    mov esi, OFFSET BitStrs
    mov ecx, LENGTHOF BitStrs

LP:
    mov al, [esi]
    call WriteChar
    inc esi
    loop LP

    call Crlf

    ret
print ENDP

change PROC USES ecx
    mov ecx, 8
    mov ebx, 0

L1:
    mov al, [esi]
    cmp al, ' '
    jz L2
    mov BitStrs[ebx], '1' ; [esi] > '*'
    jmp L3
L2: ; [esi] == ' '
    mov BitStrs[ebx], '0'
L3:
    inc esi
    inc ebx
    loop L1

    call print

    ret
change ENDP

main EQU start@0
main PROC
    mov ecx, 8
    mov esi, OFFSET ChStrs
LM:
    call change
    loop LM

    mov eax, 3000
    ; call Delay
    CALL WaitMsg

    exit
main ENDP
END main