#ifndef INV_H
#define INV_H

#define MAXNOME 50
#define MAXCODICE 7
#define MAXOGG 8

typedef struct stats{
int hp;
int mp;
int atk;
int def;
int mag;
int spr;
}stat_t;

typedef struct inv{
char nome[MAXNOME];
char tipo[MAXNOME];
stat_t stat_inv;
}inv_t;

//wrapper inventario
typedef struct {
    inv_t vettinv;
    int nInv;
    int maxInv;
}tabInv;

tabInv *carica_oggetti(FILE *fp);
tabInv *ricerca_oggetto(tabInv *p);
void stampa_inventario(tabInv *p);

#endif // INV_H
