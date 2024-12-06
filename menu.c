#include <stdio.h>
#include <stdbool.h>
#include "osszetevok.h"
#include "recept.h"
#include "uf.h"
#include "debugmalloc.h"
#include "keres.h"


bool almenu_osszetevo();
bool almenu_uj();
bool almenu_recept();
bool almenu_keres();

// A főmenü függvény. A felhasználó innen kezdi a navigációját és ide tér majd vissza.
void fomenu(void){
    bool ellenorzo = true;
    Recept *eleje = NULL;
    recept_lista(&eleje);
    int receptek_szama = recept_szamolo(&eleje);
    Osszetevo lista = osszetevo_lista();
    while(ellenorzo){
        #ifdef _WIN32
        system("cls");
        #endif
        int valasztas;
        printf("NHF | Koktéloskönyv\n");
        printf("\n 1. Összetevõk \n 2. Új koktélrecept felvétele \n 3. Receptek \n 4. Keresés \n 5. Kilépés.... \n Választás:");
        scanf("%d", &valasztas);
        if(0 > valasztas || valasztas > 6){
            printf("Hibás index!");
            return;
        }
        switch(valasztas){
            case 1:{
                ellenorzo = almenu_osszetevo(&lista);
                break;
            }
            case 2:{
                ellenorzo = almenu_uj(&eleje, &lista);
                break;
            }
            case 3:{
                ellenorzo = almenu_recept(&eleje,receptek_szama);
                break;
            }
            case 4:{
                ellenorzo = almenu_keres(&eleje,receptek_szama);
                break;
            }
            case 5:
                osszetevot_fajlba_ir(lista);
                osszetevot_felszabadit(lista.o_lista,lista.meret);
                receptet_fajlba_ir(&eleje);
                receptet_felszabadit(&eleje);
                return;
        }
    }
}

// Ebből az almenüből érhetőek el az összetevő függvények.
bool almenu_osszetevo(Osszetevo *lista){
    //Osszetevo lista = osszetevo_lista();
    int valasztas;
    printf("\n 1. Új összetevő hozzáadása \n 2. Összetevő törlése \n 3. Összetevők listája \n 4. Visszalépés \n Választás:");
    scanf("%d", &valasztas);
    if(0 > valasztas || valasztas > 5){
        printf("Hibás index!\n");
        //osszetevot_felszabadit(lista.o_lista,lista.meret);
        return 0;
    }
    switch(valasztas){
        case 1:{
            bool van_e = true;
            do{
                char valasz[5];
                printf("Van még új összetevő?");
                scanf("%4s",valasz);
                if(valaszt_tesztel(valasz)  == 1){
                    uj_osszetevo(&lista,lista->meret);
                    lista->meret++;
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
                if(lista->meret == 1){
                    printf("Az utolsó elemet nem lehet törölni!\n");
                    osszetevot_felszabadit(lista->o_lista,lista->meret);
                    return 0;
                }
                printf("Van még törlendő elem?");
                scanf("%4s",valasz);
                if(valaszt_tesztel(valasz) == 1){
                    osszetevot_torol(&lista,lista->meret);
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
            break;
        }
        case 3: {
            listat_kiir(lista->o_lista, lista->meret );
            break;
        }
        case 4:{
            return 1;
        }
    }
    //osszetevot_fajlba_ir(lista);
    //osszetevot_felszabadit(lista.o_lista,lista.meret);
    bool van_e2 = true;
    char valasz2[5];
    while(van_e2 == true){
        printf("Szeretnél még valamit csinálni?");
        scanf("%4s",valasz2);
        if(valaszt_tesztel(valasz2) == 1){
            return 1;
        }
        else if (valaszt_tesztel(valasz2) == 0) {
            van_e2 = false;
            return 0;
        }
        else{
            printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
            van_e2 = true;
        }
    }
    return 1;
}

// Ebből a függvényből érhetőek el az új receptet létrehozó és összetevőket kezelő függvények.
bool almenu_uj(Recept **eleje,Osszetevo *lista){
    //Recept *eleje = NULL;
    //recept_lista(&eleje);
    //Osszetevo lista = osszetevo_lista();
    int valasztas;
    printf(" Van e új összetevő?");
    printf("\n 1. Van \n 2. Nincs \n 3. Nem tudom\n 4. Visszalépés \n Választás:");
    scanf("%d", &valasztas);
    if(0 > valasztas || valasztas > 5){
        printf("Hibás index!\n");
        //osszetevot_felszabadit(lista.o_lista,lista.meret);
        //receptet_felszabadit(&eleje);
        return 0;
    }
    switch(valasztas){
        case 1:{
            bool van_e = true;
            do{
                char valasz[5];
                printf("Van még új összetevő?");
                scanf("%s",valasz);
                if(valaszt_tesztel(valasz)  == 1){
                    uj_osszetevo(&lista,lista->meret);
                    lista->meret++;
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
            listat_kiir(lista->o_lista, lista->meret);
            break;
        }
        case 4:
            return 1;;
    }
    //osszetevot_fajlba_ir(lista);
    //osszetevot_felszabadit(lista.o_lista,lista.meret);
    //receptet_fajlba_ir(&eleje);
    //receptet_felszabadit(&eleje);
    char valasz[5];
    bool van_e2 = true;
    while(van_e2){
        printf("Szeretnél még valamit csinálni?");
        scanf("%4s",valasz);
        if(valaszt_tesztel(valasz) == 1){
            return 1;
        }
        else if (valaszt_tesztel(valasz) == 0) {
            van_e2 = false;
            return 0;
        }
        else{
            printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
            van_e2 = true;
        }
    }
    return 1;
}
// Innen elérhetőek a recept kezelő függvények.
bool almenu_recept(Recept **eleje,int receptek_szama){
    //Recept *eleje = NULL;
    //recept_lista(&eleje);
    //int receptek_szama = recept_szamolo(&eleje);
    int valasztas;
    int valasz;
    printf("\n 1. Recept módosítása \n 2. Recept törlése \n 3. Receptek listázása \n 4. Visszalépés..... \n Választás:");
    scanf("%d", &valasztas);
    if(0 > valasztas || valasztas > 5){
        printf("Hibás index!\n");
        receptet_felszabadit(eleje);
        return 0;
    }
    switch(valasztas){
        case 1:
            printf("Melyik receptet szeretnéd módosítani?\n");
            receptet_listaz(eleje);
            printf("\n Választás:");
            scanf("%d",&valasz);
            if(0 < valasz && valasz <= receptek_szama){
                recept_modosit(eleje,valasz);
            }
            else{
                printf("Hibás index!\n");
                fomenu();
            }
            break;
        case 2:{
            char valasz2[5];
            bool van_e = true;
            while(van_e){
                receptek_szama = recept_szamolo(eleje);
                if(receptek_szama == 1){
                printf("Az utolsó receptet nem lehet törölni!\n");
                break;
                }
                printf("Van még törlendő elem?");
                scanf("%5s",valasz2);
                if(valaszt_tesztel(valasz2) == 1){
                    printf("Melyik receptet szeretnéd törölni?\n");
                    receptet_listaz(eleje);
                    printf("\nVálasztás:");
                    scanf("%d",&valasz);
                    if(0 < valasz && valasz <= receptek_szama){
                        recept_torol(eleje,valasz);
                        van_e =true;
                    }
                    else{
                        printf("Hibás index!");
                        return 0;                    }
                }
                else if (valaszt_tesztel(valasz2) == 0) {
                    van_e = false;
                    break;
                }
                else{
                    printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
                    van_e = true;
                }


            }
            break;
        }
        case 3:{
            receptet_listaz(eleje);
            printf("\nTárolt receptek száma:%d \n",receptek_szama);
            break;
        }
        case 4:
            return 1;
            break;
    }
    //receptet_fajlba_ir(eleje);
    //receptet_felszabadit(eleje);
    bool van_e2 = true;
    char valasz3[5];
    while(van_e2){
        printf("Szeretnél még valamit csinálni?");
        scanf("%4s",valasz3);
        if(valaszt_tesztel(valasz3) == 1){
            return 1;
        }
        else if (valaszt_tesztel(valasz3) == 0) {
            van_e2 = false;
            return 0;
        }
        else{
            printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
            van_e2 = true;
        }
    }
    return 1;
}


// Innen érhetőek el a kereső függvények.
bool almenu_keres(Recept **eleje,int recept_szam){
    //Recept *eleje = NULL;
    //recept_lista(&eleje);
    //int recept_szam = recept_szamolo(&eleje);
    int valasztas;
    printf("\n 1. Nincs ötletem \n 2. De innék egy kis.... \n 3. El kell használni.... \n 4. Keresés név szerint \n 5. Visszalépés \n Választás:");
    scanf("%d", &valasztas);
    if(0 > valasztas || valasztas > 5){
        printf("Hibás index!\n");
        //receptet_felszabadit(eleje);
        return 0;
    }
    switch(valasztas){
        case 1:
            nincs_otlet(eleje,recept_szam);
            break;
        case 2:
            innek_egy_kis(eleje, recept_szam);
            break;
        case 3:
            el_kell_hasznalni(eleje,recept_szam);
            break;
        case 4:
            nev_szerint(eleje);
            break;
        case 5:
            return 1;
            break;
    }
    //receptet_felszabadit(&eleje);
    char valasz[5];
    bool van_e2 = true;
    while(van_e2){
        printf("Szeretnél még valamit csinálni?");
        scanf("%4s",valasz);
        if(valaszt_tesztel(valasz) == 1){
            return 1;
        }
        else if (valaszt_tesztel(valasz) == 0) {
            van_e2 = false;
            return 0;
        }
        else{
            printf("\nIsmeretlen valasztas kerlek az igen/nem szavakat vagy I/H betut adj meg\n");
            van_e2 = true;
        }
    }
    return 1;
}

