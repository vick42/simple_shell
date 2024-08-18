#include "MyShell.h"

/**
 * function_fork - function split directory
 * @buffer: pointer
 * @command: double pointer
 * @argv: argument[0]
 * @count: count each time when execute a command
 * Return: void
 * On error, -1 is returned, and errno is set appropriately.
 */
void function_fork(char *buffer, char **command, char **argv, int count)
{
	int y, status;
	pid_t pidC;
	struct stat st;
	char *str;

	str = _itoa(count);
	if (command[0] != NULL)
	{
		pidC = fork();
		if (pidC == -1)
		{
			perror("Error Fork");
			free(buffer);
			free(command);
			exit(-1);
		}
		if (pidC == 0)
		{
			y = stat(command[0], &st);
			if (y != 0)
				command[0] = get_path(command[0]);
			if (execve(command[0], command, NULL) == -1)
			{
				_perror(argv[0], str, command[0]);
				free(str);
				free(buffer);
				free(command);
				exit(-1);
			}
		}
		else if (pidC > 0)
			wait(&status);
	}
	free(str);
	free(buffer);
	free(command);
}

/**
 * _perror - function print the error
 * @argv: argument vector zero
 * @str: string count the number of execute functions
 * @command: command [0] when the system call execve no found
 * Return: zero
 */

int *_perror(char *argv, char *str, char *command)
{
	write(STDERR_FILENO, argv, _strlen(argv));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO,  str, _strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": not found\n", 12);

	return (0);
}
