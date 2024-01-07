#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Ввести трехзначное число: ");
    int a, max = 0;
    scanf("%d", &a);
    while (a) 
    {
        int buf = a % 10;
        if (buf > max) max = buf;
        a /= 10;
    } 
    printf("Максимальная цифра: %d\n", max);
    return 0;
}

