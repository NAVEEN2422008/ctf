#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define MEM_SIZE 256
#define CODE_SIZE 512

uint8_t memory[MEM_SIZE];
uint8_t code[CODE_SIZE];

uint64_t regs[4];

void secret() {
    FILE *f = fopen("flag.enc", "rb");

    if(!f) {
        puts("missing flag");
        exit(1);
    }

    unsigned char buf[128];

    int n = fread(buf,1,sizeof(buf),f);

    fclose(f);

    puts("\\n=== FLAG ===");

    for(int i=0;i<n;i++) {
        printf("%c", buf[i] ^ 0x37);
    }

    puts("");
}

void execute(size_t size) {

    size_t ip = 0;

    while(ip < size) {

        uint8_t op = code[ip++];

        if(op == 0x10) {

            uint8_t r = code[ip++];
            uint8_t val = code[ip++];

            regs[r] = val;
        }

        else if(op == 0x20) {

            uint8_t a = code[ip++];
            uint8_t b = code[ip++];

            regs[a] += regs[b];
        }

        else if(op == 0x30) {

            uint8_t a = code[ip++];
            uint8_t b = code[ip++];

            memory[regs[a]] = regs[b];
        }

        else if(op == 0x40) {

            uint8_t r = code[ip++];

            if(regs[r] == 0xdeadbeef) {
                secret();
            }
        }

        else if(op == 0xff) {
            break;
        }
    }
}

int main() {

    setbuf(stdout,NULL);
    setbuf(stdin,NULL);

    puts("=== Ghost Hypervisor ===");
    puts("Send bytecode:");

    ssize_t n = read(0, code, CODE_SIZE);

    if(n <= 0) {
        return 0;
    }

    execute(n);

    return 0;
}
