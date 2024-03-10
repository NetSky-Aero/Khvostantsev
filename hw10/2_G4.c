/*
G4 ДЗ 1
По одному разу
В файле .txt даны два слова не более 100 символов каждое, разделенные одним пробелом. Найдите только те символы слов, которые встречаются в обоих словах только один раз. Напечатайте их через пробел в файл .txt в лексикографическом порядке.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

int main()
{
    FILE *myfile;
    char arr[N] = {0};
    char arr1[N] = {0};
    char arr2[N] = {0};
    if((myfile = fopen("input.txt", "w")) == NULL)
    {
        printf("Ошибка!");
        exit (1);
    }
    printf("Введите два слова: ");
    gets(arr);
    fprintf(myfile, "%s", arr);
    fclose(myfile);
    if((myfile = fopen("input.txt", "r")) == NULL)
    {
        fscanf(myfile, "%s %s", arr1, arr2);
        fclose(myfile);
    }
    for(int i = 0; i < strlen(arr1); i++)
    {
        for(int j = 0; j < strlen(arr2); j++)
        {
            if (arr1[i] == arr2[j])
            {
                if (arr1[i] != arr1[i+1] && arr1[i] != arr1[i-1])
                    printf("%c ", i);
            }
        }
    }
    return 0;
}

