#ifndef RECEPT_H_INCLUDED
#define RECEPT_H_INCLUDED

typedef struct Recept{char nev[51];char **o_lista;int o_meret;int **ml;char **el_lista;int el_meret;struct Recept *kov;} Recept;
void uj_recept(Recept **eleje);
void receptet_kiir(Recept *recept);

#endif // RECEPT_H_INCLUDED
