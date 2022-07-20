/* 
Пишем аналог функции asprintf()
Воспользуемся следующей идеей:
vsnprintf - возвращает количество символов, которое было бы записано, если бы n было достаточно велико
БЕЗ УЧЕТА завершающего НУЛЯ, или отрицательное значение если ошибка кодировки

Функция snprintf() тоже возвращает значение, которое было бы...

Таким образом если выполнить пробный вызов vsnprintf, передав ей однобайтовую строку, то в ответ мы узнаем, сколько 
места нужно для новой строки. После этого мы выделяем память и вызываем vsnprintf по настоящему.

Функция работает дважды, что приводит к удвоению времени, но ради безопасности и удобства на это можно пойти.

 */

#ifndef HAVE_ASPRINTF
#define HAVE_ASPRINTF
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_start et al
#include <math.h>

/* Объявление нужно перенести в h-файл. Спецификатор __attribute__ сообщает компилятору, что нужно
проверять совместимость 2-х типов в духе printf. Это 
расширение стандарта С, но большинство компиляторов его поддерживает
 */
int _asprintf(char **str, char *fmt, ...) __attribute__((format (printf,2,3)));

int _asprintf(char **str, char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    char one_char[1];
    int len = vsnprintf(one_char, 1, fmt, argp);

    if(len < 1) {
        fprintf(stderr, "Ошибка кодировки. Входной указатель сброшен в NULL.\n");
        *str = NULL;
        return len;
    }
    va_end(argp);

    *str = malloc(len + 1);
    if(!str)
    {
        fprintf(stderr, "Не удалось выделить %i байтов\n", len+1);
        return -1;
    }
    va_start(argp, fmt);
    vsnprintf(*str, len+1, fmt, argp);
    va_end(argp);
    return len;
}

#endif


#define Init_list(name, ...) \
    double *name##_list;\
    int name##_len;\
    do \
    { \
    name##_list = (double[]){__VA_ARGS__, NAN};\
    for(name##_len = 0; !isnan(name##_list[name##_len]); name##_len++);\
    }while(0)


#include <string.h>
#define BUFFCOUNT 10
void FormatOutput(char * formatstring, ...)
{
    int nSize = 0;
    char buffer[BUFFCOUNT];
    memset(buffer, 0, sizeof(buffer));
    va_list args;
    va_start(args, formatstring);
    nSize = vsnprintf(buffer, sizeof(buffer), formatstring, args);
    printf("nSize = %d, buffer = %s\n", nSize, buffer);
    va_end(args);
}



#define Test_asprintf
#ifdef Test_asprintf
int main()
{


    FormatOutput("%s %s", "Hi", "there");
    Init_list(array, 2,3,4,5,6,7);

    #define Length(name) name##_len
    for(int i = 0; i < Length(array); i++)
    {
        printf("%.1lf ", array_list[i]);
    }

    printf("\n");
    char *s;
    _asprintf(&s, "hello, %s %s.", "--Reader--", " Daniil");
    printf("%s\n", s);

    _asprintf(&s, "%c", '\0');
    printf("пустая строка: [%s]\n", s);

    int i = 0;
    _asprintf(&s, "%i", i++);
    printf("Нуль: %s\n", s);
}


#endif