/* ������������ ����
������� ��������� ������ typedef struct list { uint64_t address; size_t size; char comment[64]; struct list *next; } list;
��������� ����������� ������ ���� �������, ������� � ������ ������ ������� ����� ����� ������ ���������� ������ ����� �����.
����� �������� � ���� address, ���� size - ��������������� ������ ������� �����. ���� ������ ������, �� ������� ������ ���������� NULL.
���� ���� ��������� ����� ������, �� ������� ����� ������ �� ���. �������� �������: uint64_t findMaxBlock(list *head)

�������:
������� ������:
3
	  140525067852320 10
	  140525067852350 30
	  140525067852900 100
��������� ������: 140525067852900
*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>

typedef struct list
{
    uint64_t address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

uint64_t findMaxBlock(list *head);

uint64_t findMaxBlock(list *head)
{
    if (head == NULL)
    {
        return 0;
    }

    list *current = head;
    uint64_t maxAddress = current->address;
    size_t maxSize = current->size;

    while (current != NULL)
    {
        if (current->size > maxSize)
        {
            maxSize = current->size;
            maxAddress = current->address;
        }
        current = current->next;
    }

    return maxAddress;
}

int main()
{
    list node3 = {140525067852900, 100, "Block 3", NULL};
    list node2 = {140525067852350, 30, "Block 2", &node3};
    list node1 = {140525067852320, 10, "Block 1", &node2};

    uint64_t maxAddress = findMaxBlock(&node1);

    printf("%" PRIu64 "\n", maxAddress);

    return 0;
}
