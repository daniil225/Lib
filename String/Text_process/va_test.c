#include <stdio.h>
#include <stdarg.h>
#include <math.h>

double deviation(int first, ...);

int main()
{
    /* Call with 3 integers (-1 is used as terminator). */
    printf("Deviation is: %f\n", deviation(2, 3, 4, -1 ));

    /* Call with 4 integers. */
    printf("Deviation is: %f\n", deviation(5, 7, 9, 11, -1));

    /* Call with just -1 terminator. */
    printf("Deviation is: %f\n", deviation(-1));
}

double deviation(int first, ...)
{
    int count = 0, i = first;
    double mean = 0.0, sum = 0.0;
    va_list marker;
    va_list copy;

    va_start(marker, first);
    va_copy(copy, marker);

    while(i != -1)
    {
        sum += i;
        count++;
        i = va_arg(marker, int);
    }

    va_end(marker);
    mean = sum ? (sum/count) : 0.0;

    i = first;
    sum = 0.0;
    while(i != -1)
    {
        sum += (i-mean)*(i-mean);
        i = va_arg(copy, int);
    }
    va_end(copy);
    return count ? sqrt(sum/count) : 0.0;
}
