#include <stdio.h>
#include <stdlib.h>
#define max 50;

typedef struct node* link;


typedef struct{
char codice[6];
char nome[max];
char cognome[max];
int giorno
int mese
int anno
char via[max];
char citta[max];
int cap;
}Item;

struct node{
    Item item;
    link next;
};

typedef struct list{
    link head;
    int num;
}lista;

link NEW(item val,link next){
    link tmp=malloc(sizeof(struct node));
    if(tmp==NULL){
        printf("errore di allocazione memoria.\n");
        return NULL;
    }
    tmp->item=val;
    tmp->next=next;
    return tmp;
}
lista *crea_lista(){
    lista *qp;

    qp=(lista *)malloc(sizeof(lista));
    if(qp==NULL){
        printf("errore di allocazione memoria.\n");
        return NULL;
    }
    qp->head=NULL;
    qp->num=0;
    return qp;
}

void libera_lista(lista *qp){
    link t,p;

    if(qp==NULL) return;

    p=qp->head;
    while(p!=NULL){
        t=p;
        p=p->next;
        free(t->item);
        free(t);
    }
    free(qp);
}

int inserisci_lista(lista *qp,Item val){
    lin t,p,x;

    if(qp==NULL)return 1;
    t=NEW(val,NULL);
    if(t==NULL)return 1;

    if(qp->head==NULL){
        qp->head=t;
    }else{
    x=qp->head;
    p=NULL;
    while(x!=NULL && ((x->val)-val)<0){
        p=x;
        x=x->next;
    }
    if(p==NULL){
        t->next=qp->head;
        qp->head=t;
        else{
            t->next=x;
            qp->next=t;
        }
    }
    qp->num++;
    }
return 0;
}

void stampa_lista(FILE *fp,lista *qp){
    link p;

    if(qp==NULL) return;

    p=qp->head;
    while(p!=NULL){
        fprintf(fp,")
    }



}




int main()
{
    printf("Hello world!\n");
    return 0;
}
