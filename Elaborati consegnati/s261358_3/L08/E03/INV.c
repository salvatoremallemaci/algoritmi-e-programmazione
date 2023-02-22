#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "INV.h"

tabInv *carica_oggetti(FILE *fp){
    int i,numero_oggetti;
    tabInv *p;
    fscanf(fp,"%d",&numero_oggetti);
    p=malloc(numero_oggetti*sizeof(tabInv));
    p->maxInv=numero_oggetti;

    for(i=0;i<p->maxInv;i++){
        fscanf(fp,"%s %s %d %d %d %d %d %d",
                 p[i].vettinv.nome,p[i].vettinv.tipo,&p[i].vettinv.stat_inv.hp,
                 &p[i].vettinv.stat_inv.mp,&p[i].vettinv.stat_inv.atk,&p[i].vettinv.stat_inv.def,
                 &p[i].vettinv.stat_inv.mag,&p[i].vettinv.stat_inv.spr);
    }
    return p;
}

tabInv *ricerca_oggetto(tabInv *p){
    int i;
    char stringa_oggetto[MAXNOME];
    printf("Quale oggetto vuoi cercare? ");
    scanf("%s",stringa_oggetto);

    for(i=0;i<p->maxInv;i++){
        if(strcmp(stringa_oggetto,p[i].vettinv.nome)==0){
            printf("Oggetto presente nell'inventario!\n");
            printf("L'oggetto e' un/a %s\n",p[i].vettinv.tipo);
            printf("Presenta le seguenti statistiche:\n");
            printf("HP:%d\nMP:%d\nATK:%d\nDEF:%d\nMAG:%d\nSPR:%d",
                   p[i].vettinv.stat_inv.hp,
                   p[i].vettinv.stat_inv.mp,
                   p[i].vettinv.stat_inv.atk,
                   p[i].vettinv.stat_inv.def,
                   p[i].vettinv.stat_inv.mag,
                   p[i].vettinv.stat_inv.spr);
            printf("\n");
        }
    }
}

void stampa_inventario(tabInv *p){
    int i;
    for(i=0;i<p->maxInv;i++){
        printf("%s %s %d %d %d %d %d %d",
                 p[i].vettinv.nome,p[i].vettinv.tipo,p[i].vettinv.stat_inv.hp,
                 p[i].vettinv.stat_inv.mp,p[i].vettinv.stat_inv.atk,p[i].vettinv.stat_inv.def,
                 p[i].vettinv.stat_inv.mag,p[i].vettinv.stat_inv.spr);
        printf("\n");
    }
}

