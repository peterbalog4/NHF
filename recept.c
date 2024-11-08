#include <stdio.h>
#include <stdlib.h>
#include "osszetevo.h"

typedef struct Recept{
    char nev[51];
    char **osszetevo_lista;
    char **el;
} Recept;

char **el_lista(int meret){
    char **el_lista;
    el_lista = malloc(meret*sizeof(char *));
    if (el_lista == NULL){
        printf("Memóriafoglalási hiba!");
        return NULL;
    }
    for(int i=0;i<meret;i++){
        el_lista[i] = malloc(201 * sizeof(char));
        if (el_lista[i] == NULL){
            printf("Memóriafoglalási hiba!");
            return NULL;
        }
    }
    for(int i=0;i<meret;i++){
        printf("Add meg az elkészítési leírás %d. elemét \n ",i+1);
        scanf("%s",el_lista[i]);
    }
    return el_lista;

}

void uj_recept(){
    Recept uj;
    printf("Add meg a recept nevét:");
    scanf("%s" uj.nev);
    char **o_list = osszetevo_lista();
    char uj_list =
    printf("Válaszd ki az osszetevoket")
}
int main()
{
    char **lista;
    lista = el_lista(5);
}
