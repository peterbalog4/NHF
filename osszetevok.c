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
#include "uf.h"
#include "debugmalloc.h"

typedef struct Osszetevo{
    char **o_lista;
    int meret;
} Osszetevo;

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
    scanf("%s",ujosszetevo);
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
    lista.meret = malloc(sizeof(int));
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

// Felszabadítja az osszetevo_lista által létrehozott listát.
void osszetevot_felszabadit(char **osszetevok, int meret) {
    if (osszetevok != NULL) {
        for (int i = 0; i < meret; i++) {
            free(osszetevok[i]);
        }
        free(osszetevok);
    }
}

/*void osszetevot_listat_felszabadit(Osszetevo lista) {
    if (lista.o_lista != NULL) {
        for (int i = 0; i < lista.meret; i++) {
            free(lista.o_lista[i]);
        }
        free(lista);
    }
}*/

// A függvény kilistázza az ismert összetevőket és a felhasználó az index megadásával tud belőle törölni
void osszetevot_torol(Osszetevo *lista,int meret){
    int valasztas;
    bool van_e = true;
    char valasz[5];
    while(van_e == true){
        printf("Van még törlendő elem?");
        scanf("%s",&valasz);
        for(int i=0;i<meret;i++){
            printf("%d. %s \n",i+1,lista->o_lista[i]);
        }
        if(valaszt_tesztel(valasz) == 1){
            printf("Az összetevő sorszámának megadásával válaszd ki a törölni kívánt elemet: \n");
            printf("Választás:");
            scanf("%d",&valasztas);
            if(valasztas>meret || valasztas < 1){
                printf("Nem megfelelő számot adtál meg!");
                printf("Választás:");
                scanf("%d",&valasztas);
            }
            else{
                char **o_lista;
                o_lista = malloc((meret-1)*sizeof(char *));
                if(o_lista == NULL){
                    printf("Memóriafoglalási hiba!");
                    exit(9);
                }
                for(int i=0;i<(meret-1);i++){
                    o_lista[i] = malloc(52 * sizeof(char));
                    if (o_lista[i] == NULL){
                        printf("Memóriafoglalási hiba!");
                        exit(10);
                    }

                }
                for(int i=0;i<meret;i++){
                    if(valasztas-1 <= i){
                        strcpy(o_lista[i],lista->o_lista[i+1]);;
                    }
                    else{
                        strcpy(o_lista[i],lista->o_lista[i]);
                    }
                lista->meret--;
                //osszetevot_felszabadit(lista->o_lista,meret);
                lista->o_lista = o_lista;
                //osszetevot_felszabadit(o_lista,meret);
                }
            }
        }
        else if (valaszt_tesztel(valasz) == 0) {
            van_e = false;
        }
        else{
            printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
            van_e = true;
        }
    }
}
