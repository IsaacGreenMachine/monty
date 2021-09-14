#include "monty.h"
void pushOp(stack_t **stack, unsigned int line_number)
{
stack_t *node, *new = malloc(sizeof(stack_t));
//if (new == NULL)
//return (NULL);

printf("BOO\n");
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
new->n = atoi(currentInstruction[1]);
*stack = new;
//return (*head);
}

void pallOp(stack_t **stack, unsigned int line_number)
{
int i;
stack_t *h = *stack;
for (i = 0; h != NULL; i++, h = h->next)
printf("%i\n", h->n);
//return (i);
}
