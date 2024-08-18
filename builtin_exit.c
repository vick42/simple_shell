#include "shell.h"

int _atoi(char *status);
int is_num(char letter);

/**
 * builtin_exit - Exits the shell
 * @argv: The status to exit shell with
 *
 * Return: Either exits the shell or returns EXIT_FAILURE
 */
int builtin_exit(char *const *argv)
{
	int answer;

	if (argv[1] == NULL)
	{
		free_mem_list(&mem_head);
		free_static_mem_list(&static_mem_head);
		exit(EXIT_SUCCESS);
	}
	else
	{
		answer = _atoi(argv[1]);

		switch (answer)
		{
			case (-1):
				return (EXIT_FAILURE);
			default:
				free_mem_list(&mem_head);
				free_static_mem_list(&static_mem_head);
				exit(answer);
		}
	}
}

/**
 * _atoi - Converts string into a number
 * @status: The string to convert
 *
 * Return: Always the status as an int or -1
 */
int _atoi(char *status)
{
	int answer = 0, i = 0;

	if (status[i] == '-')
		return (-1);

	for (i = 0; status[i] != '\0'; i++)
	{
		if (is_num(status[i]))
			answer = answer * 10 + status[i] - '0';
		else
			return (-1);
	}

	if (answer > 2147483647)
		return (-1);
	else
		return (answer);
}

/**
 * is_num - Checks if a char is a number
 * @letter: The char to check
 *
 * Return: Always 1 on success or 0 on failure
 */
int is_num(char letter)
{
	if (letter >= '0' && letter <= '9')
		return (1);

	return (0);
}
