#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>

/* int sorokat_szamol(char *fajl){
    *fp = fopen(fajl,"r");
    while(fscanf(fp,c) != EOF){
        char c = fscanf(fp,c);
        int sorszamolo = 0
        if(c == '\n'){
            sorszamlo++;
        }
        else
            continue;
    }
}
*/
//Később kelhet

/*void osszetevot_listasit(char *fajl){
    char osszetevok[];
    *fp = fopen(fajl,"r");
    int i=0;
    do{
        fscanf(fp,"%s",&osszetevok[i++]);
    }
    while()
} */

// Forrás : A sztringet_nagybetusit függvény a 6. heti előadásból lett átvéve.
void sztringet_nagybetusit(char *sztring) {
    for (int i = 0; sztring[i] != '\0'; ++i)
        sztring[i] = toupper(sztring[i]);
}
int valaszt_tesztel(char *valasz){
    if(strcmp(valasz,"IGEN") == 0 || strcmp(valasz,"I") == 0 )
        return 1;
    if(strcmp(valasz,"NEM") == 0 || strcmp(valasz,"N") == 0)
        return 0;
    else
        return -1;


}

void uj_osszetevo(void){
    bool van_e;
    do{
        char valasz[5];
        char ujosszetevo[51];
        printf("Van meg uj osszetevo?");
        scanf("%s", &valasz);
        sztringet_nagybetusit(valasz);
        if(valaszt_tesztel(valasz)  == 1){
            FILE *fp;
            printf("Add meg az uj osszetevot:");
            scanf("%s",&ujosszetevo);
            van_e = true;
            strcat(ujosszetevo, '\n');
            fputs(ujosszetevo, fp);
            fclose(fp);
        }
        else if(valaszt_tesztel(valasz) == 0) {
            van_e = false;
        }
        else{
            printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
            van_e = true;
        }
    }
    while(van_e == true);
}


int main(){
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    uj_osszetevo();
    return 0;
}

// Ket string, ket while ciklus, 1. beolvassa a stringet és elmenti a másodikba
void osszetevo_lista(void){
    FILE *fp;
    int i = 0;
    char c;
    char **osszetevok;
    char temp[52];
    fp = fopen("osszetevok.txt","r");
    while(fscanf(fp,"%c",c) == 0)
        while(fscanf(fp,"%c",c) != '/0');
            temp[i++] = c;
        strcpy(*osszetevok, temp)


}
