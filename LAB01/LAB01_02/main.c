#include <stdio.h>
#define MAX 200
#define S 5


int main(){
int sol[15]={0};
int k=0;
int v[3][2]={0};
int i,j;
for(i=0;i<S;i++){
    for(j=0;j<S;j++){
        if(v[i][j]==0){
        sol[k++]=1;
        }
    }
}

for(i=0;i<k;i++){
    printf("%d-",sol[i]);
}

}



