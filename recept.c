#include <stdio.h>
#include <stdlib.h>
#include "osszetevok.h"

typedef struct Recept{
    char nev[51];
    char **osszetevo_lista;
    char **el;
} Recept;

/*char **el_lista(int meret){
    char **el_lista;
    /* el_lista = malloc(meret*sizeof(char *));
    if (el_lista == NULL){
        printf("Memóriafoglalási hiba!");
        return NULL;
    }
    for(int i=0;i<meret;i++){
        el_lista[i] = malloc(201 * sizeof(char));
        if (el_lista[i] == NULL){
            printf("Memóriafoglalási hiba!");
            return NULL;
        }
    }

    el_lista = ;
    for(int i=0;i<meret;i++){
        printf("Add meg az elkészítési leírás %d. elemét \n ",i+1);
        scanf("%s",el_lista[i]);
    }
    return el_lista;

}*/

void uj_recept(){
    Recept uj;
    FILE *fp;
    int o_meret,el_meret;
    int valasztas,szamlalo = 0;
    int k = 0;
    printf("Add meg a recept nevét:");
    scanf("%s", &uj.nev);
    printf("Add meg az összetevők számát!");
    scanf("%d",&o_meret);
    char **o_lista = osszetevo_lista();
    char **uj_lista = ures_lista(o_meret,52);
    printf("Válaszd ki az összetevőket!\n Választás:");
    listat_kiir(o_lista,sorokat_szamol("osszetevok.txt"));
    while(szamlalo < o_meret){
        printf("Választás:");
        scanf("%d",&valasztas);
        uj_lista[k++] = o_lista[valasztas-1];
        szamlalo++;
    }
    uj.osszetevo_lista = uj_lista;

    printf("Hány lépésből álljon az elkészítési leírás?\nVálasztás:");
    scanf("%d",&el_meret);
    char **el;
    el = ures_lista(el_meret,201);
    for(int i=0;i<el_meret;i++){
        printf("Add meg az elkészítési leírás %d. elemét \n ",i+1);
        scanf("%s",el[i]);
    }

    fp = fopen("recept.txt","a");

    fprintf(fp,"%s",uj.nev);
    fprintf(fp, " | ");
    listat_fajlba_ir(uj.osszetevo_lista,o_meret,fp);
    fprintf(fp, " | ");
    listat_fajlba_ir(uj.el,el_meret,fp);
    fclose(fp);
    osszetevot_felszabadit(el,el_meret);
    osszetevot_felszabadit(o_lista,sorokat_szamol("osszetevok.txt"));
    osszetevot_felszabadit(uj_lista,o_meret);


}
