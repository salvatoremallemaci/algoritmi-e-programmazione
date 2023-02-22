#ifndef ST_H
#define ST_H

#include "Item.h"

#define MAXC 20
typedef struct symboltable *ST;

ST ST_init(int maxN);
int ST_count(ST st);
void ST_free(ST st);
void ST_insert(ST st, ITEM i, int index);
int ST_search(ST st, char *label);
char *STsearchByIndex(ST st, int index);


#endif // ST_H
