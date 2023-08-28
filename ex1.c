// A simple buffer overflow

#include <string.h>

void function(char *str){
    char buffer[16];
    strcpy(buffer,str); // this statement does _not_ error (why?)
    return; // this statement will (why?)
}

int main() {
    char large_string[256];
    for(int i = 0; i < 255; i++)
        large_string[i] = 'A';

    function(large_string);

    return 0;
}
