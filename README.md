# CTF Challenge Set

A collection of Capture-The-Flag challenges with questions, encrypted flags, build scripts, Docker configurations, and authored solutions/walkthroughs.

## Features
- **Crypto - RSA (Medium)**: badly encrypted flag using a weak RSA modulus with one small prime; factor via trial/Fermat, then decrypt (writeup included).
- **Crypto - multi-layer crypto (Hard)**: multi-layer encryption challenge with challenge source and solution notes.
- **Binary - Quantum Vault (`q_m`)**: C binary with a `read`-length exploit; integer overflow in `len * 4` leads to a RIP overwrite to a `hidden()` decrypt routine (reads `flag.enc`). pwntools exploit included.
- **Binary - Ghost Hypervisor (`q_h`)**: custom bytecode vault (VM) with opcodes to load registers, add, store to memory, and a `secret()` flag decrypt when a register holds `0xdeadbeef`; pwntools bytecode included.
- Each binary ships with a **Dockerfile**, build script, question, encrypted flag, and a written WALKTHROUGH.

## Tech Stack
- Crypto: Python (RSA, multi-layer ciphers)
- Binary: C, pwntools (Python), Docker

## Project Structure
```
ctf/
├── crypto/
│   ├── chal1_medium_rsa/          # question, output, flag, solution
│   └── chal2_hard_multi_layer/    # challenge.py, flag, solution
└── binnary/ctf/
    ├── q_m/   # chall.c, build.sh, Dockerfile, solve.py, WALKTHROUGH
    └── q_h/   # vm.c, build.sh, solve.py, WALKTHROUGH
```

## Installation
Crypto requires Python with PyCrypto/PyCryptodome (`pip install pycryptodome`). Binary challenges require `pip install pwntools` and a C compiler (binary provided in the repo build or via `build.sh`).

## Usage
- Crypto: run `solution.txt` steps / challenge script to recover the flag.
- Binary: `build.sh` (or `docker build`), then run `python solve.py` against the local binary to capture the flag.

Author write-ups: each challenge's `WALKTHROUGH.md` / `solution.txt` walks through enumeration, vulnerability discovery, and exploitation.