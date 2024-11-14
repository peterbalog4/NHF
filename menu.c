// NTS: Meg kell oldani, hogy ki lehessen lépni az exit szóval. + a program csak akkor álljon le ha a főmenüben exitet kap.
// NTS: Láncolt lista az összetevőkhöz!!!

// Megjegyzés: 1. A program egyelőre nem ciklikus. Azaz mindig leáll. Ez a kész NHF-ban már javítva lesz és csak akkor áll majd le a program, ha exit kulcszót kap.
// 2. Az elmentett uj osszetevők csak a program bezárásakor kerülnek bele a fájlba. Emiatt ha a 2.1 meüben új összetevőt adunk meg, az nem lesz használható. Ezt úgy tervezem javítani, hogy nem a fájlba fog írogatni az uj_osszetevo
// függvény, hanem egy a fájlból átvett listába. Ezt idő hiányában nem tudom határidőre kivitelezni, ezért csak a kész NHF-ba fog bekerülni.

#include <stdio.h>
#include <stdbool.h>
#include "osszetevok.h"
#include "uf.h"
#include "recept.h"
#include "debugmalloc.h"

void almenu_osszetevo(char **lista,int meret);
void almenu_uj(char **lista,int meret);
void almenu_recept(void);
void almenu_keres(void);

// A főmenü függvény. A felhasználó innen kezdi a navigációját és ide tér majd vissza.
void fomenu(void){
    char **lista = osszetevo_lista();
    int meret = sorokat_szamol("osszetevok.txt");
    int valasztas;
    printf("NHF | Koktéloskönyv\n");
    printf("\n 1. Összetevõk \n 2. Új koktélrecept felvétele \n 3. Receptek \n 4. Keresés \n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:
            almenu_osszetevo(lista,meret);
            break;
        case 2:
            almenu_uj(lista,meret);
            break;
        /* case 3:
            almenu_recept();
            break;
        case 4:
            almenu_keres();
            break;*/
        default:
            fomenu();
            break;
    }
}

// Ebből az almenüből érhetőek el az összetevő függvények.
void almenu_osszetevo(char **lista,int meret){
    FILE *fp;
    int valasztas;
    char valasz[5];
    printf("\n 1. Új összetevő hozzáadása \n 2. Összetevő törlése \n 3. Összetevők listája \n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:{
            lista = uj_osszetevo(lista,meret);
            listat_kiir(lista,meret+2);
            printf("Szeretnél még valamit csinálni?");
            scanf("%s", &valasz);
            if(valaszt_tesztel(valasz) == 1){
                void almenu_osszetevo(lista,meret);
            }
            else if(valaszt_tesztel(valasz) == 0){
                fp = fopen("osszetevok.txt","w");
                for(int i=0;i<meret;i++){
                    fprintf(fp,"%s",lista[i]);
                    fprintf(fp, "\n");
                }

            }
            break;
        }
        case 2:{
            osszetevot_torol();
            //fomenu();
            break;
        }
        case 3: {
            listat_kiir(lista, sorokat_szamol("osszetevok.txt"));
            osszetevot_felszabadit(lista,sorokat_szamol("osszetevok.txt"));
            almenu_osszetevo(lista,meret);
            break;
        }
        default:
            almenu_osszetevo(lista,meret);
            break;
    }
}

// Ebből a függvényből érhetőek el az új receptet létrehozó és összetevőket kezelő függvények.
void almenu_uj(char **lista,int meret){
    FILE *fp;
    int valasztas;
    char valasz[5];
    printf(" Van e új összetevő?");
    printf("\n 1. Van \n 2. Nincs \n 3. Nem tudom\n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:{
            lista = uj_osszetevo(lista,meret);
            printf("Szeretnél még valamit csinálni?");
            scanf("%s", &valasz);
            if(valaszt_tesztel(valasz) == 1){
                void almenu_uj(lista,meret);
            }
            else if(valaszt_tesztel(valasz) == 0){
                fp = fopen("osszetevok.txt","w");
                for(int i=0;i<meret;i++){
                    fprintf(fp,"%s",lista[i]);
                    fprintf(fp,"\n");
                }

            }
            break;
        }
        case 2:{
            uj_recept();
            //fomenu();
            break;
        }
        case 3:{
            char **lista = osszetevo_lista();
            listat_kiir(lista, sorokat_szamol("osszetevok.txt"));
            osszetevot_felszabadit(lista,sorokat_szamol("osszetevok.txt"));
            almenu_uj(lista,&meret);
            break;
        }
        default:
            almenu_uj(lista,&meret);
            break;
    }
}
// Innen lesznek elérhetőek a recept kezelő függvények. Megjegyzés: Még fejlesztés alatt.
 /* void almenu_recept(){
    int valasztas;
    printf("\n1.Recept módosítása \n 2. Recept törlése \n 3. Receptek listázása \n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:
            recept_modosit();
            break;
        case 2:
            recept_torol();
            break;
        case 3:
            recept_listaz();
            break;
        default:
            almenu_recept();
            break;
    }
}
// Innen lesznek elérhetőek a kereső függvények. Megjegyzés: Még fejlesuztés alatt.
void almenu_keres(){
    int valasztas;
    printf("\n1.Nincs ötletem \n 2. De innék egy kis.... \n 3. El kell használni.... \n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:
            nincs_otlet();
            break;
        case 2:
            innek_egy_kis();
            break;
        case 3:
            el_kell_hasznalni();
            break;
        default:
            almenu_keres();
            break;
    }
}
*/
