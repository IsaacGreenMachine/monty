#include "monty.h"
/**
 * main - monty interpreter
 * @ac: number of arguments used in command call
 * @av: array of arguments in command call
 *
 * Return: appropriate error
 */

/*
 * TODO
 *in push if int is not an int or if no argument given to push
 *	print the error message L<line_number>: usage: push integer,
 *	followed by a new line, and exit with the status EXIT_FAILURE
 */
int main(int ac, char **av)
{
if (ac != 2)
{
dprintf(STDERR_FILENO, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}
getLinez(av[1]);
return (EXIT_SUCCESS);
}
