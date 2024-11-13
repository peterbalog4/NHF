#ifndef UF_H_INCLUDED
#define UF_H_INCLUDED

int sorokat_szamol(char *fajl);
void sztringet_nagybetusit(char *sztring);
int valaszt_tesztel(char *valasz);
char **ures_lista(int meret, int charsize);
void listat_kiir(char **lista, int meret);
void listat_fajlba_ir(char **lista, int meret,FILE *fp);
typedef struct ListaElem {char adat[52];struct ListaElem *kov;} ListaElem;
void lista_elejehez_beszur(ListaElem *eleje,int szam);
void lista_vegehez_hozzafuz(ListaElem *eleje, int szam);
ListaElem *L_listat_letrehoz(void);
void lancolt_listat_kiir(ListaElem *eleje);

#endif // UF_H_INCLUDED
