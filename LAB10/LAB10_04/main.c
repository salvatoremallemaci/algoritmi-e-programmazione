#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"
#include "Graph.h"

#define MAXL 30

GRAPH fileRead(FILE *fp, ST *tmp, ITEM **vertex, int *n, int *m);

int main(int argc, char *argv[])
{
    FILE *fp;
    char FILENAME[MAX];
    strcpy(FILENAME,argv[1]);
    fp=fopen(FILENAME,"r");
    if(fp==NULL){
        printf("ERRORE LETTURA FILE.\n");
        return -1;
    }

    ITEM *vertex;
    int nVertex;
    int maxVertex;
    ST itemST;
    GRAPH G;
    G=fileRead(fp,&itemST,&vertex,&nVertex,&maxVertex);
    GRAPHsetTab(G,itemST);
    GRAPH_printVERTEX(G);
    /*
    char **subg = malloc(sizeof(char *)*3);
    printf("Inserisci il nome dei tre vertici: ");
    for(int i = 0; i < 3; i++){
        subg[i] = malloc(sizeof(char)*MAXL);
        scanf("%s", subg[i]);
    }
    GRAPH_sottografo_completo(G, subg);
    */
    GRAPHgenerateLadj(G);
    GRAPHprintLadj(G);
    return 0;
}


GRAPH fileRead(FILE *fp, ST *tmp, ITEM **vertex, int *n, int *m){
    GRAPH G;
    ITEM it1, it2;
    int id1, id2;
    int wt;
    char label1[30], label2[30];
    *tmp = ST_init(4);
    int M = 4;
    *vertex = malloc(sizeof(**vertex)*M);
    *n = 0;
    while(!feof(fp)){
        fscanf(fp, "%s %s", label1, label2);
        it1 = ITEMnew(label1, label2);
        id1 = ST_search(*tmp, label1);
        fscanf(fp, "%s %s %*d", label1, label2);
        it2 = ITEMnew(label1, label2);
        id2 = ST_search(*tmp, label1);
        if(id1 < 0){
            ST_insert(*tmp, it1, ST_count(*tmp));
            if(*n == M){
                M = M*2;
                *vertex = realloc(*vertex, sizeof(**vertex)*M);
            }
            (*vertex)[(*n)++] = it1;
        }else{
            free(it1);
            it1 = NULL;
        }
        if(id2 < 0){
            ST_insert(*tmp, it2, ST_count(*tmp));
            if(*n == M){
                M = M*2;
                *vertex = realloc(*vertex, sizeof(**vertex)*M);
            }
            (*vertex)[(*n)++] = it2;
        }else{
            free(it2);
            it2 = NULL;
        }
    }
    G = GRAPH_init(ST_count(*tmp));
    rewind(fp);
    while(fscanf(fp, "%s %*s %s %*s %d", label1, label2, &wt) == 3){
        id1 = ST_search(*tmp, label1);
        id2 = ST_search(*tmp, label2);
        if(id1 >= 0 && id2 >= 0)
            GRAPH_insertE(G, id1, id2, wt);
    }
    *m = M;
    return G;
}
