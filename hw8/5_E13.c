/*
E13 ДЗ 5
Вторая с конца ноль 
Считать массив из 10 элементов и отобрать в другой массив все числа, у которых вторая с конца цифра (число десятков) – ноль. 
 */

#include <stdio.h>

enum {SIZE=10};
void Input(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        scanf ("%d", &arr[i]);
    }
}
void Sort(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        if((arr[i]/10)%10 == 0)
        {
            printf("%d ", arr[i]);
        }
    }
}
int main(void)
{
    int arr[SIZE];
    printf("Введи 10 целых чисел: ");
    Input(arr, SIZE);
    printf("Результат: ");
    Sort(arr, SIZE);
    return 0;
}
