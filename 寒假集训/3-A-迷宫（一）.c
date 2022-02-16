#include<stdio.h>

int is_t = 0;
int n,m;
char a[12][12];
int map[12][12] = {0};//地图，记有没有走过
int dx[4][4] = {0,0,1,-1};
int dy[4] ={1,-1,0,0};

void dfs(int i,int j){
    map[i][j] =1;
    if(a[i][j]=='T'){//到达终点就返回
        is_t = q;
        return;
    }
    for(int k = 0;k<4;k++){
        int fx = dx[k]+i;
        int fy = dy[k]+j;
        if(fx < 0)
    }
}