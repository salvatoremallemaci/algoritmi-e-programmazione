#include <stdio.h>
#define MAX 50
// creo una struttura per comodita',in modo da poter distinguere i 3 casi(max altezza,area e base),
// ognuno dei quali ha 3 "sottosezioni", con la propria altezza,area,base.
typedef struct struttura{
    int nr, nc;
    int i, j;
    int area;
}Matrice;

int main(){
    FILE *fp = fopen("file.txt", "r");
    if(fp == NULL) return -1;
    int nr, nc;
    int i, j;
    int matrice[MAX][MAX];
    int inizio = 0;// variabile utile per muovermi all'interno della matrice, la quale mi segnala appunto l'inizio di una regione.
    Matrice bestArea, bestAltezza, bestBase, tmp;
    //tmp utilizzata come struttura dati di appoggio.

    //memorizzo la matrice, leggendola da file.
    fscanf(fp, "%d %d", &nr, &nc);
    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            fscanf(fp, "%d", &matrice[i][j]);
        }
    }
    //1=casella nera.
    //0=casella bianca.

    for(i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            inizio = 1;
            if (matrice[i][j] == 1) {
                if (i > 0 && j > 0) {
                    if (matrice[i - 1][j] == 1 || matrice[i][j - 1] == 1) {
                        inizio = 0;
                    }
                } else {
                    if (j > 0) {
                        if (matrice[i][j - 1] == 1) inizio = 0;
                    } else if (i > 0) {
                        if (matrice[i - 1][j] == 1) inizio = 0;
                    }
                }
                if(inizio){
                    tmp.i = i;
                    tmp.j = j;
                    tmp.nr = tmp.nc = 0;
                    for(tmp.nr = 0; matrice[i+tmp.nr][j] != 0 && i+tmp.nr < nr; tmp.nr++);
                    for(tmp.nc = 0; matrice[i][j+tmp.nc] != 0 && j+tmp.nc < nc; tmp.nc++);
                    tmp.area = tmp.nr*tmp.nc;
                    if(tmp.nr > bestAltezza.nr) bestAltezza = tmp;
                    if(tmp.nc > bestBase.nc) bestBase = tmp;
                    if(tmp.area > bestArea.area) bestArea = tmp;
                }
            }
        }
    }
    //riprendo la sintassi dell'output fornito nell'esempio
    printf("Max Base: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestBase.i, bestBase.j, bestBase.nc, bestBase.nr, bestBase.area);
    printf("Max Area: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestArea.i, bestArea.j, bestArea.nc, bestArea.nr, bestArea.area);
    printf("Max Altezza: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestAltezza.i, bestAltezza.j, bestAltezza.nc, bestAltezza.nr, bestAltezza.area);
    fclose(fp);
    return 0;
}
