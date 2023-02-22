#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNOME 50
#define MAXCODICE 7
#define MAXOGG 8

typedef enum{
e_carica_pg, e_carica_ogg, e_aggiungi_pg, e_elimina_pg, e_ricerca_oggetto, e_aggiungi_ogg_equip,
e_rimuovi_ogg_equip,e_stampa_inv_pg, e_stampa_personaggi, e_stampa_inventario,
e_stampa_stats_pg, e_fine,  e_err}cmd;


typedef struct stats{
int hp;
int mp;
int atk;
int def;
int mag;
int spr;
}stat_t;

typedef struct inv{
char nome[MAXNOME];
char tipo[MAXNOME];
stat_t stat_inv;
}inv_t;

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

//wrapper inventario
typedef struct {
    inv_t vettinv;
    int nInv;
    int maxInv;
}tabInv;

cmd opzioni();

link newNode(pg_t val,link next);

tabPg *crea_lista();

tabPg *carica_lista(FILE *fp);
tabInv *carica_oggetti(FILE *fp);
tabInv *ricerca_oggetto(tabInv *p);



int inserisci_lista(tabPg *qp,pg_t *d);
void stampa_lista(tabPg *qp);
void aggiungi_pg(tabPg *qp);
void libera_lista(tabPg *qp);
void cancella_pg(tabPg *qp);

void stampa_inventario(tabInv *p);

tabEquip_t *agg_oggetti_pg(tabPg *qp,tabInv *p);
void rim_oggetti_pg(tabPg *qp,tabInv *p,tabEquip_t *t);

void stampa_inv_pg(tabPg *qp,tabEquip_t *t);
void stampa_stats_pg(tabPg *qp,tabEquip_t *t);





int main()
{
    FILE *fp_pg;
    FILE *fp_inv;
    fp_pg=fopen("pg.txt","r");
    fp_inv=fopen("inventario.txt","r");

    if(fp_pg==NULL){
        printf("errore apertura file pg.txt.\n");
        return -1;
    }
    if(fp_inv==NULL){
        printf("errore apertura file inventario.txt.\n");
        return -1;
    }
    cmd comando;
    tabPg *l;
    //l=malloc(sizeof(*l));
    tabInv *v;
    //v=malloc(sizeof(*v));
    tabEquip_t *z;
    while((comando=opzioni())!=e_fine){
        switch(comando){

        case e_carica_pg:
            l=carica_lista(fp_pg);
        break;

        case e_carica_ogg:
            v=carica_oggetti(fp_inv);
        break;

        case e_ricerca_oggetto:
            ricerca_oggetto(v);
        break;

        case e_aggiungi_pg:
            aggiungi_pg(l);
        break;

        case e_elimina_pg:
            cancella_pg(l);

        break;

        case e_stampa_personaggi:
            stampa_lista(l);
        break;

        case e_stampa_inventario:
            stampa_inventario(v);
        break;

        case e_aggiungi_ogg_equip:
            z=agg_oggetti_pg(l,v);
        break;

        case e_rimuovi_ogg_equip:
            rim_oggetti_pg(l,v,z);
        break;

        case e_stampa_inv_pg:
            stampa_inv_pg(l,z);
        break;

        case e_stampa_stats_pg:
            stampa_stats_pg(l,z);
        break;
        }
    }
    libera_lista(l);
    fclose(fp_pg);
    fclose(fp_inv);
    return 0;
}


link newNode(pg_t val,link next){
    link x;
    x=malloc(MAXOGG*sizeof(*x));
    if(x==NULL){
        printf("errore di allocazione di memoria.\n");
        return NULL;
    }
    x->val=val;
    x->next=next;
    return x;
}

tabPg *crea_lista(){
    tabPg *qp;
    qp=(tabPg *)malloc(sizeof(tabPg));
    if(qp==NULL){
        printf("errore allocazione memoria.\n");
        return NULL;
    }
    qp->headPg=NULL;
    qp->nPg=0;
    return qp;
}



tabPg *carica_lista(FILE *fp){
    pg_t d;
    tabPg *qp;
    qp=crea_lista();
    if(qp==NULL){
        printf("errore allocazione memoria.\n");
        return NULL;
    }
    while(fscanf(fp,"%s %s %s %d %d %d %d %d %d",
                 d.codice,d.nome,d.classe,
                 &d.stat_pg.hp,
                 &d.stat_pg.mp,
                 &d.stat_pg.atk,
                 &d.stat_pg.def,
                 &d.stat_pg.mag,
                 &d.stat_pg.spr)!=EOF){
                 inserisci_lista(qp,&d);
    }
    return qp;
}

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


void aggiungi_pg(tabPg *qp){
    pg_t d;
    if(qp==NULL){
        qp=crea_lista();
    }
    printf("Personaggio da aggiungere:\n");
    printf("Codice: ");scanf("%s",d.codice);
    printf("Nome: ");scanf("%s",d.nome);
    printf("Classe: ");scanf("%s",d.classe);
    printf("Statistiche:\n");
    printf("HP: ");scanf("%d",&d.stat_pg.hp);
    printf("MP: ");scanf("%d",&d.stat_pg.mp);
    printf("ATK: ");scanf("%d",&d.stat_pg.atk);
    printf("DEF: ");scanf("%d",&d.stat_pg.def);
    printf("MAG: ");scanf("%d",&d.stat_pg.mag);
    printf("SPR: ");scanf("%d",&d.stat_pg.spr);
    inserisci_lista(qp,&d);
}
void cancella_pg(tabPg *qp){
    link x,p;
    char stringa[MAXNOME];
    if(qp->headPg==NULL){
        printf("Lista vuota,non ci sono personaggi da cancellare.\n");
        return;
    }
    printf("Quale personaggio bisogna cancellare? ");
    scanf("%s",stringa);
    for(x=qp->headPg,p=NULL; x!=NULL; p=x, x=x->next){
        if(strcmp(x->val.nome,stringa)==0){
            if(x==qp->headPg)
                qp->headPg=x->next;
            else
                p->next=x->next;
            free(x);
            qp->nPg--;
            break;
        }
    }
}

int inserisci_lista(tabPg *qp,pg_t *d){
    link t,p,x;
    //p punta al nodo che precederà,x punta al nodo che seguirà il nodo puntato da t quando inserito.
    if(qp==NULL){
        printf("errore allocazione dinamica.\n");
        return 1;
    }
    t=newNode(*d,NULL);
    if(t==NULL){
        printf("errore allocazione dinamica.\n");
        return 1;
    }
//caso lista vuota
    if(qp->headPg==NULL){
        qp->headPg=t;
    }else{
    x=qp->headPg;
    p=NULL;
    while(x!=NULL){
        p=x;
        x=x->next;
    }
//caso finale
    if(p==NULL){
        qp->tailPg=t;
        t->next=qp->headPg;
        qp->headPg=t;
    }else{
    t->next=x;
    p->next=t;
    qp->tailPg=t;
    }
}
    qp->nPg++;
    return 0;
}

void stampa_lista(tabPg *qp){
    link p;
    if(qp==NULL){
        printf("errore allocazione dinamica.\n");
        return;
    }

    p=qp->headPg;
    for(p;p!=NULL;p=p->next){
        printf("%s %s %s %d %d %d %d %d %d\n",p->val.codice,p->val.nome,p->val.classe,
               p->val.stat_pg.hp,
               p->val.stat_pg.mp,
               p->val.stat_pg.atk,
               p->val.stat_pg.def,
               p->val.stat_pg.mag,
               p->val.stat_pg.spr);
    }
    qp->tailPg=p;
    printf("Ci sono attualmente %d personaggi.\n",qp->nPg);
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

tabEquip_t *agg_oggetti_pg(tabPg *qp,tabInv *p){
    //in questo caso, la chiave di ricerca del personaggio e' il suo codice (traccia LAB8)
    char stringa_codice[MAXNOME];
    char stringa_oggetto[MAXNOME];
    int i,stop=-1,j;
    link x;
    malloc(MAXOGG*sizeof(*x));

    tabEquip_t *t;
    t=malloc(p->maxInv*sizeof(*t));

    printf("Il suo codice e': ");
    scanf("%s",stringa_codice);

    //cerco il personaggio all'interno della lista.

    //controllo lista vuota
    if(qp->headPg==NULL){
        printf("Lista vuota.\n");
        return;
    }

    t->inUso=0;
    j=-1;
    //scorro la lista, fino a che trovo il mio personaggio/non trovo il personaggio.
    x=qp->headPg;
    for(x=qp->headPg;x!=NULL;x=x->next){
            x->val.equip=t;
        if(strcmp(stringa_codice,x->val.codice)==0){
            while((t->inUso)<MAXOGG){
                    j++;
            printf("Quale oggetto vuoi prendere? ");
            scanf("%s",stringa_oggetto);
            for(i=0;i<p->maxInv;i++){
                if(strcmp(p[i].vettinv.nome,stringa_oggetto)==0){
                        x->val.equip->inUso++;
                        x->val.equip->vettEq[j]=&p[i].vettinv;
                    }
                }
                printf("Vuoi fermarti? Digita 1.In caso contrario digita qualsiasi altro numero. ");
                scanf("%d",&stop);
                if(stop==1){
                    return t;
                }

            }
            break;
        }
    }
    return t;
}

void rim_oggetti_pg(tabPg *qp,tabInv *p,tabEquip_t *t){
    char stringa_codice[MAXNOME];
    char stringa_oggetto[MAXNOME];
    int i,stop=-1;
    link x;
    malloc(MAXOGG*sizeof(*x));
    //j=-1;
    printf("Vuoi rimuovere oggetti dall'inventario del pg dal codice? ");scanf("%s",stringa_codice);
    x=qp->headPg;
    for(x=qp->headPg;x!=NULL;x=x->next){
        x->val.equip=t;
        if(strcmp(stringa_codice,x->val.codice)==0){
            while(x->val.equip->inUso!=0){
                printf("Quale oggetto vuoi rimuovere? ");
                scanf("%s",stringa_oggetto);
                for(i=0;i<(x->val.equip->inUso);i++){
                    if(strcmp(stringa_oggetto,x->val.equip->vettEq[i]->nome)==0){
                        //j++;
                        x->val.equip->inUso--;
                        strcpy(x->val.equip->vettEq[i]->nome,"\0");
                        strcpy(x->val.equip->vettEq[i]->tipo,"\0");
                        x->val.equip->vettEq[i]->stat_inv.hp=0;
                        x->val.equip->vettEq[i]->stat_inv.mp=0;
                        x->val.equip->vettEq[i]->stat_inv.atk=0;
                        x->val.equip->vettEq[i]->stat_inv.def=0;
                        x->val.equip->vettEq[i]->stat_inv.mag=0;
                        x->val.equip->vettEq[i]->stat_inv.spr=0;
                    }
                }
                printf("Vuoi fermarti? Digita 1.In caso contrario digita qualsiasi altro numero. ");
                scanf("%d",&stop);
                if(stop==1){
                    return;
                }
            }
            break;
        }
    }
    return;
}

void stampa_inv_pg(tabPg *qp,tabEquip_t *t){
    link x;
    char stringa_codice[MAXNOME];
    int i;
    if(qp==NULL){
        printf("Lista nulla/errori allocazione dinamica.\n");
        return;
    }
    printf("Inventario del pg di codice: ");scanf("%s",stringa_codice);
    for(x=qp->headPg;x!=NULL;x=x->next){
        if(strcmp(stringa_codice,x->val.codice)==0){
        printf("Il pg %s di codice %s possiede i seguenti oggetti nell'inventario:\n",x->val.nome,x->val.codice);
        x->val.equip=t;
        for(i=0;i<x->val.equip->inUso;i++){
            if(strcmp(x->val.equip->vettEq[i]->nome,"\0")!=0){
                printf("%s ",x->val.equip->vettEq[i]->nome);
                printf("%s ",x->val.equip->vettEq[i]->tipo);
                printf("%d ",x->val.equip->vettEq[i]->stat_inv.hp);
                printf("%d ",x->val.equip->vettEq[i]->stat_inv.mp);
                printf("%d ",x->val.equip->vettEq[i]->stat_inv.atk);
                printf("%d ",x->val.equip->vettEq[i]->stat_inv.def);
                printf("%d ",x->val.equip->vettEq[i]->stat_inv.mag);
                printf("%d\n",x->val.equip->vettEq[i]->stat_inv.spr);
                }
            }
        }
    }
}

void stampa_stats_pg(tabPg *qp,tabEquip_t *t){
    link x;
    int HP=0,MP=0,ATK=0,DEF=0,MAG=0,SPR=0;
    char stringa_codice[MAXNOME];
    int i;
    if(qp==NULL){
        printf("Lista nulla/errori allocazione dinamica.\n");
        return;
    }
    printf("Stampa le statistiche del pg dal codice: ");
    scanf("%s",stringa_codice);
    for(x=qp->headPg;x!=NULL;x=x->next){
        if(strcmp(stringa_codice,x->val.codice)==0){
            HP=x->val.stat_pg.hp;
            MP=x->val.stat_pg.mp;
            ATK=x->val.stat_pg.atk;
            DEF=x->val.stat_pg.def;
            MAG=x->val.stat_pg.mag;
            SPR=x->val.stat_pg.spr;
            printf("Questo pg ha stats base pari ad:\n");
            printf("HP:%d\n",HP);
            printf("MP:%d\n",MP);
            printf("ATK:%d\n",ATK);
            printf("DEF:%d\n",DEF);
            printf("MAG:%d\n",MAG);
            printf("SPR:%d\n",SPR);
            //APPLICO BONUS/MALUS DOVUTI AGLI OGGETTI DELL'INVENTARIO.
            for(i=0;i<(t->inUso);i++){
                HP=HP+x->val.equip->vettEq[i]->stat_inv.hp;
                MP=MP+x->val.equip->vettEq[i]->stat_inv.mp;
                ATK=ATK+x->val.equip->vettEq[i]->stat_inv.atk;
                DEF=DEF+x->val.equip->vettEq[i]->stat_inv.def;
                MAG=MAG+x->val.equip->vettEq[i]->stat_inv.mag;
                SPR=SPR+x->val.equip->vettEq[i]->stat_inv.spr;
            }
        }
    }
        if(HP<1)HP=1;
        if(MP<1)MP=1;
        if(ATK<1)ATK=1;
        if(DEF<1)DEF=1;
        if(MAG<1)MAG=1;
        if(SPR<1)SPR=1;

            printf("Applicando i bonus/malus dovuti all'inventario, le sue stats sono:\n");
            printf("HP:%d\n",HP);
            printf("MP:%d\n",MP);
            printf("ATK:%d\n",ATK);
            printf("DEF:%d\n",DEF);
            printf("MAG:%d\n",MAG);
            printf("SPR:%d\n",SPR);
}

void libera_lista(tabPg *qp){
    link t,p;

    if(qp==NULL){
        printf("errore allocazione dinamica.\n");
        return;
    }

        p=qp->headPg;
        while(p!=NULL){
            t=p;
            p=p->next;
            free(t->next);
            free(t);
        }
        free(qp);
    }

cmd opzioni(){
    int i;
    do{
    printf("1. Carica personaggi da file.\n");
    printf("2. Carica oggetti da file.\n");
    printf("3. Aggiungi personaggio da tastiera.\n");
    printf("4. Elimina un personaggio.\n");
    printf("5. Cerca un oggetto nell'inventario.\n");
    printf("6. Aggiungi oggetto ad un personaggio.\n");
    printf("7. Rimuovi oggetto ad un personaggio.\n");
    printf("8. Stampa inventario di un personaggio.\n");
    printf("9. Stampa personaggi.\n"); //V
    printf("10. Stampa inventario.\n"); //V
    printf("11. Stampa statistiche del personaggio.\n");
    printf("12. Esci.\n");
    printf("Inserisci il comando: ");
    scanf("%d", &i);
    i--;
    }while(i == e_err);
    return i;
}
