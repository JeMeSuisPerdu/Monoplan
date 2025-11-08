# Monoplan
pour merge les branches : git config pull.rebase false

Cmd compilation séparée en prenant en compte le dossier mod_list (I pour inclure le dossier): gcc -I mod_list main.c mod_list/list.c -o 
Ou alors mettre : #include "mod_list/list.h" dans main.c (solution retenu pour le moment)
