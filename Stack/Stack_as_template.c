#ifdef T
#include <stdlib.h>
#include "stdio.h"
#include "Stack_as_template.h"
#include "template.h"




int TEMPLATE(Init, T)(TEMPLATE(Stack, T) *stack)
{
    int res = 0; // Status Ok
    stack->MAX_SIZE = SIZE;
    stack->size = 0;
    stack->element = malloc(SIZE*sizeof(T));
    if(stack->element == NULL)
        res = 1; // Status Error
    
    return res;
}



void TEMPLATE(push, T)(TEMPLATE(Stack, T) *stack, T elem)
{
    if(stack->size < stack->MAX_SIZE)
    {
        stack->element[stack->size] = elem; //  Костыльный вариант который сработает исключительно со структурами в которых содержится одно значение
        stack->size++;
    }
    else
    {
        stack->MAX_SIZE += SIZE;
        stack->element = realloc(stack->element, stack->MAX_SIZE);
        stack->element[stack->size] = elem;
        stack->size++;
    }
}

T TEMPLATE(pop, T)(TEMPLATE(Stack, T) *stack)
{
    stack->size--;
    T res = stack->element[stack->size];
    return res;
}

T TEMPLATE(peak, T)(TEMPLATE(Stack, T) *stack)
{
    int pos = stack->size - 1;
    T res = stack->element[pos];
    return res;
}



#endif