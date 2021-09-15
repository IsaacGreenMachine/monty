#ifndef HOLBERTON_H
#define HOLBERTON_H
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
int n;
struct stack_s *prev;
struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
char *opcode;
void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern char **currentInstruction;
void getLinez(char *fileName);
void setExternToInstruction(char *line, int lineNum, instruction_t funcList[]);
void pushOp(stack_t **stack, unsigned int line_number);
void pallOp(stack_t **stack, unsigned int line_number);
void pintOp(stack_t **stack, unsigned int line_number);
void popOp(stack_t **stack, unsigned int line_number);
void swapOp(stack_t **stack, unsigned int line_number);
void addOp(stack_t **stack, unsigned int line_number);
void nopOp(stack_t **stack, unsigned int line_number);
int checkWord(char *word, instruction_t funcList[]);
void goOp(char *opName, instruction_t funcList[], int lineNum, stack_t **head);
void freeList(stack_t *head);
#endif
