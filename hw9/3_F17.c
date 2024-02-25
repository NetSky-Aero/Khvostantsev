/*
F17 
След матрицы 
Написать функцию и программу, демонстрирующую работу данной функции, которая находит след матрицы в двумерном массиве. Показать пример ее работы на матрице из 5 на 5 элементов. След матрицы - это сумма элементов на главной диагонали. 
 */

#include <stdio.h>

void input(int a, int b, int arr[a][b])
{
    int i, j;
    for (i = 0; i < a; i++)
        for (j = 0; j < b; j++)
            scanf("%d", &arr[i][j]);
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
                 res += arr[i][j];
        }
    }
    return res;
}

int main(void)
{
    int arr[5][5] = {0};
    printf("Требуется ввести по 5 чисел через пробел в 5 строк (матрица): \n");
    printf("\n");
    input(5, 5, arr);
    printf("\nСумма элементов по главной диагонали: %d\n", array(5, 5, arr));
    return 0;
}

