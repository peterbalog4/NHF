#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "osszetevok.h"
#include "uf.h"
#include "debugmalloc.h"

// A recepteket tároló láncolt lista struktúrája.
typedef struct Recept{
    char nev[51];
    char **o_lista;
    int o_meret;
    char **ml;
    char **el_lista;
    int el_meret;
    struct Recept *kov;
} Recept;

//Hozzáad egy új receptet a recepteket tároló láncolt listához.
void uj_recept(Recept **eleje){
    Recept *uj = (Recept*)malloc(sizeof(Recept));
    Osszetevo lista = osszetevo_lista();

    printf("Add meg a recept nevét:");
    fflush(stdin);
    fgets(uj->nev,52,stdin);
    uj->nev[strcspn(uj->nev, "\n")] = '\0';

    int o_meret,valasz;
    printf("Hány összetevő legyen?");
    scanf("%d", &o_meret);
    if (0 > o_meret || o_meret > 18446744073709551615){
        printf("Hibás index!");
        return;
    }
    if(0 >o_meret ){
        printf("Hibás index!");
        return;
    }

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
        listat_kiir(lista.o_lista,lista.meret);
        for(int i=0;i < o_meret;i++){
            printf("Választás:");
            scanf("%d",&valasz);
            //Hibakezelés!!
            lista.o_lista[valasz-1][strcspn(lista.o_lista[valasz-1], "\n")] = '\0';
            strcpy(uj->o_lista[i],lista.o_lista[valasz-1]);
            printf("Hány ml-t?");
            scanf("%s", uj->ml[i]);
        }
    }
    else{
        exit(3);
    }

    int el_meret;

    printf("Hány lépés legyen az elkészítési leírás?");
    scanf("%d",&el_meret);
    if (0 > el_meret || el_meret > 18446744073709551615){
        printf("Hibás index!");
        return;
    }

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
            fflush(stdin);
            fgets(uj->el_lista[i],201,stdin);
            uj->el_lista[i][strcspn(uj->el_lista[i], "\n")] = '\0';
            if(strcmp(uj->el_lista[i],"\n") == 0){
                printf("Hibás bemenet!");
                receptet_felszabadit(&eleje);
                exit(9);
            }
        }
    }
    else{
        exit(6);
    }
    uj->o_meret = o_meret;
    uj->el_meret = el_meret;


    osszetevot_felszabadit(lista.o_lista,lista.meret);

    if (*eleje == NULL){
        *eleje = uj;
        uj->kov = NULL;
        return;
    }
    else{
        Recept *utolso = *eleje;
        while(utolso->kov != NULL){
            utolso = utolso->kov;
        }
        utolso->kov = uj;
        uj->kov = NULL;
        return;
    }
}

//Kiír egy konkrét receptet.
void receptet_kiir(Recept *recept){
    if (recept != NULL) {
        printf("Név: %s\n", recept->nev);
        printf("Összetevők: \n");
        for(int i=0;i<recept->o_meret;i++){
            printf("%s %s ml \n",recept->o_lista[i],recept->ml[i]);
        }
        printf("Elkészítési leírás: \n");
        for(int i=0;i<recept->el_meret;i++){
            printf("%s \n",recept->el_lista[i]);
        }
    }
}

//A recepteket tároló láncolt listát fájlba írja.
void receptet_fajlba_ir(Recept **eleje){
    FILE *fp;
    Recept *utolso = *eleje;
    fp = fopen("receptek.txt","w");
    if(utolso != NULL){
        do{
            fprintf(fp,"%s;", utolso->nev);
            for(int i=0;i<utolso->o_meret;i++){
                fprintf(fp,"%s,%d?",utolso->o_lista[i],*(utolso->ml[i]));
            }
            fprintf(fp,";");
            for(int i=0;i<utolso->el_meret;i++){
                fprintf(fp,"%s?",utolso->el_lista[i]);
            }
            fprintf(fp,";");
            fprintf(fp,"\n");
            utolso = utolso->kov;
        }while(utolso->kov != NULL);
            fprintf(fp,"%s;", utolso->nev);
            for(int i=0;i<utolso->o_meret;i++){
                fprintf(fp,"%s,%d?",utolso->o_lista[i],*(utolso->ml[i]));
            }
            fprintf(fp,";");
            for(int i=0;i<utolso->el_meret;i++){
                fprintf(fp,"%s?",utolso->el_lista[i]);
            }
            fprintf(fp,";");
            fprintf(fp,"\n");
    }
}

// Felszabadítja a recepteket tároló láncolt listát. Megjegyzés: Feltűnő lehet, hogy az NHF-ben magyar kifejezéseket használok, itt
// pedig a temp angol kifejezést. A kódot nem plagizáltam, csupán a magyar "időleges" vagy "eseti" nagyon furán használható/értelmezhető.
void receptet_felszabadit(Recept **eleje){
    Recept *temp;
    while (*eleje != NULL) {
        temp = *eleje;
        *eleje = (*eleje)->kov;

        osszetevot_felszabadit(temp->el_lista, temp->el_meret);
        osszetevot_felszabadit(temp->o_lista, temp->o_meret);

        for (int i = 0; i < temp->o_meret; i++) {
            free(temp->ml[i]);
        }
        free(temp->ml);

        free(temp);

    }
}
// Megjegyzés: A lenti függvényt "összefoltoztam". Néhány trükköt, például a tokenezést és az strtok() függvényt az internetről tanultam, néhány ötlet pedig
// a sajátom. A függvény nem copy-paste, de nem teljesen a Prog1 tananyagra épül.
// string = A használt string, stop = A delimiter karakter, esetünkben a ; | ? | ,
char** elvalaszt(const char* string, const char* stop, int* hossz) {
    char* temp = strdup(string);
    char* token;
    char** eredmeny = NULL;
    int meret = 0;

    token = strtok(temp, stop);
    while (token != NULL) {
        eredmeny = realloc(eredmeny, sizeof(char*) * (meret + 1));
        eredmeny[meret] = strdup(token);
        meret++;
        token = strtok(NULL, stop);
    }


    if (hossz != NULL) {
        *hossz = meret;
    }

    return eredmeny;
}
//A szemem fénye. Ez a függvény olvassa ki a receptek.txt fájlból a recepteket és épít belőlük láncolt listát. A függvény két nap munka
//és ipari mennyiségű kávé eredménye.
void recept_lista(Recept **eleje){
    FILE *fp = fopen("receptek.txt", "r");

    char sor[256];
    while (fgets(sor, sizeof(sor), fp)) {

        Recept *uj = (Recept*)malloc(sizeof(Recept));
        int hossz,o_meret,el_meret;
        char **elvalasztott = elvalaszt(sor, ";",&hossz);

        strcpy(uj->nev,elvalasztott[0]);

        char **eredmeny2 = elvalaszt(elvalasztott[1], "?",&hossz);

        o_meret = hossz;

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

        uj->ml = malloc(o_meret*sizeof(char *));
        if (uj->ml == NULL){
            printf("Memóriafoglalási hiba!");
            exit(7);
        }
        for(int i=0;i<o_meret;i++){
            uj->ml[i] = malloc(52*sizeof(char));
            if (uj->ml[i] == NULL){
                printf("Memóriafoglalási hiba!");
                exit(8);
            }
        }

        for(int i = 0; i < hossz; i++){
            char **o_lista_elvalasztott = elvalaszt(eredmeny2[i], ",", NULL);
            strcpy(uj->o_lista[i],o_lista_elvalasztott[0]);
            strcpy(uj->ml[i],o_lista_elvalasztott[1]);
            free(o_lista_elvalasztott);
        }


        char **leirasok = elvalaszt(elvalasztott[2], "?",&hossz);

        el_meret = hossz;
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

        for(int i = 0; i < el_meret; i++){
            strcpy(uj->el_lista[i], leirasok[i]);
        }

        uj->o_meret = o_meret;
        uj->el_meret = el_meret;
        Recept *utolso=*eleje;

        if (*eleje == NULL) {
            *eleje = uj;
            uj->kov = NULL;
        }
        else {
            while (utolso->kov != NULL) {
                utolso = utolso->kov;
            }
            utolso->kov = uj;
            uj->kov = NULL;
        }
        free(elvalasztott);
        free(leirasok);
        free(eredmeny2);
    }
    fclose(fp);
}

//Ez a függvény a teljes recepteket tároló láncolt listát kiírja a képernyőre.
void receptet_listaz(Recept **eleje){
    Recept *utolso = *eleje;
    int szamolo=1;
    while(utolso->kov != NULL){
        printf("%d.",szamolo);
        receptet_kiir(utolso);
        utolso = utolso->kov;
        szamolo++;
    }
    printf("%d.",szamolo);
    receptet_kiir(utolso);
    return szamolo;
}

// Ez a függvény eltávolít egy receptet a recepteket tároló láncolt listából.
void recept_torol(Recept **eleje, int mennyi){
    Recept *elozo = NULL, *temp = *eleje;
    int szamolo = 0;

    if (mennyi == 1){
        elozo = *eleje;
        *eleje = temp->kov;
        osszetevot_felszabadit(elozo->el_lista, elozo->el_meret);
        osszetevot_felszabadit(elozo->o_lista, elozo->o_meret);
        osszetevot_felszabadit(elozo->ml, elozo->o_meret);
        free(elozo);
        return;
    }

    while (temp != NULL && szamolo < mennyi - 1){
        elozo = temp;
        temp = temp->kov;
        szamolo++;
    }

    if (temp != NULL){
        if (temp->kov == NULL) {
            elozo->kov = NULL;
        }
        else {
            elozo->kov = temp->kov;
        }
        osszetevot_felszabadit(temp->el_lista, temp->el_meret);
        osszetevot_felszabadit(temp->o_lista, temp->o_meret);
        osszetevot_felszabadit(temp->ml, temp->o_meret);
        free(temp);
    }
}

// Ez a függvény módosít egy receptet a recepteket tároló láncolt listában.
void recept_modosit(Recept **eleje,int mennyi){
    int valasz;
    Recept *utolso= *eleje;
    int szamolo =0;
    while (eleje != NULL && szamolo < mennyi - 1 && mennyi != 1){
        utolso = utolso->kov;
        szamolo++;
    }

    printf("Mit szeretnél módosítani?\n 1. Név \n 2. Összetevők \n 3. Elkészítési leírás \n");
    scanf("%d", &valasz);
    if(0 > valasz || valasz > 4){
        printf("Hibás index!\n");
        return;
    }
    switch(valasz){
        case 1:{
            printf("Új név:");
            fflush(stdin);
            fgets(utolso->nev,52,stdin);
            break;
        }
        case 2:{
            Osszetevo lista = osszetevo_lista();
            int valasz;
            osszetevot_felszabadit(utolso->o_lista,utolso->o_meret);
            osszetevot_felszabadit(utolso->ml,utolso->o_meret);
            int o_meret;
            printf("Hány összetevő legyen?");
            scanf("%d", &o_meret);
            if (0 > o_meret || o_meret > 18446744073709551615){
                printf("Hibás index!");
                return;
            }

            utolso->o_lista = malloc(o_meret*sizeof(char *));
            if (utolso->o_lista == NULL){
                printf("Memóriafoglalási hiba!");
                exit(1);
            }
            for(int i=0;i<o_meret;i++){
                utolso->o_lista[i] = malloc(52 * sizeof(char));
                if (utolso->o_lista[i] == NULL){
                    printf("Memóriafoglalási hiba!");
                    exit(2);
                }
            }

            utolso->ml = malloc(o_meret*sizeof(int *));
            if (utolso->ml == NULL){
                printf("Memóriafoglalási hiba!");
                exit(7);
            }
            for(int i=0;i<o_meret;i++){
                utolso->ml[i] = malloc(sizeof(int));
                if (utolso->ml[i] == NULL){
                    printf("Memóriafoglalási hiba!");
                    exit(8);
                }
            }
            if(o_meret >= 0){
                listat_kiir(lista.o_lista,lista.meret);
                for(int i=0;i < o_meret;i++){
                    printf("Választás:");
                    scanf("%d",&valasz);
                    lista.o_lista[valasz-1][strcspn(lista.o_lista[valasz-1], "\n")] = '\0';
                    strcpy(utolso->o_lista[i],lista.o_lista[valasz-1]);
                    printf("Hány ml-t?");
                    fflush(stdin);
                    fgets(utolso->ml[i],52,stdin);
                }
            }
            else{
            exit(3);
            }
            utolso->o_meret = o_meret;
            osszetevot_felszabadit(lista.o_lista,lista.meret);
            free(lista.meret);
            break;
        }
        case 3:{
            osszetevot_felszabadit(utolso->el_lista,utolso->el_meret);
            int el_meret;
            printf("Hány lépés legyen az elkészítési leírás?");
            scanf("%d",&el_meret);
            if (0 > el_meret || el_meret > 18446744073709551615){
                printf("Hibás index!");
                return;
            }

            utolso->el_lista = malloc(el_meret*sizeof(char *));
            if (utolso->el_lista == NULL){
                printf("Memóriafoglalási hiba!");
                exit(4);
            }
            for(int i=0;i<el_meret;i++){
                utolso->el_lista[i] = malloc(201 * sizeof(char));
                if (utolso->el_lista[i] == NULL){
                    printf("Memóriafoglalási hiba!");
                    exit(5);
                }
            }

            if(el_meret > 0){
                for(int i=0;i < el_meret;i++){
                    char temp[201];
                    printf("%d. lépés:",i+1);
                    fflush(stdin);
                    fgets(temp,201,stdin);
                    if(strcmp(temp,"\n")== 0){
                        printf("Hibás bemenet!");
                        receptet_felszabadit(&eleje);
                        exit(9);
                    }
                    else {
                        strcpy(utolso->el_lista[i],temp);
                    }
                }
            }
            else{
                exit(6);
            }
            utolso->el_meret = el_meret;
            break;
        }
    }
}

//Megszámolja, hogy hány recept van.
int recept_szamolo(Recept **eleje){
    Recept *utolso = *eleje;
    int szamolo=1;
    while(utolso->kov != NULL){
        utolso = utolso->kov;
        szamolo++;
    }
    return szamolo;
}
