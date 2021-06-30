TITLE lab4                (lab4.ASM)
INCLUDE Irvine32.inc

.data
    myID BYTE "108502572"
    size_ID = 9
    myID2 BYTE "108502571"
    size_ID2 = 9

.code
Convert PROC USES eax
; Convert change myID valus 0-A 1-b and so on
    L1:
        mov al, [esi]
        add al, 17
        mov [esi], al

        inc esi
        loop L1
    ret
Convert ENDP

Convert2 PROC
; Convert2 do the same thing as Convert
    push eax
    L1:
        mov al, [esi]
        add al, 17
        mov [esi], al

        inc esi
        loop L1
    pop eax
    ret
Convert2 ENDP

main EQU start@0
main PROC
    mov eax, 9999h      ; The value of eax cannot be changed
    mov ebx, 9999h      ; The value of ebx cannot be changed
    mov edx, 9999h      ; The value of edx cannot be changed

    mov esi, OFFSET myID
    mov ecx, size_ID
    call Convert

    mov esi, OFFSET myID2
    mov ecx, size_ID2
    call Convert2

    exit
main ENDP
END main