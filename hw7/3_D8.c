/*
D8 ДЗ 2
От A до B
Составить рекурсивную функцию, Выведите все числа от A до B включительно, в порядке возрастания, если A < B, или в порядке убывания в противном случае.
 */


#include <stdio.h>

void number(int a, int b)
{
    printf("%d ", a);
    if (a > b)
        number(a - 1, b);
    if (a < b)  
        number(a + 1, b);
}

int main(void)
{
    int a, b;
    printf("Введите первое число: ");
    scanf("%d", &a);
    printf("Введите второе число: ");
    scanf("%d", &b);
    number(a, b);
    return 0;
}

