#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "INV.h"

void stat_read(FILE *fp, stat_t *statp){
    if(fp==NULL){
        printf("errore apertura file.\n");
        return;
    }
    fscanf(fp,"%d %d %d %d %d %d",
           &statp->hp,&statp->mp,&statp->atk,&statp->def,&statp->mag,&statp->spr);
}

void stat_print(FILE *fp, stat_t *statp, int soglia){

    if(statp->hp<soglia){
            printf("HP=1 ");}
        else{
            fprintf(fp,"HP=%d ",statp->hp);
        }
    if(statp->mp<soglia){
            printf("MP=1 ");}
        else{
            fprintf(fp,"MP=%d ",statp->mp);
        }
    if(statp->atk<soglia){
            printf("ATK=1 ");}
        else{
            fprintf(fp,"ATK=%d ",statp->atk);
        }
    if(statp->def<soglia){
            printf("DEF=1 ");}
        else{
            fprintf(fp,"DEF=%d ",statp->def);
        }
    if(statp->mag<soglia){
            printf("MAG=1 ");}
        else{
            fprintf(fp,"MAG=%d ",statp->mag);
        }
    if(statp->spr<soglia){
            printf("SPR=1\n");}
        else{
            fprintf(fp,"SPR=%d\n",statp->spr);
        }
}

void inv_read(FILE *fp, inv_t *invp){
    if(fp==NULL){
        printf("errore apertura file inventario.\n");
        return;
    }
    fscanf(fp,"%s %s %d %d %d %d %d %d",
           invp->nome,invp->tipo,
           &invp->stat.hp,&invp->stat.mp,&invp->stat.atk,&invp->stat.def,&invp->stat.mag,&invp->stat.spr);
}

void inv_print(FILE *fp, inv_t *invp){

    fprintf(fp,"%s %s %d %d %d %d %d %d",
            invp->nome,invp->tipo,invp->stat.hp,invp->stat.mp,invp->stat.atk,invp->stat.def,invp->stat.mag,invp->stat.spr);

}

stat_t inv_getStat(inv_t *invp){
    stat_t c;
    char stringa[MAXNOME];
    printf("Stats dell'oggetto in inventario: ");scanf("%s",stringa);

    if(strcmp(stringa,invp->nome)==0){
        c.hp=invp->stat.hp;
        c.mp=invp->stat.mp;
        c.atk=invp->stat.atk;
        c.def=invp->stat.def;
        c.mag=invp->stat.mag;
        c.spr=invp->stat.spr;
    }
    return c;
}


