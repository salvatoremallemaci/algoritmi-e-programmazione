#ifndef INV_H
#define INV_H

#define MAXNOME 50
#define MAXCODICE 7
#define MIN_STAT 1
#define maxInv 15

/* quasi ADT statistiche */
typedef struct stats{
int hp;
int mp;
int atk;
int def;
int mag;
int spr;
}stat_t;

/* quasi ADT oggetto di inventario */
typedef struct inv{
char nome[MAXNOME];
char tipo[MAXNOME];
stat_t stat;
}inv_t;

/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp);
void stat_print(FILE *fp, stat_t *statp, int soglia);

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp);
void inv_print(FILE *fp, inv_t *invp);

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp);


#endif // INV_H
