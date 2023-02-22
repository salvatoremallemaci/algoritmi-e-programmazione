#include <stdio.h>
#include <stdlib.h>
#define FILENAME "very_easy_test_set.txt"
#define N 4 //4 diverse tipologie di gemme


//int check(int *sol,int k);
//int disp_rip(int pos,int *disp_gemme,int *sol,int n,int k,int prec);
int disp_rip_optim(int pos,int *disp_gemme,int *sol,int n,int k,int prec);
int main()
{

    // La lunghezza della soluzione deve essere compresa tra 1 e(z+r+s+t)
    // OBIETTIVO: stampare a video la composizione della collana a lunghezza massima, che rispetti le regole.

    //MODELLO DEL CALCOLO COMBINATORIO: DISPOSIZIONI RIPETUTE
    //-In quanto ogni pietra puo' essere ripetute piu' volte nelle varie combinazioni...;
    //-L'ordine delle pietre conta;
    //...

    //z=zaffiri, r=rubino, t=topazi, s=smeraldi


    int *sol;
    int i,j,k,lunghezza_max,lunghezza_ok;
    int numero_test,min,max,qualcosa;
    int num_gemme[N],disp_gemme[N];
    char gemme[N]={'Z','R','T','S'};
    FILE *fp;
    fp=fopen(FILENAME,"r");
    if(fp==NULL){
        printf("errore apertura file\n");
        return -1;
    }
    fscanf(fp,"%d",&numero_test);
    printf("inserisci qualcosa:");
    scanf("%d",&qualcosa);
    printf("Si effettueranno %d test.\n",numero_test);
    for(j=0;j<numero_test;j++){
        printf("test NUM%d\n",j+1);
        min=0;
        lunghezza_max=0;
        for(i=0;i<N;i++){
            fscanf(fp,"%d",&num_gemme[i]);
            lunghezza_max=lunghezza_max+num_gemme[i];
        }
        max=lunghezza_max;
        sol=malloc(lunghezza_max*sizeof(int));

        while(min<=max){
            k=(min+(max-min)/2); //per ottimizzare la ricerca della soluzione, parto dal centro, a mo di ricerca dicotomica.
            for(i=0;i<N;i++)
                disp_gemme[i]=num_gemme[i];
            if(disp_rip_optim(0,disp_gemme,sol,N,k,-1)==1){
                lunghezza_ok=k;
                min=k+1; // disp_rip a partire da k+1 (min)
            }else{
            max=k-1;//disp_rip fino a k-1 (max)
            }
        }
        printf("Una soluzione a lunghezza massima %d e' ",lunghezza_ok);
        for (i=0; i<lunghezza_ok; i++){
            printf("%c", gemme[sol[i]]);
            }
        printf("\n");
        free(sol);
    }
    fclose(fp);
    return 0;
}

/*int disp_rip(int pos,int *disp_gemme,int *sol,int n,int k,int prec){
    int i;

    if(pos>=k){
        if(check(sol,k)==1){
            return 1;
        }
        return 0;
    }

    for(i=0;i<n;i++){
        if(disp_gemme[i]>0){

            disp_gemme[i]--;//ho usato una gemma del campo i-esimo.
            sol[pos]=i;//memorizzo la gemma che ho utilizzato.
            if(disp_rip(pos+1,disp_gemme,sol,n,k,pos)==1)
                return 1;
            disp_gemme[i]++;
        }
    }
    return 0;
}

int check(int *sol,int k){
    int i;

    for(i=0;i<k;i++){
        if( (sol[i-1]==0 || sol[i-1]==2) && (sol[i]!=0) && (sol[i]!=1) ){
            return 0;
        }
        if( (sol[i-1]==3 || sol[i-1]==1) && (sol[i]!=3) && (sol[i]!=2) ){
            return 0;
        }

    }
    return 1;
}
*/

    //0=zaffiro
    //1=rubino
    //2=topazio
    //3=smeraldo

    // REGOLE:
    // Uno zaffiro deve essere seguito immediatamente o da un altro zaffiro o da un rubino (0->0/1)
    // Uno smeraldo deve essere seguito immediatamente o da un altro smeraldo o da un topazio (3->3/2)
    // Un rubino deve essere seguito immediatamente o da uno smeraldo o da un topazio (1->3,2)
    // Un topazio deve essere seguito immediatamente o da uno zaffiro o da un rubino. (2->0,1)


int disp_rip_optim(int pos,int *disp_gemme,int *sol,int n,int k,int prec){
    int i;
    if(pos>=k){
    return 1;
    }

    for(i=0;i<n;i++){
        if(disp_gemme[i]>0) {
            if(prec!=-1) {
                //(se ho uno zaffiro o un topazio,controllo se il porssimo è uno zaffiro o uno rubino)
                if (((sol[prec]==0) || (sol[prec]==2)) && (i!=0) && (i!=1))
                continue;
                //(se ho uno smeraldo o un rubino,controllo se il porssimo è un topazio o uno smeraldo)
                if (((sol[prec]==3) || (sol[prec]==1)) && (i!=2) && (i!=3))
                continue;
        }
        disp_gemme[i]--;
        sol[pos] = i;
        if (disp_rip_optim(pos+1, disp_gemme, sol, n, k, pos)==1)
        return 1;
        disp_gemme[i]++;
        }
    }
    return 0;
}
