#include <stdio.h>
#include <stdlib.h>
#define MAXNOME 100
#define BONUS 1.5
#define MAX_ELEMENTI 5
#define MAX_DIAG 3
/*
-nome dell'elemento (una stringa di massimo 100 caratteri senza spazi)
-tipologia: l'elemento può essere un elemento acrobatico avanti [2], acrobatico indietro [1] o di transizione [0]
-direzione di ingresso: il ginnasta può entrare in un elemento frontalmente [1] o di spalle [0]
-direzione di uscita: il ginnasta può uscire da un elemento frontalmente [1] o di spalle [0]
-requisito di precedenza: l'elemento può essere eseguito come primo di una sequenza [0] o deve essere preceduto da almeno un altro elemento [1]
-finale: l'elemento non può essere seguito da altri elementi [1] o meno [0]
-valore: il punteggio ottenuto dall'atleta per la corretta esecuzione di un elemento (reale)
-difficoltà: la difficoltà di esecuzione dell'elemento (intero).
*/

typedef struct{
char nome[MAXNOME];
int tipo;
int dir_ingresso;
int dir_uscita;
int precedenza;
int finale;
float valore;
int diff_elemento;
}elemento;

typedef struct{
elemento *el;
int diff_diag;
}diagonale;

typedef struct{
diagonale *diag;
int diff_progr;
}programma;

int main()
{   //DD=MASSIMA DIFFICOLTA' DIAGONALE
    //DP=MASSIMA DIFFICOLTA' PROGRAMMA
    int DD,DP;
    int NUM_ELEMENTI;
    int i;

    FILE *fp;
    fp=fopen("elementi.txt","r");
    if(fp==NULL){
        printf("errore apertura file \"elementi\"\n");
        return -1;
    }

    elemento *E;
    diagonale *D;
    programma *P;

    fscanf(fp,"%d%*c",&NUM_ELEMENTI);
    E=malloc(NUM_ELEMENTI*sizeof(elemento));
    D=malloc(sizeof(diagonale));
    D->el=malloc(MAX_ELEMENTI*sizeof(*(D->el)));
    P=malloc(sizeof(programma));
    P->diag=malloc(MAX_DIAG*sizeof(*(P->diag)));

    for(i=0;i<NUM_ELEMENTI;i++){
        fscanf(fp,"%s %d %d %d %d %d %f %d%*c",
               E[i].nome,&E[i].tipo,&E[i].dir_ingresso,&E[i].dir_uscita,&E[i].precedenza,
               &E[i].finale,&E[i].valore,&E[i].diff_elemento);
    }


    printf("INSERIRE MASSIMA DIFFICOLTA' DIAGONALE: ");
    scanf("%d",&DD);
    printf("INSERIRE MASSIMA DIFFICOLTA' PROGRAMMA: ");
    scanf("%d",&DP);


    return 0;
}
