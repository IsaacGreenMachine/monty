#include "monty.h"
char **curIns;

/**
 * getLinez - get lines from file and parse them
 * @fileName: name of file
 * Return: void
 */
void getLinez(char *fileName)
{
int charCount = 0, lineNum = 0;
size_t bufSize = 0;
char *buf = NULL;
FILE *file;
instruction_t funcList[] = {
{"push", pushOp}, {"pall", pallOp}, {"pop", popOp},
{"swap", swapOp}, {"add", addOp}, {"nop", nopOp}, {"pint", pintOp}
};
stack_t *head = NULL;

file = fopen(fileName, "r");
if (file == NULL)
{
dprintf(STDERR_FILENO, "Error: Can't open file %s\n", fileName);
exitFunc(&head, buf, file);
exit(EXIT_FAILURE);
}
while (charCount != -1)
{
charCount = getline(&buf, &bufSize, file);
/*printf("currentLine: %s\n", buf);*/
lineNum++;
if (charCount == -1)
break;
setGlobalVarArray(buf, lineNum, &head, file);
/*printf("L%i%s\n", lineNum, buf);*/
/*printf("currentInstruction[0]: %s\n", currentInstruction[0]);*/
/*printf("currentInstruction[1]: %s\n", currentInstruction[1]);*/
rnOp(funcList, lineNum, &head, buf, file);
if (curIns[0] != NULL)
free(curIns[0]);
if (curIns[1] != NULL)
free(curIns[1]);
if (curIns != NULL)
free(curIns);
}
freeList(head);
free(buf);
fclose(file);
}
/**
 * setGlobalVarArray - sets extern var [0] and [1] to correct value
 * @line: line from file
 * @lineNum: line Number
 * @head: head of stack
 * @file: file currently open
 * Return: void
 */
void setGlobalVarArray(char *line, int lineNum, stack_t **head, FILE *file)
{
char *word;
curIns = malloc(sizeof(char *) * 3);
if (curIns == NULL)
{
dprintf(STDERR_FILENO, "Error: malloc failed\n");
exitFunc(head, line, file);
exit(EXIT_FAILURE);
}
word = strtok(line, "\n\t ");
if (word == NULL)
{
curIns[0] = NULL;
curIns[1] = NULL;
}
else /*word is not NULL*/
{
curIns[0] = strdup(word);
if (strcmp(word, "push") == 0)
{
word = strtok(NULL, "\n\t ");
if (word == NULL || checkForChars(word) == -1)
{
dprintf(STDERR_FILENO, "L%i: usage: push integer\n", lineNum);
exitFunc(head, line, file);
exit(EXIT_FAILURE);
}
else
{
curIns[1] = strdup(word);
}
}
else
curIns[1] = NULL;
}
}

/**
 * rnOp - runs an monty operation
 * @fL: list of possible instructions
 * @buf: line from file
 * @lNum: line Number
 * @head: head of stack
 * @file: file currently open
 * Return: void
 */
void rnOp(instruction_t fL[], int lNum, stack_t **head, char *buf, FILE *file)
{
int i;
if (curIns[0] == NULL)
return;
for (i = 0; i <= 6; i++)
{
/*printf("curIns[0]:%s\n fL[%i]:%s\n", curIns[0], i, fL[i].opcode);*/
/*printf("strcmp: %i\n", strcmp(curIns[0], fL[i].opcode));*/
/*printf("BOOP: currIns[1]:%s\n", curIns[1]);*/
if (strcmp(curIns[0], fL[i].opcode) == 0)
{
fL[i].f(head, lNum);
if (curIns[2] != NULL)
{
if (strcmp(curIns[2], "FAILMALLOC") == 0)
{
dprintf(STDERR_FILENO, "Error: malloc failed\n");
exitFunc(head, buf, file);
exit(EXIT_FAILURE);
}
}
break;
}
}
if (i > 6)
{
dprintf(STDERR_FILENO, "L%i: unknown instruction %s\n", lNum, curIns[0]);
exitFunc(head, buf, file);
exit(EXIT_FAILURE);
}
}

/**
 * exitFunc - frees up malloced items from function
 * @buf: line from file
 * @stack: head of stack
 * @file: file currently open
 * Return: void
 */
void exitFunc(stack_t **stack, char *buf, FILE *file)
{
if (curIns != NULL)
{
if (curIns[0] != NULL)
free(curIns[0]);
if (curIns[1] != NULL)
free(curIns[1]);
if (curIns[2] != NULL)
free(curIns[2]);
free(curIns);
}
if (stack != NULL)
freeList(*stack);
free(buf);
fclose(file);
exit(EXIT_FAILURE);
}

/**
 * checkForChars - checks if a string is an int
 * @str: string to check
 * Return: 0 or -1 if fails
 */
int checkForChars(char *str)
{
int i;
char c;
for (i = 0; str[i] != '\0'; i++)
{
c = str[i];
if ((c == '-' && i != 0) || ((c < '0' || c > '9') && c != '-'))
return (-1);
}
return (0);
}
