#include "shell.h"
/**
 * builtin_env - print process environment
 * @argv: command table
 *
 * Return: 0 on Success, -1 on Failure
 */
int builtin_env(char *const *argv)
{
	size_t row, len;

	if (!argv[1])
		for (row = 0; environ[row]; row++) /* iterate rows */
		{
			len = _strlen(environ[row]); /* take row length */

			if ((write(STDOUT_FILENO, environ[row], len)) == -1) /* print row */
				return (-1); /* if write fails */

			if ((write(STDOUT_FILENO, "\n", 1)) == -1) /* print newline */
				return (-1); /* if write fails */
		}
	else /* error if argument is passed */
	{
		errno = ENOENT;
		return (-1);
	}

	return (0);
}
