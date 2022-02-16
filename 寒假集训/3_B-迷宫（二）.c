#include<stdio.h>
//BFS广度优先搜索，一般靠队列进行完成，本题q代表队列头，cnt代表队列中已保存的数据个数（队列长度），并且方便保存数据进入队列尾
//每次搜索队列头的点可以去到的点，并把这个点的数据压入队列
int n,m,book[12][12];//标记地图上的点是否被走过
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};//上下左右移动
int queue_map[12*12][3];//记录队列位置记录的点的数据，最多12*12个点，一个点三个数据：横纵坐标和到达该点的最短步数
int cnt = 0;//记录队列位置，cnt所指位置来存放当前点的数据（也表示现在有几个点的数据被保存了）
int q = -1;//记录到达终点需要的最短步数，走不出就是-1
char map[12][12];//记录地图
void bfs(int p)//从现在的队列头开始
{
    if(p >= cnt) //如果队列头的位置已经超过了队列中所有保存数据的位置，说明说所有的点都已经记录过了，直接返回
        return;
    int x = queue_map[p][0],y = queue_map[p][1];//读取队列头位置的点的数据：横纵坐标，下一行读取步数
    int sum = queue_map[p][2];//sum表示从起点到达这个点所需的最短步数
    if(map[x][y] == 'T')//是终点就保存最短步数并返回
    {
        q = p;
        return;
    }
    for(int i = 0;i < 4;i++)//从读取的队列头位置的点向上下左右四个位置移动
    {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if(tx < 0 || tx >= n || ty < 0 || ty >= m || book[tx][ty] || map[tx][ty] == '*')
            continue;//如果这个点坐标出界，去过，或者是*的话就不去这个点，跳过去下一个点
        queue_map[cnt][0] = tx,queue_map[cnt][1] = ty,queue_map[cnt++][2] = sum + 1;//将这个点压入到当前队列位置，并保存数据，cnt++到下一个队列位置
    }
    book[x][y] = 1;//标记这个点已经去过
    bfs(p + 1);//更新队列头，继续从下一个队列头开始
    return;
}
int main(void)
{
    int x,y;
    scanf("%d %d",&n,&m);
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
    //读入地图，并找到起点.
    queue_map[cnt][0] = x,queue_map[cnt][1] = y,queue_map[cnt++][2] = 0;//将起点压入起始队列头0，cnt++到队列的下一个位置，即1
    bfs(0);//从起始队列头0保存的起点开始搜索
    if(q == -1)
        printf("-1");
    else
        printf("%d",queue_map[q][2]);

    return 0;
}