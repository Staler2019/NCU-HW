TITLE lab3                (lab3.ASM)
INCLUDE Irvine32.inc

.data
ninenine    byte    9 DUP(?)

.code
main    EQU     start@0
main    PROC


        mov     ecx, LENGTHOF ninenine  ; loop count
        mov     esi, OFFSET ninenine    ; mov esi, [ninenine]
        mov     ebx, 9                  ; make a var ebx as 9 - init

L1:     mov     [esi], ebx              ; let &esi[k] to be ebx
L2:     inc     esi
        add     ebx, 9                  ; add 9 to ebx
        loop    L1

        exit

main    ENDP
END     main