TITLE lab9_2                (lab9_2.ASM)
INCLUDE Irvine32.inc

.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO,
    dwExitCode: DWORD
Str_remove PROTO,
    pStart: PTR BYTE,
    nChars: DWORD

main EQU start@0
.data
target1 BYTE "108502571", 0
target2 BYTE "108502572", 0
target3 BYTE "999999999", 0

.code
main PROC

    INVOKE Str_remove, OFFSET target1, 5
    mov edx, OFFSET target1
    call WriteString
    call Crlf

    INVOKE Str_remove, OFFSET target2, 2
    mov edx, OFFSET target2
    call WriteString
    call Crlf

    INVOKE Str_remove, OFFSET [target2+1], 15
    mov edx, OFFSET target2
    call WriteString
    call Crlf

    call WaitMsg
    INVOKE ExitProcess, 0
    exit

main ENDP

Str_remove PROC,
    pStart: PTR BYTE, nChars: DWORD


    INVOKE Str_length, pStart
    mov ecx, eax

    .IF nChars <= ecx
        sub ecx, nChars
    .ENDIF

    mov esi, pStart     ;
    add esi, nChars
    mov edi, pStart     ; edi = esi >> 指標改變

    cld
    rep movsb           ; 只有這一行的loop
    mov BYTE PTR [edi], 0

Exit_proc:
    ret

Str_remove ENDP

END main