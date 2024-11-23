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
#include "keres.h"

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
    if(0 > valasztas || valasztas > 6){
        printf("Hibás index!");
        return;
    }
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
        case 4:
            almenu_keres();
            break;
        case 5:
            return;
    }
}

// Ebből az almenüből érhetőek el az összetevő függvények.
void almenu_osszetevo(){
    Osszetevo lista = osszetevo_lista();
    int valasztas;
    printf("\n 1. Új összetevő hozzáadása \n 2. Összetevő törlése \n 3. Összetevők listája \n 4. Visszalépés \n Választás:");
    scanf("%d", &valasztas);
    if(0 > valasztas || valasztas > 5){
        printf("Hibás index!\n");
        osszetevot_felszabadit(lista.o_lista,lista.meret);
        return;
    }
    switch(valasztas){
        case 1:{
            bool van_e = true;
            do{
                char valasz[5];
                printf("Van még új összetevő?");
                scanf("%s",valasz);
                if(valaszt_tesztel(valasz)  == 1){
                    uj_osszetevo(&lista,lista.meret);
                    lista.meret++;
                }
                else if(valaszt_tesztel(valasz) == 0) {
                    van_e = false;
                }
                else{
                printf("\nIsmeretlen választás kérlek az igen/nem szavakat vagy I/H betut adj meg\n");
                van_e = true;
                }
        }while(van_e);
        break;
        }
        case 2:{
            bool van_e = true;
            char valasz[5];
            while(van_e == true){
                if(lista.meret == 1){
                    printf("Az utolsó elemet nem lehet törölni!\n");
                    osszetevot_felszabadit(lista.o_lista,lista.meret);
                    return;
                }
                printf("Van még törlendő elem?");
                scanf("%5s",valasz);
                if(valaszt_tesztel(valasz) == 1){
                    osszetevot_torol(&lista,lista.meret);
                    lista.meret--;
                    van_e =true;
                }
                else if (valaszt_tesztel(valasz) == 0) {
                    van_e = false;
                    break;
                }
                else{
                    printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
                    van_e = true;
                }
            }
        }
        case 3: {
            listat_kiir(lista.o_lista, lista.meret );
            break;
        }
        case 4:
            fomenu();
    }
    osszetevot_fajlba_ir(lista);
    osszetevot_felszabadit(lista.o_lista,lista.meret);
}

// Ebből a függvényből érhetőek el az új receptet létrehozó és összetevőket kezelő függvények.
void almenu_uj(){
    Recept *eleje = NULL;
    recept_lista(&eleje);
    Osszetevo lista = osszetevo_lista();
    int valasztas;
    printf(" Van e új összetevő?");
    printf("\n 1. Van \n 2. Nincs \n 3. Nem tudom\n 4. Visszalépés \n Választás:");
    scanf("%d", &valasztas);
    if(0 > valasztas || valasztas > 5){
        printf("Hibás index!\n");
        osszetevot_felszabadit(lista.o_lista,lista.meret);
        receptet_felszabadit(&eleje);
             return;
    }
    switch(valasztas){
        case 1:{
            bool van_e = true;
            do{
                char valasz[5];
                printf("Van még új összetevő?");
                scanf("%s",valasz);
                if(valaszt_tesztel(valasz)  == 1){
                    uj_osszetevo(&lista,lista.meret);
                    lista.meret++;
                }
                else if(valaszt_tesztel(valasz) == 0) {
                    van_e = false;
                }
                else{
                printf("\nIsmeretlen választás kérlek az igen/nem szavakat vagy I/H betut adj meg\n");
                van_e = true;
                }
            }while(van_e);
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
            listat_kiir(lista.o_lista, lista.meret);
            break;
        }
        case 4:
            fomenu();
    }
    osszetevot_fajlba_ir(lista);
    osszetevot_felszabadit(lista.o_lista,lista.meret);
    receptet_fajlba_ir(&eleje);
    receptet_felszabadit(&eleje);
}
// Innen elérhetőek a recept kezelő függvények. Megjegyzés: kész
void almenu_recept(){
    Recept *eleje = NULL;
    recept_lista(&eleje);
    int receptek_szama = recept_szamolo(&eleje);
    int valasztas;
    int valasz;
    printf("\n 1. Recept módosítása \n 2. Recept törlése \n 3. Receptek listázása \n 4. Visszalépés..... \n Választás:");
    scanf("%d", &valasztas);
    if(0 > valasztas || valasztas > 5){
        printf("Hibás index!\n");
        receptet_felszabadit(&eleje);
        return;
    }
    switch(valasztas){
        case 1:
            printf("Melyik receptet szeretnéd módosítani?\n");
            receptet_listaz(&eleje);
            printf("\n Választás:");
            scanf("%d",&valasz);
            if(0 < valasz && valasz <= receptek_szama){
                recept_modosit(&eleje,valasz);
            }
            else{
                printf("Hibás index!\n");
                fomenu();
            }
            break;
        case 2:
            if(receptek_szama == 1){
                printf("Az utolsó receptet nem lehet törölni!\n");
                break;
            }
            printf("Melyik receptet szeretnéd törölni?\n");
            receptet_listaz(&eleje);
            printf("\nVálasztás:");
            scanf("%d",&valasz);
            if(0 < valasz && valasz <= receptek_szama){
                recept_torol(&eleje,valasz);
            }
            else{
                printf("Hibás index!");
                fomenu();
            }
            break;
        case 3:{
            receptet_listaz(&eleje);
            printf("\nTárolt receptek száma:%d \n",receptek_szama);
            break;
        }
        case 4:
            fomenu();
            break;
    }
    receptet_fajlba_ir(&eleje);
    receptet_felszabadit(&eleje);
}
// Innen lesznek elérhetőek a kereső függvények. Megjegyzés: Még fejlesuztés alatt.
void almenu_keres(){
    Recept *eleje = NULL;
    recept_lista(&eleje);
    int recept_szam = recept_szamolo(&eleje);
    int valasztas;
    printf("\n 1. Nincs ötletem \n 2. De innék egy kis.... \n 3. El kell használni.... \n 4. Keresés név szerint \n 5. Visszalépés \n Választás:");
    scanf("%d", &valasztas);
    if(0 > valasztas || valasztas > 5){
        printf("Hibás index!\n");
        receptet_felszabadit(&eleje);
        return;
    }
    switch(valasztas){
        case 1:
            nincs_otlet(&eleje,recept_szam);
            break;
        case 2:
            innek_egy_kis(&eleje, recept_szam);
            break;
        case 3:
            el_kell_hasznalni(&eleje,recept_szam);
            break;
        case 4:
            //nev_szerint();
            break;
        case 5:
            fomenu();
            break;
    }
    receptet_felszabadit(&eleje);
}

