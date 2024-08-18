#include "MyShell.h"

/**
 * validator_getline - validator input
 * @void: parameter input
 *
 * Return: buffer
 * On error, -1 is returned, and errno is set appropriately.
 */

char *validator_getline(void)
{
	char *buffer = NULL;
	size_t size = 0;
	ssize_t ret;
	int i = 0;

	ret = getline(&buffer, &size, stdin);
	if (!buffer)
	{
		perror("Error in Allocate Memory Buffer");
		return (NULL);
	}
	if (ret == 1)
	{
		free(buffer);
		return (NULL);
	}
	else if (ret == EOF)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(buffer);
		exit(0);
	}
	else
	{
		while (buffer[i] == ' ' && buffer[i + 1] == ' ')
			i++;
		if (buffer[i + 1] == '\n')
		{
			free(buffer);
			return (NULL);
		}
	}
	return (buffer);
}

/**
 * sighandler - signal for press ctrl + D
 * @signum: void input
 *
 * Return: void function, no return
 */


void sighandler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n:) ", 4);
}
