#include <stdio.h>

/*
    出题人：袁野
    考点：指针和字符串数数组的结合，指针运算
*/

// 梳理好思路，画出结构示意图并解释程序输出
int main(){
    char* c[] = { "XI", "YOU", "LINUX", "GROUP" };
    char** cp[] = { c + 3, c + 2, c + 1, c };
    char*** cpp = cp;
    printf("%s\n", **++cpp);   
    printf("%s\n", *-- * ++cpp + 3);    
    printf("%s\n", *cpp[-2] + 3);   
    printf("%s\n", cpp[-1][-1] + 1);  

    return 0;
}