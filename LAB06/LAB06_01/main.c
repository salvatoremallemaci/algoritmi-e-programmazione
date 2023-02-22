#include <stdio.h>
#include <stdlib.h>

typedef struct{
int u,v;
}arco;

void stampa(int *nodi,int n_nodi,arco *archi,int n_archi);
void funz_g(int pos,int *val,int lung,int start,int *sol,arco *archi,int n_archi);
void funz_v(int *sol,int lung,arco *archi,int n_archi);

int main(){
    int *nodi;
    arco *archi;
    int n_nodi,n_archi;
    int i;
    FILE *fp;
    fp=fopen("grafo.txt","r");
    if(fp==NULL){
        printf("errore file.\n");
        return -1;
    }
    fscanf(fp,"%d %d",&n_nodi,&n_archi);
    nodi=malloc(n_nodi*sizeof(int));
    archi=malloc(n_archi*sizeof(arco));
    for(i=0;i<n_nodi;i++){
        nodi[i]=i;
    }
    for(i=0;i<n_archi;i++){
        fscanf(fp,"%d %d",&archi[i].u,&archi[i].v);
    }
    stampa(nodi,n_nodi,archi,n_archi);
    free(nodi);
    free(archi);
}

void stampa(int *nodi,int n_nodi,arco *archi,int n_archi){
    int* sol=calloc(n_nodi,sizeof(int));
    funz_g(0,nodi,n_nodi,0,sol,archi,n_archi);
}

void funz_g(int pos,int *val,int lung,int start,int *sol,arco *archi,int n_archi){
    int i;
    if(start>=lung){
        if(pos>0)funz_v(sol,pos,archi,n_archi);
        return;
    }
    for(i=start;i<lung;i++){
        sol[pos]=val[i];
        funz_g(pos+1,val,lung,i+1,sol,archi,n_archi);
    }
    funz_g(pos,val,lung,lung,sol,archi,n_archi);
}
void funz_v(int *sol,int lung,arco *archi,int n_archi){
    int i,j;
    int mark[n_archi];
    int ok=1;
    for(i=0;i<n_archi;i++){
        mark[i]=0;
    }
    for(i=0;i<lung;i++){
        for(j=0;j<n_archi;j++){
            if(sol[i]==archi[j].u || sol[i]==archi[j].v) mark[j]=1;
        }
    }
    for(i=0;i<n_archi;i++) if(mark[i]==0) ok=0;

    if(ok){
        printf("(");
        for(i=0;i<lung;i++){
            printf("%d",sol[i]);
            if(i<lung-1) printf(", ");
        }
        printf(")\n");
    }
}
