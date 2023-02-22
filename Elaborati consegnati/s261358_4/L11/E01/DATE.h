#ifndef DATE_H
#define DATE_H
#include <stdio.h>

typedef struct{
    int hh;
    int mm;
} ORARIO;

typedef struct{
    int aaaa;
    int mm;
    int gg;
} DATA;


int DATAcmp(DATA d1, DATA d2);
/*RITORNA -1 SE d1<d2
           0 SE d1=d2
           1 SE d1>d2 */
DATA DATAsetNull();
DATA DATAload(FILE *fp);
void DATAstore(DATA d, FILE *fp);

#endif // DATE_H
