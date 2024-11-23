//Megjegyzések: Ez az univerzális függvénykönyvtáram. Olyan kicsi függvények amiket a NHF szinte összes moduljában használok, ezért összegyûjtöttem egy helyre.

// Ez a függvény sorokat számol. Az összetevőket és a recepteket tartozó fájlok sorszámolására használom.
// Az uj_osszetevo fuggveny es az uj_recept fuggveny minden sor végére rak egy \n karaktert így pontosan számol a függvény.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "recept.h"
#include "osszetevok.h"

 int sorokat_szamol(char *fajl){
    FILE *fp;
    fp = fopen(fajl,"r");
    char c;
    int sorszamolo = 0;
    while(fscanf(fp,"%c",&c) != EOF){
        if(c == '\n'){
            sorszamolo++;
        }
        else
            continue;
    }
    fclose(fp);
    return sorszamolo;
}

// Forrás : A sztringet_nagybetusit függvény a 6. heti elõadásból lett átvéve.
void sztringet_nagybetusit(char *sztring) {
    for (int i = 0; sztring[i] != '\0'; ++i){
        sztring[i] = toupper(sztring[i]);
    }
}
// Egy általános függvény ami a felhasználó által megadott sztringet teszteli. A (y/n) típusú kérdéseknél ezzel a függvényel tesztelek, majd az if ciklusban már csak ellenőrzöm, a visszaadott int-et.
// Nagyrészt helyspórolás és a copy-paste elkerülése miatt készült.
int valaszt_tesztel(char *valasz){
    sztringet_nagybetusit(valasz);
    if(strcmp(valasz,"IGEN") == 0 || strcmp(valasz,"I") == 0 )
        return 1;
    if(strcmp(valasz,"NEM") == 0 || strcmp(valasz,"N") == 0)
        return 0;
    else
        return -1;


}
// A függvény egy üres pointertömböt hoz létre amiben sztringeket tárolok. A meret adja meg a sztringek számát, a charsize adja meg,hogy a sztringek milyen hosszúak legyenek.
char **ures_lista(int meret, int charsize){
    char **lista;
    lista = malloc(meret*sizeof(char *));
    if (lista == NULL){
        printf("Memóriafoglalási hiba!");
        exit(1);
        return NULL;
    }
    for(int i=0;i<meret;i++){
        lista[i] = malloc(charsize * sizeof(char));
        if (lista[i] == NULL){
            printf("Memóriafoglalási hiba!");
            exit(2);
            return NULL;
        }
    }
    return lista;
}

// Kiírja egy lista összes elemét.
void listat_kiir(char **lista, int meret){
    printf("Ismert összetevők:\n");
    for(int i=0; i<meret;i++){
        printf("\n %d. %s",i+1,lista[i]);
    }
    printf("\n");
}

void uj_sort_torol(char *string) {
    string[strcspn(string, "\n")] = '\0';
}
