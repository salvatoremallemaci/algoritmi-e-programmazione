#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pgList.h"

typedef struct node *link;

struct node{
    pg_t val;
    link next;
};

struct pgList_s{
    link headPg;
    link tailPg;
    int nPg;
};

link newNode(pg_t val,link next);
int inserisci_lista(pgList_t pgList,pg_t *d);

link newNode(pg_t val,link next){
    link x;
    x=malloc(EQUIP_SLOT*sizeof(*x));
    if(x==NULL){
        printf("errore di allocazione di memoria.\n");
        return NULL;
    }
    x->val=val;
    x->next=next;
    return x;

}

pgList_t pgList_init(){
    pgList_t qp;
    qp=malloc(sizeof(pgList_t));
    if(qp==NULL){
        printf("Errore allocazione dinamica in lista.\n");
    }
    qp->headPg=NULL;
    qp->nPg=0;
    return qp;

}

int inserisci_lista(pgList_t pgList,pg_t *d){
    link t,p,x;
    //p punta al nodo che precederà,x punta al nodo che seguirà il nodo puntato da t quando inserito.
    if(pgList==NULL){
        printf("errore allocazione dinamica.\n");
        return 1;
    }
    t=newNode(*d,NULL);
    if(t==NULL){
        printf("errore allocazione dinamica.\n");
        return 1;
    }
//caso lista vuota
    if(pgList->headPg==NULL){
        pgList->headPg=t;
    }else{
    x=pgList->headPg;
    p=NULL;
    while(x!=NULL){
        p=x;
        x=x->next;
    }
//caso finale
    if(p==NULL){
        pgList->tailPg=t;
        t->next=pgList->headPg;
        pgList->headPg=t;
    }else{
    t->next=x;
    p->next=t;
    pgList->tailPg=t;
    }
}
    pgList->nPg++;
    return 0;
}


void pgList_free(pgList_t pgList){
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList){

    pg_t d;
    pgList_init();
    if(pgList==NULL){
        printf("errore allocazione memoria.\n");
        return NULL;
    }
    while(fscanf(fp,"%s %s %s %d %d %d %d %d %d",
                 d.cod,d.nome,d.classe,
                 &d.b_stat.hp,
                 &d.b_stat.mp,
                 &d.b_stat.atk,
                 &d.b_stat.def,
                 &d.b_stat.mag,
                 &d.b_stat.spr)!=EOF){
                 inserisci_lista(pgList,&d);
    }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link p;
    if(pgList==NULL){
        printf("errore allocazione dinamica.\n");
        return;
    }

    p=pgList->headPg;
    for(p;p!=NULL;p=p->next){
        fprintf(fp,"%s %s %s %d %d %d %d %d %d\n",p->val.cod,p->val.nome,p->val.classe,
               p->val.b_stat.hp,
               p->val.b_stat.mp,
               p->val.b_stat.atk,
               p->val.b_stat.def,
               p->val.b_stat.mag,
               p->val.b_stat.spr);
    }
    pgList->tailPg=p;
    printf("Ci sono attualmente %d personaggi.\n",pgList->nPg);
}

void pgList_insert(pgList_t pgList, pg_t pg){

    if(pgList==NULL){
        pgList=pgList_init();
    }
    printf("Personaggio da aggiungere:\n");
    printf("Codice: ");scanf("%s",pg.cod);
    printf("Nome: ");scanf("%s",pg.nome);
    printf("Classe: ");scanf("%s",pg.classe);
    printf("Statistiche:\n");
    printf("HP: ");scanf("%d",&pg.b_stat.hp);
    printf("MP: ");scanf("%d",&pg.b_stat.mp);
    printf("ATK: ");scanf("%d",&pg.b_stat.atk);
    printf("DEF: ");scanf("%d",&pg.b_stat.def);
    printf("MAG: ");scanf("%d",&pg.b_stat.mag);
    printf("SPR: ");scanf("%d",&pg.b_stat.spr);
    inserisci_lista(pgList,&pg);

}


void pgList_remove(pgList_t pgList, char* cod){
    link x,p;

    if(pgList->headPg==NULL){
        printf("Lista vuota,non ci sono personaggi da cancellare.\n");
        return;
    }
    for(x=pgList->headPg,p=NULL; x!=NULL; p=x, x=x->next){
        if(strcmp(x->val.cod,cod)==0){
            if(x==pgList->headPg)
                pgList->headPg=x->next;
            else
                p->next=x->next;
            free(x);
            pgList->nPg--;
            break;
        }
    }
}


pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    malloc(EQUIP_SLOT*sizeof(*x));
    x=pgList->headPg;

     //controllo lista vuota
    if(pgList->headPg==NULL){
        printf("Lista vuota.\n");
        return NULL;
    }

    for(x=pgList->headPg;x!=NULL;x=x->next){
        if(strcmp(x->val.cod,cod)==0){
            return *(x->val.cod);
        }
    }
    return NULL;
}
