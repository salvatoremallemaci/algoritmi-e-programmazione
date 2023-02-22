#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int nr, int nc);
void malloc2dP(int ***mp,int nr,int nc);
void free2d(int **mp,int nr);
void separa(int **mat, int nr, int nc, int *nero, int *bianco);
int main()
{
    FILE *fp;
    fp=fopen("scacchiera.txt","r");
    if(fp==NULL){
        printf("errore durante l'apertura del file di testo.\n");
        return -1;
    }

    int nr,nc;
    int i,j;
    int **mat;
    int *bianco,*nero;
    int flag=-1;
    fscanf(fp,"%d %d",&nr,&nc);

    printf("Usare la malloc2dR(comando 1) o la malloc2dP(comando 2): ");
    scanf("%d",&flag);
    if(flag==1){
         mat=malloc2dR(nr,nc);
    }
    else if(flag==2){
        malloc2dP(&mat,nr,nc);
    }
    else{
        printf("comando sbagliato,ripetere!\n");
        return -1;
    }

    nero=calloc(nr*nc/2,sizeof(int));
    bianco=calloc(nr*nc/2,sizeof(int));

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }

    separa(mat,nr,nc,nero,bianco);
    printf("Nelle caselle nere ci sono: ");
    //il +1 e' dovuto al fatto che ci sono n+1 numeri nella casella nera, dove n sarebbero i numeri nella casella bianca.
    for(i=0;i<nr*nc/2+1;i++){
        printf("%d ",nero[i]);
    }
    printf("\nNelle caselle bianche ci sono: ");
    for(i=0;i<nc*nr/2;i++){
        printf("%d ",bianco[i]);
    }
    free(nero);
    free(bianco);
    free2d(mat,nr);
    return 0;
}
int **malloc2dR(int nr, int nc){
    int **m;
    int i;
    m=malloc(nr*sizeof(int *));
    for(i=0;i<nr;i++){
        m[i]=malloc(nc*sizeof(int));
    }
    return m;
}

void separa(int **mat, int nr, int nc, int *nero, int *bianco){
    int i,j,k=0;

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
            //sfrutto la simmetria della scacchiera, in particolare so che
            //la casella nera ha come somma degli indici un numero pari,quindi sfrutto il resto (se 0,casella nera;se diverso da zero,casella bianca).
            if((i*nr+j)%2==0){
                nero[k]=mat[i][j];
            }else{
                bianco[k++]=mat[i][j];
            }
        }
    }
}
void malloc2dP(int ***mp,int nr,int nc){
    int **m;
    int i;
    m=malloc(nr*sizeof(int *));
    for(i=0;i<nr;i++){
        m[i]=malloc(nc*sizeof(int));
    }
    *mp=m;
}
void free2d(int **mp,int nr){
    int i;
    for(i=0;i<nr;i++){
        free(mp[i]);
    }
    free(mp);
}
