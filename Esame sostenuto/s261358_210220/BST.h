/* ALLEGO ESCLUSIVAMENTE IL .h DEL MODULO BST, AL FINE DI POTER DARE UN'IDEA
   DI COME AVREI VOLUTO TRATTARE LA MEMORIZZAZIONE DI CIASCUN MENU' IN BST   */

// SI TRATTA DI UN ADT DI PRIMA CLASSE, DUNQUE PUNTATORE OPACO ALLA STRUCT DA DICHIARARE IN UN EVENTUALE BST.c

#ifndef BST_H
#define BST_H

typedef struct binarysearchtree *BST;

BST BSTinit();
void BSTfree(BST bst);
void BSTinsert(BST bst,MENU m);
void BSTvisit(BST bst,int strategy);
//penserei ad una visita in-ordere per la stampa

#endif // BST_h

