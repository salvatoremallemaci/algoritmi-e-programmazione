#include <stdio.h>
#define MAX 200
#define S 30

int main(){
    FILE *fp1,*fp2,*fp3;
    //apertura file
    fp1=fopen("sorgente.txt","r");
    fp2=fopen("dizionario.txt","r");
    fp3=fopen("ricodificato.txt","w");
    if(fp1==NULL || fp2==NULL || fp3==NULL){ //test apertura file.
        printf("errore apertura file.\n");
        return -1;
    }
    char riga[MAX],nuova_riga[MAX];
    int dim,trovato,ok;
    char dizionario[S][MAX];
    char sostituto[S][MAX];
    int i,j,k,s,t=0,lung_trov;
    //leggo la dimensione del dizionario(da quante righe di parole effettive e' costituito il file "dizionario")
    fscanf(fp2,"%d",&dim);
    //spezzo le fscanf, dato che il puntatore fp2,adesso punterà alla prima parola del file.
    for(i=0;i<dim;i++){
        fscanf(fp2,"%s %s",sostituto[i],dizionario[i]);
    }
    while(fgets(riga,MAX,fp1)!=NULL){//leggo il file, riga per riga
        i=0;
        while(riga[i]!='\0'){ //leggo carattere per carattere
            trovato=-1;
            lung_trov=0;
            for(j=0;j<dim;j++){
                k=0;
                ok=1;//inizializzo a "vero"
                while(dizionario[j][k]!='\0' && ok){
                    if(dizionario[j][k]!=riga[i+k])ok=0;
                    k++;
                }
                if(ok==1 && k>lung_trov){
                    trovato=j;
                    lung_trov=k;
                }
            }
            if(trovato==-1){
                nuova_riga[t++]=riga[i++];
            }else{
            s=0;
            while(sostituto[trovato][s]!='\0'){
                nuova_riga[t++]=sostituto[trovato][s++];
            }
            i+=lung_trov;
        }
    }
    //a questo punto, stampo il testo convertito sul file di output(file "ricodificato.txt"), riga per riga
    nuova_riga[t]='\0';
    fputs(nuova_riga,fp3);
    t=0;
    nuova_riga[t]='\0';
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}




