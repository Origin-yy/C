#include<stdio.h>

int is_t = 0;
int sum = 0;
int n,m;
char a[12][12];//地图
int map[12][12] = {0};//地图，记地图上的坐标有没有走过
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

void dfs(int i,int j){
    map[i][j] =1;
    if(a[i][j]=='T')//到达终点就返回
    {
        is_t = 1;
        return;
    }
    for(int k = 0;k<4;k++)
    {
        int fx = dx[k]+i;
        int fy = dy[k]+j;//依次去目前所在位置的上下左右四个点
        sum += 1;
        if(fx < 0 || fy<0 || fx>=n || fy>=m || map[fx][fy] || a[fx][fy]=='*')
        {//如果这个点坐标出界，去过，或者是*的话就不去这个点，跳过去下一个点
            sum -= 1;
            continue;
        }
        
        dfs(fx,fy);//去到了下一个点，从这个点开始再走，递归
    }
}
int main(void)
{
    int x,y;
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%s",a[i]);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(a[i][j]=='S' && map[i][j]==0)
            {//是起始点并且没去过就用x，y记下点的位置
                x=i;
                y=j;
                break;
            }
        }
    }
    dfs(x,y);//用记下的点的坐标x，y调用函数dfs
    if(is_t < 0)
        printf("-1");
    if(is_t > 0)
        printf("%d",sum);

    return 0;
}