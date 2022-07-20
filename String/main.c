#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>


typedef struct 
{
    int const a;
    int const b;
} counter_s;


bool check_name(char const **in)
{
    char str1[] = "Iggy";
    char str2[] = "Pop";
    in[0] = "";
    in[1] = str2;
    return (!strcasecmp(in[0], "Iggy") &&  !strcasecmp(in[1], "Pop"));
}


int main(int argc, char **argv)
{

   // if(argc < 2) return 0;
    //return check_name((char const**)&argv[1]);

    counter_s cc;

    int *v;
    int const **exp = &v;
    *exp = &cc.a;
    *v = 10;


    
    printf("cc.a = %d\n", cc.a);


    int *var;
    int const **constexper = &var;
    int const fixed = 20;
    *constexper = &fixed;
    *var = 30;

    printf("x=%i y=%i\n", fixed, *var);
    return 0;
}