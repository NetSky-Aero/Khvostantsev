/*Поиск последовательности бит
На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31). Требуется взять K подряд идущих битов числа N так, чтобы полученное число было максимальным. Программа должна вывести полученное число.
Примеры
Входные данные
2 1
Результат работы
1
Входные данные
12 3
Результат работы
6
Входные данные
3 5
Результат работы
3
Входные данные
1024 3
Результат работы
4
*/

#include <stdio.h>

unsigned int find_max_subsequence(unsigned int N, int K)
{
    unsigned int max = 0, mask = (1u << K) - 1;
    for (int i = 0; i <= 32 - K; ++i) {
        unsigned int subseq = (N >> i) & mask;
        max = subseq > max ? subseq : max;
    }
    return max;
}

int main(void)
{
    unsigned int N, K;
    scanf("%u %u", &N, &K);
    printf("%u\n", find_max_subsequence(N, K));
    return 0;
}
