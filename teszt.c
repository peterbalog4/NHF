#include <stdio.h>
#include <stdlib.h>
#include "osszetevok.h"
#include "uf.h"
#include "debugmalloc.h"

typedef struct Recept{
    char nev[51];
    char **o_lista;
    int o_meret;
    int **ml;
    char **el_lista;
    int el_meret;
    struct Recept *kov;
} Recept;

Recept *uj_recept(Recept *eleje){
    Recept *uj = (Recept*)malloc(sizeof(Recept));
    char**lista = osszetevo_lista();
    int meret = sorokat_szamol("osszetevok.txt");

    printf("Add meg a recept nevét:");
    scanf("%50s",uj->nev);

    int o_meret,valasz;
    printf("Hány összetevő legyen?");
    scanf("%d", &o_meret);

    uj->o_lista = malloc(o_meret*sizeof(char *));
    if (uj->o_lista == NULL){
        printf("Memóriafoglalási hiba!");
        exit(1);
    }
    for(int i=0;i<o_meret;i++){
        uj->o_lista[i] = malloc(52 * sizeof(char));
        if (uj->o_lista[i] == NULL){
            printf("Memóriafoglalási hiba!");
            exit(2);
        }
    }

    uj->ml = malloc(o_meret*sizeof(int *));
    if (uj->ml == NULL){
        printf("Memóriafoglalási hiba!");
        exit(7);
    }
    for(int i=0;i<o_meret;i++){
        uj->ml[i] = malloc(sizeof(int));
        if (uj->ml[i] == NULL){
            printf("Memóriafoglalási hiba!");
            exit(8);
        }
    }

    if(o_meret >= 0){
        listat_kiir(lista,meret);
        for(int i=0;i < o_meret;i++){
            printf("Választás:");
            scanf("%d",&valasz);
            strcpy(uj->o_lista[i],lista[valasz-1]);
            printf("Hány ml-t?");
            scanf("%d",uj->ml[i]);
        }
    }
    else{
        exit(3);
    }

    int el_meret;

    printf("Hány lépés legyen az elkészítési leírás?");
    scanf("%d",&el_meret);

    uj->el_lista = malloc(el_meret*sizeof(char *));
    if (uj->el_lista == NULL){
        printf("Memóriafoglalási hiba!");
        exit(4);
    }
    for(int i=0;i<el_meret;i++){
        uj->el_lista[i] = malloc(201 * sizeof(char));
        if (uj->el_lista[i] == NULL){
            printf("Memóriafoglalási hiba!");
            exit(5);
        }
    }

    if(el_meret >= 0){
        for(int i=0;i < el_meret;i++){
            printf("%d. lépés:",i+1);
            scanf("%200s", uj->el_lista[i]);
        }
    }
    else{
        exit(6);
    }
    uj->o_meret = o_meret;
    uj->el_meret = el_meret;


    uj->kov = eleje;
    eleje = uj;

    osszetevot_felszabadit(lista,meret);
    //osszetevot_felszabadit(el_lista,el_meret);
    //osszetevot_felszabadit(o_lista,o_meret);

    return uj;
}
void receptet_kiir(Recept *recept){
    if (recept != NULL) {
        printf("Név: %s\n", recept->nev);
        printf("Összetevők: \n");
        for(int i=0;i<recept->o_meret;i++){
            printf("%s %d ml \n",recept->o_lista[i],recept->ml[i]);
        }
        printf("Elkészítési leírás: \n");
        for(int i=0;i<recept->el_meret;i++){
            printf("%s \n",recept->el_lista[i]);
        }
    }
}
int main(){
    system("chcp 65001 >nul");
    Recept *eleje = NULL;
    Recept *uj = uj_recept(eleje);

    receptet_kiir(uj);
    osszetevot_felszabadit(uj->el_lista,uj->el_meret);
    osszetevot_felszabadit(uj->o_lista,uj->o_meret);
    for(int i=0;i<uj->o_meret;i++){
        free(uj->ml[i]);
    }
    free(uj->ml);
    free(uj);
}
