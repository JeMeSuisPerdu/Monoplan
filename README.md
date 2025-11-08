# Monoplan
pour merge les branches : git config pull.rebase false

Cmd compilation séparée en prenant en compte le dossier mod_list (I pour inclure le dossier) + les logs: gcc -I mod_list -I mod_log main.c mod_list/list.c -o launch
Mettre : #include "mod_list/list.h" dans main.c 
