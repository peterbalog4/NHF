#include <stdio.h>
#include <stdlib.h>
#include "osszetevok.h"
#include "uf.h"
#include "debugmalloc.h"


typedef struct osszetevo{
    char nev[52];
    int ml;
} osszetevo;

typedef struct Recept{
    char nev[51];
    char **o_lista;
    char **el_lista;
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

    char **o_lista = malloc(o_meret*sizeof(char *));
    if (o_lista == NULL){
        printf("Memóriafoglalási hiba!");
        exit(1);
    }
    for(int i=0;i<o_meret;i++){
        o_lista[i] = malloc(52 * sizeof(char));
        if (o_lista[i] == NULL){
            printf("Memóriafoglalási hiba!");
            exit(2);
        }
    }

    if(o_meret >= 0){
        listat_kiir(lista,meret);
        for(int i=0;i < o_meret;i++){
            printf("Választás:");
            scanf("%d",&valasz);
            strcpy(o_lista[i],lista[valasz-1]);
        }
    }
    else{
        exit(3);
    }

    int el_meret;

    printf("Hány lépés legyen az elkészítési leírás?");
    scanf("%d",&el_meret);

    char **el_lista = malloc(el_meret*sizeof(char *));
    if (el_lista == NULL){
        printf("Memóriafoglalási hiba!");
        exit(4);
    }
    for(int i=0;i<el_meret;i++){
        el_lista[i] = malloc(201 * sizeof(char));
        if (el_lista[i] == NULL){
            printf("Memóriafoglalási hiba!");
            exit(5);
        }
    }

    if(el_meret >= 0){
        for(int i=0;i < el_meret;i++){
            printf("%d. lépés:",i+1);
            scanf("%200s", el_lista[i]);
        }
    }
    else{
        exit(6);
    }

    uj->o_lista = o_lista;
    uj->el_lista = el_lista;

    uj->kov = eleje;
    eleje = uj;

    osszetevot_felszabadit(lista,meret);
    osszetevot_felszabadit(el_lista,el_meret);
    osszetevot_felszabadit(o_lista,o_meret);

    return uj;
}
