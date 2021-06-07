TITLE HW3 BONUS of 108502571                (hw3.ASM)
INCLUDE Irvine32.inc

; return value in eax
CountMatches    PROTO,
    x:          ptr sdword,
    y:          ptr sdword,
    lengthInt:  dword


.data
array1  sdword  2, 4, -3, -9, 7, 1, 8
array2  sdword  2, -3, 6, 0, 7, 8, 5
string1 byte    " matches", 0h

.code
main    EQU     start@0
main    PROC


        INVOKE CountMatches,
                OFFSET array1,
                OFFSET array2,
                LENGTHOF array1
        ; print out ans
        call    WriteInt
        mov     edx, OFFSET string1
        call    WriteString
        call    Crlf
        call    WaitMsg

        exit
main    ENDP

CountMatches    PROC    USES    ecx esi edi,
    x:          ptr sdword,
    y:          ptr sdword,
    lengthInt:  dword


        mov     eax, 0
        mov     ecx, lengthInt
        mov     esi, x

        ; outer loop L11
L11:    push    ecx
        mov     ecx, lengthInt
        mov     ebx, [esi]
        mov     edi, y

        ; inner loop L1
L1:     push    eax
        mov     eax, [edi]

        .IF     ebx == eax
                pop     eax
                inc     eax
        .ELSE
                pop     eax
        .ENDIF

        add     edi, 4
        loop    L1
        ; inner loop L1 end

        add     esi, 4
        pop     ecx
        loop    L11
        ; outer loop L11 end

        ret

CountMatches ENDP

END main