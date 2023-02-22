#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "invArray.h"



struct invArray_s{
inv_t *vettInv;
};

invArray_t invArray_init(){
    //int i;
    invArray_t c;
    c=malloc(maxInv*sizeof(invArray_t));
    /*
    if(c!=NULL){
        //for(i=0;i<maxInv;i++){
            c->vettInv->stat.hp=0;
            c->vettInv->stat.mp=0;
            c->vettInv->stat.atk=0;
            c->vettInv->stat.def=0;
            c->vettInv->stat.mag=0;
            c->vettInv->stat.spr=0;
        //}
    }
    */
}

void invArray_free(invArray_t invArray){
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray){
    int i;
    for(i=0;i<maxInv;i++){
        //inv_read(fp,&invArray[i].vettInv);
        fscanf(fp,"%s %s %d %d %d %d %d %d",
               invArray->vettInv[i].nome,
               invArray->vettInv[i].tipo,
               &invArray->vettInv[i].stat.hp,
               &invArray->vettInv[i].stat.mp,
               &invArray->vettInv[i].stat.atk,
               &invArray->vettInv[i].stat.def,
               &invArray->vettInv[i].stat.mag,
               &invArray->vettInv[i].stat.spr);
    }
}

void invArray_print(FILE *fp, invArray_t invArray){
    int i;
    for(i=0;i<maxInv;i++){
        //inv_print(fp,&invArray[i].vettInv)
        fprintf(fp,"%s %s %d %d %d %d %d %d",
                invArray->vettInv[i].nome,
                invArray->vettInv[i].tipo,
                invArray->vettInv[i].stat.hp,
                invArray->vettInv[i].stat.mp,
                invArray->vettInv[i].stat.atk,
                invArray->vettInv[i].stat.def,
                invArray->vettInv[i].stat.mag,
                invArray->vettInv[i].stat.spr);
        printf("\n");
    }
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    int i;
    char stringa[MAXNOME];
    for(i=0;i<maxInv;i++){
        if(strcmp(stringa,invArray->vettInv[i].nome)==0){
            index=i;
        }
    fprintf(fp,"%s %s %d %d %d %d %d %d",
            invArray->vettInv[index].nome,
            invArray->vettInv[index].tipo,
            invArray->vettInv[index].stat.hp,
            invArray->vettInv[index].stat.mp,
            invArray->vettInv[index].stat.atk,
            invArray->vettInv[index].stat.def,
            invArray->vettInv[index].stat.mag,
            invArray->vettInv[index].stat.spr);
    }
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    if(invArray==NULL){
        return NULL;
    }
    else{
        return &invArray->vettInv[index];
    }
}

int invArray_searchByName(invArray_t invArray, char *name){
    int i;

    for(i=0;i<maxInv;i++){
        if(strcmp(name,invArray->vettInv[i].nome))
            return i;
    }
    return -1;//?
}



