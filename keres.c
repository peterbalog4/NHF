#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "osszetevok.h"
#include "uf.h"
#include "debugmalloc.h"
#include "recept.h"
#include "menu.h"
#include <time.h>

//Megnézi, hogy az adott receptben megtalálható e a keresett elem
bool van_e_benne(char** o_lista,int o_meret,char *keres){
    for(int i=0;i<o_meret;i++){
        if(strcmp(o_lista[i],keres) == 0){
            return true;
        }
    }
    return false;
}

//Megkeres egy bizonyos összetevőt receptekben, majd visszaadja az összes olyan receptet amiben ez megvan.
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
    fflush(stdin);
    fgets(keres,52,stdin);
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

//Gyakorlatilag az innek_egy_kis függvény kibővített változata több keresett elemre.
void el_kell_hasznalni(Recept **eleje,int recept_szam){
    char **van_benne;
    int valasz;
    int k=0,szamolo=0,szamolo2=0;
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
    char **keres;
    int mennyit;
    printf("Hány összetevőt keresünk?");
    scanf("%d", &mennyit);
    if (0 > mennyit || mennyit > 18446744073709551615){
        printf("Hibás index!");
        return;
    }
    if(mennyit <0){
        printf("Hibás index!");
        osszetevot_felszabadit(van_benne,recept_szam);
        return;
    }
    keres = malloc(mennyit*sizeof(char *));
    if (keres == NULL){
        printf("Memóriafoglalási hiba!");
        return;
    }
    for(int i=0;i<mennyit;i++){
        keres[i] = malloc(52 * sizeof(char));
        if (keres[i] == NULL){
            printf("Memóriafoglalási hiba!");
            return;
        }
    }
    for(int i=0;i<mennyit;i++){
        printf("Add meg az %d. keresett összetevőt:",i+1);
        fflush(stdin);
    fgets(keres[i],52,stdin);
    }
    Recept *utolso = *eleje;
    while(utolso->kov != NULL){
        for(int i=0;i<mennyit;i++){
            if(van_e_benne(utolso->o_lista,utolso->o_meret,keres[i]) == true){
                szamolo++;
            }
        }
        if(szamolo == mennyit){
            strcpy(van_benne[k++],utolso->nev);
            szamolo2++;
        }
        utolso = utolso->kov;
    }
    if(szamolo2 == 0){
        printf("Nincs ilyen recept!\n");
        osszetevot_felszabadit(van_benne,recept_szam);
        osszetevot_felszabadit(keres,mennyit);
        return;
    }
    for(int i=0;i<szamolo2;i++){
        printf("%d. %s\n",i+1,van_benne[i]);
    }
    printf("Ezekben a receptekben vannak meg a keresett összetevők, melyiket szeretnéd elkészíteni? \n Választás:");
    scanf("%d",&valasz);
    valasz--;
    if(0 <=valasz && valasz < szamolo2){
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
    osszetevot_felszabadit(keres,mennyit);


}

void nincs_otlet(Recept **eleje,int receptek_szama){
    ide:
    srand(time(NULL));
    int r = rand();
    r = r % receptek_szama;
    char valasz[5];
    Recept *utolso = *eleje;
    int szamolo = 1;
    while(szamolo != r){
        utolso = utolso->kov;
        szamolo++;
    }
    receptet_kiir(utolso);
    printf("Ez a recept megfelelő?");
    scanf("%5s",valasz);
    bool van_e =true;
    while(van_e){
        if (valaszt_tesztel(valasz) == 1){
            return;
        }
        else if (valaszt_tesztel(valasz) == 0) {
            goto ide;
            break;
        }
        else{
            printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
            van_e = true;
        }
    }
}

void nev_szerint(Recept **eleje){
    char keres[52];
    printf("Add meg a keresett recept nevét!");
    fflush(stdin);
    fgets(keres,52,stdin);
    keres[strcspn(keres, "\n")] = '\0';
    Recept *utolso = *eleje;
    while(utolso->kov != NULL){
        if(strcmp(utolso->nev,keres) == 0){
            receptet_kiir(utolso);
            return;
        }
        utolso = utolso->kov;
    }
    printf("Nincs ilyen recept!\n");
}
