/*
G9 ДЗ 4
Удалить повторяющиеся символы
В файле .txt строка из меленьких и больших английских букв, знаков препинания и пробелов. Требуется удалить из нее повторяющиеся символы и все пробелы. Результат записать в файл .txt. 
 */


#include <stdio.h>
#define N 1000

int data_input (FILE *myfile, int size, char arr[])
{
    int i;
    for (i = 0; i < size; i++)
    {
        fprintf (myfile, "%c", arr[i]);
    }
    return i;
}

int data_reading (FILE *myfile, int size, char arr[])
{
    int i;
    for (i = 0; i < size; i++)
    {
        fscanf (myfile, "%c", &arr[i]);
    }
    return i;
}

int input_arr (char arr[])
{
    int i = 0;
    char c;
    while ((c = getchar()) != '\n')
    {
        arr[i] = c;
        i++;
    }
    return i;
}

void clear(int size, char arr[])
{
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] != ' ')
        {
            arr[j++] = arr[i];
        }
    }
    arr[j] = '\0';
}

void duplicat (int size, char arr[])
{
    int duplicat = 1;
    for (int i = 1; i < size; i++) 
    {
        int j;
        for (j = 0; j < duplicat; j++)
        {
            if (arr[i] == arr[j])
            {
                break;
            }
        }
        if (j == duplicat)
        {
            arr[duplicat] = arr[i];
            duplicat++;
        }
    }
    arr[duplicat] = '\0';
    for (int i = 0; i < duplicat; i++)
    {
        printf("%c", arr[i]);
    }
}

int main (void)
{
    FILE *myfile;
    char arr[N];
    int c;
    char *b = arr;
    printf("Введите буквы и символы: ");
    c = input_arr(b);
    myfile = fopen("myfile.txt", "w");
    data_input(myfile, c, b);
    fclose(myfile);
    myfile = fopen("myfile.txt", "r");
    data_reading(myfile, c, b);
    fclose(myfile);
    printf("Результат: ");
    clear(c, b);
    duplicat(c, b);
    if((myfile = fopen("myfile_res.txt", "w")) == NULL);
    data_input(myfile, c, b);
    fclose(myfile);
    return 0;
}

