//Megjegyzések: Ez az univerzális függvénykönyvtáram. Olyan kicsi függvények amiket a NHF szinte összes moduljában használok, ezért összegyûjtöttem egy helyre.
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>

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
int valaszt_tesztel(char *valasz){
    if(strcmp(valasz,"IGEN") == 0 || strcmp(valasz,"I") == 0 )
        return 1;
    if(strcmp(valasz,"NEM") == 0 || strcmp(valasz,"N") == 0)
        return 0;
    else
        return -1;


}
