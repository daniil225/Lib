#define __GNU__SOURCE  // что бы stdio.h включил asprintf
#include <stdio.h>
#include <stdlib.h>

void get_string(char const *in)
{
    char *cmd;
    asprintf(&cmd, "%s", in);
    printf("%s\n", cmd);
    //if(system(cmd)) fprintf(stderr, "Error\n");
    free(cmd);
}

int main(int argc, char **argv)
{

    get_string(argv[1]);

}