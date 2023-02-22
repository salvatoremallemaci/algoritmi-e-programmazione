#include <stdio.h>
#include <stdlib.h>
#define N 30


int main()
{
    int dim,i,dim_max=0,cont=0,dim_app=0,j;

    printf("Qual e' la dimensione del vettore? ");
    scanf("%d",&dim);
    if(dim>N)
    {
        printf("Errore : dimensione non supportata!");
        return(-1);
    }
    printf("Definisci il vettore.\n");
    int V[dim];
    for(i=0;i<dim;i++)
    {
        scanf("%d",&V[i]);
    }

    //1^a cosa: trovare la dimensione massima

    for(i = 0; i < dim; i++)
    {
        if(V[i] != 0)
        {
            for( ; V[i] != 0 && i < dim; i++)
            {
                dim_app++;
            }
            if(dim_app > dim_max)
            {
                dim_max = dim_app;
                dim_app = 0;
        }
        }
    }



    for(i = 0; i < dim; i++)
        {
        for(j = i; V[j] != 0 && j < dim; j++);
        if(j-i == dim_max)
        {
            printf("[");
            for(; V[i] != 0 && i < dim; i++) printf("%d", V[i]);
            printf("]");
        }
    }

    return 0;

}
