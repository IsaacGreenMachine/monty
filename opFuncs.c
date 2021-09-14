#include "monty.h"
/**
 * pushOp - push function for stack
 * @stack: points to head of stack
 * @line_number: current line number of file
 * Return: void
 */
void pushOp(stack_t **stack, unsigned int line_number)
{
stack_t *node, *new = malloc(sizeof(stack_t));
/*if (new == NULL)*/
/*return (NULL);*/

if (stack == NULL)
node = NULL;
else
node = *stack;

if (node == NULL)
{
new->next = NULL;
}
else
{
new->next = *stack;
node->prev = new;
}
new->prev = NULL;
new->n =  atoi(currentInstruction[1]);
*stack = new;
line_number++;
line_number--;
/*return (*head);*/
}

/**
 * pallOp - prints stack
 * @stack: points to head of stack
 * @line_number: current line number of file
 * Return: void
 */
void pallOp(stack_t **stack, unsigned int line_number)
{
int i;
stack_t *h = *stack;
for (i = 0; h != NULL; i++, h = h->next)
printf("%i\n", h->n);
line_number++;
line_number--;
/*return (i);*/
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
