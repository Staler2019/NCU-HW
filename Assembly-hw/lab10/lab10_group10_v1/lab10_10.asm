TITLE lab10               (lab10.ASM)
INCLUDE Irvine32.inc

Str_copyN PROTO,
    source: PTR BYTE,
    target: PTR BYTE,
    maxChars: DWORD

main EQU start@0
.data
string_1 BYTE "108502571", 0
string_2 BYTE "108502572", 0

.code
main PROC

    INVOKE Str_copyN,
        OFFSET string_1,
        OFFSET string_2+9,
        (SIZEOF string_2)-1

    mov edx, OFFSET string_2
    call WriteString
    call Crlf
    call WaitMsg
    exit

main ENDP

Str_copyN PROC USES eax ecx esi edi,
    source: PTR BYTE,
    target: PTR BYTE,
    maxChars: DWORD


    mov ecx, maxChars
    mov esi, source
    mov edi, target
    cld
    rep movsb                                                   ; TODO: I don't know why to use movsb with how edi &esi
    ; mov BYTE PTR [edi], 0
    mov al, 0
    stosb   ; ax: byte: add 0 to string
    ; 從eax最後端拿對應的byte數

    ret

Str_copyN ENDP

END main