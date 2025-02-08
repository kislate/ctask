#include <stdio.h>
#include <string.h>
void sort(char a[][20],int);
int compare(const char *a, const char *b);
// int comparechar(char a,char b);
int main(){
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    char old[110000][20];//n
    int flag[110000];//n
    char full[110000][20];//m
    char new1[110000][20];//k
    for(int i=0;i<n;i++){
        scanf("%s",old[i]);
        flag[i]=0;  //0为要输出
    }
    for(int i=0;i<m;i++){
        scanf("%s",full[i]);
    }
    for(int i=0;i<k;i++){
        scanf("%s",new1[i]);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(strcmp(old[i],full[j])==0){
                flag[i]=1;
                break;
            }
        }
    }
    char putout[210000][20];
    int j=0;
    for(int i=0;i<n;i++){
        if(flag[i]==0){
            //putout[j]=old[i];
            strcpy(putout[j],old[i]);
            j++;
        }
    }
    for(int i=0;i<k;i++){
        // putout[j]=new1[i];
        strcpy(putout[j],new1[i]);
        j++;
    }
    sort(putout,j);
    for(int i=0;i<j;i++){
        puts(putout[i]);
    }
}
void sort(char a[][20],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(compare(a[j],a[j+1])>0){     //ascii码小的在前
                char temp[20];
                // temp=a[j];
                strcpy(temp,a[j]);
                // a[j]=a[j+1];
                strcpy(a[j],a[j+1]);
                // a[j+1]=temp;
                strcpy(a[j+1],temp);
            }
        }
    }
}
int compare(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        int result = comparechar(a[i], b[i]);
        if (result != 0) {
            return result;
        }
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') {
        return 0;
    } else if (a[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}
int comparechar(char a,char b){
    if(a==b){
        return 0;
    }
    else if(a>b){
        return 1;
    }
    else{
        return -1;
    }
}