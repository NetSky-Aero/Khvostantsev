/*
G8 ДЗ 3
Числа в массив
В файле .txt дана строка, не более 1000 символов, содержащая буквы, целые числа и иные символы. Требуется все числа, которые встречаются в строке, поместить в отдельный целочисленный массив. Например, если дана строка "data 48 call 9 read13 blank0a", то в массиве числа 48, 9, 13 и 0. Вывести массив по возрастанию в файл .txt.  
 */


#include <stdio.h>
#define N 1000

int data_input (FILE *f, int size, char arr[])
{
    int i;
    for (i = 0; i < size; i++)
    {
        fprintf (f, "%c", arr[i]);
    }
    return i;
}

int data_reading(FILE *f, int size, char arr[])
{
    int i;
    for (i = 0; i < size; i++)
    {
        fscanf (f, "%c", &arr[i]);
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

void sort (int size, int arr[])
{
    int value;
    do
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[j] > arr[j+1])
            {
                value = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = value;
            }
        }
        size--;
    } while (size >= 0);
}

void num (int size, char arr[])
{
    int array[size];
    int value = 0, j = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] >= '0' && arr[i] <= '9')
        {
            value = value*10 + arr[i] - '0';
            if (arr[i+1] <= '0' || arr[i+1] >= '9')
            {
                array[j] = value;
                j++;
                value = 0;
            }
        }
    }
    sort(j-1, array);
    for (int i = 0; i < j; i++)
    {
        printf("%d ", array[i]);
    }
}

int main (void)
{
    FILE *myfile;
    char arr[N], *b;
    int c;
    b = arr;
    printf("Введите буквы и цифры: ");
    c = input_arr(b);
    myfile = fopen("myfile.txt", "w");
    data_input(myfile, c, b);
    fclose(myfile);
    myfile = fopen("myfile.txt", "r");
    data_reading(myfile, c, b);
    fclose(myfile);
    printf("Данные на выходе: ");
    num(c, b);
    return 0;
}

