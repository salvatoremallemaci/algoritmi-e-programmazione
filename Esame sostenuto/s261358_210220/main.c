#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "menu.h"

#define MAXL 100

/*NON HO IMPLEMENTATO IL MODULO BST, DATO CHE IN AULA NON SONO ARRIVATO A TRATTARLO SUFFICIENTEMENTE,
  LIMITANDOMI AD UNA DESCRIZIONE SOMMARIA DELLA PARTE IN QUESTIONE.*/

int menuCOMPARE(int *menu1,int *menu2,int P,int N,piatti *ElencoPiatti);

int main(int argc, char **argv)
{
    int N=0;
    char nome[MAXL],portata[MAXL],tipologia[MAXL];
    float costo=0.00;
    int P=0,i;

    FILE *in;
    in=fopen("piatti.txt","r");
    if(in==NULL){
        printf("ERRORE APERTURA FILE.\n");
        return -1;
    }

    if(argc!=2){
        printf("ERRORE, NUMERO ARGOMENTI SU LINEA DI COMANDO ERRATI.\n");
        return -1;
    }
    fscanf(in,"%d",&N);
    //alloco un vettore di struct,grande N
    piatti *ElencoPiatti;
    ElencoPiatti=malloc(N*sizeof(piatti));
    //leggo il file
    for(i=0;i<N;i++){
        fscanf(in,"%s %s %s %f",nome,portata,tipologia,&costo);
        ElencoPiatti[i].nome=strdup(nome);
        ElencoPiatti[i].portata=strdup(portata);
        ElencoPiatti[i].tipologia=strdup(tipologia);
        ElencoPiatti[i].costo=costo;
        printf("%s %s %s %.2f\n",ElencoPiatti[i].nome,ElencoPiatti[i].portata,ElencoPiatti[i].tipologia,ElencoPiatti[i].costo);
    }
    //Tale vettore ElencoPiatti è ordinato così come compare nel file.
    //leggo il numero di piatti che costituirà il menu
    P=atoi(argv[1]);
    MENU *ElencoMenu;
    ElencoMenu=MENUinit(P);
    /*Segue la chiamata alla funzione ricorsiva e, una volta generata una soluzione, seguirebbe la memorizzazione della soluzione (menu) all'interno del BST,
      ordinato grazie alla funzione MENUcompare.
      Infine la stampa del BST tramite visita in-order. */
    COMB_RIP_WRAPPER(ElencoMenu,ElencoPiatti,P,N);


    free(ElencoPiatti);
    free(ElencoMenu);

}
//TALE FUNZIONE,A DIFFERENZA DELLA VERSIONE DELL'ESAME, E' DIRETTAMENTE DEL MAIN.

/*TALE FUNZIONE RESTITUISCE 1 SE IL MENU1 E' PIU' VANTAGGIOSO RISPETTO A MENU2
                RESTITUISCE 2 SE IL MENU2 E' PIU' VANTAGGIOSO RISPETTO A MENU1 */

int menuCOMPARE(int *menu1,int *menu2,int P,int N,piatti *ElencoPiatti){
    float prezzo1=0.00;
    float prezzo2=0.00;
    int i;
    int risultato=-1;

    for(i=0;i<P;i++){
        prezzo1+=ElencoPiatti[menu1[i]].costo;
        prezzo2+=ElencoPiatti[menu2[i]].costo;
    }

    //SE IL PRIMO MENU E' PIU' VANTAGGIOSO
    if(prezzo1<prezzo2){
        risultato=1;
        return risultato;
    }
    //SE IL SECONDO ME E' PIU' VANTAGGIOSO
    else if(prezzo2<prezzo1){
        risultato=2;
        return risultato;
    }
    //A PARITA' DI PREZZO, VERIFICO L'ORDINE DEI PIATTI (IN BASE A COME E' ORGANIZZATO IL FILE)
    //Poiche' il vettore menu e' di indici,il contenuto sarà la posizione dell'x-esimo ingrediente nel file.
    else if(prezzo1==prezzo2){
        for(i=0;i<P;i++){
            if(menu1[i]<menu2[i]){
                risultato=1;
                return risultato;
            }
            else if(menu2[i]<menu1[i]){
                risultato=2;
                return risultato;
            }
        }
    }
    return 0;
}
