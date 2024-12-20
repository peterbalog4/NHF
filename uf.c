//Megjegyzések: Ez az univerzális függvénykönyvtáram. Olyan kicsi függvények amiket a NHF szinte összes moduljában használok, ezért összegyûjtöttem egy helyre.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "recept.h"
#include "osszetevok.h"

// Ez a függvény sorokat számol. Az összetevőket és a recepteket tartozó fájlok sorszámolására használom.
// Az uj_osszetevo fuggveny es az uj_recept fuggveny minden sor végére rak egy \n karaktert így pontosan számol a függvény.
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

// Kiírja egy lista összes elemét.
void listat_kiir(char **lista, int meret){
    printf("Ismert összetevők:\n");
    for(int i=0; i<meret;i++){
        printf("\n %d. %s",i+1,lista[i]);
    }
    printf("\n");
}
