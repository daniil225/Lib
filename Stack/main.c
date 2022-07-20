#include <stdio.h>
#include "Stack.h"

int main()
{

    TEMPLATE(Stack, double) stack;
    TEMPLATE(Init, double)(&stack);

    double a = 5.4;
    double b = 10.12;
    double g = 12.345;
    TEMPLATE(push, double)(&stack, a);
    TEMPLATE(push, double)(&stack, b);
    TEMPLATE(push, double)(&stack, g);

    printf("%.3lf\n", TEMPLATE(pop, double)(&stack));
    printf("%.2lf\n", TEMPLATE(pop, double)(&stack));
    printf("%.1lf\n", TEMPLATE(pop, double)(&stack));
    return 0;
}