/* ����������� �������
���������� ����������� ���������, ������� �� ����� ��������� ������������ ����� � ���� float, ��� ���������� ������� ������� �������� � ���� EXP � ���� ����������� ������ �����.
������� ������ ������ ��������������� ��������� int extractExp(float)

�������:
������� ������: 1.0 ��������� ������: 127
������� ������: 2.0 ��������� ������: 128
������� ������: 3.99999 ��������� ������: 128
������� ������: 0.001 ��������� ������: 117
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
