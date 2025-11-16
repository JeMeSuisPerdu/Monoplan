# Mon petit Makefile minimaliste
launch: test_jalon2.c mod_cell_form/cell.c mod_cell_form/calcul_sheet.c stack/stack.c
	gcc -I mod_cell_form -I stack -I log test_jalon2.c mod_cell_form/cell.c mod_cell_form/calcul_sheet.c stack/stack.c -o launch -lm

clean:
	rm -f launch