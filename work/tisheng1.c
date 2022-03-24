#include<stdio.h>

int main()
{
    float x,y;
    scanf("%f,%f",&x,&y);
    float a,b,c,d;
    a=(x-2)*(x-2)+(y-2)*(y-2);
    b=(x+2)*(x+2)+(y-2)*(y-2);
    c=(x+2)*(x+2)+(y+2)*(y+2);
    d=(x-2)*(x-2)+(y+2)*(y+2);
    
    if(a<=1||b<=1||c<=1||d<=1)
        printf("该点的建筑高度为10m");
    else
        printf("该点的建筑高度为0");

    return 0;
}
