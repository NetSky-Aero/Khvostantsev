/* Распаковать порядок
Необходимо реализовать программу, которой на входе передаётся вещественное число в типе float, она возвращает порядок который хранится в поле EXP в виде десятичного целого числа.
Функция должна строго соответствовать прототипу int extractExp(float)

Примеры:
Входные данные: 1.0 Результат работы: 127
Входные данные: 2.0 Результат работы: 128
Входные данные: 3.99999 Результат работы: 128
Входные данные: 0.001 Результат работы: 117
*/
#include <stdio.h>
#include <stdint.h>

int extractExp(float number)
{
    union
    {
        float f;
        uint32_t u;
    }
    converter;
    converter.f = number;
    uint32_t bits = converter.u;
    int exp = (bits >> 23) & 0xFF;
    return exp;
}

int main(void)
{
    float number;
    scanf("%f", &number);
    printf("%d\n", extractExp(number));
    return 0;
}
