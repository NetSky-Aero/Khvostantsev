/*
F2 ДЗ 2
Четные в начало
Написать функцию и программу, демонстрирующую работу данной функции, которая ставит в начало массива все четные элементы, а в конец – все нечетные. Не нарушайте порядок следования чисел между собой. Строго согласно прототипу:
void sort_even_odd(int n, int a[])

 */

#include <stdio.h>
#define N 20 //или иное кол-во чисел, например 5

void input(int a[])
{
    for(int i = 0; i < N; i++)
    {
        printf("%d. Введи целое число и нажми Enter: ", i+1);
        scanf("%d", &a[i]);
    }
}
void Print(int a[])
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ",a[i]);
    }
}
void sort_even_odd(int n, int a[])
{
int i = 0;
int j = 0;
int temp = 0;    
    for(i = 0; i<n; i++)
    {
        for(j = n-1; j > i; j--)
        {
            if (a[j-1]%2 > a[j]%2)
            {
                temp = a[j-1];
                a[j-1] = a[j];
                a[j] = temp;
            }
        }
    }
}
int main(void)
{
    int a[N] = {0};
    input(a);
    sort_even_odd(N, a);
    printf("\n");
    printf("Результат: ");
    Print(a);
    return 0;
}
