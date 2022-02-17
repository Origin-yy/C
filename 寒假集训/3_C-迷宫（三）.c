#include<stdio.h>

int n,m,book[17][17];
int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0};
int p = 0,q = -1,cnt = 0;//现存队列头，是否有出口，队列尾
char map[17][17];
int queue_map[17*17][3];//队列

void bfs(int p)
{
    if (p >= cnt)
        return;
    int x = queue_map[p][0],y = queue_map[p][1],sum = queue_map[p][2];
    if(map[x][y] == '.' && (x == 0 || x == n - 1 || y == 0 || y == m - 1))
    {
        if( q == -1 || q > sum)
            q = sum;
    }
    for(int i = 0;i < 4;i++)
    {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if(tx < 0 || tx >=n || ty < 0 || ty >= m || book[tx][ty] || map[tx][ty] == '#')
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
    scanf("%d %d",&n,&m);
    for(int i = 0;i < n;i++)
    {
        scanf("%s",map[i]);
    }
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < m;j++)
        {
            if(map[i][j] == '@')
            {
                x = i;
                y = j;
                break;
            }
        }
    }
    queue_map[cnt][0] = x,queue_map[cnt][1] = y,queue_map[cnt++][2] = 0;
    bfs(0);
    if(q == -1)
        printf("-1");
    else
        printf("%d",q);
    
    return 0;
}