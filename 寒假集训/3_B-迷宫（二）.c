#include<stdio.h>
int n,m,book[12][12];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
int queue_map[12*12][3],cnt,q = 1;
char map[12][12];
void bfs(int p)
{
    if(p >= cnt) 
        return;
    int x = queue_map[p][0],y = queue_map[p][1],sum = queue_map[p][2];
    if(map[x][y] == 'T')
    {
        q = p;
        return;
    }
    for(int i = 0;i < 4;i++)
    {
        int tx = x + dx[i],ty = y + dy[i];
        if(tx < 0 || tx >= n || ty < 0 || ty >= m || book[tx][ty] || map[tx][ty] == '*')
            continue;
        queue_map[cnt][0] = tx,queue_map[cnt][1] = ty,queue_map[cnt++][2] = sum + 1;
    }
    book[x][y] = 1;
    bfs(p + 1);
    return;
}
int main(void)
{
    int x,y;
    scanf("%d %d",n,m);
    for(int i = 0;i < n;i++)
    {
        scanf("%s",map[i]);
        for(int i = 0;i < n;i++)
        {
            for(int j = 0;j < m;j++){
                if(map[i][j] == 'S')
                {
                    x = i;
                    y = j;
                    break;
                }
            }
        } 
    }
    queue_map[cnt][0] = x,queue_map[cnt][1] = y,queue_map[cnt++][2] = 0;
    bfs(0);
    return 0;
}