#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "equipArray.h"
#include "invArray.h"

struct invArray_s{
inv_t *vettInv;
};

struct equipArray_s{
inv_t *vettEq[EQUIP_SLOT];
};

equipArray_t equipArray_init(){
    int i;
    equipArray_t e;
    e=malloc(EQUIP_SLOT*sizeof(*e));

    if(e!=NULL){
        for(i=0;i<EQUIP_SLOT;i++){
            e->vettEq[i]->stat.hp=0;
            e->vettEq[i]->stat.mp=0;
            e->vettEq[i]->stat.atk=0;
            e->vettEq[i]->stat.def=0;
            e->vettEq[i]->stat.mag=0;
            e->vettEq[i]->stat.spr=0;
        }
    }
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}


int equipArray_inUse(equipArray_t equipArray){
    int i;
    int cont=0;
    for(i=0;i<EQUIP_SLOT;i++){
        if(strcmp(equipArray->vettEq[i]->nome,"\0")!=0){
            cont++;
        }
    }
    return cont;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    printf("Gli oggetti disponibili sono:\n");
    invArray_print(stdout,invArray);

    printf("Questo personaggio ha il seguente equipaggiamento:\n");
    for(i=0;i<EQUIP_SLOT;i++){
        fprintf(fp,"%s %s %d %d %d %d %d %d",
            equipArray->vettEq[i]->nome,
            equipArray->vettEq[i]->tipo,
            equipArray->vettEq[i]->stat.hp,
            equipArray->vettEq[i]->stat.mp,
            equipArray->vettEq[i]->stat.atk,
            equipArray->vettEq[i]->stat.def,
            equipArray->vettEq[i]->stat.mag,
            equipArray->vettEq[i]->stat.spr);
        printf("\n");
    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int i,j,cont=0,stop=-1;
    char stringa[MAXNOME];
    while(cont<EQUIP_SLOT || stop!=1){
        printf("Quale oggetto vuoi prendere? ");
        scanf("%s",stringa);
        for(i=0;i<maxInv;i++){
            if(strcmp(invArray->vettInv[i].nome,stringa)==0){
                cont++;
                for(j=0;j<EQUIP_SLOT;j++){
                    if(strcmp(equipArray->vettEq[j]->nome,"\0")==0){
                        strcpy(equipArray->vettEq[j]->nome,invArray->vettInv[i].nome);
                        strcpy(equipArray->vettEq[j]->tipo,invArray->vettInv[i].tipo);
                        equipArray->vettEq[j]->stat.hp=invArray->vettInv[i].stat.hp;
                        equipArray->vettEq[j]->stat.mp=invArray->vettInv[i].stat.mp;
                        equipArray->vettEq[j]->stat.atk=invArray->vettInv[i].stat.atk;
                        equipArray->vettEq[j]->stat.def=invArray->vettInv[i].stat.def;
                        equipArray->vettEq[j]->stat.mag=invArray->vettInv[i].stat.mag;
                        equipArray->vettEq[j]->stat.spr=invArray->vettInv[i].stat.spr;
                    }
                }
            }
        }
        printf("Vuoi fermarti? Digita 1.In caso contrario digita qualsiasi altro numero. ");
        scanf("%d",&stop);
    }
    if(cont==8){
        printf("Equipaggiamento al completo per il personaggio %s",stringa);
    }
}

//?
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    int i;
    char stringa[MAXNOME];
    for(i=0;i<maxInv;i++){
        if(strcmp(stringa,equipArray->vettEq[i]->nome)==0){
            index=i;
            return index;
        }
    }
    return -1;//?
}



