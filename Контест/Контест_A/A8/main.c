/*����
� ������� ����� Geek Brains ���� ����������� �������� ���� (����������� ������ ����� 1 �����) � ���� ������� 1�, 3�, 9�, 27�, � �.�. �� ����� ����� ������ �����.
�������� �� ���������� ������ ���� ����� ���� � �� �����, ����� �� �������� ���-������ ������� � ���� �����, ������� ���� �������� �������� �� ���� (�� ����� �����).
���� ������ ���. ������ ������� ������: ������������ ����������� ����� � ����� ������������� ������ � ������� (�� ������ 1000000000).
������ �������� ������: ������������ ����� ����� � ����� ���������� ���� ��� ����� �1 ���� ������ ����� �������� ����������.

�������:
������� ������: 8 ��������� ������: 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count_weights(int weight)
{
    int total_weights = 0;
    long long max_mass = 0;
    long long power = 1;

    while (max_mass < 1000000000)
    {
        max_mass = max_mass * 3 + power;
        power *= 3;
    }

    if (weight > max_mass)
    {
        return -1;
    }

    while (weight > 0)
    {
        int remainder = weight % 3;

        if (remainder == 1)
        {
            total_weights++;
        } else if (remainder == 2)
        {
            total_weights++;
            weight += 1;
        }

        weight /= 3;
    }

    return total_weights;
}

int main()
{
    int weight;
    scanf("%d", &weight);
    if (weight <= 0 || weight > 1000000000)
    {
        printf("-1\n");
        return 0;
    }
    int result = count_weights(weight);
    printf("%d\n", result);

    return 0;
}
