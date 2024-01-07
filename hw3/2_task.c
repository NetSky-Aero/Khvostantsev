#include <stdio.h>

int main(void)
{
    int a,b,c,x,y;
    printf("Три целых числа через пробел:\n");
    scanf ("%d%d%d", &a, &b, &c);
    x = a+b+c;
    y = a*b*c;
    printf("%d\n %d", x, y);
    return 0;
}

