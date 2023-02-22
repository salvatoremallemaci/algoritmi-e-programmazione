#include <stdio.h>
#define MAX 50
int leggiMatrice(int M[][MAX],int MAXR,int *nr,int *nc);
int riconosciRegione(int M[][MAX], int nr, int nc, int r, int c, int *b, int *h);
// creo una struttura per comodita',in modo da poter distinguere i 3 casi(max altezza,area e base),
// ognuno dei quali ha 3 "sottosezioni", con la propria altezza,area,base.
typedef struct Matrice{
    int nr, nc;
    int i, j;
    int area;
}Matrice;

int main(){

    int nr, nc;
    int i, j, ok;
    int matrice[MAX][MAX];
    int inizio = 0;// variabile utile per muovermi all'interno della matrice, la quale mi segnala appunto l'inizio di una regione.
    Matrice bestArea, bestAltezza, bestBase, tmp;
    //tmp utilizzata come struttura dati di appoggio.


    //apertura,lettura(file e matrice)e chiusura file, all'interno della funzione seguente
    ok=leggiMatrice(matrice,MAX,&nr,&nc);
    if(ok==0){
        printf("Lettura della matrice da file terminata con successo!\n");
    }else if(ok==-1){
        printf("Errore lettura matrice da file!\n");
    }

    // 1=casella nera.
    // 0=casella bianca.

    for(i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if(riconosciRegione(matrice, nr, nc, i, j, &tmp.nc, &tmp.nr)){
                tmp.i = i;
                tmp.j = j;
                tmp.area = tmp.nr * tmp.nc;
                if (tmp.nr > bestAltezza.nr) bestAltezza = tmp;
                if (tmp.nc > bestBase.nc) bestBase = tmp;
                if (tmp.area > bestArea.area) bestArea = tmp;
            }
        }
    }

    //riprendo la sintassi dell'output fornito nell'esempio
    printf("Max Base: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestBase.i, bestBase.j, bestBase.nc, bestBase.nr, bestBase.area);
    printf("Max Area: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestArea.i, bestArea.j, bestArea.nc, bestArea.nr, bestArea.area);
    printf("Max Altezza: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestAltezza.i, bestAltezza.j, bestAltezza.nc, bestAltezza.nr, bestAltezza.area);

    return 0;
}


//lo scopo di questa funzione e' quello di leggere da file di testo la tabella,memorizzandola all'interno di una matrice.
int leggiMatrice(int M[][MAX],int MAXR,int *nr,int *nc){
    FILE *fp;
    int i,j;

    fp=fopen("file.txt","r");
    if(fp==NULL){
        printf("errore apertura file.\n");
        return -1;
    }
    fscanf(fp,"%d %d",nr,nc);//poiche' ho dichiarato nr ed nc come puntatori, non metto la & come di consueto.
    for(i=0;i<*nr;i++){
        for(j=0;j<*nc;j++){
            fscanf(fp,"%d",&M[i][j]);
        }
    }
    fclose(fp);
    return 0;//restituisco 0 come successo,-1 come fallimento.
}
//lo scopo di questa funzione e' quello di individuare una regione
int riconosciRegione(int M[][MAX], int nr, int nc, int r, int c, int *b, int *h) {
    int inizio;
    inizio = 1;
    if (M[r][c] == 1) {
        if (r > 0 && c > 0) {
            if (M[r - 1][c] == 1 || M[r][c - 1] == 1) {
                inizio = 0;
            }
        } else {
            if (c > 0) {
                if (M[r][c - 1] == 1) inizio = 0;
            } else if (r > 0) {
                if (M[r - 1][c] == 1) inizio = 0;
            }
        }
        if(inizio){
            for (*h = 0; M[r + *h][c] != 0 && r + *h < nr; (*h)++);
            for (*b = 0; M[r][c + *b] != 0 && c + *b < nc; (*b)++);
        }
        return inizio;//restituisco la "casella" inziale della mia regione.
    }
}
