#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct{
       int gg;
       int mese;
       int anno;
       int toint;
}data_di_nascita;
typedef struct{
        char codice[4];
        char nome[MAX];
        char cognome[MAX];
        data_di_nascita nascita;
        char via[MAX];
        char citta[MAX];
}Item;
/*la lista e' una struct wrapper con campo puntatore alla testa e campo intero con il numero di elementi contenuti*/
/*si dichiara un alias link per un puntatore a struct node*/
typedef struct node *link;
struct node{
        Item val;
        link next;
};
struct list{
    link head;
    int num;
};
int schermo_menu();
void AddItem(Item x,link *root,link *aux);
void insertItem();
link new_file(link *aux,link *root);
Item SortListSearchbycode(Item *nodo,link head);
link listDelkeybycode(Item *nodo,link head);
link listDelkeybydates(Item *nodo,link head);
void print(Item *nodo);
int main()
{
    int i=0,cmd;
    link root=NULL,aux;
    Item x;

    cmd=schermo_menu();
        switch(cmd){
                    case 1:
                            insertItem();
                            AddItem(x,root,aux);
                            break;
                    case 2:
                            root=new_file(&x,root);
                            break;
                    case 3:
                            SortListSearchbycode(&x,root);
                            break;
                    case 4:
                            listDelkeybycode(&x,root);
                            break;
                    case 5:
                            listDelkeybydates(&x,root);
                            break;
                    case 6:
                            print(&x);
                            break;
                    case 7:
                            printf("Fine \n");
                            break;
                }
    return 0;
}
int schermo_menu(){
        int scelta;
           do{
            printf("Menu':\n");
            printf("1.acquisizione e inserimento da tastiera \n");
            printf("2.acquisizione e inserimento da file\n");
            printf("3.ricerca per codice \n");
            printf("4.cancellazione con estrazione per codice \n");
            printf("5.cancellazione con estrazione degli elementi con date comprese tra 2\n");
            printf("6.stampa della lista su file.\n");
            printf("7.fine \n");
            printf("Fai una scelta: \n");
            scanf("%d",&scelta);
           }while(scelta==1||scelta==2||scelta==3||scelta==4||scelta==5||scelta==6||scelta==7);
           return scelta;
}
/*funzione che alloca nuovo nodo memorizzandone il duplicato dell'input*/
void AddItem(Item x,link *root,link *aux){
          if(root==NULL){
                root=(link *)malloc(sizeof(link));
                aux=root;
        }else{
                aux->next=(link *)malloc(sizeof(link));
                aux=aux->next;
        }
        aux->val=x;
        aux->next=NULL;

}
void insertItem(){
        Item i;
        printf("Inserire codice \n");
        scanf("A%d",&i.codice);
        printf("Inserire nome e cognome \n");
        scanf("%s %s",i.nome,i.cognome);
        printf("Inserire data di nascita \n");
        scanf("%d/%d/%d",&i.nascita.gg,&i.nascita.mese,&i.nascita.anno);
        printf("Inserire via e citta' \n");
        scanf("%s %s",i.via,i.citta);
}
link new_file(link *aux,link *root){
    char *res;
    FILE *fp;
    /*dichiarazione e allocazione puntatore x al nodo*/
    link x=malloc(sizeof *x);
    if((fp=fopen("anagrafica.txt","r"))==NULL){
        printf("Errore in apertura file \n");
        return -1;
    }
    //lettura e riempimento struct Item
    while(res!=EOF){
        res=fscanf(fp,"A%d %s %s %d/%d/%d %s %s",&x.codice,x.nome,x.cognome,&x.nascita.gg,&x.nascita.mese,&x.nascita.anno,x.via,x.citta);
    }
    AddItem(x,root,aux);
    return x;
}
//attraversamento lista con la tecnica del solo puntatore, restituisce il dato vuoto ad esito negativo
Item SortListSearchbycode(Item *nodo,link root){
        int code;
        Item x;
        printf("Inserire codice di ricerca: \n");
        scanf("%d",&code);
        for(x=head;x!=NULL && (code==x->codice);x=x->next){
                if(x!=NULL)
                        return x->val;
        }
}
link listDelkeybycode(Item *nodo,link head){
        link x,p; //puntatore x al nodo corrente e p al predecessore
        int code;
        Item x;
        printf("Inserire codice degli elementi da eliminare: \n");
        scanf("%d",&code);
        if(head==NULL)
                return NULL; //caso lista vuota
        for(x=head,p=NULL;x!=NULL ;p=x,x=x->next){
                if(code==x->codice){
                        if(x==head)
                                head=x->next;
                        else
                                p->next=x->next;
                        free(x);
                        break;
                }
        }
        return head;
}
link listDelkeybydates(Item *nodo,link head){
        int gg1,mese1,anno1,toint1,gg2,mese2,anno2,toint2;
        link x,p;
        x->nascita->toint=x->nascita->gg + 30*x->nascita->mese + 365*x->nascita->anno;
        printf("Inserire prima data: \n");
        scanf("%d/%d/%d",&gg1,&mese1,&anno1);
        toint1=gg1+30*mese1+365*anno1;
        printf("Inserire seconda data: \n");
        scanf("%d/%d/%d",&gg2,&mese2,&anno2);
        toint2=gg2+30*mese2+365*anno2;
        if(head==NULL)
                return NULL; //caso lista vuota
        for(x=head,p=NULL;x!=NULL ;p=x,x=x->next){
                if((x->nascita->toint >toint1 && x->nascita->toint <toint2)||(x->nascita->toint >toint2 && x->nascita->toint <toint1)){
                        if(x==head)
                                head=x->next;
                        else
                                p->next=x->next;
                        free(x);
                        break;
                }
        }
}
void print(Item *nodo){
        int i=0;
        FILE *fp;
        char file[10];
        Item x;
        printf("Inserire file di salvataggio \n");
        scanf("%s",file);
        fp=fopen("file","w");
        if(nodo==NULL)
                return;
        x=nodo->head;
        while(x!=NULL){
                fprintf(fp,"A%d %s %s %d/%d/%d %s %s",x[i]->codice,x[i]->nome,x[i]->cognome,x[i]->nascita->gg,x[i]->nascita->mese,x[i]->nascita->anno,x[i]->via,x[i]->citta);
                i++;
                x=x->next;
        }
}
