#include <stdio.h>

int main(int argc, char **argv)
{
    int a, b, c, d, f, max;
    printf("Введите пять чисел: ");
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &f);
    if (a >= b && a >= c && a >= d && a >= f)
        max = a;
    else if (b >= a && b >= c && b >= d && b >= f)
        max = b;
    else if (c >= a && c >= b && c >= d && c >= f)
        max = c;
    else if (d >= a && d >= b && d >= c && d >= f)
        max = d;
    else
        max = f;
    printf("Max = %d\n", max);
    return 0;
}

