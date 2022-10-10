#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct // 运算符栈
{
    char top;
    int elem[MAXSIZE];
} OPTR;

typedef struct // 操作数栈
{
    int top;
    int elem[MAXSIZE];
} OPND;

OPTR R;
OPND D;

void OPTRInitStack() //运算符栈初始化
{
    R.top = -1;
}

void OPNDInitStack() //操作数栈初始化
{
    D.top = -1;
}

void PushR(char x) //运算符入栈
{
    R.top++;
    R.elem[(int)R.top] = x;
}

void PushD(int m) //操作数入栈
{
    D.top++;
    D.elem[D.top] = m;
}

char GetTopR() //返回运算符栈顶元素
{
    char top;
    top = R.elem[(int)R.top];
    return top;
}

int GetTopD() //返回操作数栈顶元素
{
    int top;
    top = D.elem[D.top];
    return top;
}

char optr[7] = {'+', '-', '*', '/', '(', ')', '#'};

char seek[7][7] = {
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'<', '<', '<', '<', '<', '=', ' '},
    {'>', '>', '>', '>', ' ', '>', '>'},
    {'<', '<', '<', '<', '<', ' ', '='}};

int Isoperator(char ch) //判断输入的字符是否是运算符
{
    int i;
    for (i = 0; i < 7; i++)
    {
        if (optr[i] == ch)
            return 1; //如果输入的字符是运算符
    }
    return 0;
}

char compare(char ch1, char ch2) //比较运算符优先级
{
    int i, m, n;
    char p;
    for (i = 0; i < 7; i++) //找出两个数的位置
    {
        if (optr[i] == ch1)
            m = i;
        if (optr[i] == ch2)
            n = i;
    }
    p = seek[m][n]; //找到比较结果
    return p;
}

char PopR() //运算符栈出栈
{
    char k;
    k = R.elem[(int)R.top];
    R.top--;
    return k;
}

int PopD() //操作数栈出栈
{
    int x;
    x = D.elem[D.top];
    D.top--;
    return x;
}

int Operate(int a, char theta, int b)
{
    int res;
    switch (theta)
    {
    case '+':
        res = a + b;
        break;
    case '-':
        res = a - b;
        break;
    case '*':
        res = a * b;
        break;
    case '/':
        if (b != 0)
        {
            res = a / b;
            break;
        }
        else
        {
            printf("除数不能为0!");
            exit(0);
        }
    }
    return res;
}

int Putint(int x, int sum)
{
    sum = sum * 10 + x;
    return sum;
}

void Estimate() //判断计算函数

{

    int a, b, x, c;
    int sum = 0;
    char theta, e, ch, z, result;
    a = b = x = 0;
    theta = e = z = '0';
    result = '0';
    printf("请输入表达式（以#结束）：\n");
    ch = getchar();
    while (ch != '#' || GetTopR() != '#')
    {
        if (!Isoperator(ch)) // 当不是运算数符时
        {
            x = ch - '0'; // 将字符转换为十进制数
            sum = Putint(x, sum);
            ch = getchar();
        }
        else // 当是运算符时
        {
            if (sum != 0)
            {
                PushD(sum);
                sum = 0;
            }
            e = GetTopR();
            switch (compare(e, ch)) // 进入的运算符与前一个比较优先级
            {
            case '<':
                PushR(ch); // 如果当前运算符比前一个运算符的优先级高，则进入运算符栈，继续读取下一个字符
                ch = getchar();
                break;
            case '>':
                theta = PopR(); // 如果当前运算符比前一个运算符的优先级低,退出前一个运算符
                b = PopD();     // 从操作数栈弹出栈顶的两个元素
                a = PopD();
                c = Operate(a, theta, b);
                PushD(c);
                break;
            case '=':
                z = PopR();
                ch = getchar();
                break;
            }
        }
    }
    result = GetTopD();
    printf("计算结果为：%d", result);
}

int main()
{
    OPTRInitStack(); //初始化运算符栈
    PushR('#');      //将#输入运算符栈
    OPNDInitStack(); //初始化操作数栈
    Estimate();      //调用判断计算函数
    return 0;
}