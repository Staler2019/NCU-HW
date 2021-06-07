@echo off
REM make
REM Assembles and links the 32-bit ASM program into .exe which can be used by WinDBG
REM Uses MicroSoft Macro Assembler version 6.11 and 32-bit Incremental Linker version 5.10.7303
REM Created by Huang

REM delete related files
REM del week05.lst	REM week05可以替換成.asm檔的檔名
REM del week05.ilk
del week05.pdb
del week05.exe

setlocal
set INCLUDE=C:\WINdbgFolder\windbg\;	REM 這裡要設成WINdbgFolder的路徑
set LIB=C:\WINdbgFolder\windbg\;
set PATH=C:\WINdbgFolder\windbg\;

REM /c          assemble without linking
REM /coff       generate object code to be linked into flat memory model
REM /Zi         generate symbolic debugging information for WinDBG
REM /Fl		Generate a listing file


ML /c /coff /Zi   week05.asm
if errorlevel 1 goto terminate

REM /debug              generate symbolic debugging information
REM /subsystem:console  generate console application code
REM /entry:start        entry point from WinDBG to the program
REM                           the entry point of the program must be _start

REM /out:%1.exe         output %1.exe code
REM %1.obj              input %1.obj
REM Kernel32.lib        library procedures to be invoked from the program
REM irvine32.lib
REM user32.lib

LINK /INCREMENTAL:no /debug /subsystem:console /entry:start /out:week05.exe week05.obj Kernel32.lib irvine32.lib user32.lib
if errorlevel 1 goto terminate

del week05.obj

REM Display all files related to this program:
DIR week05.*

:terminate

pause
endlocal