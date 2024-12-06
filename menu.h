#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "osszetevok.h"
#include "recept.h"
#include <stdbool.h>
void fomenu();
bool almenu_osszetevo(Osszetevo *lista);
bool almenu_uj(Recept **eleje,Osszetevo *lista);
bool almenu_recept(Recept **eleje,int receptek_szama);
bool almenu_keres(Recept **eleje,int recept_szam);

#endif // MENU_H_INCLUDED
