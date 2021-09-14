#include "monty.h"
int main(int ac, char **av)
{
if(ac != 2)
{
dprintf(STDERR_FILENO, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}
getLinez(av[1]);
}
