TITLE lab9_1                (lab9_1.ASM)
INCLUDE Irvine32.inc

.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO,
    dwExitCode: DWORD
DifferentInputs PROTO,
    v1: DWORD, v2: DWORD, v3: DWORD

main EQU start@0
.data
.code
main PROC
    INVOKE DifferentInputs, 2, 2, 3
    INVOKE DifferentInputs, 2, 3, 2
    INVOKE DifferentInputs, 3, 5, 5
    INVOKE DifferentInputs, 2, 2, 2
    INVOKE DifferentInputs, 104522064, 108502571, 108502572

    CALL WaitMsg
    INVOKE ExitProcess, 0
    exit
main ENDP

DifferentInputs PROC,
    v1: DWORD, v2: DWORD, v3: DWORD
    MOV eax, v1
    CMP v2, eax
    JE Label_Equal  ; if equal -> jmp Label_Equal
    CMP v3, eax
    JE Label_Equal
    MOV eax, v2
    CMP v3, eax
    JE Label_Equal
    MOV eax, 1
    JMP Exit_Label

Label_Equal:
    MOV eax, 0

Exit_Label:
    CALL DumpRegs
    RET
DifferentInputs ENDP

END main