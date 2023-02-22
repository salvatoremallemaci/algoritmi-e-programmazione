#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char *cercaRegexp(char *src, char *regexp);
int main()
{
    char src[100],regexp[100];
    char *res;
    printf("Stringa sorgente in cui effetturare le ricerche: ");
    scanf("%s",src);
    printf("Comandi disponibili:\n");

    printf(".parola\n");
    printf("[carattere]parola.\n");
    printf("[^carattere]parola.\n");
    printf("\\carattere minuscolo parola.\n");
    printf("\\carattere maiuscolo parola.\n");

    printf("Stringa \"espressione regolare\": ");
    scanf("%s",regexp);



    res=cercaRegexp(src,regexp);
    if(res==NULL){
        printf("NULL");
    }else{
    printf("%s",res);
    }

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int i,j,ok=-1,good1=-1,good2=-1,good3=-1,good4=-1,good5=-1;
    int lung_reg=strlen(regexp);
    int lung_src=strlen(src);
    char lettera;

    char tmp1[100]={0},tmp2[100]={0};


    //blocco 1
    if(regexp[0]=='.'){
        for(i=0;i<lung_reg-1;i++){
            tmp1[i]=regexp[i+1];
        }
    }
        for(i=0;i<lung_src-1;i++){
            tmp2[i]=src[i+1];
        }
    if(strcmp(tmp1,tmp2)==0){
        good1=1;
        return src;
    }else{
    good1=0;
    }

    //blocco 2
    i=0;j=0;

    if(regexp[0]=='['){
    if(regexp[i+1]!='^'){
    while(regexp[i]!=']'){
        tmp1[j]=regexp[i+1];
        i++;
        j++;
    }
    tmp1[j-1]='\0';
    for(i=0;i<strlen(tmp1);i++){
        if(src[0]==tmp1[i]){
            good2=1;
            return src;
            break;
        }else{
        good2=0;
        }
    }
    //blocco 3
    }else if(regexp[i+1]=='^'){
        lettera=regexp[i+2];
        if(src[0]!=lettera){
            good3=1;
            return src;
        }else if(src[0]==lettera){
        good3=0;
        }
    }
    }

    i=0;j=0;
    if(regexp[0]=='\\' && regexp[1]=='a'){
        if(src[0]>=97 && src[0]<=122){ //sfrutto il codice ASCII.In esadecimale, le lettere minuscole sono comprese tra il 97 e il 122.
             for(i=2;i<lung_reg;i++){
                tmp1[j]=regexp[i];
                j++;
            }
            j=0;
            for(i=1;i<lung_src;i++){
                tmp2[j]=src[i];
                j++;
            }
            if(strcmp(tmp1,tmp2)==0){
                good4=1;
                return src;
            }else{
            good4=0;
            }
        }
    }
    else if(regexp[0]=='\\' && regexp[1]=='A'){
        if(src[0]>=65 && src[0]<=90){//sfrutto il codice ASCII.In esadecimale, le lettere maiuscole sono comprese tra il 65 e il 90.
            for(i=2;i<lung_reg;i++){
                tmp1[j]=regexp[i];
                j++;
            }
            j=0;
            for(i=1;i<lung_src;i++){
                tmp2[j]=src[i];
                j++;
            }
            if(strcmp(tmp1,tmp2)==0){
                good5=1;
                return src;
            }else{
            good5=0;
            }
        }
    }

    if(!good1 || !good2 || !good3 || !good4 || !good4){
        return NULL;
    }
}
