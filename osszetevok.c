#include <stdio.h>
#include <stdbool.h>
#ifdef _WIN32
    #include <windows.h>
#endif
#include "debugmalloc.h"
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

void uj_osszetevo(void){
    do{
        bool van_e;
        char valasz[5]; ujosszetevo[51];
        printf("Van még új összetevõ?");
        scanf("%s", &valasz);
        toupper(valasz);
        if( valasz == "IGEN" || valasz == "I"){
            FILE *fbe = fopen("osszetevok.txt", "a+");
            printf("Add meg az új összetevõt:")
            scanf("%s",&ujosszetevo);
            strcat(ujosszetevo, '\n');
            fputs(ujosszetevo, fbe);
            fclose(fbe);
            van_e = true;
        }
        else if(valasz == "NEM" || valasz == "N") {
            van_e = false;
        }
        else{
            printf("Ismeretlen választás kérlek az igen/nem szavakat vagy I/H betût adj meg")
            van_e = true;
        }
    }
    while(van_e == true);
}
