
# Ghost Hypervisor — Walkthrough

## Step 1 — Analyze the VM

Open the binary in:
- Ghidra
- Binary Ninja
- radare2

You will notice:
- a custom bytecode interpreter
- multiple VM opcodes
- suspicious memory writes

---

## Step 2 — Understand the Opcodes

Key instructions:

### MOV

Opcode:

    0x10

Format:

    [0x10][reg][value]

---

### ADD

Opcode:

    0x20

Format:

    [0x20][regA][regB]

---

### STORE

Opcode:

    0x30

Format:

    [0x30][regA][regB]

This writes:

    memory[regs[a]] = regs[b];

No bounds checking exists.

---

## Step 3 — Discover the Vulnerability

The STORE instruction allows arbitrary writes outside the VM memory array.

This enables corruption of nearby memory structures.

---

## Step 4 — Trigger secret()

The VM checks:

    if(regs[r] == 0xdeadbeef)

You must manipulate execution flow to reach secret().

---

## Step 5 — Craft Malicious Bytecode

Example payload structure:

```python
payload = bytes([
    0x10, 0x00, 0xff,
    0x10, 0x01, 0xef,
    0x30, 0x00, 0x01,
    0xff
])
```

---

## Step 6 — Recover Flag

When secret() executes, the encrypted flag is XOR-decrypted.

Recovered flag:

    flag{vm_escape_memory_corruption_master}
