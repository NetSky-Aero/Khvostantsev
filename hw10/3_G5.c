/*
G5 ДЗ 2
Заменить a на b
В файле .txt дана символьная строка не более 1000 символов. Необходимо заменить все буквы "а" на буквы "b" и наоборот, как заглавные, так и строчные. Результат записать в .txt. 
 */


#include <stdio.h>
#define N 100

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

int input_arr(char arr[])
{
    int i = 0;
    char a;
    while ((a = getchar()) != '\n')
    {
        arr[i] = a;
        i++;
    }
    return i;
}

char data_change (char arr)
{
    if (arr == 'a')
        return 'b';
    else if (arr == 'b')
        return 'a';
    else if (arr == 'A')
        return 'B';
    else if (arr == 'B')
        return 'A';
    else
        return 0;
}

void data_reverse (int size, char arr[])
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == 'a' || arr[i] == 'b' || arr[i] == 'A' || arr[i] == 'B')
        {
            arr[i] = data_change(arr[i]);
        }
    }
    for (int i = 0; i < size; i++)
    {
        printf("%c", arr[i]);
    }
}

int main (void)
{
    FILE *myfile;
    char arr[N], *b;
    int c;
    b = arr;
    printf("Введите буквы в разных регистрах: ");
    c = input_arr(b);
    myfile = fopen("myfile.txt", "w");
    data_input(myfile, c, b);
    fclose(myfile);
    myfile = fopen("myfile.txt", "r");
    data_reading(myfile, c, b);
    fclose(myfile);
    printf("Результат: ");
    data_reverse(c, b);
    if((myfile = fopen("myfile_res.txt", "w")) == NULL);
    data_input(myfile, c, b);
    fclose(myfile);
    return 0;
}
