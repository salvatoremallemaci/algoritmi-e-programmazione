#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int trova_vocale(char c);
int conta(char S[], int n);

int main()
{
    FILE *fp;
    char nome_file[20],parola[20];
    int i,n,N,risultato=0,contatore=0;

    printf("Inserire nome del file contenente i dati: ");
    scanf("%s",nome_file);
    fp=fopen(nome_file,"r");
    if(fp==NULL){
        printf("errore durante l'apertura del file!\n");
        return(-1);
    }
    printf("Inserire lunghezza delle sottostringhe cercate: ");
    scanf("%d",&n);
     if(fp == NULL) return -1;
    fscanf(fp, "%d", &N);

    for(i = 0; i < N; i++){
        fscanf(fp, "%s", parola);
        risultato += conta(parola, n);
        contatore += conta(parola, n);
        printf("Per la parola %s ci sono %d sottostringhe.\n",parola,risultato);
        risultato=0;
    }
    fclose(fp);
    printf("Ci sono %d sottostringhe cercate.\n",contatore);

    return 0;
}

int conta(char S[], int n){
    int i,j,max_vocali=2,n_sottostringhe=0,n_vocali=0;
    for(i=0;S[i]!='\0'&&i+n<20;i++){
        n_vocali=0;
        for(j=0;j<n;j++){
            if(trova_vocale(S[i+j])==1){
                n_vocali++;
            }
            if(n_vocali==max_vocali){
                n_sottostringhe++;
            }
        }
    }
    return n_sottostringhe;
}

int trova_vocale(char c){
    //così anche se trovo un carattere maiuscolo,
    //lo trasforma in minuscolo, riducendo il numero di controlli all'interno dell'if
    if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u')return 1;
    return 0;
    }

