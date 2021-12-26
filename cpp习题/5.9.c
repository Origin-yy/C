#include<stdio.h>
void Temperature(double T);

int main(void) 
{
    double T = 0.0;

    printf("Please enter the Fahrenheit temperature:\n");
    while(scanf("%lf",&T) == 1)
    {
        Temperature(T);
        printf("Please enter the Fahrenheit temoerature(enter q to quit):\n");
    }
    return 0;
}

void Temperature(double T)
{
    const double a = 32.0; 
    const double b = 273.16;
    const double t = 5.0/9.0*(T-a);
    const double K = t + b;

    printf("Celsius:%.2lf Fahrenheit:%.2lf Kellogg's:%.2lf\n",T,K,t);

}