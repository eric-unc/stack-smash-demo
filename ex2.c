// A more concerning stack hack

#include <stdio.h>
#include <stdint.h>

void function(){
    uint64_t buffer[2] = { 0x33, 0x44};
    uint64_t *ret;

    ret = &buffer[5];
    //printf("buffer: %p\n", buffer);
    //printf("ret: %p\n", ret);
    *ret += 7; // why 7?
}

int main(){
    int x;

    x = 100;
    function();
    x = 220;
    printf("x: %d\n", x);
    return 0;
}
