/*
G3 Практ 1
Последний номер символа
В файле .txt дана строка из 1000 символов. Показать номера символов, совпадающих с последним символом строки. Результат записать в файл .txt 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fptr;
    char arr[1000] = {0};
    int count = 0;
    
    if((fptr = fopen("input.txt", "w")) == NULL)
    {
        printf("Не удалось открыть файл!");
        exit (1);
    }
    printf("Введите aabbcdb: ");
    gets(arr);
    fprintf(fptr, "%s\n", arr);
    fclose(fptr);
    count = strlen(arr);
    for(int i = 0; i<count-1; i++)
    {
        if (arr[count-1] == arr[i])
            printf("%d ", i);
    }
    return 0;
}

