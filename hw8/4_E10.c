/*
E10 ДЗ 3
Циклический сдвиг массива вправо на 4
Считать массив из 12 элементов и выполнить циклический сдвиг ВПРАВО на 4 элемента. 
 */

#include <stdio.h>
#define SIZE 12

void Input(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d. Введи целое число и нажми Enter: ", i+1);
        scanf("%d", &arr[i]);
    }
}
void Print(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void Shift(int arr[], int size, int shift)
{
    for (int j = 0; j < shift; j++ )
    {
        int temp = arr[size-1];
        for (int i = size - 1; i > 0; i--)
        {
            arr[i] = arr[i -1];
        }
        arr[0] = temp;
    }
}
int main(void)
{
    int arr[SIZE];
    Input(arr, SIZE);
    Shift(arr, SIZE, 4);
    printf("\n");
    printf("Результат: ");
    Print(arr, SIZE);
    return 0;
}
