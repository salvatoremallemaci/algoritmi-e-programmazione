#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"

//GRAFO NON ORIENTATO E PESATO

typedef struct node *link;

struct node{
int v;
//int wt;
link next;
};


struct graph{
int V;
int E;
int **Madj;
link* Ladj;
link z;
ST tab;
};

//standard e statica(si vede solo in questa modulo)
static int **MATRIXint(int r, int c, int val){
    int i,j;
    int **ret=malloc(r*sizeof(int *));
    for(i=0;i<r;i++)
        ret[i]=malloc(c*sizeof(int));

    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
        ret[i][j]=val;
    return ret;
}

//standard e statica(si vede solo in questa modulo)
static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v=v;
    e.w=w;
    e.wt=wt;
    return e;
}

static link NEWnode(int v, link next){
    link x = malloc(sizeof(*x));
    x->v = v;
    x->next = next;
    return x;
}

GRAPH GRAPH_init(int V){
    int i;

    GRAPH G=malloc(sizeof(*G));
    G->V=V;
    G->E=0;
    G->Madj=MATRIXint(V,V,0);
    G->Ladj=malloc(G->V*sizeof(*(G->Ladj)));
    G->z=NEWnode(-1,NULL);
    for(i = 0; i < G->V; i++){
        G->Ladj[i] = G->z;
    }
    G->tab=ST_init(V);
    return G;
}

void GRAPHfree(GRAPH G){
    int i;
    free(G->tab);
    for(i=0;i<G->V;i++){
        free(G->Madj[i]);
    }
}

static void insertE(GRAPH G, Edge e){
    int v,w,wt;
    v=e.v;
    w=e.w;
    wt=e.wt;
    if(G->Madj[v][w]==0)G->E++;
    G->Madj[v][w]=wt;
    G->Madj[w][v]=wt;
    //Si tratta di un grafo non orientato
    //Da cio' ne consegue che la matrice di adiacenza e' una matrice simmetrica.
}


void GRAPH_insertE(GRAPH G,int id1, int id2, int wt){
    insertE(G,EDGEcreate(id1,id2,wt));
}

/*ALGORITMO DI ORDINAMENTO RICORSIVO, UTILIZZATO SUCCESSIVAMENTE AL FINE DI DISPORRE IN ORDINE
  ALFABETICO I SINGOLI VERTICI ED ARCHI DEL GRAFO IN QUESTIONE*/

static void merge(char **vett, char **tmp, int l, int m, int r){
    int i, j, k;
    i = l;
    j = m+1;
    for(k = l; k <= r; k++){
        if(i > m){
            tmp[k] = vett[j++];
        } else if (j > r){
            tmp[k] = vett[i++];
        } else if (strcmp(vett[i], vett[j]) <= 0){
            tmp[k] = vett[i++];
        } else {
            tmp[k] = vett[j++];
        }
    }
    for(k = l; k <= r; k++){
        vett[k] = tmp[k];
    }
}
static void mergeSortR(char **vett, char **tmp, int l, int r){
    int m = (l+r)/2;
    if(l >= r) return;
    mergeSortR(vett, tmp, l, m);
    mergeSortR(vett, tmp, m+1, r);
    merge(vett, tmp, l, m, r);
}
static void mergeSort(char **vett, int n){
    char **tmp = malloc(sizeof(char *)*n);
    mergeSortR(vett, tmp, 0, n-1);
    free(tmp);
}

void GRAPH_printVERTEX(GRAPH G){
    int n,m;
    int i,t,k;
    char **vertici_nome;
    char **archi_incidenti;

    int index;

    //numero di vertici
    n=G->V;

    m=(G->V-1);
    t=0;i=0;

    vertici_nome=malloc(n*sizeof(char*));
    archi_incidenti=malloc(m*sizeof(char*));
    for(i=0;i<n;i++){
        vertici_nome[i]=strdup(STsearchByIndex(G->tab,i));
    }
    //ORDINO I VERTICI IN ORDIEN ALFABETICO
    mergeSort(vertici_nome,n);
    for(i=0;i<n;i++){
        t=0;
        printf("Nome del vertice: %s\n", vertici_nome[i]);
        index=ST_search(G->tab,vertici_nome[i]);
        for(k=0;k<G->V;k++){
            if(G->Madj[index][k]!=0){
                archi_incidenti[t++]=strdup(STsearchByIndex(G->tab,k));
            }
        }
    }
    //ORDINO GLI ARCHI INCIDENTI IN ORDIEN ALFABETICO
    mergeSort(archi_incidenti,t);
    printf("ARCHI INCIDENTI: \n");
    for(k=0;k<t;k++){
        printf("\t %s\n",archi_incidenti[k]);
        free(archi_incidenti);
    }
}

void GRAPHsetTab(GRAPH G, ST tab){
    ST_free(G->tab);
    G->tab = tab;
    return;
}

void GRAPH_sottografo_completo(GRAPH G, char **vertex){
    int i = 0;
    const int n = 3;
    int ad = 1;
    int v[3];
    for(i = 0; i < n; i++){
        v[i] = ST_search(G->tab, vertex[i]);
    }
    for(i = 0; i < n; i++){
        if(G->Madj[v[i]][v[(i+1)%n]] == 0)
            ad = 0;
    }
    if(ad == 0){
        printf("I tre vertici non formano un sottografo completo.\n");
    }else{
        printf("I tre vertici formano un sottografo completo.\n");
    }
}


//GENERO LA LISTA DI ADIACENZA A PARTIRE DALLA MATRICE DI ADIACENZA.
void GRAPHgenerateLadj(GRAPH G){
    int V=G->V;
    int i,j;

    for(i=0;i<V;i++){
        for(j=i+1;j<V;j++){
            if(G->Madj[i][j]!=0){
                //ESSENDO UN GRAFO NON ORDINATO, ANCHE LA LISTA DI ADIACENZA PRESENTA UNA PROPRIA SIMMETRIA.
                G->Ladj[i]=NEWnode(j,G->Ladj[i]);
                G->Ladj[j]=NEWnode(j,G->Ladj[j]);
            }
        }
    }
}

void GRAPHprintLadj(GRAPH G){
    int i;
    link x;
    for(i = 0; i < G->V; i++){
        printf("%s ", STsearchByIndex(G->tab, i));
        for(x = G->Ladj[i]; x != G->z; x = x->next){
            printf("-> %s", STsearchByIndex(G->tab, x->v));
        }
        printf("\n");
    }
}

