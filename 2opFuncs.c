#include "lists.h"
/**
 * addOp - adds top two numbers on stack;
 * @stack: points to head of stack
 * @line_number: current line number of file
 * Return: void
 */
void addOp(stack_t **stack, unsigned int line_number)
{
stack_t *a, *b;
int i;
if (stack == NULL || *stack == NULL)
{
dprintf(STDERR_FILENO, "L%i: can't add, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
a = *stack;
b = a->next;
if (b == NULL)
{
dprintf(STDERR_FILENO, "L%i: can't add, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
i = a->n;
b->n += i;
popOp(stack, line_number);
}

/**
 * nopOp - does nothing
 * @stack: points to head of stack
 * @line_number: current line number of file
 * Return: void
 */
void nopOp(stack_t **stack, unsigned int line_number)
{
line_number++;
line_number--;
stack++;
}

/**
 * freeList - frees a stack
 * @head: points to head of stack
 * Return: void
 */
void freeList(stack_t *head)
{
stack_t *a = head;
while (a != NULL)
{
a = a->next;
free(head);
head = a;
}
}
