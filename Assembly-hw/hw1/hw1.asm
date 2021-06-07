TITLE HW1 of 108502571                (hw1.ASM)
INCLUDE Irvine32.inc

.data
MyID DWORD ?
Digit0 BYTE 2
Digit1 BYTE 5
Digit2 BYTE 7
Digit3 BYTE 1

.code
main EQU start@0
main PROC
    mov eax, 0      ; eax(16 bits), give all the number to 0
    mov al, Digit0  ; eax the last half is ax, ax = ah + al
    ; BYTE: 4 bits, DWORD: 16 bits
    shl eax, 8      ; 16 bits shift to left for 2
    add al, Digit1  ; add the new number
    shl eax, 8      ;
    add al, Digit2  ;
    shl eax, 8      ;
    add al, Digit3  ;
    mov MyID, eax   ; copy eax to MyID

    ; mov ah, Digit0  ;
    ; shl ah, 2       ;
    ; add ah, Digit1  ;

    ; mov al, Digit2  ;
    ; shl al, 2       ;
    ; add al, Digit3  ;

    ; mov MyID, ax    ;

    ; movsx ax, Digit0    ;
    ; mov bh, Digit1    ;
    ; mov ch, Digit2    ;
    ; mov dh, Digit3    ;

    ; shl ax, 2   ;
    ; add ax, bh  ;
    ; shl ax, 2   ;
    ; add ax, ch  ;
    ; shl ax, 2   ;
    ; add ax, dh  ;

    ; mov MyID, ax;

    exit
main ENDP
END main