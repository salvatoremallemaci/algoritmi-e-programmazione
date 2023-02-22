#ifndef ST_H
#define ST_H

typedef struct symboltable *ST;
ST STinit(int maxN);
void STinsert(ST st, char *code);
int STsearch(ST st, char *code);
char *STsearchByIndex(ST st, int index);
int STcount(ST st);
void STfree(ST st);

#endif // ST_H
