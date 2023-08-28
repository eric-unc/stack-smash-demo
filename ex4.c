// ex3, but purely in Assembly!
// info on x64 stacks/calling conventions -> https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64.html
int main(){
    asm volatile(
            // We use a call to get the addr of the string in memory (on the stack)
            // Notice by using labels, we don't need to do any math manually...

            "jmp eric_call_lbl\n\t"

            "eric_after_jmp_lbl: pop %rsi\n\t"

            // & to "/bin/sh", then NULL
            "pushq $0\n\t"
            "pushq %rsi\n\t"

            "movq $0x3b, %rax\n\t"
            "movq %rsp, %rdi\n\t"
            "leaq 0(%rdi), %rsi\n\t"
            "movq 0(%rdi), %rdi\n\t"
            "mov $0, %rdx\n\t"

            // so at this point:
            // %rax = 0x3b [the syscall number]
            // %rdi = name[0]
            // %rsi = name
            // %rdx = 0 (null)
            "syscall\n\t"

            // exit if execve fails
            "movq $0x3c, %rax\n\t"
            "movq $0, %rbx\n\t"
            "syscall\n\t"

            "eric_call_lbl: call eric_after_jmp_lbl\n\t"
            ".string \"/bin/sh\""
    );
}
