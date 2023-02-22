#include <stdio.h>
#include <stdlib.h>
#include "INV.h"
#include "PG.h"

typedef enum{
e_carica_pg, e_carica_ogg, e_aggiungi_pg, e_elimina_pg, e_ricerca_oggetto, e_aggiungi_ogg_equip,
e_rimuovi_ogg_equip,e_stampa_inv_pg, e_stampa_personaggi, e_stampa_inventario,
e_stampa_stats_pg, e_fine,  e_err}cmd;

cmd opzioni();

int main()
{
    FILE *fp_pg;
    FILE *fp_inv;
    fp_pg=fopen("pg.txt","r");
    fp_inv=fopen("inventario.txt","r");

    if(fp_pg==NULL){
        printf("errore apertura file pg.txt.\n");
        return -1;
    }
    if(fp_inv==NULL){
        printf("errore apertura file inventario.txt.\n");
        return -1;
    }
    cmd comando;
    tabPg *l;
    //l=malloc(sizeof(*l));
    tabInv *v;
    //v=malloc(sizeof(*v));
    tabEquip_t *z;
    while((comando=opzioni())!=e_fine){
        switch(comando){

        case e_carica_pg:
            l=carica_lista(fp_pg);
        break;

        case e_carica_ogg:
            v=carica_oggetti(fp_inv);
        break;

        case e_ricerca_oggetto:
            ricerca_oggetto(v);
        break;

        case e_aggiungi_pg:
            aggiungi_pg(l);
        break;

        case e_elimina_pg:
            cancella_pg(l);

        break;

        case e_stampa_personaggi:
            stampa_lista(l);
        break;

        case e_stampa_inventario:
            stampa_inventario(v);
        break;

        case e_aggiungi_ogg_equip:
            z=agg_oggetti_pg(l,v);
        break;

        case e_rimuovi_ogg_equip:
            rim_oggetti_pg(l,v,z);
        break;

        case e_stampa_inv_pg:
            stampa_inv_pg(l,z);
        break;

        case e_stampa_stats_pg:
            stampa_stats_pg(l,z);
        break;
        }
    }
    libera_lista(l);
    fclose(fp_pg);
    fclose(fp_inv);
    return 0;
}



cmd opzioni(){
    int i;
    do{
    printf("1. Carica personaggi da file.\n");
    printf("2. Carica oggetti da file.\n");
    printf("3. Aggiungi personaggio da tastiera.\n");
    printf("4. Elimina un personaggio.\n");
    printf("5. Cerca un oggetto nell'inventario.\n");
    printf("6. Aggiungi oggetto ad un personaggio.\n");
    printf("7. Rimuovi oggetto ad un personaggio.\n");
    printf("8. Stampa inventario di un personaggio.\n");
    printf("9. Stampa personaggi.\n"); //V
    printf("10. Stampa inventario.\n"); //V
    printf("11. Stampa statistiche del personaggio.\n");
    printf("12. Esci.\n");
    printf("Inserisci il comando: ");
    scanf("%d", &i);
    i--;
    }while(i == e_err);
    return i;
}
