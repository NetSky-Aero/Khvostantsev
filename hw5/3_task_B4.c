/*
B4 Урок 5 ДЗ 2
Ровно три цифры
Ввести целое число и определить, верно ли, что в нём ровно 3 цифры.
 */

#include <stdio.h>

int main(void) 
{
    int a, b;
    printf("Введи целое число: ");
    scanf("%d", &a);
    for(; a != 0; b++, a = a / 10);
    b == 3 ? printf("YES") : printf("NO");
    return 0;
}

