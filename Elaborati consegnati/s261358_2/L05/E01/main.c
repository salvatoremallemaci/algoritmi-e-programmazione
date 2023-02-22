#include <stdio.h>
#include <stdlib.h>
#define max 255
typedef struct{
int n_canzoni;
char **canzoni;
}item;

//come modello del calcolo combinatorio,uso le combinazioni semplici, in quanto:
//-l'ordine non conta, dato che prendo per identiche due playlist costituite dalle stesse canzoni,indipendentemente dall'ordine di esse;
//-le canzoni sono distinte
int comb_sempl(int pos,item* val,int n,char **sol,int cont);
int main()
{
    FILE *fp;
    fp=fopen("brani.txt","r");
    if(fp==NULL){
        printf("errore apertura file.\n");
        return -1;
    }
    int i,j;
    item *amici;
    char **playlist;
    int n_amici;
    int start=0,cont=0;
    fscanf(fp,"%d",&n_amici);
    amici=calloc(n_amici,sizeof(item));
    playlist=calloc(n_amici,sizeof(char *));

    for(i=0;i<n_amici;i++){
        fscanf(fp,"%d",&amici[i].n_canzoni);
        amici[i].canzoni=calloc(amici[i].n_canzoni,sizeof(char*));
        for(j=0;j<amici[i].n_canzoni;j++){
            amici[i].canzoni[j]=calloc(max,sizeof(char));
            fscanf(fp,"%s",amici[i].canzoni[j]);
        }
    }
    printf("\nTOTALE PLAYLIST GENERATE: %d",comb_sempl(start,amici,n_amici,playlist,cont));

    for(i=0;i<n_amici;i++){
        for(j=0;j<n_amici;j++){
            free(amici[i].canzoni[j]);
        }
        free(amici[i].canzoni);
    }
    free(amici);
    return 0;
}

int comb_sempl(int pos,item* val,int n,char **sol,int cont){
    int i;
    if(pos>=n){
        printf("Playlist numero %d: \n",cont+1);
        for(i=0;i<n;i++){
            printf("\tAmico %d:\t%s\n", i+1, sol[i]);
        }
        return cont+1;
    }

    for(i=0;i<val[pos].n_canzoni;i++){
        sol[pos]=val[pos].canzoni[i];
        cont=comb_sempl(pos+1,val,n,sol,cont);
    }
    return cont;
}
