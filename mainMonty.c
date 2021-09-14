#include "monty.h"
/**
 * main - monty interpreter
 * @ac: number of arguments used in command call
 * @av: array of arguments in command call
 *
 * Return: appropriate error
 */
int main(int ac, char **av)
{
if (ac != 2)
{
dprintf(STDERR_FILENO, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}
getLinez(av[1]);
}
