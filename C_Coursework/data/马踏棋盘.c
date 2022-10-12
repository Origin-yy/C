#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define X 6   // 棋盘宽度
#define Y 6   // 棋盘长度
#define YELLOW   "\e[1;33m"     // 黄色
#define U_YELLOW "\e[4;1;33m"   // 下划线加黄色
#define GREEN    "\e[4;1;36m"   // 下划线加绿色
#define UNDER    "\e[4m"        // 下划线
#define NONE     "\e[0m"

int chess[X][Y];   // 棋盘
// 找到下一个可走的位置
int next(int *px, int *py, int count){
    int x = *px;
    int y = *py;

    switch (count){
    case 0:
        if (x + 2 <= X - 1 && y - 1 >= 0 && chess[x + 2][y - 1] == 0){
            *px = x + 2;
            *py = y - 1;
            return 1;
        }
        break;
    case 1:
        if (x + 2 <= X - 1 && y + 1 <= Y - 1 && chess[x + 2][y + 1] == 0){
            *px = x + 2;
            *py = y + 1;
            return 1;
        }
        break;
    case 2:
        if (x + 1 <= X - 1 && y - 2 >= 0 && chess[x + 1][y - 2] == 0){
            *px = x + 1;
            *py = y - 2;
            return 1;
        }
        break;
    case 3:
        if (x + 1 <= X - 1 && y + 2 <= Y - 1 && chess[x + 1][y + 2] == 0){
            *px = x + 1;
            *py = y + 2;
            return 1;
        }
        break;
    case 4:
        if (x - 2 >= 0 && y - 1 >= 0 && chess[x - 2][y - 1] == 0){
            *px = x - 2;
            *py = y - 1;
            return 1;
        }
        break;
    case 5:
        if (x - 2 >= 0 && y + 1 <= Y - 1 && chess[x - 2][y + 1] == 0){
            *px = x - 2;
            *py = y + 1;
            return 1;
        }
        break;
    case 6:
        if (x - 1 >= 0 && y - 2 >= 0 && chess[x - 1][y - 2] == 0){
            *px = x - 1;
            *py = y - 2;
            return 1;
        }
        break;
    case 7:
        if (x - 1 >= 0 && y + 2 <= Y - 1 && chess[x - 1][y + 2] == 0){
            *px = x - 1;
            *py = y + 2;
            return 1;
        }
        break;
    }

    return 0;
}
int setHorse(int x, int y, int tag){
    int x1 = x, y1 = y, flag = 0, count = 0;

    // tag记录步数
    chess[x][y] = tag;
    // 如果步数为X*Y说明马踏完了
    if (tag == X * Y){
        return 1;
    }

    // 如果可以走，那么flag为1
    flag = next(&x1, &y1, count);
    // 否则尝试其他路径
    while (flag == 0 && count < 7){
        count += 1;
        flag = next(&x1, &y1, count);
    }
    // 递归进入下一个坐标
    while (flag){
        // 返回1表示成功找到落脚点
        if (setHorse(x1, y1, tag + 1)){
            return 1;
        }
        // 否则从上一步重新尝试
        x1 = x;
        y1 = y;
        count += 1;
        flag = next(&x1, &y1, count);
        while (flag == 0 && count < 7){
            count += 1;
            flag = next(&x1, &y1, count);
        }
    }

    if (flag == 0){
        chess[x][y] = 0;
    }

    return 0;
}

int main(void){
    // 棋盘全局初始化为0；
    for (int i = 0; i < X; i++){
        for (int j = 0; j < Y; j++){
            chess[i][j] = 0;
        }
    }
    int begin_x = 1;   // 马的起始横坐标    
    int begin_y = 1;   // 马的起始纵坐标
    printf(YELLOW"请输入马的起始位置(输入-1表示随机放置,格式:1,1)\n"NONE);
    while(1){
        scanf("%d",&begin_x);
        if(begin_x == -1){
            srand(((unsigned)time(NULL)));
            begin_x = rand() % X;
            begin_y = rand() % Y;
        }else{
            scanf(",%d",&begin_y);
        }
        if(begin_x >= X || begin_x < -1 || begin_y >= Y || begin_y < 0){
            printf("输入不符合要求,请重新输入.\n");
        }else{
            break;
        }
    }
    printf(YELLOW"马儿的起始位置为:%d,%d\n"NONE, begin_x, begin_y);
    printf(YELLOW"聪明的马儿正在思考...\n"NONE);
    if (setHorse(begin_x, begin_y, 1)){
        for(int t = 0; t <= X*Y; t++){
            system("clear");
            printf(YELLOW"马儿的起始位置为:%d,%d\n"NONE, begin_x, begin_y);
            printf(YELLOW"聪明的马儿是这样走的:\n"NONE);
            for(int i = 0; i < X; i++){
                printf(UNDER"   "NONE);
            }
            printf("\n");
            for (int i = 0; i < X; i++){
                for (int j = 0; j < Y; j++){
                    if(chess[i][j] < t){
                        printf(GREEN"〇"NONE);
                        printf(UNDER"│"NONE);
                    }
                    else if(chess[i][j] == t){
                        printf(U_YELLOW"马"NONE);
                        printf(UNDER"│"NONE);
                    }else{
                        printf(UNDER"  │"NONE);
                    }
                }
                putchar('\n');
            }
            usleep(500000);
        }
    }
    else{
        printf("走不完,怎么想都走不完吧!\n");
    }

    return 0;
}