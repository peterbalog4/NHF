#ifndef UF_H_INCLUDED
#define UF_H_INCLUDED

int sorokat_szamol(char *fajl);
void sztringet_nagybetusit(char *sztring);
int valaszt_tesztel(char *valasz);
void listat_kiir(char **lista, int meret);
void listat_fajlba_ir(char **lista, int meret,FILE *fp);
void pt_foglal(char **lista,int meret);
#endif // UF_H_INCLUDED
