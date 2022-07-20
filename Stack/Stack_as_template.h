#ifdef T
#include "template.h"

#define SIZE 10

typedef struct
{
    T *element;
    int size;
    int MAX_SIZE;
}TEMPLATE(Stack, T);


int TEMPLATE(Init, T)(TEMPLATE(Stack, T) *stack);

void TEMPLATE(push, T)(TEMPLATE(Stack, T) *stack, T elem);

T TEMPLATE(pop, T)(TEMPLATE(Stack, T) *stack);

T TEMPLATE(peak, T)(TEMPLATE(Stack, T) *stack);

#endif