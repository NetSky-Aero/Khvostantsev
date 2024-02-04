/*
D3 Практик 1
В обратном порядке
Дано целое неотрицательное число N. Выведите все его цифры по одной, в обратном порядке, разделяя их пробелами или новыми строками.
 */


#include <stdio.h>

int main(void)
{
    int n, numRevers = 0, num;
    printf("Введите целое число: ");
    scanf ("%d", &n);
    while(n!=0)
    {
        num = n%10;
        numRevers = numRevers * 10 + num;
        n/=10;
    }
    printf("Обратное число = %d\n", numRevers);
    return 0;
}

