#ifndef KERES_H_INCLUDED
#define KERES_H_INCLUDED

bool van_e_benne(char** o_lista,int o_meret,char *keres);
void innek_egy_kis(Recept **eleje,int recept_szam);
void el_kell_hasznalni(Recept **eleje,int recept_szam);
void nincs_otlet(Recept **eleje,int receptek_szama);
void nev_szerint(Recept **eleje);

#endif // KERES_H_INCLUDED
