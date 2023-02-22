#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "PG.h"

int pg_read(FILE *fp, pg_t *pgp){
    int cont=0;
    if(fp==NULL){
        printf("errore apertura file\n");
        return -1;
    }
    equipArray_init();
    fscanf(fp,"%s %s %s %d %d %d %d %d %d",
           pgp->cod,pgp->nome,pgp->classe,
           &pgp->b_stat.hp,
           &pgp->b_stat.mp,
           &pgp->b_stat.atk,
           &pgp->b_stat.def,
           &pgp->b_stat.mag,
           &pgp->b_stat.spr);
           cont++;
    return cont;
}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    //int i;

    printf("Gli oggetti disponibili sono:\n");
    invArray_print(stdout,invArray);

    printf("Ci sono i seguenti personaggi:\n");

    fprintf(stdout,"%s %s %s %d %d %d %d %d %d",
            pgp->cod,pgp->nome,pgp->classe,
            pgp->b_stat.hp,
            pgp->b_stat.mp,
            pgp->b_stat.atk,
            pgp->b_stat.def,
            pgp->b_stat.mag,
            pgp->b_stat.spr);
    printf("\n");
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    printf("Vuoi modificare l'equipaggiamento di quale personaggio? ");
    equipArray_update(pgp->equip,invArray);
}
