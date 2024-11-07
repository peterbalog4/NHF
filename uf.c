//Megjegyz�sek: Ez az univerz�lis f�ggv�nyk�nyvt�ram. Olyan kicsi f�ggv�nyek amiket a NHF szinte �sszes modulj�ban haszn�lok, ez�rt �sszegy�jt�ttem egy helyre.
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

// Forr�s : A sztringet_nagybetusit f�ggv�ny a 6. heti el�ad�sb�l lett �tv�ve.
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
