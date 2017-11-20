#include "helpers.h"
#include <stdio.h>
int main(void)
{
    //set values
    int n = 6;
    int values[] = {3,4,1,5,2,6};
    //test function
    sort(values,n);
    //print out result
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", values[i]);
    } 
    printf("\n");
}