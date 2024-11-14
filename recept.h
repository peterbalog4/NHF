#ifndef RECEPT_H_INCLUDED
#define RECEPT_H_INCLUDED

typedef struct Recept{char nev[51];char **o_lista;char **el_lista;struct Recept *kov;} Recept;
Recept *uj_recept(Recept *eleje);

#endif // RECEPT_H_INCLUDED
