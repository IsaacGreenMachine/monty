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
stack_t *head = NULL;
file = fopen(fileName, "r");
instruction_t funcList[] = {
	{"push", pushOp}, 
	{"pall", pallOp},
	{"pop", popOp},
        {"swap", swapOp},
	{"add", addOp},
        {"nop", nopOp}
};
while (charCount != -1)
{
charCount = getline(&buf, &bufSize, file);
/*printf("currentLine: %s\n", buf);*/
lineNum++;
if (charCount == -1)
break;
setExternToInstruction(buf, lineNum, funcList);
/*printf("L%i%s\n", lineNum, buf);*/
/*printf("currentInstruction[0]: %s\n", currentInstruction[0]);*/
if (currentInstruction[0] != NULL)
goOp(currentInstruction[0], funcList, lineNum, &head);
free(currentInstruction[0]);
free(currentInstruction[1]);
free(currentInstruction);
}
freeList(head);
free(buf);
fclose(file);
}

/**
 * setExternToInstruction - sets extern var [0] and [1] to correct value
 * @line: line from file
 * @lineNum: line Number
 * @funcList: list of instructions and functions
 *
 * Return: void
 */
void setExternToInstruction(char *line, int lineNum, instruction_t funcList[])
{
char *word;
int j = 0;
currentInstruction = malloc(100);
word = strtok(line, "\n\t ");
/*printf("word: %s\n", word);*/
j = checkWord(word, funcList);
/*printf("j: %i\n", j);*/
while (word != NULL && j == 0)
{
word = strtok(NULL, "\n\t ");
/*printf("word: %s\n", word);*/
j = checkWord(word, funcList);
/*printf("j: %i\n", j);*/
}
if (j == -1)
{
dprintf(STDERR_FILENO, "L%i: unknown instruction %s", lineNum, word);
}
/*printf("TOODALAOOOOO");*/
}

/**
 * checkWord - checks word that is given
 * @word: given word. e.g. "push"
 * @funcList: list of instructions and functions
 *
 * Return: -1 (error), 0(repeat), or 1(success).
 */
int checkWord(char *word, instruction_t funcList[])
{
int i;
/*printf("word to CheckWord: %s\n", word);*/
if (word == NULL)
return (0);
for (i = 0; i <= 5; i++)
{
/*printf("strcmping %s\n", funcList[i].opcode);*/
if (strcmp(word, funcList[i].opcode) == 0)
{
currentInstruction[0] = strdup(word);
/*printf("currentInstruction[0]: %s\n", currentInstruction[0]);*/
if (strcmp(word, "push") == 0)
{
word = strtok(NULL, "\n ");
if (strcmp(word, "0") == 0 || atoi(word) != 0)
{
currentInstruction[1] = strdup(word);
/*printf("currentInstruction[1]: %s\n", currentInstruction[1]);*/
return (1);
}
else
return (-1);
}
else
return (1);
}
}
return (0);
}
/**
 * goOp - activates a function based on given op
 * @opName: name of Op
 * @funcList: list of instructions and functions
 * @lineNum: line number
 * @head: pointer to head of stack
 *
 * Return: void
 */
void goOp(char *opName, instruction_t funcList[], int lineNum, stack_t **head)
{
int i;
for (i = 0; i <= 5; i++)
{
if (strcmp(opName, funcList[i].opcode) == 0)
{
/*printf("ABOUT TO FUNC: %s\nLINENUM: %i\n", funcList[i].opcode, lineNum);*/
funcList[i].f(head, lineNum);
}
}
}
