#include "monty.h"
char **currentInstruction;
int main ()
{
currentInstruction[1] = "3";
stack_t *head = NULL;
int lineNumber = 5;
pushOp(&head, lineNumber);
pallOp(&head, lineNumber);
}
