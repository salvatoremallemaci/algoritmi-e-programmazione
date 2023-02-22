#ifndef ITEM_H
#define ITEM_H

#define MAXC 20
typedef struct item *ITEM;
ITEM ITEMnew(char *label, char *net);
void ITEMfree(ITEM item);
char *ITEMgetLabel(ITEM item);
char *ITEMgetNet(ITEM item);
void ITEMdisplay(ITEM item);

#endif // ITEM_H
