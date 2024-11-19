#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

void uj_recept(Recept **eleje){
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
            scanf("%d", uj->ml[i]);
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


    osszetevot_felszabadit(lista,meret);

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

int recept_szamolo(Recept **eleje){
    int recept_szamolo = 0;
    Recept *utolso = *eleje;
    while(utolso->kov != NULL){
        recept_szamolo++;
        utolso = utolso->kov;
    }
    return recept_szamolo;
}

void receptet_kiir(Recept *recept){
    if (recept != NULL) {
        printf("Név: %s\n", recept->nev);
        printf("Összetevők: \n");
        for(int i=0;i<recept->o_meret;i++){
            printf("%s %d ml \n",recept->o_lista[i],*(recept->ml[i]));
        }
        printf("Elkészítési leírás: \n");
        for(int i=0;i<recept->el_meret;i++){
            printf("%s \n",recept->el_lista[i]);
        }
    }
}

void receptet_fajlba_ir(Recept **eleje){
    FILE *fp;
    Recept *utolso = *eleje;
    fp = fopen("receptek.txt","w");
    if(utolso != NULL){
        do{
            fprintf(fp,"%d\n", utolso->o_meret);
            fprintf(fp,"%d\n", utolso->el_meret);
            fprintf(fp,"%s\n", utolso->nev);
            for(int i=0;i<utolso->o_meret;i++){
                fprintf(fp,"%s %d\n",utolso->o_lista[i],*(utolso->ml[i]));
            }
            for(int i=0;i<utolso->el_meret;i++){
                fprintf(fp,"%s\n",utolso->el_lista[i]);
            }
            utolso = utolso->kov;
        }while(utolso->kov != NULL);
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

int recept_lista(Recept **eleje){

    FILE *fp,*fp2;

    fp2 = fopen("recept.txt","r");

    int o_meret,el_meret,recept_szamolo,szamolo=0;
    fp = fopen("receptek.txt","r");
    fscanf(fp2,"%d",&recept_szamolo);
    while(recept_szamolo != szamolo){
        fscanf(fp,"%d",&o_meret);
        Recept *uj = (Recept*)malloc(sizeof(Recept));
        fscanf(fp,"%d",&el_meret);
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

        fscanf(fp,"%s",uj->nev);

        for(int i=0;i<o_meret;i++) {
            fgets(uj->o_lista[i], 52, fp);
            uj->o_lista[i][strcspn(uj->o_lista[i], "\n")] = '\0';
            fscanf(fp, "%d", uj->ml[i]);
        }

        for(int i=0;i<el_meret;i++) {
            fgets(uj->el_lista[i], 201, fp);
             uj->el_lista[i][strcspn(uj->el_lista[i], "\n")] = '\0';
        }

        uj->o_meret = o_meret;
        uj->el_meret = el_meret;

        Recept *utolso = *eleje;

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
        szamolo++;
        }
    }
    fclose(fp);
}

void recept_listaz(Recept **eleje){
    Recept *utolso = eleje;
    int szamolo=1;
    do{
        printf("%d.",szamolo);
        receptet_kiir(utolso);
        utolso = utolso->kov;
        szamolo++;
    }while(utolso->kov != NULL);
}

void recept_torol(Recept **eleje,int mennyi){
    Recept *elozo,*temp = NULL;
    temp = *eleje;
    int szamolo=0;
    if(mennyi == 1){
        *eleje = temp->kov;
        free(temp);
        return;
    }
    else{
        while(szamolo != mennyi-1){
            temp->kov;
            szamolo++;
        }
        elozo = temp;
        elozo->kov = temp->kov;
        free(temp);
    }
}
