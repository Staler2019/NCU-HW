TITLE lab5                (lab5.ASM)
INCLUDE Irvine32.inc

.data
    myID BYTE "108502572"   ; leader
    myID2 BYTE "108502571"  ; member
    size_ID = 9             ; length of ID
    result byte 9 DUP(?)    ; save the result for cmp

.code
main EQU start@0
main PROC
    mov ecx, LENGTHOF myID  ; loop count
    mov esi, OFFSET myID    ; myID stores in esi
    mov edi, OFFSET myID2   ; myID stores in edi
    mov ebx, 0
L1:
    mov al, [esi]
    cmp al, [edi]
    jz L2
    jc L4
    jmp L3

L2: ; D>S
    mov result[ebx], 42h
    jmp L5

L3: ; D=S
    mov result[ebx], 41h
    jmp L5

L4: ; D<S
    mov result[ebx], 43h
    jmp L5

L5: ; new loop
    inc esi
    inc edi
    inc ebx
    loop L1

    exit
main ENDP
END main