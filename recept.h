#ifndef RECEPT_H_INCLUDED
#define RECEPT_H_INCLUDED

typedef struct Recept{char nev[51];char **o_lista;int o_meret;int **ml;char **el_lista;int el_meret;struct Recept *kov;} Recept;
void uj_recept(Recept **eleje);
char** elvalaszt(const char* string, const char* stop, int* hossz);
void receptet_kiir(Recept *recept);
void receptet_felszabadit(Recept **eleje);
void recept_lista(Recept **eleje);
int recept_szamolo(Recept **eleje);
int recept_listaz(Recept **eleje);
void recept_torol(Recept **eleje,int mennyi);
int recept_szamolo(Recept **eleje);
#endif // RECEPT_H_INCLUDED
