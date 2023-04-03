#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    // Aim: To access a new cache line every time
    // Pointers to calculate the sum of two arrays and store the result in a third array
    // An index array to store the indices of the elements to be accessed

    int *a, *b, *c, *index;

    // Command line arguments
    // Number of elements in the arrays - n
    // Error to be introduced - e
    // Number of elements in the index array - k
    int n = 1000000, k = 0, e;

    // To measure the performance
    clock_t start, end;
    double cpu_time_used, time_taken;

    // For loop variables
    int j, f;

    // For getopt()
    int s;

    // Fetch the command line arguments
    while ((s = getopt(argc, argv, "k:e:")) != -1)
    {
        switch (s)
        {

        case 'k':
            if (optarg != NULL)
                k = atoi(optarg);

        case 'e':

            if (strcmp(argv[4], "bo") == 0)
                e = 1;

            else if (strcmp(argv[4], "uaf") == 0)
                e = 2;

            else if (strcmp(argv[4], "df") == 0)
                e = 3;

            else if (strcmp(argv[4], "u") == 0)
                e = 4;

            else

                printf("We do not support injecting this error currently\n");
        }
    }

    // Allocate heap memory for the arrays
    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));
    index = (int *)malloc(k * sizeof(int));

    // Initialize the arrays with values between 0 and 100
    for (j = 0; j < n; j++)
    {
        a[j] = rand() % 100;
        b[j] = rand() % 100;
    }

    // Initialize the index array with random values rand % n
    for (int j = 0; j < k; j++)
    {
        index[j] = rand() % n;
    }

    // Start the timer
    start = clock();

    // Perform the computation i times
    // Print the k value from command line
    printf("k: %d\n", k);
    for (j = 0; j < k; j++)
    {

        // Access the value at the index stored in the index array
        f = index[j];
        *(c + f) = *(a + f) + *(b + f);
    }

    end = clock();

    cpu_time_used = ((double)end - start) / CLOCKS_PER_SEC; // In seconds

    time_taken = cpu_time_used * 1000;                            // In milliseconds
    printf("\nThe time taken is %lf milliseconds\n", time_taken); // Print the time taken

    // Inject the errors

    if (e == 1) // Buffer - Overflow
    {
        printf("Introducing buffer overflow - Accessing a location beyond the range\n");
        // Access a location beyond the range of the array
        *(c + n + 3) = 4;
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
        printf("New value: %d\n", *(c + 1));
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

    /*  else if ( ch == 4) // Unallocated - Memory
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
