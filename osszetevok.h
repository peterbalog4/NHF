#ifndef OSSZETEVOK_H_INCLUDED
#define OSSZETEVOK_H_INCLUDED

typedef struct Osszetevo{char **o_lista;int meret;} Osszetevo;
void uj_osszetevo(Osszetevo *lista,int meret);
Osszetevo osszetevo_lista();
void osszetevot_felszabadit(char **osszetevok, int meret);
void osszetevot_torol(Osszetevo *lista,int meret);
void osszetevot_fajlba_ir(Osszetevo lista);
#endif // OSSZETEVOK_H_INCLUDED
