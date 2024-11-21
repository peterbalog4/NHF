#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "osszetevok.h"
#include "uf.h"
#include "debugmalloc.h"
#include "recept.h"

bool van_e_benne(char** o_lista,int o_meret,char *ezt){
    for(int i=0;i<o_meret;i++){
        if(strcmp(o_lista[i],ezt) == 0){
            return true;
        }
    }
    return false;
}


void innek_egy_kis(Recept **eleje,int recept_szam){
    char **van_benne;
    int valasz;
    int k=0,szamolo=0;
    van_benne = malloc(recept_szam*sizeof(char *));
    if (van_benne == NULL){
        printf("Memóriafoglalási hiba!");
        return;
    }
    for(int i=0;i<recept_szam;i++){
        van_benne[i] = malloc(52 * sizeof(char));
        if (van_benne[i] == NULL){
            printf("Memóriafoglalási hiba!");
            return;
        }
    }
    char keres[52];
    Recept *utolso = *eleje;
    printf("Mit szeretnél ma inni?");
    scanf("%s",keres);
    while(utolso->kov != NULL){
        if(van_e_benne(utolso->o_lista,utolso->o_meret,keres) == true){
            strcpy(van_benne[k++],utolso->nev);
            szamolo++;
        }
        utolso = utolso->kov;
    }
    if(szamolo == 0){
        printf("Nincs ilyen recept!\n");
        osszetevot_felszabadit(van_benne,recept_szam);
        return;
    }
    for(int i=0;i<szamolo;i++){
        printf("%d. %s\n",i+1,van_benne[i]);
    }
    printf("Ezekben a receptekben van %s, melyiket szeretnéd elkészíteni? \n Választás:",keres);
    scanf("%d",&valasz);
    valasz--;
    if(0 <=valasz && valasz < szamolo){
        Recept *mozgo = *eleje;
        while(mozgo->kov != NULL || strcmp(van_benne[valasz],mozgo->nev) != 0){
            mozgo = mozgo->kov;
        }
        receptet_kiir(mozgo);
    }
    else{
        printf("Hibás index!");
        fomenu();
    }
    osszetevot_felszabadit(van_benne,recept_szam);
}
