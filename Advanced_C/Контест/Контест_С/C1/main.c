/* ������� � ������
�� ����������� ������ ����� �������� ��� ���������� ������, ���������� �������� �������� ������. ������ �� ����� �� ��������� ������� 104.
� ������� �� ����������� ���������� �������. �� ����������� ����� ������ ����������� ��� �����,
���������� ��������: ������ ����� � ����� ����������� �������� ������������, ����������� ��������� ������;
������ ����� � ��������, ����� ����������� �������� ������ ������, ����������� ���������������.
��������� �������� ��������� � ������ �������� (�.�. ������� 'a' � 'A' ��������).

�������:
������� ������:
don't_panic
nick_is_a_mastodon
��������� ������: 3 3
������� ������:
monty_python
python_has_list_comprehensions
��������� ������: 0 6
*/

#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[10005], str2[10005];

    fgets(str1, sizeof(str1), stdin);
    fgets(str2, sizeof(str2), stdin);
    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int prefix_suffix = 0;
    for (int i = 1; i <= len1 && i <= len2; i++)
    {
        if (strncmp(str1, str2 + len2 - i, i) == 0)
        {
            prefix_suffix = i;
        }
    }
    int suffix_prefix = 0;
    for (int i = 1; i <= len1 && i <= len2; i++)
    {
        if (strncmp(str1 + len1 - i, str2, i) == 0)
        {
            suffix_prefix = i;
        }
    }

    printf("%d %d\n", prefix_suffix, suffix_prefix);

    return 0;
}
