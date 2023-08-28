# stack-smashing-demo

## Meta
Some comments about the paper:
* Notice Phrack is NOT an academic journal; rather, it is an "e-zine" (online magazine) for hackers/hobbyists.
* Essentially a cookbook for hackers or troublemakers in general. Includes articles on hacking software, the [telecom networks](http://phrack.org/issues/5/9.html#article), [radio](http://phrack.org/issues/5/8.html#article), [picking locks](http://phrack.org/issues/1/6.html#article), making bombs and guns, as well as [world news](http://phrack.org/issues/2/3.html#article).
* The name Phrack comes from "phreaking" (hacking telephone networks to be able to take long distance calls for free), which was one of its original subject matters.
* Original Phrack article [here](http://phrack.org/issues/49/14.html#article) (1996).
* Article published by "Aleph One" (Elias Levy). He became a cofounder/CTO of SecurityFocus, which was sold to Symantec in 2002. Worked at Cisco 2013-2021, now a Principal Engineer at Google.

## Examples
### Example 1
Our stack layout (right before the `strcpy`), pretending we start at 0xFFFF (and ignoring `_start`):
```
[top]
0xFFFF: large_string[255]
...
0xFEFF: large_string[0]
0xFEF7: <return address of ex1.c:17>
0xFEF0: %rbp ["base poiner"/frame pointer]
0xFFEF: buffer[15]
...
0xFFE0: buffer[0]
```

### Example 2
```
[top]
<return address>
%rbp ["base poiner"/frame pointer]
buffer[1]
buffer[0]
```

#### Disassembly
```
(gdb) disassemble main
Dump of assembler code for function main:
   0x0000000000001182 <+0>:	endbr64 
   0x0000000000001186 <+4>:	push   %rbp
   0x0000000000001187 <+5>:	mov    %rsp,%rbp
   0x000000000000118a <+8>:	sub    $0x10,%rsp
   0x000000000000118e <+12>:	movl   $0x64,-0x4(%rbp)
   0x0000000000001195 <+19>:	mov    $0x0,%eax
   0x000000000000119a <+24>:	call   0x1149 <function>
   0x000000000000119f <+29>:	movl   $0xdc,-0x4(%rbp)
   0x00000000000011a6 <+36>:	mov    -0x4(%rbp),%eax
   0x00000000000011a9 <+39>:	mov    %eax,%esi
   0x00000000000011ab <+41>:	lea    0xe52(%rip),%rax        # 0x2004
   0x00000000000011b2 <+48>:	mov    %rax,%rdi
   0x00000000000011b5 <+51>:	mov    $0x0,%eax
   0x00000000000011ba <+56>:	call   0x1050 <printf@plt>
   0x00000000000011bf <+61>:	mov    $0x0,%eax
   0x00000000000011c4 <+66>:	leave  
   0x00000000000011c5 <+67>:	ret 
End of assembler dump.
```

### Example 3

#### Disassembly
```
(gdb) disassemble main
Dump of assembler code for function main:
   0x0000000000401745 <+0>:	endbr64 
   0x0000000000401749 <+4>:	push   %rbp
   0x000000000040174a <+5>:	mov    %rsp,%rbp
   0x000000000040174d <+8>:	sub    $0x10,%rsp
   0x0000000000401751 <+12>:	lea    0x968ac(%rip),%rax        # 0x498004
   0x0000000000401758 <+19>:	mov    %rax,-0x10(%rbp)
   0x000000000040175c <+23>:	movq   $0x0,-0x8(%rbp)
   0x0000000000401764 <+31>:	mov    -0x10(%rbp),%rax
   0x0000000000401768 <+35>:	lea    -0x10(%rbp),%rcx
   0x000000000040176c <+39>:	mov    $0x0,%edx
   0x0000000000401771 <+44>:	mov    %rcx,%rsi
   0x0000000000401774 <+47>:	mov    %rax,%rdi
   0x0000000000401777 <+50>:	call   0x446730 <execve>
   0x000000000040177c <+55>:	mov    $0x0,%eax
   0x0000000000401781 <+60>:	leave  
   0x0000000000401782 <+61>:	ret    
End of assembler dump.
(gdb) disassemble execve
Dump of assembler code for function execve:
   0x0000000000446730 <+0>:	endbr64 
   0x0000000000446734 <+4>:	mov    $0x3b,%eax
   0x0000000000446739 <+9>:	syscall 
   0x000000000044673b <+11>:	cmp    $0xfffffffffffff001,%rax
   0x0000000000446741 <+17>:	jae    0x446744 <execve+20>
   0x0000000000446743 <+19>:	ret    
   0x0000000000446744 <+20>:	mov    $0xffffffffffffffb8,%rcx
   0x000000000044674b <+27>:	neg    %eax
   0x000000000044674d <+29>:	mov    %eax,%fs:(%rcx)
   0x0000000000446750 <+32>:	or     $0xffffffffffffffff,%rax
   0x0000000000446754 <+36>:	ret    
End of assembler dump.
```

#### Modified steps
Because this is x86-64 and not 32-bit, some things are a bit different. 
1. Have the null terminated string "/bin/sh" somewhere in memory.
2. Have the address of the string "/bin/sh" somewhere in memory followed by a null long word.
3. Copy 0x3B into `%rax` (59, the system call for `execve`; see [here](https://filippo.io/linux-syscall-table/))
4. Copy the address of the string "/bin/sh" into `%rdi`.
5. Copy the address of the array containing the string "/bin/sh", then NULL, into `%rsi`.
6. Copy NULL into `%rdx`.
7. Execute the `syscall` instruction.

The original guide includes an `exit` should `execve` fail; this ended up being somewhat useful for debugging, so I included it.

### Example 4

### Example 5

## GDB friends
```
disassemble main
x/10x $sp
x/i $pc

set step-mode on
display/i $pc

si
info registers rsi
i r rsi
p (char *)0x55a4aa971154
```
