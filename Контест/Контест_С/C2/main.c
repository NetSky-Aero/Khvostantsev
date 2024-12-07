/* Польская запись
Необходимо вычислить выражение написанное в обратной польской записи.
На вход подается строка состоящая из целых, неотрицательных чисел и арифметических символов.
В ответ единственное целое число - результат.

Примеры:
Входные данные: 3 4 +.
Результат работы: 7
Входные данные: 1 2 + 4 × 3 +.
Результат работы: 15
Входные данные: 100 25 + 25 /.
Результат работы: 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

typedef struct
{
    int data[MAX_STACK_SIZE];
    int top;
}
Stack;

void initStack(Stack* s)
{
    s->top = -1;
}

int isEmpty(Stack* s)
{
    return s->top == -1;
}

int pop(Stack* s)
{
    if (!isEmpty(s))
    {
        return s->data[s->top--];
    }
    return -1;
}

void push(Stack* s, int value)
{
    if (s->top < MAX_STACK_SIZE - 1)
    {
        s->data[++s->top] = value;
    }
}

int applyOperator(int a, int b, char operator)
{
    switch (operator)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

int evaluateRPN(const char* expression)
{
    Stack stack;
    initStack(&stack);
    char exprCopy[100];
    strcpy(exprCopy, expression);
    const char* token = strtok(exprCopy, " ");
    while (token != NULL)
    {
        if (isdigit(token[0]))
        {
            push(&stack, atoi(token));
        }
        else
        {
            int b = pop(&stack);
            int a = pop(&stack);
            int result = applyOperator(a, b, token[0]);
            push(&stack, result);
        }
        token = strtok(NULL, " ");
    }
    return pop(&stack);
}

int main(void)
{
    char expression[100];

    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = 0;
    int result = evaluateRPN(expression);
    printf("%d\n", result);

    return 0;
}
