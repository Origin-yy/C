#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void*x, const void*y){
    return *(int*)x - *(int*)y;
}
int main(){
    srand((unsigned)time(NULL));
    for(int i = 0; i < 10; i++){
        int a[50] = {0};
        int b[100] = {0};
        int m = 0, n = 0;
        m = rand()%50+1;
        n = rand()%50+1; 

        printf("一班:\n");
        for(int j = 0; j < m; j++){
            a[j] = rand()%101;
        }
        qsort(a,m,sizeof(int),cmp);
        for(int j = 0; j < m; j++){
            printf("%d ",a[j]);
        }
        printf("\n");

        printf("二班:\n");
        for(int j = 0; j < n; j++){
            b[j] = rand()%101;
        }
        qsort(b,n,sizeof(int),cmp);
        for(int j = 0; j < n; j++){
            printf("%d ",b[j]);
        }
        printf("\n");

        for(int j = 0; j < m; j++){
            b[n+j] = a[j];
        }
        qsort(b,m+n,sizeof(int),cmp);
        printf("总:\n");
        for(int j = 0; j < m+n; j++){
            printf("%d ",b[j]);
        }
        printf("\n");
    }
    return 0;
}