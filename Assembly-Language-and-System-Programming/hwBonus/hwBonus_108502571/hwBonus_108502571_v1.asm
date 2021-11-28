TITLE HWBONUS of 108502571                (hwBonus.ASM)
INCLUDE Irvine32.inc

; return value in eax
Str_nextWord    PROTO,
    pString:    ptr byte,
    delimiter:  byte


.data
testStr byte    "ABC\DE\FGHIJK\LM", 0

.code
main    EQU     start@0
main    PROC


        call    Clrscr
        mov     edx, OFFSET testStr
        call    WriteString
        call    Crlf

        mov     esi, OFFSET testStr

L1:     INVOKE  Str_nextWord, esi, "\"
        jnz     Exit_prog
        mov     edx, eax
        mov     esi, edx
        call    WriteString
        call    Crlf
        jmp     L1

Exit_prog:
        call    WaitMsg
        exit

main    ENDP

Str_nextWord    PROC    USES    esi edi,
    pString:    ptr byte,
    delimiter:  byte


        mov     edi, pString
        mov     eax, 0

L1:     mov     al, [edi]
        inc     edi

        ; end loop in main by ZF=0
        .IF     al == 0
                or      al, 1
                ret
        .ENDIF
        .IF     al == delimiter
                mov     eax, edi
                ret
        .ENDIF
        jmp     L1

Str_nextWord    ENDP

END main