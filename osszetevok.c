#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>
#include "uf.h"

// Megjegyzések a kódhoz:
// 1. Minden összetevő sztring 52 méretű. A felhasználónak 50 karakter lett "megígérve". A sorokat_szamol függvényem \n karaktereket számol így ez kell,hogy
// minden sztring végén ott legyen. Így a lezáró nullával együtt minden összetevő sztring 50+1+1 méretű.
// 2. A segédfüggvények az uf.c fájlban vannak.

// NTS: Fájlkezelést javítani!!! || Fájlt az elején beolvassa, végén fájlba ír

void uj_osszetevo(void){
    bool van_e;
    do{
        FILE *fp;
        fp = fopen("osszetevok.txt", "a");
        char valasz[5];
        char ujosszetevo[51];
        printf("Van még új összetevő?");
        scanf("%s", &valasz);
        sztringet_nagybetusit(valasz);
        if(valaszt_tesztel(valasz)  == 1){
            printf("Add meg az új összetevőt:");
            scanf("%s",&ujosszetevo);
            van_e = true;
            //strcat(ujosszetevo, "\n");
            fprintf(fp,"%s\n",ujosszetevo);
        }else if(valaszt_tesztel(valasz) == 0) {
            fclose(fp);
            van_e = false;
        }
        else{
            printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
            van_e = true;
        }
    }while(van_e);
}

char **osszetevo_lista(){
    FILE *fp;
    char **osszetevok;
    int meret = sorokat_szamol("osszetevok.txt");
    fp = fopen("osszetevok.txt","r");
    if (fp == NULL) {
        printf("Fájlkezelési hiba! \n");
        return NULL;
    }
    osszetevok = malloc(meret*sizeof(char *));
    if (osszetevok == NULL){
        printf("Memóriafoglalási hiba!");
        return NULL;
    }
    for(int i=0;i<meret;i++){
        osszetevok[i] = malloc(52 * sizeof(char));
        if (osszetevok[i] == NULL){
            printf("Memóriafoglalási hiba!");
            return NULL;
        }
        fgets(osszetevok[i],52,fp);

    }
    fclose(fp);
    return osszetevok;
}

void osszetevot_felszabadit(char **osszetevok, int meret){
    for(int i=0;i<meret;i++){
        free(osszetevok[i]);
    }
    free(osszetevok);
}

void osszetevot_torol(){
    int meret = sorokat_szamol("osszetevok.txt");
    char **lista = osszetevo_lista();
    int valasztas;
    FILE *fp;
    fp = fopen("osszetevok.txt","w");
    bool van_e = true;
    char valasz[5];
    while(van_e == true){
        printf("Van még törlendő elem?");
        scanf("%s",&valasz);
        if(valaszt_tesztel(valasz) == 1){
            continue;
        }
        else if (valaszt_tesztel(valasz) == 0) {
            van_e = false;
        }
        else{
            printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
            van_e = true;
        }
        printf("Az összetevő sorszámának megadásával válaszd ki a törölni kívánt elemet: \n");
        for(int i=0;i<meret;i++){
            printf("%d. %s \n",i+1,lista[i]);
        }
        printf("Választás:");
        scanf("%d",&valasztas);
        if(valasztas>meret){
            printf("Nem megfelelő számot adtál meg!");
            printf("Választás:");
            scanf("%d",&valasztas);
        }
        for(int i=0;i<meret;i++){
            if (valasztas== i){
                continue;
            }
            else
                fputs(lista[i],fp);
        }
    }
        fclose(fp);
        osszetevot_felszabadit(lista,meret);
}
