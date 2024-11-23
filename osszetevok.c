// Megjegyzések a kódhoz:
// 1. Minden összetevő sztring 52 méretű. A felhasználónak 50 karakter lett "megígérve". A sorokat_szamol függvényem \n karaktereket számol így ez kell,hogy
// minden sztring végén ott legyen. Így a lezáró nullával együtt minden összetevő sztring 50+1+1 méretű.
// 2. A segédfüggvények az uf.c fájlban vannak.
// 3. Az összetevő fuggvenyek(uj_osszetevo,osszetevo_lista,osszetevot_torol) jelenleg jól működnek. Viszont vannak dolgok benne amin szeretnék változtatni. Például amit laboron beszéltünk, a sok
// felesleges fájlnyitogatás. A végleges verzióban a modul és a kód funkcionalitása nem fog változni, de bizonyos dolgokat szeretnék "okosabban" megoldani.
//structot csinálni!!!!!

// NTS: Fájlkezelést javítani!!! || Fájlt az elején beolvassa, végén fájlba ír.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "uf.h"
#include "debugmalloc.h"

typedef struct Osszetevo{
    char **o_lista;
    int meret;
} Osszetevo;

// Felszabadítja az osszetevo_lista által létrehozott listát.
void osszetevot_felszabadit(char **osszetevok, int meret) {
    if (osszetevok != NULL) {
        for (int i = 0; i < meret; i++) {
            free(osszetevok[i]);
        }
        free(osszetevok);
    }
}

//Fájlba írja az összetevő listát
void osszetevot_fajlba_ir(Osszetevo lista){
    FILE *fp;
    fp =fopen("osszetevok.txt","w");
    for(int i=0;i<lista.meret;i++){
        fputs(lista.o_lista[i],fp);
    }
    fclose(fp);
}

// A függvény összetevőket ad hozzá az "osszetevok.txt" fájlhoz.
void uj_osszetevo(Osszetevo *lista,int meret){
    char ujosszetevo[52];
    printf("Add meg az új összetevőt:");
    fflush(stdin);
    fgets(ujosszetevo,52,stdin);
    char **temp;
    temp = malloc((meret)*sizeof(char *));
        if(temp == NULL){
            printf("Memóriafoglalási hiba!");
            return ;
        }
        for(int i=0;i<meret;i++){
            temp[i] = malloc(52 * sizeof(char));
            if (temp[i] == NULL){
                printf("Memóriafoglalási hiba!");
                return;
            }
        }
    for(int i=0;i<meret;i++){
        strcpy(temp[i],lista->o_lista[i]);
    }

    osszetevot_felszabadit(lista->o_lista,meret);
    lista->o_lista = malloc((meret+1)*sizeof(char *));
    if (lista->o_lista == NULL){
        printf("Memóriafoglalási hiba!");
        return;
    }
    for(int i=0;i<(meret+1);i++){
        lista->o_lista[i] = malloc(52 * sizeof(char));
        if (lista->o_lista[i] == NULL){
            printf("Memóriafoglalási hiba!");
            return;
        }
        }
    for(int i=0;i<meret;i++){
        strcpy(lista->o_lista[i],temp[i]);
    }
    strcpy(lista->o_lista[meret],ujosszetevo);
    osszetevot_felszabadit(temp,meret);
}

// Az osszetevo_lista függvény az "osszetevok.txt" fájlban levő adatokat sztringek listájává alakítja.
Osszetevo osszetevo_lista(){
    FILE *fp;
    Osszetevo lista;
    lista.meret = sorokat_szamol("osszetevok.txt");
    fp = fopen("osszetevok.txt","r");
    if (fp == NULL) {
        printf("Fájlkezelési hiba! \n");
        return;
    }
    lista.o_lista = malloc(lista.meret*sizeof(char *));
    if (lista.o_lista == NULL){
        printf("Memóriafoglalási hiba!");
        return;
    }
    for(int i=0;i<lista.meret;i++){
        lista.o_lista[i] = malloc(52 * sizeof(char));
        if (lista.o_lista[i] == NULL){
            printf("Memóriafoglalási hiba!");
            return;
        }
        fgets(lista.o_lista[i],52,fp);

    }
    fclose(fp);
    return lista;
}

// A függvény kilistázza az ismert összetevőket és a felhasználó az index megadásával tud belőle törölni
void osszetevot_torol(Osszetevo *lista,int meret){
    int valasztas;
    for(int i=0;i<meret;i++){
        printf("%d. %s \n",i+1,lista->o_lista[i]);
    }
    printf("Az összetevő sorszámának megadásával válaszd ki a törölni kívánt elemet: \n");
    printf("Választás:");
    scanf("%d",&valasztas);
    if(valasztas>meret || valasztas < 0){
        printf("Nem megfelelő számot adtál meg!");
        printf("Választás:");
        scanf("%d",&valasztas);
    }
    else{
        char **temp;
        temp = malloc(meret*sizeof(char *));
        if(temp == NULL){
            printf("Memóriafoglalási hiba!");
            exit(9);
        }
        for(int i=0;i<meret;i++){
            temp[i] = malloc(52 * sizeof(char));
            if (temp[i] == NULL){
                printf("Memóriafoglalási hiba!");
                exit(10);
            }

        }
        for (int i=0;i<meret;i++){
            strcpy(temp[i],lista->o_lista[i]);
        }

        osszetevot_felszabadit(lista->o_lista,meret);
        lista->o_lista = malloc((meret-1)*sizeof(char *));
        if (lista->o_lista == NULL){
            printf("Memóriafoglalási hiba!");
            return;
        }
        for(int i=0;i<meret-1;i++){
            lista->o_lista[i] = malloc(52 * sizeof(char));
            if (lista->o_lista[i] == NULL){
                printf("Memóriafoglalási hiba!");
                return;
            }
        }
        int k=0;
        for(int i=0;i<meret;i++){
            if(valasztas-1 == i){
                continue;
            }
            else{
                strcpy(lista->o_lista[k++],temp[i]);
            }
        }

        osszetevot_felszabadit(temp,meret);

    }
}
