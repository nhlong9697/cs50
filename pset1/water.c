#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("minutes:");
    int i = GetInt();
    printf("bottles:%i\n",192*i/16);
}