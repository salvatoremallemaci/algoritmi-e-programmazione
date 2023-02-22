#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ST.h"

//a=matrice di caratteri, ossia VETTORE DI STRINGHE.

struct symboltable{
char **a;
int N;
int M;
};

ST ST_init(int maxN){
    int i;
    ST st;

    st=malloc(sizeof(*st));
    st->a=malloc(maxN*sizeof(char *));
    //alloco il vettore di caratteri(stringa)
    for(i=0;i<maxN;i++){
        st->a[i]=malloc(maxN*sizeof(char));
        //alloco carattere per carattere, allocando cosi' la memoria per la matrice.
        st->a[i][0]='\0';
    }
    st->N=0;
    st->M=maxN;
    return st;
}

int ST_count(ST st){
    return st->N;
}

void ST_free(ST st){
    int i;
    for(i=0;i<st->M;i++){
        free(st->a[i]);
    }
    free(st->a);
    free(st);
}

void ST_insert(ST st, ITEM i, int index){
    int j;
    if(st->N>=st->M){
        st->a=realloc(st->a,2*st->M*sizeof(char*));
        st->M=2*(st->M);
        for(j=st->N;j<st->M;j++){
            st->a[j]=malloc(MAXC*sizeof(char));
        }
    }
    strncpy(st->a[index],ITEMgetLabel(i),MAXC);
    st->N++;
}

int ST_search(ST st, char *label){
    int i;

    for(i=0;i<st->N;i++){
        if(strcmp(label,st->a[i])==0) return i;
    }
    //-1=non trovato. e' pur sempre un vettore, dunque l'indice -1 non e' accessibile.
    return -1;
}

char *STsearchByIndex(ST st, int index){
    return strdup(st->a[index]);
}
