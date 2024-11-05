#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>

 int sorokat_szamol(char *fajl){
    FILE *fp;
    fp = fopen(fajl,"r");
    char c;
    int sorszamolo = 0;
    while(fscanf(fp,"%c",&c) != 0){
        c = fscanf(fp,"%c",&c);
        if(c == '\n'){
            sorszamolo++;
        }
        else
            continue;
    }
    return sorszamolo;
}

//Később kellhet

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
        FILE *fp;
        fp = fopen("osszetevok.txt", "a");
        char valasz[5];
        char ujosszetevo[51];
        printf("Van még új összetevő?");
        scanf("%s", &valasz);
        sztringet_nagybetusit(valasz);
        if(valaszt_tesztel(valasz)  == 1){
            printf("Add meg az új összetevőt:");
            scanf("%s",&ujosszetevo);
            van_e = true;
            //strcat(ujosszetevo, "\n");
            fprintf(fp,"%s\n",ujosszetevo);
        }else if(valaszt_tesztel(valasz) == 0) {
            van_e = false;
            fclose(fp);
        }
        else{
            printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
            van_e = true;
        }
    }while(van_e);
}


/* int main(){
    system("chcp 65001 >nul");
    FILE *fp;
    fp = fopen("osszetevok.txt", "r");
    int x = sorokat_szamol("osszetevok.txt");
    printf("%d",x);





    return 0;
} */

// Ket string, ket while ciklus, 1. beolvassa a stringet és elmenti a másodikba
void osszetevo_lista(void){
    FILE *fp;
    int k=0;
    int i = 0;
    char c;
    char **osszetevok;
    char temp[52];
    fp = fopen("osszetevok.txt","r");
    while(fscanf(fp,"%c",c) == 0)
        while(fscanf(fp,"%c",c) != '/0');
            temp[i++] = c;
        strcpy(osszetevok[k++], temp);

    for(int i=0; i<k;i++){
        printf("%s",osszetevok[i]);
    }
}



// teszt
