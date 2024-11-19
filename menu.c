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

/*typdef struct List{
    char ** osszetevok;
    int meret;
} List;*/

void almenu_osszetevo();
void almenu_uj();
void almenu_recept(void);
void almenu_keres(void);

// A főmenü függvény. A felhasználó innen kezdi a navigációját és ide tér majd vissza.
void fomenu(void){
    int valasztas;
    printf("NHF | Koktéloskönyv\n");
    printf("\n 1. Összetevõk \n 2. Új koktélrecept felvétele \n 3. Receptek \n 4. Keresés \n 5. Kilépés.... \n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:
            almenu_osszetevo();
            break;
        case 2:
            almenu_uj();
            break;
        case 3:
            almenu_recept();
            break;
        /*case 4:
            almenu_keres();
            break;*/
        case 5:
            return;
        default:
            fomenu();
            break;
    }
}

// Ebből az almenüből érhetőek el az összetevő függvények.
void almenu_osszetevo(){
    int meret = sorokat_szamol("osszetevok.txt");
    FILE *fp;
    int valasztas;
    char valasz[5];
    printf("\n 1. Új összetevő hozzáadása \n 2. Összetevő törlése \n 3. Összetevők listája \n 4. Visszalépés \n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:{
            printf("Szeretnél még valamit csinálni?");
            scanf("%s", &valasz);
            if(valaszt_tesztel(valasz) == 1){
                almenu_osszetevo();
            }
            else if(valaszt_tesztel(valasz) == 0){
                fp = fopen("osszetevok.txt","w");
                for(int i=0;i<meret;i++){
                    //fprintf(fp,"%s",ujlista[i]);
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
            //listat_kiir(lista, sorokat_szamol("osszetevok.txt"));
            //osszetevot_felszabadit(lista,sorokat_szamol("osszetevok.txt"));
            almenu_osszetevo();
            break;
        }
        case 4:
            fomenu();
        default:
            almenu_osszetevo();
            break;
    }
}

// Ebből a függvényből érhetőek el az új receptet létrehozó és összetevőket kezelő függvények.
void almenu_uj(){
    Recept *eleje = NULL;
    recept_lista(&eleje);
    int valasztas;
    printf(" Van e új összetevő?");
    printf("\n 1. Van \n 2. Nincs \n 3. Nem tudom\n 4. Visszalépés \n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:{
            break;
        }
        case 2:{
            char valasz[5];
            bool van_e = true;
            while(van_e == true){
                printf("Szeretnél még új receptet hozzáadni?");
                scanf("%s",valasz);
                if (valaszt_tesztel(valasz) == 1){
                    uj_recept(&eleje);
                }
                else if (valaszt_tesztel(valasz) == 0) {
                    van_e = false;
                }
                else{
                    printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
                    van_e = true;
                }
            }
            break;
        }
        case 3:{
            char **lista = osszetevo_lista();
            listat_kiir(lista, sorokat_szamol("osszetevok.txt"));
            osszetevot_felszabadit(lista,sorokat_szamol("osszetevok.txt"));
            break;
        }
        case 4:
            fomenu();
        default:
            break;
    }
    receptet_fajlba_ir(&eleje);
    receptet_felszabadit(&eleje);
    return 0;
}
// Innen lesznek elérhetőek a recept kezelő függvények. Megjegyzés: Még fejlesztés alatt.
void almenu_recept(){
    Recept *eleje = NULL;
    recept_lista(&eleje);
    int valasztas;
    int valasz;
    int receptek_szama = recept_szamolo(&eleje);
    printf("\n1.Recept módosítása \n 2. Recept törlése \n 3. Receptek listázása \n 4. Visszalépés..... Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:
            //recept_modosit();
            break;
        case 2:
            printf("Melyik receptet szeretnéd törölni?");
            for(int i=0;i<receptek_szama;i++){
                recept_listaz(&eleje);
            }
            scanf("%d",&valasz);
            if(0 < valasz && valasz <= receptek_szama){
                recept_torol(&eleje,valasz);
            }
            else{
                printf("Hibás index!");
                fomenu();
            }
            break;
        case 3:
            recept_listaz(&eleje);
            break;
        case 4:
            fomenu();
            break;
        default:
            almenu_recept();
            break;
    }
}
// Innen lesznek elérhetőek a kereső függvények. Megjegyzés: Még fejlesuztés alatt.
/*void almenu_keres(){
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
}*/

