// Megjegyzések a kódhoz:
// 1. A legtöbb modulban vannak NTS kezdetű megjegyzések. Azaz Note To Self jegyzetek magamnak, hogy mit kell még javítanom. Ez a végleges kódban nem fog szerepelni. Úgy gondoltam, hogy bent hagyom a félkészben,
// mert így talán látszik, hogy milyen hibák vannak a programomban amivel én is tisztában vagyok, hogy hiba.
// 2. A program inputja egyelőre nem tud UTF-8-at, csak ASCII-t. Kész NHF-ban ez javítva lesz és az input is utf-8 lesz.

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "osszetevok.h"
#include "recept.h"
#include "uf.h"
#include "debugmalloc.h"

int main(void){
    system("chcp 65001 >nul");
    fomenu();
    return 0;

}
