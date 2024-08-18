#include "shell.h"

size_t count_tokens(char *line);
size_t token_length(char *line, size_t tok_need);

/**
 * **_strtok - Sets up a 2D array by parsing a string
 * @line: The string to be parsed into tokens
 *
 * Return: Always the 2D array
 */
char **_strtok(char *line)
{
	/* Initalize needed variables */
	size_t alloc_size;
	size_t tok_amnt;
	size_t tok_len = 0, tok_curr = 1;
	size_t line_it = 0, tok_it = 0, i = 0;
	char **tok_array = NULL;

	tok_amnt = count_tokens(line);
	if (tok_amnt == 0)
		return (NULL);

	/* **TO CHANGE. INSERT ALLOC_MNGR()** */
	alloc_size = (tok_amnt + 1) * (sizeof(char *));
	tok_array = (char **)alloc_mngr((char *)tok_array, alloc_size);
	if (tok_array == NULL)
		return (NULL);

	/* Main loop to fill allocated tok_array with tokens */
	for (i = 0; tok_curr <= tok_amnt; tok_curr++, i++)
	{
		/* Setting tok_len equal to length of current token */
		tok_len = token_length(line, tok_curr);

		/* **TO CHANGE. INSERT ALLOC_MNGR()** */
		alloc_size = (tok_len + 1) * (sizeof(char));
		tok_array[i] = alloc_mngr(tok_array[i], alloc_size);
		if (tok_array[i] == NULL)
			return (NULL);

		/* Helps set line_it to the position of the needed token */
		while (line[line_it] == ' ' || line[line_it] == '\t')
			line_it++;

		/* Copying the token from line into tok_array */
		for (tok_it = 0; tok_it < tok_len; tok_it++, line_it++)
			tok_array[i][tok_it] = line[line_it];

		/* Ending the token in the array with a null-byte */
		tok_array[i][tok_it] = '\0';
	}

	/* Set last tok_array[i]'s to NULL */
	tok_array[i] = NULL;

	return (tok_array);
}

/**
 * count_tokens - Counts the amount of tokens
 * @line: The string to count how many tokens it has
 *
 * Return: Always the total amount of tokens
 */
size_t count_tokens(char *line)
{
	size_t it = 0, tok_amnt = 0;

	/* Loops through line and counts the amount of tokens */
	while (line[it] != '\0')
	{
		if ((line[it + 1] == ' ' || line[it + 1] == '\t') || line[it + 1] == '\0')
			if (line[it] != ' ' && line[it] != '\t')
				tok_amnt++;
		it++;
	}
	return (tok_amnt);
}

/**
 * token_length - Count how long a specified token is
 * @line: The string containing the token
 * @tok_need: Specifys which token within line is needed
 *
 * Return: Always the length of the specified token
 */
size_t token_length(char *line, size_t tok_need)
{
	size_t it = 0, tok_len = 0, tok_curr = 0;

	while (tok_curr < tok_need)
	{
		while (line[it] == ' ' || line[it] == '\t')
			it++;

		if (line[it] != '\0' && line[it] != ' ' && line[it] != '\t')
		{
			tok_curr++;
			while (line[it] != '\0' && line[it] != ' ' && line[it] != '\t')
			{
				if (tok_curr == tok_need)
					tok_len++;
				it++;
			}
		}
	}
	return (tok_len);
}
