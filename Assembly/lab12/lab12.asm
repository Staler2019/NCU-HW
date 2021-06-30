TITLE       lab12       (lab12.ASM)

INCLUDE     Irvine32.inc
main        EQU start@0
BoxWidth    =   7
BoxHeight   =   7

.data
boxTop          BYTE    0dah, (BoxWidth - 2) DUP(0c4h), 0bfh
boxBody         BYTE    0b3h, (BoxWidth - 2) DUP(' '), 0b3h
boxBottom       BYTE    0c0h, (BoxWidth - 2) DUP(0c4h), 0d9h

outputHandle    DWORD   0
bytesWritten    DWORD   0
count           DWORD   0
xyPosition      COORD   <10,5>

cellsWritten    DWORD   ?
attributes0     WORD    BoxWidth DUP(0bh)
attributes1     WORD    (BoxWidth-1) DUP(0ah), 0eh
attributes2     WORD    BoxWidth DUP(0ch)


.code
main PROC

    INVOKE  GetStdHandle,
                STD_OUTPUT_HANDLE   ; Get the console ouput handle
    mov     outputHandle, eax       ; save console handle
    call    Clrscr
    ; 畫出box的第一行

    ; OFFSET with global variable
    ; ADDR with local variable
    INVOKE  WriteConsoleOutputAttribute,
                outputHandle,
                ADDR attributes0,
                BoxWidth,
                xyPosition,
                ADDR cellsWritten

    INVOKE  WriteConsoleOutputCharacter,
                outputHandle,       ; console output handle
                ADDR boxTop,        ; pointer to the top box line
                BoxWidth,           ; size of box line
                xyPosition,         ; coordinates of first char
                ADDR bytesWritten   ; output count

    inc     xyPosition.Y            ; 座標換到下一行位置

    mov     ecx, (BoxWidth-2)       ; number of lines in body



L1: push    ecx     ; save counter 避免invoke 有使用到這個暫存器
    INVOKE  WriteConsoleOutputAttribute,
                outputHandle,
                ADDR attributes1,
                BoxWidth,
                xyPosition,
                ADDR cellsWritten

    INVOKE  WriteConsoleOutputCharacter,
                outputHandle,
                ADDR boxBody,       ; pointer to the box body
                BoxWidth,
                xyPosition,
                ADDR cellsWritten

    inc     xyPosition.Y            ; next line
    pop     ecx                     ; restore counter
    loop    L1

    INVOKE  WriteConsoleOutputAttribute,
                outputHandle,
                ADDR attributes2,
                BoxWidth,
                xyPosition,
                ADDR cellsWritten

    ; draw bottom of the box
    INVOKE  WriteConsoleOutputCharacter,
                outputHandle,
                ADDR boxBottom,     ; pointer to the bottom of the box
                BoxWidth,
                xyPosition,
                ADDR cellsWritten

    call    WaitMsg
    call    Clrscr
    exit
main ENDP
END main