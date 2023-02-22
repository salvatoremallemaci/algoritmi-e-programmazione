#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 30

int leggiComando(int comando);
/*void selezionaDati(char cod_tratta[],char partenza[],char destinazione[],int giorno,int mese,int anno,
                   int ora_partenza, int ora_arrivo, int ritardo, int num_righe,int comando_e);
*/

int giorni(int giorno,int mese,int anno);
char funz1(char cod_tratta[],int intervallo_start,int intervallo_stop,int intervallo_mio[],int num_righe);
char funz2(char partenza[],char cod_tratta[],char stringa,int num_righe);
char funz3(char destinazione[],char cod_tratta[],char stringa,int num_righe);
char funz4(char cod_tratta[],int intervallo_start,int intervallo_stop,int intervallo_mio[]
           ,int num_righe,char destinazione[],int ritardo,char s[]);
int  funz5(char cod_tratta[],int ritardo[],int num_righe,char stringa[]);
enum comando_e{r_date=1, r_partenza=2, r_capolinea=3, r_ritardo=4, r_ritardo_tot=5, r_fine=6};

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

int main()
{
    FILE *fp;
    fp=fopen("tabella.txt","r");
    if(fp==NULL){
        printf("errore apertura file.\n");
        return -1;
    }
    int comando,esegui,num_righe,i,start,stop;
    int v1[3],v2[3];

    fscanf(fp,"%d",&num_righe);
    //num_righe=20, problemi con struttura.
    dati v[20];

    for(i=0;i<20;i++){
        fscanf(fp,"%s %s %s %d/%d/%d %d %d %d",v[i].cod_tratta,
               v[i].partenza,v[i].destinazione,&v[i].giorno,&v[i].mese,&v[i].anno,
               &v[i].ora_partenza,&v[i].ora_arrivo,&v[i].ritardo);
    }



    printf("Quale azione vuoi eseguire?\n1:r_date, 2:r_partenze, 3:r_capolinea, 4:r_ritardo, 5:r_tot_ritardo 6:r_fine.\n");
    scanf("%d",&comando);
    esegui=leggiComando(comando);
    switch(esegui){
        case 1:
        printf("inizio intervallo data: ");for(i=0;i<3;i++)scanf("%d",&v1[i]);
        printf("fine intervallo data: ");for(i=0;i<3;i++)scanf("%d",&v2[i]);
        for(i=0;i<num_righe;i++){
            start=giorni(v1[0],v1[1],v1[2]);
            stop=giorni(v2[0],v2[1],v2[2]);
        }



        break;

        case 2:

        break;

        case 3:

        break;

        case 4:

        break;

        case 5:

        break;

        case 6 :

        break;
    }


    return 0;
}


int leggiComando(int comando){
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

int giorni(int giorno,int mese,int anno){
    int res;
    res=giorno+(mese*30)+(anno*365);
}

char funz1(char cod_tratta[],int intervallo_start,int intervallo_stop,int intervallo_mio[],int num_righe){
    char res_codice[num_righe];
    int z;
    for(z=0;z<num_righe;z++){
        if(intervallo_mio[z]>=intervallo_start && intervallo_mio[z]<=intervallo_stop){
            strcpy(res_codice[z],cod_tratta[z]);
        }
    }
    return res_codice;
}

char funz2(char partenza[],char cod_tratta[],char stringa,int num_righe){
    int z,i=0;
    char v_c[num_righe];
    for (z=0;z<num_righe;z++){
        if(strcmp(partenza[z],stringa)==0){
            strcpy(cod_tratta[z],v_c[i]);
            i++;
        }
    }
    return v_c;
}

char funz3(char destinazione[],char cod_tratta[],char stringa,int num_righe){
    int z,i=0;
    char v_c[num_righe];
    for (z=0;z<num_righe;z++){
        if(strcmp(destinazione[z],stringa)==0){
            strcpy(cod_tratta[z],v_c[i]);
            i++;
        }
    }
    return v_c;
}

char funz4(char cod_tratta[],int intervallo_start,int intervallo_stop,
           int intervallo_mio[],int num_righe,char destinazione[],int ritardo,char s[]){
    int z;
    char res_codice[num_righe];
    for(z=0;z<num_righe;z++){
        if(intervallo_mio[z]>=intervallo_start
           && intervallo_mio[z]<=intervallo_stop && (strcmp(destinazione[z],s)==0) && ritardo!=0 ){
           strcpy(res_codice[z],cod_tratta[z]);
        }
    }
    return res_codice;
}



int funz5(char cod_tratta[],int ritardo[],int num_righe,char stringa[]){
    int z,sum;
    for (z=0;z<num_righe;z++){
        if(strcmp(cod_tratta[z],stringa)==0){
            sum=sum+ritardo[z];
        }
    }
    return sum;
}

/*void selezionaDati(char cod_tratta[],char partenza[],char destinazione[],int giorno,int mese,int anno,
                   int ora_partenza, int ora_arrivo, int ritardo, int num_righe,int comando_e){

    if(comando_e==1){

    }



}
*/
