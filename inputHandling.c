#include "monty.h"
//extern/global var
char **currentInstruction;

//gets lines from file
void getLinez(char *fileName)
{
int charCount = 0, lineNum = 0;
size_t bufSize = 0;
char *buf = NULL;
FILE *file;
stack_t **head = NULL;
file = fopen(fileName, "r");
instruction_t funcList[] = {{"push", pushOp}, {"pall", pallOp}};
while (charCount != -1)
{
charCount = getline(&buf, &bufSize, file);
lineNum++;
if (charCount == -1)
break;
setExternToInstruction(buf, lineNum, funcList);
//printf("L%i%s", lineNum, buf);
activateOp(currentInstruction[0], funcList, lineNum, head);
}
free(buf);
}

//sets the extern variable [0] and [1] to correct value
void setExternToInstruction(char *line, int lineNum, instruction_t funcList[])
{
char *word;
int i, j = 0;
currentInstruction = malloc(5);
word = strtok(line, "\n\t ");
//printf("word: %s\n", word);
j = checkWord(word, funcList);
//printf("j: %i\n", j);
while(word != NULL && j == 0)
{
word = strtok(NULL, "\n\t ");
//printf("word: %s\n", word);
j = checkWord(word, funcList);
//printf("j: %i\n", j);
}
if (j == -1)
{
dprintf(STDERR_FILENO, "L%i: unknown instruction %s", lineNum, word);
}
}

int checkWord(char *word, instruction_t funcList[])
{
int i;
//printf("word to CheckWord: %s\n", word);
if (word == NULL)
return (0);
for(i = 0; i <= 1; i++)
{
//printf("strcmping %s\n", funcList[i].opcode);
if (strcmp(word, funcList[i].opcode) == 0)
{
currentInstruction[0] = word;
printf("currentInstruction[0]: %s\n", currentInstruction[0]);
if (strcmp(word, "push") == 0)
{
word = strtok(NULL, "\n ");
if (strcmp(word, "0") == 0 || atoi(word) != 0)
{
currentInstruction[1] = word;
printf("currentInstruction[1]: %s\n", currentInstruction[1]);
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

void activateOp(char *opName, instruction_t funcList[], int lineNum, stack_t **head)
{
int i;
for(i = 0; i <= 1; i++)
{
if (strcmp(opName, funcList[i].opcode) == 0)
printf("ABOUT TO FUNC: %s\nLINENUM: %i\n", funcList[i].opcode, lineNum);
funcList[i].f(head, lineNum);
}
}
