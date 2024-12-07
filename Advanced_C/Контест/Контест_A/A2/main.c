/* Циклический сдвиг
На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31).
Требуется циклически сдвинуть битычисла N вправо на K битов и вывести полученное таким образом число.

Примеры:
Входные данные: 2 1 Результат работы: 1
Входные данные: 1 2 Результат работы: 1073741824
Входные данные: 3 1 Результат работы: 2147483649
Входные данные: 12 2 Результат работы: 3
Входные данные: 19 3 Результат работы: 1610612738
*/

#include <stdio.h>

unsigned int cyclic_right_shift(unsigned int N, int K)
{
    unsigned int mask = (1u << K) - 1;
    unsigned int shifted = N >> K;
    unsigned int moved = (N & mask) << (32 - K);
    return shifted | moved;
}

int main()
{
    unsigned int N, K;
    scanf("%u %u", &N, &K);
    printf("%u\n", cyclic_right_shift(N, K));
    return 0;
}
