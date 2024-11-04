#include <stdio.h>
#include <stdbool.h>
#ifdef _WIN32
    #include <windows.h>
#endif
#include "osszetevok.c"

void almenu_osszetevo(void);
void almenu_uj(void);
void almenu_recept(void);
void almenu_keres(void);

void fomenu(void){
    int valasztas;
    printf("1.Összetevõk \n 2. Új koktékrecept felvétele \n 3. Receptek \n 4. Keresés \n Választás:");
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
        case 4:
            almenu_keres();
            break;
        default:
            fomenu();
            break;
    }
}

// A függvényeket megírni !!!
void almenu_osszetevo(){
    int valasztas;
    printf("1.Új összetevő hozzáadása \n 2. Összetevő törlése \n 3. Összetevők listája \n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:
            uj_osszetevo();
            break;
        case 2:
            osszetevo_torol();
            break;
        case 3:
            osszetevo_lista();
            break;
        default:
            almenu_osszetevo();
            break;
    }
}

void almenu_uj(){
    int valasztas;
    printf("Van e új összetevő?");
    printf("1.Van \n 2. Nincs \n 3. Nem tudom\n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:
            uj_osszetevo();
            break;
        case 2:
            uj_recept();
            break;
        case 3:
            osszetevo_lista();
            break;
        default:
            almenu_uj();
            break;
    }
}

void almenu_recept(){
    int valasztas;
    printf("1.Recept módosítása \n 2. Recept törlése \n 3. Receptek listázása \n Választás:");
    scanf("%d", &valasztas);
    switch(valasztas){
        case 1:
            almenu_recept_modosit();
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

void almenu_keres(){
    int valasztas;
    printf("1.Nincs ötletem \n 2. De innék egy kis.... \n 3. El kell használni.... \n Választás:");
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
