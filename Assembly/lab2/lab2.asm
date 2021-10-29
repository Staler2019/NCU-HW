TITLE lab2                (lab2.ASM)
INCLUDE Irvine32.inc

.data
Val1 SBYTE  03h
Val2 SBYTE  02h
Val3 SBYTE  8fh
Rval SWORD  ?

.code
main EQU start@0
main PROC
    movsx ax, Val1  ; ax = Val1
    movsx bx, Val2  ; bx = Val2
    ;movsx cx, Val3  ; cx 2 Val3

    ;   caculate Rval = -(Val3-14*(Val1+Val2)).
    add ax, bx      ; ax = Val1 + Val2
    mov bx, ax      ; bx = ax
    shl ax, 4       ; ax *= 16
    shl bx, 1       ; bx *=2
    sub ax, bx      ; ax -= bx
    ; ax = 14*(Val1+Val2)
    sub cx, ax      ; cx -= ax
    ;sub Rval, ax
    ; cx = Val3-14*(Val1+Val2)
    neg cx          ; cx *= (-1)
    ;neg Rval
    mov Rval, cx    ;

    exit
main ENDP
END main