#include <stdio.h>
#include <stdlib.h> // for malloc(), and rand()
#include <getopt.h> // for getopt()
#include <time.h>   // for clock()
#include <string.h> // for strcmp()

int main(int argc, char *argv[])
{
    
    // Pointers to calculate the sum of two arrays and store the result in a third array
    int *a, *b, *c;


    int s = 0, j = 0; // s - optarg(), j - for index

    // Command line arguments
    // Number of elements in the arrays - n
    // Error to be introduced - e
    // Number of iterations - t
    int n = 0, e = 0, t = 0;

    // To measure the performance

    clock_t start, end;
    double cpu_time_used, time_taken;

    // Get the command-line arguments n and i
    while ((s = getopt(argc, argv, ":n:e:t")) != -1) // Where, t - number of iterations
    {
        switch (s)
        {

        case 'n':
            if (optarg != NULL)
                n = atoi(optarg);

        case 'e':
            if (strcmp(argv[4], "bo") == 0) // Buffer - Overflow
                e = 1;

            else if (strcmp(argv[4], "uaf") == 0) // Use - After - Free
                e = 2;

            else if (strcmp(argv[4], "df") == 0) // Double - Free
                e = 3;

            else if (strcmp(argv[4], "u") == 0) // Unallocated - Memory
                e = 4;

            else
                printf("We do not support injecting this error currently\n");

        case 't':
            t = atoi(argv[6]);
            break;

        default:
            break;
        }
    }

    // Allocate heap memory for the arrays

    a = (int *)malloc(16 * n * sizeof(int));
    b = (int *)malloc(16 * n * sizeof(int));
    c = (int *)malloc(16 * n * sizeof(int));

        printf("hello");
    // Print the sizes of malloc requested for each array
    printf("\nSize of a: %ld\n", 16 * n * sizeof(int));

    // Assign values to the arrays - random values between 0 and 99
    // Store only one element in a cacheline and fill the rest of the elements in a cacheline with zeros

    for (j = 0; j < n; j++)
    {

        *(a + j * 16) = rand() % 100;
        *(b + j * 16) = rand() % 100;
        // Rest of the elements of the cacheline with zeros
        for (s = 1; s < 16; s++)
        {
            *(a + j * 16 + s) = 0;
            *(b + j * 16 + s) = 0;
        }
    }

    // Perform the computation

    start = clock(); // Start the timer
    while (t != 0)
    {
        for (j = 0; j < t; j++)
        {
            *(c + j * 16) = *(a + j * 16) + *(b + j * 16);
        }

        t--;
    }

    end = clock();
    cpu_time_used = ((double)end - start) / CLOCKS_PER_SEC;       // In seconds
    time_taken = cpu_time_used * 1000;                            // In milliseconds
    printf("\nThe time taken is %lf milliseconds\n", time_taken); // lf is the format specifier for double in c

    // Inject the errors based on the choice

    if (e == 1) // Buffer - Overflow
    {
        printf("Introducing buffer overflow - Accessing a location beyond the range");
        // Access a location beyond the range of the array and write to it
        *(c + n * 16 + 3) = 4;
    }

    else if (e == 2) // Use - After - Free
    {
        printf("\nBefore freeing: %d\n", *(c + 1));

        // Free the memory locations and then try to access it
        free(a);
        free(b);
        free(c);

        printf("After freeing: %d\n", *(c + 1));

        // Writing to a memory location that has been freed
        *(c + 1) = 4;
    }

    else if (e == 3) // Double - Free
    {
        // Free the memory twice : to introduce double-free-error

        free(a);
        free(b);
        free(c);

        free(a);
        free(b);
        free(c);

        // Occurs in multi-threaded programs
    }

    /*  else if ( e == 4) // Unallocated - Memory
        {
        }
    */
    else
    {
        printf(" To be filled \n");
    }

    free(a);
    free(b);
    free(c);

    return 0;
}