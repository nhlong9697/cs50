/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"
#include <stdlib.h>

/**
 * Returns true if value is in array of n values, else false.
 */
void swap(int* x, int* y);
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    bool a = false;
    for (int i = 0; i < n; i++)
    {
        if (value == values[i])
        {
            a = true;
            break;
        }
    }
    return a;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1;j < n; j++)
        {
            if (values[j] < values[i])
            {
                swap(&values[j], &values[i]);
            }
        }
    }
    
}
void swap(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}