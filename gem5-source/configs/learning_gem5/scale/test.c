#include <stdio.h>
#include <malloc.h>

int main()

{

    int *a1, *a2, *a3;

    a1 = (int *)malloc(2 * sizeof(int));
    a2 = (int *)malloc(2 * sizeof(int));
    a3 = (int *)malloc(2 * sizeof(int));

    for (int i = 0; i < 2; i++)
    {
        a1[i] = i;
        a2[i] = i;
        a3[i] = i;
    }

    // Addition of two arrays
    for (int i = 0; i < 2; i++)
    {
        a1[i] = a2[i] + a3[i];
    }

    // Printing the result
    for (int i = 0; i < 2; i++)
    {
        printf("%d\n ", a1[i]);
    }
}