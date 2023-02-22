#ifndef MENU_H
#define MENU_H

typedef struct{
char *nome;
char *portata;
char *tipologia;
float costo;
}piatti;

typedef struct{
int *menu;
float prezzo;
}MENU;

MENU *MENUinit(int P);
void MENUprint(int P,MENU *ElencoMenu,piatti *ElencoPiatti);
void COMB_RIP_WRAPPER(MENU *ElencoMenu,piatti *ElencoPiatti,int P,int N);
void COMB_RIP(MENU *ElencoMenu,piatti *ElencoPiatti,int pos,int start,int *sol,int *mark,int P,int N);
#endif // MENU_H
