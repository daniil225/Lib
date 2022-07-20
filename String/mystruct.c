#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mystruct.h"




String Init()
{
    String string = { .str = malloc(SIZE),
                        .length = 0
                      };
    
    return string;
}


void SetString(String *string,char const *str)
{
    int length = strlen(str);
    free((void*)string->str);
    string->str = str;
    string->length = length;
}

void Add(String *string, char const *str)
{
    int length_str = strlen(str);
    char *res = malloc(length_str+string->length);
    memcpy(res, string->str, string->length);
    
    for(int i = string->length, j = 0; i < string->length+length_str; i++, j++)
        res[i] = str[j];
    
    string->length += length_str;

    string->str = res;
    free(res);
}



int main()
{

    String string = Init();
    

    SetString(&string, "Hello ");
    Add(&string, "World");

    Add(&string, "\nAnton shout crowing!!!");
 

    PrintString(&string);
    

  

    return 0;
}