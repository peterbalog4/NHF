#ifndef RECEPT_H_INCLUDED
#define RECEPT_H_INCLUDED

typedef struct Recept{char nev[51];char **o_lista;int o_meret;int **ml;char **el_lista;int el_meret;struct Recept *kov;} Recept;
void uj_recept(Recept **eleje);
void receptet_kiir(Recept *recept);
void receptet_felszabadit(Recept **eleje);
void recept_lista(Recept **eleje);
int recept_szamolo(Recept **eleje);
void recept_listaz(Recept **eleje);
void recept_torol(Recept **eleje,int mennyi);
#endif // RECEPT_H_INCLUDED
