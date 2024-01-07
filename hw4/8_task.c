#include <stdio.h>

int main(void)
{
    int a, b, c, d, f, min;
    printf("Введите пять чисел: ");
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &f);
    if (a <= b && a <= c && a <= d && a <= f)
        min = a;
    else if (b <= a && b <= c && b <= d && b <= f)
        min = b;
    else if (c <= a && c <= b && c <= d && c <= f)
        min = c;
    else if (d <= a && d <= b && d <= c && d <= f)
        min = d;
    else
        min = f;
    printf("Min = %d\n", min);
    return 0;
}

