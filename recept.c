// Megjegyzés a kódhoz:
// 1. A Recept struktúra sokkal jobban ki lesz használva a végleges kódban.
// 2. Az uj_recept függvény jelenleg működik, de nagyon "bután" csinálja, amit csinálnia kell. A végleges programban a függvény funkcionalitása nem fog változni, de a belső müködése valószínűleg igen.
// 3. Az uj_recept függvényben valahol van egy memóriafoglalási hiba. A debugmalloctól azt kapom vissza, hogy olyan területet akarok felszabadítani, ami nincs lefoglalva.
// Egyszerűen nem tudok rájönni, hogy hol lehet a kódban a hiba. Kéne valaki aki friss szemmel néz rá a kódra, de így vasárnap nincs nagyon senki aki tudna segíteni. A kész NHF-ra
// természetesen ez javítva lesz.
#include <stdio.h>
#include <stdlib.h>
#include "osszetevok.h"
#include "debugmalloc.h"
#include "uf.h"
#include "menu.h"

typedef struct Recept{
    char nev[51];
    char **osszetevo_lista;
    char **el_lista;
} Recept;

// A függvény hozzáad egy receptet a "receptek.txt" fájlhoz.
void uj_recept(){
    Recept uj;
    FILE *fp;
    int o_meret,el_meret;
    int valasztas,szamlalo = 0;
    int k = 0;
    printf("Add meg a recept nevét:");
    scanf("%50s", uj.nev);
    printf("Add meg az összetevők számát!\n Választás:");
    scanf("%d",&o_meret);
    char **o_lista = osszetevo_lista();
    char **uj_lista = ures_lista(o_meret,52);
    if(o_meret >0){
        printf("Válaszd ki az összetevőket!\n Választás:");
        listat_kiir(o_lista,sorokat_szamol("osszetevok.txt"));
        while(szamlalo < o_meret){
            printf("Választás:");
            scanf("%d",&valasztas);
            if (valasztas <= sorokat_szamol("osszetevok.txt") && valasztas >0){
                szamlalo++;
                uj_lista[k++] = o_lista[valasztas-1];
            }
            else{
                printf("Indexelési hiba!");
                fomenu();
            }
        }
    }
    else{
        printf("Hibás választás!");
    }

    printf("Hány lépésből álljon az elkészítési leírás?\nVálasztás:");
    scanf("%d",&el_meret);
    char **el;
    if(el_meret >0){
        el = ures_lista(el_meret,201);
        for(int i=0;i<el_meret;i++){
            printf("Add meg az elkészítési leírás %d. elemét \n ",i+1);
            scanf("%200s",el[i]);
        }
    }
    else{
        printf("Hibás választás!");
    }
    fp = fopen("recept.txt","a");
    if (fp == NULL) {
        printf("Fájlkezelési hiba! \n");
        return NULL;
    }
    fprintf(fp,"%s",uj.nev);
    fprintf(fp, " | ");
    listat_fajlba_ir(uj_lista,o_meret,fp);
    fprintf(fp, " | ");
    listat_fajlba_ir(el,el_meret,fp);
    fclose(fp);
    osszetevot_felszabadit(el,el_meret);
    osszetevot_felszabadit(o_lista,sorokat_szamol("osszetevok.txt"));
    osszetevot_felszabadit(uj_lista,o_meret);
}

