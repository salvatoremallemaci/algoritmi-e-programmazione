#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Item.h"

struct item{
char *label;
char *net;
};

ITEM ITEMnew(char *label, char *net){
    ITEM ret=malloc(sizeof(ITEM));
    ret->label=malloc(MAXC*sizeof(char));
    ret->net=malloc(MAXC*sizeof(char));
    strncpy(ret->label,label,MAXC);
    strncpy(ret->net,net,MAXC);
    return ret;
}

void ITEMfree(ITEM item){
    if(item==NULL)return;
    free(item->label);
    free(item->net);
    free(item);
}

char* ITEMgetLabel(ITEM item){
    char *ret=malloc(MAXC*sizeof(char));
    strncpy(ret,item->label,MAXC);
    return ret;
}

char* ITEMgetNet(ITEM item){
    char *ret=malloc(MAXC*sizeof(char));
    strncpy(ret,item->net,MAXC);
    return ret;
}

void ITEMdisplay(ITEM item){
    printf("%s %s\n",item->label,item->net);
}
