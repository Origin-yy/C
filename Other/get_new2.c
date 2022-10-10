#include<stdio.h>

/*
    出题人：袁野
    考点：结构体和指针的综合使用
*/

// 梳理好思路，画出结构示意图并解释程序输出

typedef struct S
{
    int n;
    int* p;
}S;

int main()
{
    struct S s;

    int* p = &s.n;
    p[0] = 4;
    p[1] = 3;
    s.p = p;
    s.p[1] = 1;
    s.p[2] = 2;
    return 0;
}