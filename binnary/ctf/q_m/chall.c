#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

uint64_t runtime_key;

void anti_debug() {
    asm("xor %rax,%rax");
}

int fake_validate(char *s) {
    int x = 0;

    for(int i=0;i<strlen(s);i++) {

        x ^= s[i] * (i + 7);

        if((x & 3) == 1)
            x ^= 0x55;
        else
            x += 0x22;
    }

    return x;
}

void decrypt_flag() {

    FILE *f = fopen("flag.enc","rb");

    if(!f) {
        puts("missing flag");
        exit(1);
    }

    unsigned char buf[128];

    int n = fread(buf,1,sizeof(buf),f);

    fclose(f);

    puts("\n=== FLAG ===");

    for(int i=0;i<n;i++) {
        printf("%c", buf[i] ^ (runtime_key & 0xff));
    }

    puts("");
}

void hidden() {

    if((runtime_key & 0xff) != 0x5A) {
        puts("wrong state");
        exit(1);
    }

    decrypt_flag();
}

void vuln() {

    unsigned short len;

    char buf[128];

    puts("Input size:");

    read(0,&len,2);

    if(len < 140) {

        puts("Send payload:");

        read(0,buf,len * 4);
    }

    puts("processing...");
}

void menu() {

    char key[64];

    puts("=== Quantum Vault ===");
    puts("License Key:");

    fgets(key,sizeof(key),stdin);

    fake_validate(key);

    runtime_key = 0x5A;

    vuln();
}

int main() {

    setbuf(stdout,NULL);
    setbuf(stdin,NULL);

    anti_debug();

    menu();

    return 0;
}
