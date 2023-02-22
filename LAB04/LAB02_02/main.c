#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 30

typedef struct{
char cod_tratta[max];
char partenza[max];
char destinazione[max];
int giorno;
int mese;
int anno;
int ora_partenza;
int ora_arrivo;
int ritardo;
}dati;


int converti_data(int giorno,int mese,int anno);
void funz1(dati *v,int data1,int data2);
void funz2(dati *v,char *fermata_partenza);
void funz3(dati *v,char *fermata_arrivo);
void funz4(dati *v,int data1,int data2);
void funz5(dati *v,char *codice_tratta);

//int leggiComando(int comando);
enum comando_e{r_date=1, r_partenza=2, r_capolinea=3, r_ritardo=4, r_ritardo_tot=5, r_fine=6};


int main()
{
    FILE *fp;
    fp=fopen("tabella.txt","r");
    if(fp==NULL){
        printf("errore apertura file.\n");
        return -1;
    }
    int comando,num_righe,i,giorno1,mese1,anno1,giorno2,mese2,anno2,data1,data2;
    char stringa[30];

    fscanf(fp,"%d",&num_righe);
    if(num_righe>1000){
        printf("errore\n");
        return -1;
    }
    //num righe=20,lo inserisco manualmente poiche' da problemi alla struttura.
    dati v[20];

    for(i=0;i<20;i++){
        fscanf(fp,"%s %s %s %d/%d/%d %d %d %d",v[i].cod_tratta,
               v[i].partenza,v[i].destinazione,&v[i].giorno,&v[i].mese,&v[i].anno,
               &v[i].ora_partenza,&v[i].ora_arrivo,&v[i].ritardo);
    }

    printf("Quale azione vuoi eseguire?\n1:r_date, 2:r_partenze, 3:r_capolinea, 4:r_ritardo, 5:r_tot_ritardo 6:r_fine.\n");
    scanf("%d",&comando);
    if(comando==1){
        printf("giorno iniziale:");scanf("%d",&giorno1);
        printf("mese iniziale:");scanf("%d",&mese1);
        printf("anno iniziale:");scanf("%d",&anno1);
        data1=converti_data(giorno1,mese1,anno1);
        printf("giorno finale:");scanf("%d",&giorno2);
        printf("mese finale:");scanf("%d",&mese2);
        printf("anno finale:");scanf("%d",&anno2);
        data2=converti_data(giorno2,mese2,anno2);
        printf("Nell'intervallo che va da %d/%d/%d a %d/%d/%d partono:\n",giorno1,mese1,anno1,giorno2,mese2,anno2);
        funz1(v,data1,data2);

    }
    if(comando==2){
        printf("Inserire stringa \"FERMATA\": ");
        scanf("%s",stringa);
        printf("Da questa fermata partono:\n");
        funz2(v,stringa);
    }
    if(comando==3){
        printf("Inserire stringa \"ARRIVO\": ");
        scanf("%s",stringa);
        printf("Fanno capolinea a questa fermata:\n");
        funz3(v,stringa);
    }
    if(comando==4){
        printf("giorno iniziale:");scanf("%d",&giorno1);
        printf("mese iniziale:");scanf("%d",&mese1);
        printf("anno iniziale:");scanf("%d",&anno1);
        data1=converti_data(giorno1,mese1,anno1);
        printf("giorno finale:");scanf("%d",&giorno2);
        printf("mese finale:");scanf("%d",&mese2);
        printf("anno finale:");scanf("%d",&anno2);
        data2=converti_data(giorno2,mese2,anno2);
        printf("Nell'intervallo che va da %d/%d/%d a %d/%d/%d partono in ritardo:\n",giorno1,mese1,anno1,giorno2,mese2,anno2);
        funz4(v,data1,data2);
    }
    if(comando==5){
        printf("Inserire stringa \"CODICE TRATTA\": ");
        scanf("%s",stringa);
        printf("Il ritardo complessivo per la tratta selezionata ammonta a : ");
        funz5(v,stringa);
    }
    return 0;
}

/*int leggiComando(int comando){
int res;
    if(comando==1){
        res=r_date;
    }
    else if(comando==2){
        res=r_partenza;
    }
    else if(comando==3){
        res=r_capolinea;
    }
    else if(comando==4){
        res=r_ritardo;
    }
    else if(comando==5){
        res=r_ritardo_tot;
    }
    return res;
}
*/
int converti_data(int giorno,int mese,int anno){
    int data;
    data=giorno+30*(mese)+365*(anno);
    if(data==0){
        return NULL;
    }
    return data;

}
void funz1(dati *v,int data1,int data2){
    int i=0,data,good=0;

    for(i=0;i<20;i++){
        data=converti_data(v[i].giorno,v[i].mese,v[i].anno);
        if(data>=data1 && data<=data2){
            good++;
            printf("%s,da %s a %s.\n",v[i].cod_tratta,v[i].partenza,v[i].destinazione);
        }
    }
    if(good==0){
       printf("nessun treno per l'intervallo di date selezionato.\n");
    }
    return;
}
void funz2(dati *v,char *fermata_partenza){
    int i=0,good=0;

    for(i=0;i<20;i++){
        if(strcmp(v[i].partenza,fermata_partenza)==0){
            good++;
            printf("%s\n",v[i].cod_tratta);
        }
    }
    if(good==0){
        printf("nessun treno.\n");
    }
    return;
}

void funz3(dati *v,char *fermata_arrivo){
    int i=0,good=0;

    for(i=0;i<20;i++){
        if(strcmp(v[i].destinazione,fermata_arrivo)==0){
            good++;
            printf("%s\n",v[i].cod_tratta);
        }
    }
    if(good==0){
        printf("nessun treno.\n");
    }
    return;
}
void funz4(dati *v,int data1,int data2){
    int i=0,data,good=0;

    for(i=0;i<20;i++){
        data=converti_data(v[i].giorno,v[i].mese,v[i].anno);
        if(data>=data1 && data<=data2){
            if(v[i].ritardo!=0){
                good++;
                printf("%s,da %s a %s con %d minuti di ritardo.\n",v[i].cod_tratta,v[i].partenza,v[i].destinazione,v[i].ritardo);
            }
        }
    }
    if(good==0){
        printf("nessun treno.\n");
    }
    return;
}

void funz5(dati *v,char *codice_tratta){
    int i=0,good=0,totale=0;

    for(i=0;i<20;i++){
        if(strcmp(v[i].cod_tratta,codice_tratta)==0){
            totale=totale+v[i].ritardo;
            good++;
        }
    }
    printf("%d",totale);
    return;
}


