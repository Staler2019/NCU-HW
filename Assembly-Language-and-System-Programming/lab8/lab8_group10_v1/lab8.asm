TITLE lab8                (lab8.ASM)
INCLUDE Irvine32.inc

main EQU start@0

.stack 4096
ExitProcess PROTO,
    swExitCode: DWORD
FindLargest PROTO,
    aPtr: PTR SDWORD,
    arraySize: DWORD

.data
Ex1Array SDWORD 105522063, 108502571, 108502572
Ex2Array SDWORD -105522063, -108502571, -108502572

.code
main PROC
    INVOKE FindLargest, OFFSET Ex1Array, LENGTHOF Ex1Array
    INVOKE FindLargest, OFFSET Ex2Array, LENGTHOF Ex2Array

    call WaitMsg
    INVOKE ExitProcess, 0
    exit
main ENDP

FindLargest PROC,
    aPtr: PTR SDWORD, arraySize: DWORD  ;**STACK**TOP
    PUSH esi                            ;esi
    PUSH ecx                            ;ecx
    MOV eax, 80000000h ;TODO
    MOV esi, aPtr
    MOV ecx, arraySize

L1: CMP eax, [esi]
    JG L2
    MOV eax, [esi]

L2: ADD esi, 4
    LOOP L1

    CALL WriteInt
    CALL Crlf

    POP ecx
    POP esi
    RET
FindLargest ENDP

END main