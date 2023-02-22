#include <stdio.h>
#include <stdlib.h>

typedef struct tile_t{
    char coloreT1;
    char coloreT2;
    int valoreT1;
    int valoreT2;
    int fissa;
    int usata;
} tile;

typedef struct board_t{
    int i;
    int ruota;
} boardCell;

tile ruotaTile(tile t);
void generaSoluzione(boardCell **board, int R, int C, tile **tiles, int T);
void generaSoluzioneR(int pos, boardCell **board, int R, int C, tile **tiles, int T, boardCell **bestBoard, int *bestPunteggio);
int calcolaPunteggio(boardCell **board, int R, int C, tile *tiles, int T);

int main(){
    setbuf(stdout, NULL);
    tile* tiles;
    boardCell** board;
    int i, j, T, tmp;
    int R, C;
    FILE* fp1 = fopen("tiles.txt", "r");
    FILE* fp2 = fopen("board.txt", "r");

    if(fp1 == NULL || fp2 == NULL) return -1;
    fscanf(fp1, "%d%*c", &T);
    tiles = calloc(T, sizeof(struct tile_t));
    for(i = 0; i < T; i++){
        fscanf(fp1, "%c %d %c %d%*c", &tiles[i].coloreT1, &tiles[i].valoreT1, &tiles[i].coloreT2, &tiles[i].valoreT2);
        tiles[i].fissa = 0;
        tiles[i].usata = 0;
    }
    fscanf(fp2, "%d %d", &R, &C);
    board = calloc(R, sizeof(struct board_t *));
    for(i = 0; i < R; i++){
        board[i] = calloc(C, sizeof(struct board_t));
        for(j = 0; j < C; j++){
            fscanf(fp2, "%d/%d", &board[i][j].i, &board[i][j].ruota);
            if(board[i][j].i != -1){
                tiles[board[i][j].i].fissa = 1;
                tiles[board[i][j].i].usata = 1;
            }
        }
    }

    fclose(fp1);

    printf("Tessere lette:\n");
    for(i = 0; i < T; i++){
        printf("%c %d %c %d\n", tiles[i].coloreT1, tiles[i].valoreT1, tiles[i].coloreT2, tiles[i].valoreT2);
    }
    printf("Board letta:\n");
    for(i = 0; i < R; i++){
        for(j = 0; j < C; j++){
            tmp = -1;
            if(board[i][j].i != -1) tmp = board[i][j].ruota;
            printf("%d/%d", board[i][j].i, tmp);
            }
        printf("\n");
    }
    generaSoluzione(board, R, C, &tiles, T);
    return 0;
}

void generaSoluzione(boardCell **board, int R, int C, tile **tiles, int T){
    boardCell **bestBoard = calloc(R, sizeof(boardCell *));
    int bestPunteggio = 0;
    int i, j;
    for(i = 0; i < R; i++){
        bestBoard[i] = calloc(C, sizeof(boardCell));
    }
    generaSoluzioneR(0, board, R, C, tiles, T, bestBoard, &bestPunteggio);
    printf("Soluzione ottima:\n");
    for(i = 0; i < R; i++){
        for(j = 0; j < C; j++){
            printf("%d/%d ", bestBoard[i][j].i, bestBoard[i][j].ruota);
        }
        printf("\n");
    }
    printf("Punteggio massimo: %d\n", bestPunteggio);
}

void generaSoluzioneR(int pos, boardCell **board, int R, int C, tile **tiles, int T, boardCell **bestBoard, int *bestPunteggio){
    int i, j, k, currPunteggio;
    i = pos/R;
    j = pos%C;
    if(pos >= R*C){
        currPunteggio = calcolaPunteggio(board, R, C, *tiles, T);
        if(currPunteggio > *bestPunteggio){
            *bestPunteggio = currPunteggio;
            for(i = 0; i < R; i++){
                for(j = 0; j < C; j++){
                    bestBoard[i][j] = board[i][j];
                }
            }
        }
        return;
    }

    if(board[i][j].i >= 0){
        return generaSoluzioneR(pos+1, board, R, C, tiles, T, bestBoard, bestPunteggio);
    }
    for(k = 0; k < T; k++) {
        if ((*tiles)[k].usata == 0) {
            (*tiles)[k].usata = 1;
            board[i][j].i = k;
            board[i][j].ruota = 0;
            generaSoluzioneR(pos + 1, board, R, C, tiles, T, bestBoard, bestPunteggio);
            board[i][j].ruota = 1;
            generaSoluzioneR(pos + 1, board, R, C, tiles, T, bestBoard, bestPunteggio);
            (*tiles)[k].usata = 0;
            board[i][j].i = -1;
        }
    }
}

int calcolaPunteggio(boardCell **board, int R, int C, tile *tiles, int T){
    int punteggioOrizzontale = 0;
    int punteggioVerticale = 0;
    int i, j;
    int tmp = 0;
    tile tilesTmp[T];
    for(i = 0; i < T; i++){
        tilesTmp[i] = tiles[i];
    }
    for(i = 0; i < R; i++){
        for(j = 0; j < C; j++){
            if(board[i][j].ruota == 1){
                tilesTmp[board[i][j].i] = ruotaTile(tilesTmp[board[i][j].i]);
            }
        }
    }
    for(i = 0; i < R; i++){
        tmp = 0;
        for(j = 0; j < C; j++){
            if(tilesTmp[board[i][j].i].coloreT1 == tilesTmp[board[i][0].i].coloreT1)  tmp++;
        }
        if(tmp == C){
            for(j = 0; j < C; j++){
                punteggioOrizzontale += tilesTmp[board[i][j].i].valoreT1;
            }
        }
    }
    for(j = 0; j < C; j++){
        tmp = 0;
        for(i = 0; i < R; i++){
            if(tilesTmp[board[i][j].i].coloreT2 == tilesTmp[board[0][j].i].coloreT2) tmp++;
        }
        if(tmp == R){
            for(i = 0; i < R; i++){
                punteggioVerticale += tilesTmp[board[i][j].i].valoreT2;
            }
        }
    }
    return punteggioOrizzontale+punteggioVerticale;
}
tile ruotaTile(tile t){
    tile tmp;
    tmp.coloreT2 = t.coloreT1;
    tmp.valoreT2 = t.valoreT1;
    tmp.coloreT1 = t.coloreT2;
    tmp.valoreT1 = t.valoreT2;
    return tmp;
}
