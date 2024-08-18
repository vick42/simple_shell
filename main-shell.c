#include "MyShell.h"

/**
 * main - SIMULATOR PROGRAM SHELL
 * @argc: Unused argument
 * @argv: argument[0]
 * Return: function will always return 0
 */

int main(__attribute__((unused)) int argc, char *argv[])
{
	char *buffer = NULL, **command;
	int pointer, i, count = 0;

	signal(SIGINT, sighandler);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, ":) ", 3);
		buffer = validator_getline();
		count++;
		if (!buffer)
			continue;
		pointer = _memory(buffer);
		command = function_strtok(buffer, pointer);
		exit1(buffer, command);
		i = env1(buffer, command);

		if (i == 0 || command == 0)
			continue;
		function_fork(buffer, command, argv, count);
	}
	return (0);
}
