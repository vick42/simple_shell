#include "MyShell.h"

/**
 * env1 - Function the validate the the enviroment variables
 * @buffer: string of getline.
 * @command: is the arguments of the buffer.
 * Return: 1 is the function env or 0 is not function env.
 */

int env1(char *buffer, char **command)
{
	int i, j, ret;

	if (command[1] == NULL)
	{
		ret = _strcmp(command[0], "env");
		if (ret == 0)
		{
			for (i = 0; environ[i] != '\0'; i++)
			{
				for (j = 0; environ[i][j] != '\0'; j++)
				{
					write(STDOUT_FILENO, &environ[i][j], 1);
				}
				write(STDOUT_FILENO, "\n", 1);
			}
			free(buffer);
			free(command);
			return (0);
		}
		return (1);
	}
	return (1);
}


/**
 * exit1 - Function the validate the command exit
 * @buffer: string of getline.
 * @command: is the arguments of the buffer.
 * Return: no return is function void.
 */

void exit1(char *buffer, char **command)
{
	int ret;

		ret = _strcmp(command[0], "exit");
		if (ret == 0)
		{
			free(buffer);
			free(command);
			exit(-1);
		}
}
