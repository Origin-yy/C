#include <stdio.h>
#define per_gallons 3.785
#define per_km 1.609

int main (void)
{
    const double miles = 3.785;
    double mileage;
    double gasoline;

    printf("Enter the mileage and the amount of gasoline consumed,\n");
    scanf("%lf %lf",&mileage,&gasoline);
    printf("Consumed one gasoline oil can deive %.1lf miles.\n",mileage/gasoline);
    printf("fTranslate in rise/km:%.1lf",((gasoline*per_gallons)/(per_km*mileage*100)));

    return 0;
}
