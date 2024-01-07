#include <stdio.h>

int main(void)
{
    int a,b,c;
    float x;
    printf("Три целых целых числа через пробел:\n");
    scanf("%d%d%d", &a, &b, &c);
    x = (a + b + c)/3.;
    printf("%.2f\n", x);
    return 0;
}

