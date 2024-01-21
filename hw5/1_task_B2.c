/*
B2 Урок 4 Практика 1
Квадраты чисел
Ввести два целых числа a и b (a ≤ b) и вывести квадраты всех чисел от a до b. 
*/
#include <stdio.h>

int main(void)
{
    int a, b;
    scanf("%d%d", &a, &b);
    if (a <= b)
    { 
    for (int i = a; i <= b; i++)
        {
            printf("Отлично: %d\n", i*i); 
        }
        return 0;
    }
    printf("Не верно!\nДолжно быть: a<=b");
    return 0;
}
