#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

MENU *MENUinit(int P){

    int i;
    MENU *ElencoMenu;
    //alloco il vettore di indici, grande P, numero dei piatti.
    ElencoMenu->menu=malloc(P*sizeof(int));
    for(i=0;i<P;i++){
        ElencoMenu->menu[i]=-1;
        ElencoMenu->prezzo=0.00;
    }
    return ElencoMenu;

}

void MENUprint(int P,MENU *ElencoMenu,piatti *ElencoPiatti){
    int i;
    printf("Il menu selezionato e' il seguente: \n");
    for(i=0;i<P;i++){
        printf("%s %s %s %.2f",ElencoPiatti[ElencoMenu->menu[i]].nome,
                               ElencoPiatti[ElencoMenu->menu[i]].portata,
                               ElencoPiatti[ElencoMenu->menu[i]].tipologia,
                               ElencoPiatti[ElencoMenu->menu[i]].costo);
        printf("\n");
        ElencoMenu->prezzo+=ElencoPiatti[ElencoMenu->menu[i]].costo;
    }
    printf("Per un totale di: %.2f\n",ElencoMenu->prezzo);
    ElencoMenu->prezzo=0.00;
}

void COMB_RIP_WRAPPER(MENU *ElencoMenu,piatti *ElencoPiatti,int P,int N){
    int start=0,pos=0,i;
    int *sol;
    int *mark;
    //sol, vettore soluzione, contenente gli indici
    sol=malloc(P*sizeof(int));
    //mark,vettore di occorrenze
    mark=malloc(N*sizeof(int));
    //inizializzo sol a -1
    for(i=0;i<P;i++){
        sol[i]=-1;
    }
    //inizializzo le occorrenze di ogni piatto a due, data la possibilità al più un bis.
    for(i=0;i<N;i++){
        mark[i]=2;
    }
    //chiamo la funzione ricorsiva COMB_RIP
    COMB_RIP(ElencoMenu,ElencoPiatti,0,0,sol,mark,P,N);
}
void COMB_RIP(MENU *ElencoMenu,piatti *ElencoPiatti,int pos,int start,int *sol,int *mark,int P,int N){
    int i;
    //int count;
    if(pos>=P){
        /*Una volta arrivato in condizione di terminazione, seguirebbe una funzione che, dato sol vettore di indici,
          mi memorizzasse il menu corrente,facendo riferimento ad ElencoPiatti per i dati effettivi, all'interno
          di un BST*/

        //count++; per contare quanti menu inserire nel BST

        /*Si tratta di una BST_insert che sfrutta la gerarchia del menu, dunque seguirebbe una insertL o una insertR, rispettando le proprietà
         dei BST, stabilita dalla MENUcompare. */

          //TEST STAMPA DELLE COMBINAZIONI SENZA BST

          ElencoMenu->menu=sol;
          MENUprint(P,ElencoMenu,ElencoPiatti);
          return;


    }
    for(i=start;i<N;i++){
        if(mark[i]>0){
            mark[i]--;
            sol[pos]=i;
            COMB_RIP(ElencoMenu,ElencoPiatti,pos+1,start,sol,mark,P,N);
            mark[i]++;
            start++;
        }
    }

}
