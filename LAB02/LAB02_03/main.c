#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void conversione(char *str);// con tale funzione, converto tutti caratteri in minuscolo e rimuovo eventuali punteggiature.
int main()
{
    FILE *fp1,*fp2;
    fp1=fopen("sequenze.txt","r");
    fp2=fopen("testo.txt","r");

    if(fp1==NULL){
        printf("errore apertura file 'sequenze.txt'!\n");
        return -1;
    }
    if(fp2==NULL){
        printf("errore apertura file 'testo.txt'!\n");
        return -2;
    }

    int n_seq,i,cont_parole=0,n_occorrenze=0;
    fscanf(fp1,"%d",&n_seq);
    char parola[n_seq][5],tabella[200];

    for(i=0;i<n_seq;i++){
        fscanf(fp1,"%s",parola[i]);
        conversione(parola[i]);
    }
    char *pch;

    for(i=0;i<n_seq;i++){
        rewind(fp2);//"riavvolgo" il file,in modo che possa confrontare ciascuna sequenza nell'intero file,stampando le varie occorrenze in modo ordinato.
        cont_parole=0;//tale counter mi indica la posizione in cui trovo la sequenza cercata.
        n_occorrenze=0;//tale counter mi e' utile,poichè per comodità ci fermiamo a 10 occorrenze per sequenza.
        while(fscanf(fp2,"%s",tabella)!=EOF){
        conversione(tabella);
        cont_parole++;
        pch=strstr(tabella,parola[i]);
        if(pch!=NULL){//ossia se la sequenza(stringa) e' stata individuata all'interno del file.
            printf("La sequenza '%s' e' contenuta in '%s', in pos %d\n",parola[i],tabella,cont_parole);
            n_occorrenze++;
            }
        if(n_occorrenze>=10){
            break;
            }
        }
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
// con tale funzione, converto tutti caratteri in minuscolo e rimuovo eventuali punteggiature.
void conversione(char *str){
    int i;
    for(i=0;str[i]!='\0';i++){
        str[i]=tolower(str[i]);
        if(ispunct(str[i])!=0){
            str[i]=' ';
        }
    }
}

