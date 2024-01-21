/*
B8
Ровно одна цифра 9
Ввести целое число и определить, верно ли, что в нём ровно одна цифра «9».
*/

#include <stdio.h>

int main(void)
{
    int a, b;
    printf("Введите целое число: ");
    scanf("%d", &a);
    while(a)
    {
       b += (a%10) == 9;
       a = a/10;
    }
    b == 1 ? printf("Yes") : printf("No");
    return 0;
}

