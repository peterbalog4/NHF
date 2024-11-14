#ifndef UF_H_INCLUDED
#define UF_H_INCLUDED

int sorokat_szamol(char *fajl);
void sztringet_nagybetusit(char *sztring);
int valaszt_tesztel(char *valasz);
char **ures_lista(int meret, int charsize);
void listat_kiir(char **lista, int meret);
void listat_fajlba_ir(char **lista, int meret,FILE *fp);
char **listat_bovit(char **lista,int ujmeret,char *adat);
//void lista_elejehez_beszur(Recept *eleje,int szam);
//void lista_vegehez_hozzafuz(Recept *eleje, int szam);
//Recept*L_listat_letrehoz(void);
//void lancolt_listat_kiir(Recept *eleje);

#endif // UF_H_INCLUDED
