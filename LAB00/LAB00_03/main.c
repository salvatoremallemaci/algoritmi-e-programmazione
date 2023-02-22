#include "stdio.h"
#define maxN 30

void ruota(int v[], int N, int P, int dir);
int main(){
    int N,i,dir,P;
    printf("dimensione vettore: ");scanf("%d",&N);
    if(N>maxN){
        printf("errore,dimensione non valida.\n");
        return -1;
    }
    int v[N];
    printf("vettore: ");
    for(i=0;i<N;i++){
        scanf("%d",&v[i]);
    }
    do{
        printf("direzione: ");scanf("%d",&dir);
        printf("posizoni: ");scanf("%d",&P);
        if(P<=0){
            printf("errore.\n");
        }
        ruota(v,N,P,dir);
        for(i=0;i<N;i++){
            printf("%d",v[i]);
        }
        printf("\n");
    }while(P>0);

return 0;
}


void ruota(int v[], int N, int P, int dir){
    int i = 0, j = 0;
    int tmp_prev = 0, tmp_next = 0;
    if(dir == -1){
        for(j = 0; j < P; j++){
            tmp_prev = v[0];
            for(i = 0; i < N; i++){
                tmp_next = v[(i+1)%N];
                v[(i+1)%N]= tmp_prev;
                tmp_prev = tmp_next;
            }
        }
    }else if(dir == 1){
        for(j = 0; j < P; j++){
            tmp_prev = v[0];
            for(i = N-1; i > 0; i--){
                tmp_next = v[i];
                v[i] = tmp_prev;
                tmp_prev = tmp_next;
            }
            v[0] = tmp_prev;
        }
    }
}
