#ifndef MY_STRUCRT_H_
#define MY_STRUCRT_H_

#define SIZE 10

typedef struct
{
    char const *str;
    int length;

}String;


String Init();

void SetString(String *string,char const *str);

static int Length(String const *string) { return string->length; }

void Add(String *string, char const *str);

static void PrintString(String const *string) { printf("%s\n", (char*)string->str); }

#endif