/*
F5 ДЗ 3
Максимум в массиве
Написать функцию и программу, демонстрирующую работу данной функции, которая находит максимальный элемент в массиве.
 */

#include <stdio.h>
#define NUM 5

int find_max_array(int size, int* a)
{
    int max = a[0];
    for (int i = 1; i < size; i++)
    {
        if (max < a[i])
        {
        max = a[i];
        }
    }
    return max;
}

int main(void) 
{
    int a[NUM];
    for (int i = 0; i < NUM; i++) 
    {
        printf("Введите %d целых чисел через пробел: ", NUM);
        for (int i = 0; i < NUM; i++)
        scanf("%d", &a[i]);
            break;
    }
    printf("Максимальный элемент в массиве: %d", find_max_array(NUM, a));
    return 0;
}
