#include<stdio.h>
void read(double arr[][5]);
void aver_part(double arr[],int n);
double aver_all(double arr[][5]);
double max(double arr[][5]);
void write(double arr[][5],double average,double max_a);

int main(void)
{
    int n;
    double average;
    double max_a;
    double a[3][5] = {0};

    read(a);
    for(int j = 0;j < 3;j++)
        aver_part(a[j],j);
    average = aver_all(a)/15;
    max_a = max(a);
    write(a,average,max_a);
    return 0;
}

void read(double arr[][5])
{
    for (int i = 0;i < 3;i++)
    {
        printf("Please enter the %dth set of 5 data.\n",i+1);
        for(int j = 0;j < 5;j++)
            scanf("%lf",&arr[i][j]);
    }
}

void aver_part(double arr[],int n)
{
    double sum = 0;
    for(int i = 0;i < 5;i++)
        sum += arr[i];  
    printf("The average value of %dth set of data is %.5lf\n",n,sum/5);
}

double aver_all(double arr[][5])
{
    double sum = 0;
    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 5;j++)
            sum += arr[i][j];
    }
    return sum;
}

double max(double arr[][5])
{
    double *p =arr[0];
    double max = *p;
    for(int i = 0;i < 15;i++)
    {
        if(*(p + i + 1) > max)
            max = *(p + i + 1);
    }
    return max;
}

void write(double arr[][5],double average,double max_a)
{
    printf("The average of all data is %.5lf.\n",average);
    printf("The maximum value of all data is %.5lf.\n",max_a);
    printf("All results are to five decimal places。\n");
}