#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do 
    {
        printf("Height:");
        h = GetInt();
    }
    while (h > 23 || h < 0);
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= h - i; j++)
        {
            printf(" ");
        }
        for (int j = 1; j <= i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
