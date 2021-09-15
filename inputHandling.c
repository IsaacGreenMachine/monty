#include "monty.h"
char **currentInstruction;

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
{"push", pushOp}, {"pall", pallOp},
{"pop", popOp}, {"swap", swapOp},
{"add", addOp}, {"nop", nopOp} };
stack_t *head = NULL;
file = fopen(fileName, "r");
if (file == NULL)
dprintf(STDERR_FILENO, "Error: Can't open file %s\n", fileName);
while (charCount != -1)
{
charCount = getline(&buf, &bufSize, file);
/*printf("currentLine: %s\n", buf);*/
lineNum++;
if (charCount == -1)
break;
setExternToInstruction(buf, lineNum);
/*printf("L%i%s\n", lineNum, buf);*/
/*printf("currentInstruction[0]: %s\n", currentInstruction[0]);*/
printf("currentInstruction[0]: %s\n", currentInstruction[0]);
printf("currentInstruction[1]: %s\n", currentInstruction[1]);
runOp(funcList, lineNum, &head);
if (currentInstruction[0] != NULL) 
free(currentInstruction[0]);
if (currentInstruction[1] != NULL)
free(currentInstruction[1]);
if (currentInstruction != NULL)
free(currentInstruction);
}
freeList(head);
//free(buf);
fclose(file);
}

/**
 * setExternToInstruction - sets extern var [0] and [1] to correct value
 * @line: line from file
 * @lineNum: line Number
 *
 * Return: void
 */
void setExternToInstruction(char *line, int lineNum)
{
char *word;
currentInstruction = malloc(sizeof(char*) * 3);
word = strtok(line, "\n\t ");
if (word == NULL)
{
currentInstruction[0] = NULL;
currentInstruction[1] = NULL;
}
else //word is not NULL
{
currentInstruction[0] = word;
if (strcmp(word, "push") == 0)
{
word = strtok(NULL, "\n\t ");
if (word == NULL || (strcmp(word, "0") != 0 && atoi(word) == 0))
{
dprintf(STDERR_FILENO, "L%i: usage: push integer", lineNum);
exit(EXIT_FAILURE);
}
else
{
currentInstruction[1] = strdup(word);
}
}
else
currentInstruction[1] = NULL;	
}
}

void runOp(instruction_t funcList[], int lineNum, stack_t **head)
{
int i;
for (i = 0; i <= 5; i++)
{
//printf("BEEP: currIns[0]:%s\n funcList[%i]:%s\n", currentInstruction[0], i, funcList[i].opcode);
//printf("strcmp: %i\n", strcmp(currentInstruction[0], funcList[i].opcode));
//printf("BOOP: currIns[1]:%s\n", currentInstruction[1]);
if (strcmp(currentInstruction[0], funcList[i].opcode) == 0)
{
funcList[i].f(head, lineNum);
break;
}
}
if (i > 5)
{
dprintf(STDERR_FILENO, "L%i: unknown instruction %s\n", lineNum, currentInstruction[0]);
exit(EXIT_FAILURE);
}
}
