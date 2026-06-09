A military contractor developed a classified virtual machine called:

“Ghost Hypervisor”

It was used to execute untrusted code in isolated environments.

However, during a security audit, engineers discovered something disturbing:

The VM behaves differently every time it runs
Certain memory regions are “not supposed to exist”
Some instructions do things not documented anywhere

The system was immediately shut down.

Only the VM binary remains.

🎯 Challenge Description (What player sees)
# Ghost Hypervisor

A classified virtual machine implementation was recovered from a secure facility.

It executes unknown bytecode in a sandboxed environment.

Security analysts believe it may contain a critical design flaw.

Your objective:
- Understand how the VM processes instructions
- Analyze its memory behavior
- Find a way to escape execution
- Retrieve the hidden flag
📦 Files Given to Player
vm → virtual machine binary
program.bin → unknown bytecode
flag.enc → encrypted flag
README.md → story