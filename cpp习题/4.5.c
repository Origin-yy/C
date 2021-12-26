#include<stdio.h>
int main(void)
{
    float v,s,t;
    printf("请输入文件下载速度和文件大小（以空格隔开，单位：Mb/s，MB）：\n");
    scanf("%f %f",&v,&s);
    t = 8*s/v;
    printf("At %.2f megabits per second,a flie of %.2f megabytes\n\
    \b\b\b\bdownloads in %.2f second.\n",v,s,t);
    return 0;

}