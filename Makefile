EXECUTABLES=ex1 ex1butbetter ex2 ex3 ex4 ex5
GCC_OPTIONS=gcc -fno-stack-protector -zexecstack -g

all: $(EXECUTABLES)

ex1: ex1.c
	gcc ex1.c -o ex1

ex1butbetter: ex1.c
	$(GCC_OPTIONS) ex1.c -o ex1butbetter

ex2: ex2.c
	$(GCC_OPTIONS) ex2.c -o ex2

ex3: ex3.c
	$(GCC_OPTIONS) -static ex3.c -o ex3

ex4: ex4.c
	$(GCC_OPTIONS) ex4.c -o ex4

ex5: ex5.c
	$(GCC_OPTIONS) ex5.c -o ex5

clean:
	rm -rf $(EXECUTABLES)
