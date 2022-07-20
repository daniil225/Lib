#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int  SIZE = 10;
    int length = 0;

    int *a = malloc(sizeof(int)*SIZE);
    int *b = malloc(sizeof(int)*SIZE);

    for(int i = 0; i < 10; i++)
    {
        a[i] = i;
    }

      for(int i = 0; i < 10; i++)
    {
        b[i] = i*i+100;
    }

      for(int i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");

    for(int i = -12, j = 0; i < -2, j < 10; i++, j++)
    {
        if(&a[j] == &b[i]) printf("1 ");
        else printf("0 ");
    }


}