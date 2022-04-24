#include<stdio.h>
int main(void)
{
    int M=0,sum=0;
    printf("请输入方阵的长：\n");
    scanf("%d",&M);
    int map[M][M];
    //初始化方阵
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<M; j++)
        {
            map[i][j] = 0;
        }
        printf("\n");
    }
    //从外向内绕圈对每个位置进行赋值
    int x=0,y=0,k=1;
    for(int i=0; i<M/2; i++)
    {
        while(y<M-i)
            map[x][y++] = k++;
        y--;
        x++;
        while(x<M-i)
            map[x++][y] = k++;
        x--;
        y--;
        while(y>=0+i)
            map[x][y--] = k++;
        y++;
        x--;
        while(x>=1+i)
            map[x--][y] = k++;
        x++;
        y++;
    }
    //边长为为奇数时补上最中间的
    if(M%2==1)
        map[M/2][M/2] = M*M;
    //打印结果
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<M; j++)
        {
            printf("%3d",map[i][j]);
            if( j!=M-1)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}