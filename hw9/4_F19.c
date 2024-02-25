/*
F19 ДЗ 6 
Больше среднего
Написать функцию и программу, демонстрирующую работу данной функции.
Определить количество положительных элементов квадратной матрицы, превышающих по величине среднее арифметическое всех элементов главной диагонали. Реализовать функцию среднее арифметическое главной диагонали. 
 */


#include <stdio.h>
#define N 5

void input(int a, int b, int arr[a][b])
{
    int i, j;
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
}

int array(int a, int b, int arr[a][b])
{
    int res = 0;
    int i, j;
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            if (i == j)
            {
                res += arr[i][j];
            }
        }
    }
    return res;
}

void max(int a, int b, int arr[a][b])
{
    int sum_res = 0, max_res = 0, j = 0;
    for (int i = 0; i < a; i++)
    {
        sum_res += arr[i][j];
        j++;
        if (i == a - 1)
        {
            sum_res /= a;
        }
    }
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (arr[i][j] > sum_res)
            {
                max_res++;
            }
        }
    }
    printf("\nСреднее арифметическое положительных элементов главной диагонали: %d", max_res);
}

int main(void)
{
    int arr[N][N] = {0};
    printf("Введите 5 строк по 5 целых чисел через пробел: ");
    input(N, N, arr);
    max(N, N, arr);
    return 0;
}

