#ifndef PG_H
#define PG_H

#define MAXNOME 50
#define MAXCODICE 7
#define MAXOGG 8
#include "INV.h"


typedef struct equipaggiamento{
int inUso;
inv_t *vettEq[MAXOGG];
}tabEquip_t;

typedef struct pg{
char codice[MAXCODICE];
char nome[MAXNOME];
char classe[MAXNOME];
tabEquip_t *equip;
stat_t stat_pg;
}pg_t;

typedef struct nodePg_t *link;

struct nodePg_t{
pg_t val;
link next;
};

//wrapper personaggi
typedef struct{
link headPg;
link tailPg;
int nPg;
}tabPg;


link newNode(pg_t val,link next);

tabPg *crea_lista();
tabPg *carica_lista(FILE *fp);

int inserisci_lista(tabPg *qp,pg_t *d);
void stampa_lista(tabPg *qp);
void libera_lista(tabPg *qp);
void aggiungi_pg(tabPg *qp);
void cancella_pg(tabPg *qp);


tabEquip_t *agg_oggetti_pg(tabPg *qp,tabInv *p);
void rim_oggetti_pg(tabPg *qp,tabInv *p,tabEquip_t *t);

void stampa_inv_pg(tabPg *qp,tabEquip_t *t);
void stampa_stats_pg(tabPg *qp,tabEquip_t *t);

#endif // PG_H
