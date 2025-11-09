# Mon petit Makefile minimaliste
launch: main.c mod_list/list.c
	gcc -I mod_list main.c mod_list/list.c -o launch

clean:
	rm -f launch