/*
F6 ДЗ 4
Два одинаковых
Написать функцию и программу, демонстрирующую работу данной функции, которая определяет, верно ли, что среди элементов массива есть два одинаковых. Если ответ «да», функция возвращает 1; если ответ «нет», то 0. Строго согласно прототипу:
int is_two_same(int size, int a[]);
 */


#include <stdio.h>
#include <stdbool.h>
#define N 100 
void input(int size, int arr[])
{
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);
}

int is_two_same(int size, int a[])
{
    for (int i=0; i < size; i++)
        for (int j=i+1; j < size-1; j++)
        {
            if (a[i] == a[j])
            {
                return true;
            }
        }
    return false;
}

int main(void)
{
    int arr[N] = {0};
    int size = 0;
    printf("Задайте размер массива одним числом и нажмите Enter: ");
    scanf("%d", &size);
    printf("Введите массив целых чисел через пробел и нажмите Enter: ");
    input(size, arr);
    printf("Результат: %s", is_two_same(size, arr) == true ? "YES":"NO");
    return 0;
}

