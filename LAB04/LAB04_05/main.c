#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 30
#define max_righe 1000
//per comodità setto il max_righe "manualmente"a 20,in modo da poter analizzare la situazione volta per volta con il debugger.

//in quanto modifica di un programma precedente,commento le parti ritenute superlfue al fine dell'esercizio mirato al multiordinamento.

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


/*
void funz1(dati *v,int data1,int data2);
void funz2(dati *v,char *fermata_partenza);
void funz3(dati *v,char *fermata_arrivo);
void funz4(dati *v,int data1,int data2);
void funz5(dati *v,char *codice_tratta);
int ricerca_dicotomica(dati *v,char *chiave,int l,int r);
void ricerca_lineare(dati *v,char *chiave);
*/
int converti_data(int giorno,int mese,int anno);
void data(dati *v[20]);
void tratta(dati *v[20]);
void partenza(dati *v[20]);
void arrivo(dati *v[20]);
void stampa(dati dati);
void multi_ord(dati *v[][20],int comando,dati *temp);

//int leggiComando(int comando);
//enum comando_e{r_date=1, r_partenza=2, r_capolinea=3, r_ritardo=4, r_ritardo_tot=5, r_fine=6};


int main()
{
    FILE *fp;
    fp=fopen("tabella.txt","r");
    if(fp==NULL){
        printf("errore apertura file.\n");
        return -1;
    }
    int comando=-1,num_righe,i,j,giorno1,mese1,anno1,giorno2,mese2,anno2,data1,data2;
    char stringa[30];
    int l,N,r,m;


    fscanf(fp,"%d",&num_righe);
    if(num_righe>max_righe){
        printf("errore\n");
        return -1;
    }
    //num righe=20,lo inserisco manualmente poiche' da problemi alla struttura.
    //il programma e' strutturato per 20 righe,come il file allegato.
    dati v[20];
    dati temp[20];
    //gestisco 4 tipi di ordinamenti, segue che sfrutto questa matrice di puntatori come appoggio
    dati *ord[4][20];

    for(i=0;i<20;i++){
        fscanf(fp,"%s %s %s %d/%d/%d %d %d %d",v[i].cod_tratta,
               v[i].partenza,v[i].destinazione,&v[i].giorno,&v[i].mese,&v[i].anno,
               &v[i].ora_partenza,&v[i].ora_arrivo,&v[i].ritardo);
               for(j=0;j<4;j++){
                    ord[j][i]=&v[i];
               }
    }

    /*
    printf("COMANDI DISPONIBILI:\n");
    printf("1: r_date\n2: r_partenze\n3: r_capolinea\n4: r_ritardo\n5: tot_ritardo\n0: r_fine\n");
    printf("6: ordina per DATA\n7: ordina per CODICE TRATTA\n8: ordina per STAZIONE PARTENZA\n9: ordina per STAZIONE ARRIVO\n10: RICERCA DICOTOMICA\n11: RICERCA LINEARE\n");
    */

    while(comando!=5){
        printf("comando da eseguire:\n");
        printf("0:DATA\n1:TRATTA\n2:PARTENZA\n3:ARRIVO\n4:STAMPA\n5:INTERROMPI\n");
        scanf("%d",&comando);
        multi_ord(ord,comando,temp);
    }

/*
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
    if(comando==6){
        ordina_data(v,temp);
        printf("La struttura dati, ordinata per DATA, e' la seguente:\n");
        for(i=0;i<20;i++){
            printf("%s %s %s %d/%d/%d %d %d %d\n",v[i].cod_tratta,v[i].partenza,v[i].destinazione,v[i].giorno,
                   v[i].mese,v[i].anno,v[i].ora_partenza,v[i].ora_arrivo,v[i].ritardo);
        }
    }
    if(comando==7){
        ordina_codtratta(v,temp);
        printf("La struttura dati, ordinata per CODICE TRATTA, e' la seguente:\n");
        for(i=0;i<20;i++){
            printf("%s %s %s %d/%d/%d %d %d %d \n",v[i].cod_tratta,v[i].partenza,v[i].destinazione,v[i].giorno,
                   v[i].mese,v[i].anno,v[i].ora_partenza,v[i].ora_arrivo,v[i].ritardo);
        }
    }
    if(comando==8){
        ordina_partenza(v,temp);
        printf("La struttura dati, ordinata per STAZIONE DI PARTENZA, e' la seguente:\n");
        for(i=0;i<20;i++){
            printf("%s %s %s %d/%d/%d %d %d %d \n",v[i].cod_tratta,v[i].partenza,v[i].destinazione,v[i].giorno,
                   v[i].mese,v[i].anno,v[i].ora_partenza,v[i].ora_arrivo,v[i].ritardo);
        }
    }
    if(comando==9){
        ordina_arrivo(v,temp);
        printf("La struttura dati, ordinata per STAZIONE DI ARRIVO, e' la seguente:\n");
        for(i=0;i<20;i++){
            printf("%s %s %s %d/%d/%d %d %d %d \n",v[i].cod_tratta,v[i].partenza,v[i].destinazione,v[i].giorno,
                   v[i].mese,v[i].anno,v[i].ora_partenza,v[i].ora_arrivo,v[i].ritardo);
        }
    }
    if(comando==10){
        l=0,N=20;r=N-1;
        printf("Inserire stazione di partenza da cercare: ");
        scanf("%s",stringa);
        m=ricerca_dicotomica(v,stringa,l,r);
        printf("Dalla stazione selezionata parte: ");
        printf("%s",v[m].cod_tratta);
    }
    if(comando==11){
        printf("Inserire stazione di partenza da cercare: ");
        scanf("%s",stringa);
        printf("Dalla stazione selezionata partono:\n");
        ricerca_lineare(v,stringa);

    }
    */
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
/*
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
*/
/*
//ordinamento di v per data, a parità di data per ora.
void ordina_data(dati *v,dati *temp){
    int i,j,data1,data2;
    int l=0,N=20,r=N-1;

    for(i=l;i<r;i++){
        for(j=l;j<r-i+l;j++){
            data1=converti_data(v[j].giorno,v[j].mese,v[j].anno);
            data2=converti_data(v[j+1].giorno,v[j+1].mese,v[j+1].anno);
            if(data1>data2){

                *temp=v[j];
                v[j]=v[j+1];
                v[j+1]=*temp;
            }
            else if(data1==data2){
                if(v[j].ora_partenza>v[j+1].ora_partenza){
                    *temp=v[j];
                    v[j]=v[j+1];
                    v[j+1]=*temp;
                }
            }
        }
    }
}
/*
void ordina_codtratta(dati *v,dati *temp){
    int i,j;
    int l=0,N=20,r=N-1;

    for(i=l;i<r;i++){
        for(j=l;j<r-i+l;j++){
            if(strcmp(v[j].cod_tratta,v[j+1].cod_tratta)>0){
                *temp=v[j];
                v[j]=v[j+1];
                v[j+1]=*temp;
            }
        }
    }
}


void ordina_partenza(dati *v,dati *temp){
    int i,j;
    int l=0,N=20,r=N-1;

    for(i=l;i<r;i++){
        for(j=l;j<r-i+l;j++){
            if(strcmp(v[j].partenza,v[j+1].partenza)>0){
                *temp=v[j];
                v[j]=v[j+1];
                v[j+1]=*temp;
            }
        }
    }
}

void ordina_arrivo(dati *v,dati *temp){
    int i,j;
    int l=0,N=20,r=N-1;

    for(i=l;i<r;i++){
        for(j=l;j<r-i+l;j++){
            if(strcmp(v[j].destinazione,v[j+1].destinazione)>0){
                *temp=v[j];
                v[j]=v[j+1];
                v[j+1]=*temp;
            }
        }
    }
}
*/
/*
int ricerca_dicotomica(dati *v,char *chiave,int l,int r){
    int m;
    if(l>r){
        return -1;
        //poiche' l e' l'elemento iniziale dell'insieme
        //r l'elemento finale
    }
    //parto dall'elemento centrale
    m=(l+r)/2;
    //la chiave di ricerca,e' la stazione di partenza
    if(strcmp(chiave,v[m].partenza)==0){
        return (m);
    }
    if(strcmp(chiave,v[m].partenza)==0){
        return ricerca_dicotomica(v,chiave,l,m-1);
        //se la chiave e' minore dell'elemento di mezzo,analizziamo il sottovettore sx, con estremi l e m-1
    }
    return ricerca_dicotomica(v,chiave,m+1,r);
        ////se la chiave e' maggiore dell'elemento di mezzo,analizziamo il sottovettore dx, con estremi m+1 e r

}

void ricerca_lineare(dati *v,char *chiave){
    int i;
    /*
    for(i=0;i<20;i++){
        if(strcmp(chiave,v[i].partenza)==0){
            printf("%s\n",v[i].cod_tratta);
        }
    }
    */
    /*
    char *pch;
    for(i=0;i<20;i++){
        pch=strstr(v[i].partenza,chiave);
        if(pch!=NULL){
            printf("%s\n",v[i].cod_tratta);
        }
    }
}
    */

void multi_ord(dati *v[][20],int comando,dati *temp){
    char *ordinamenti[4]={"data","tratta","partenza","arrivo"};
    int i,j;

    switch(comando){

case 4:
    for(j=0;j<4;j++){
        printf("Struttura dati ordinata per %s:\n",ordinamenti[j]);
        for(i=0;i<20;i++){
            stampa(*v[j][i]);
        }
            printf("\n");
        }
        printf("\n");
        break;
case 0:
    data(v[0]);
    break;
case 1:
    tratta(v[1]);
    break;
case 2:
    partenza(v[2]);
    break;
case 3:
    arrivo(v[3]);
    break;
default:
    printf("terminato e/o comando non supportato.\n");
    }
}

void stampa(dati dati){
    printf("%s %s %s %d/%d/%d %d %d %d",dati.cod_tratta,dati.partenza,dati.destinazione,dati.giorno,
           dati.mese,dati.anno,dati.ora_partenza,dati.ora_arrivo,dati.ritardo);
    printf("\n");
}

void data(dati *v[20]){
    int i,j;
    int data2,data1;
    int flag=1;
    dati *tmp;
    for(i=1;i<20;i++){
        tmp=v[i];
        for(j=i-1,data2=converti_data(tmp->giorno,tmp->mese,tmp->anno),data1=converti_data(v[j]->giorno,v[j]->mese,v[j]->anno);j>=0 && flag==1;j--){
            if(data2-data1<0){
                v[j+1]=v[j];
                flag=1;
            }
            else if(data2==data1){
                if(tmp->ora_partenza<v[j]->ora_partenza){
                    v[j+1]=v[j];
                    flag=1;
                }
            }
            else{
                flag=-1;
            }
        }
        v[j+1]=tmp;
        flag=1;
    }
}

void tratta(dati *v[20]){
    int i,j;
    dati *tmp;
    for(i=1;i<20;i++){
        tmp=v[i];
        for(j=i-1;j>=0 && strcmp(tmp->cod_tratta,v[j]->cod_tratta)<0;j--){
            v[j+1]=v[j];
        }
        v[j+1]=tmp;
    }
}

void partenza(dati *v[20]){
    int i,j;
    dati *tmp;
    for(i=1;i<20;i++){
        tmp=v[i];
        for(j=i-1;j>=0 && strcmp(tmp->partenza,v[j]->partenza)<0;j--){
            v[j+1]=v[j];
        }
        v[j+1]=tmp;
    }
}

void arrivo(dati *v[20]){
    int i,j;
    dati *tmp;
    for(i=1;i<20;i++){
        tmp=v[i];
        for(j=i-1;j>=0 && strcmp(tmp->destinazione,v[j]->destinazione)<0;j--){
            v[j+1]=v[j];
        }
        v[j+1]=tmp;
    }
}




