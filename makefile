all: shell

shell: funnyShell.c
	gcc -o shell funnyShell.c -lrt
