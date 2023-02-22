#include <stdio.h>
#include <stdlib.h>

int majority( int *a, int N);
void quicksort(int *v,int first,int last);
int main()
{
    int N,i,res;
    printf("Definire dimensione del vettore: ");scanf("%d",&N);
    int v[N];
    printf("Scandire il vettore v[N]\n");
    for(i=0;i<N;i++){
        scanf("%d",&v[i]);
    }
    printf("Il vettore v[N] e' il seguente: ");
    for(i=0;i<N;i++){
        printf("%d ",v[i]);
    }
    quicksort(v,0,N-1);
    printf("\nDopo aver applicato il quick sort, il vettore ordinato e': ");
    for(i=0;i<N;i++){
        printf("%d ",v[i]);
    }
    res=majority(v,N);
    if(res!=-1){
        printf("\nIl valore maggioritario e': %d",res);
    }else{
    printf("\nNon ci sono valori maggioritari.\n");
    }

}
void quicksort(int *v,int first,int last){
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(v[i]<=v[pivot]&&i<last)
            i++;
         while(v[j]>v[pivot])
            j--;
         if(i<j){
            temp=v[i];
            v[i]=v[j];
            v[j]=temp;
         }
      }

      temp=v[pivot];
      v[pivot]=v[j];
      v[j]=temp;
      quicksort(v,first,j-1);
      quicksort(v,j+1,last);

   }
}
//lo scopo di questa funzione e' quello di "ritornare" il numero che si ripete più volte all'interno del vettore.
//ho prima ordinato il vettore, cosi' posso ricercare il massimo tra valori contigui nel vettore,senza la necessita' di
//fare un doppio for, la quale operazione avrebbe un costo O(n^2).In questo caso, mi servo di un solo for, dunque costo O(n)
int majority( int *a, int N){
int i,cont=0,val,res=0;
    for(i=0;i<N;i++){
        val=a[i];
        if(a[i+1]==val){
            cont++;
            if(cont>((N-1)/2)){
                res=a[i];
            }
            else{
                res=-1;
            }
        }
        else{
            cont=0;
        }
    }
    return res;
}
