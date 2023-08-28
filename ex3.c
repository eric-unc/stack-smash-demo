// Simple replacing the current program with a Shell
// This is what we want to inject!
#include <unistd.h>

int main(){
    char *name[2];
    name[0] = "/bin/sh";
    name[1] = NULL;
    execve(name[0], name, NULL);
    return 0;
}
