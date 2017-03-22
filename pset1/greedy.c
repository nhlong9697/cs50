#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    printf("O hai! ");
    
    float f;
    do
    {
        printf("How much change is owed?\n");
        f = GetFloat();
    }
    while (f <= 0);
    int change = round(f * 100);
    int coin = 0;
    while (change > 0)
    {
        if (change >= 25)
        {
            change -= 25;
        }
        else if (change >= 10)
        {
            change -= 10;
        }
        else if (change >= 5)
        {
            change -= 5;
        }
        else 
        {
            change -= 1;
        }
        coin++;
    }
    printf ("%i\n",coin);
    
}