#include <stdio.h>
//#include <conio.h>
int keydoor(int key)
{
    char size[6];
    char yes_password[6] = {2,7,0,4,2,6}; //正确密码
    int i,j;
    int yes_number = 0; //输入正确的密码个数

//   keydoor:
    for(i=0; i<6;i++){
        size[i] = getchar();
        printf("*");
    }

    for(i=0; i<6; i++)
    {
        for(j=0; j==i; j++)
        {
            if(size[i] == yes_password[j])
            {
                yes_number++;
            }
        }
    }
    if(yes_number == 6)
    {
        printf("密码正确\n门开了！！！");
        return 0;
    }
    else{
        printf("密码错误，请重新输入");
//        goto keydoor;
    return 1;
    }
 }
int main(void)
{   
    int n;
    n = keydoor(1);
    if(n)
    {
        n = keydoor(1);
    }
    
}