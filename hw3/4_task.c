#include <stdio.h>

int main(void)
{
    int a,b,c;
    float x;
    printf("Три целых целых числа через пробел:\n");
    scanf("%d%d%d", &a, &b, &c);
    x = (a + b + c)/3;
    printf("%.2f\n", x); // можно было по варианту printf ("%d+%d+%d=%d", a, b, с, a+b+с ), но захотел сделать так
    return 0;
}

