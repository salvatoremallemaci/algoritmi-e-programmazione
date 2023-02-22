#include <stdio.h>
#include <stdlib.h>
#define max 20
int main()
{
    int v[max][max],i,j,r,cont=0,c,v_max=0,pos_X=0;
    FILE *fp;

    fp=fopen("calendario.txt","r");
    if(fp==NULL){
        printf("Errore apertura file.\n");
        return -1;
    }

    printf("Squadre: ");scanf("%d",&r);
    printf("Giornate: ");scanf("%d",&c);
    if(r>max||c>max ||r<0||c<0){
        printf("errore numero squadre/giornate.\n");
        return -1;
    }
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            fscanf(fp,"%d",&v[i][j]);
            printf("%d",v[i][j]);
            cont++;
            if(cont==r){
                printf("\n");
                cont=0;
            }
        }
    }

    for(j=0;j<c;j++){
        for(i=0;i<r;i++){
            if(v[i][j]>=v_max){
                v_max=v[i][j];
                pos_X=i;
            }
        }
            printf("La capolista per la %da giornata e' in pos %d.\n",(j+1),(pos_X+1));
            v_max=0;
        }
    printf("(le posizioni sono da leggere lungo la colonna).\n");
    return 0;
}
