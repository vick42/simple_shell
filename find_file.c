#include "MyShell.h"

/**
 * get_path - get path
 * @command: command get
 *
 * Return: file
 * On error, -1 is returned, and errno is set appropriately.
 */

char  *get_path(char *command)
{
	int i, pointer;
	char *delim = ":=", *tokens, **folder, *buffer;
	char *file = NULL;

	i = 0;
	buffer = _getenv("PATH");

	pointer = _memory1(buffer);
	folder = malloc(sizeof(char *) * pointer);

	if (folder == NULL)
	{
		perror("error allocated memory");
		return (NULL);
	}
	tokens = strtok(buffer, delim);

	i = 0;
	while (tokens)
	{
		folder[i] = tokens;
		tokens = strtok(NULL, delim);
		i++;
	}
	folder[i] = NULL;
	file = found_function(folder, command);
	i = 0;
	free(folder);
	return (file);
}

/**
 * found_function - found directory
 * @folder: Double pointer at the directory
 * @command: command found
 * Return: command
 * On error, -1 is returned, and errno is set appropriately.
 */

char *found_function(char **folder, char *command)
{
	int i = 0;
	char *temp;

	temp = malloc(sizeof(char) * 100);

	if (temp == NULL)
		return (NULL);

	while (folder[i])
	{
		DIR *d;
		struct dirent *dir;

		d = opendir(folder[i]);

		if (d)
		{
			while ((dir = readdir(d)) != NULL)
			{
				if ((_strcmp(dir->d_name, command)) == 0)
				{
					_strcpy(temp, folder[i]);
					_strcat(temp, "/");
					_strcat(temp, dir->d_name);
					closedir(d);
					return (temp);
				}
			}
			closedir(d);
			i++;
		}
	}
	free(temp);
	return (command);
}

/**
 * _getenv - get variables enviroment
 * @s: parameter in
 *
 * Return: command
 * On error, -1 is returned, and errno is set appropriately.
 */
char *_getenv(char *s)
{
	int i;
	char *find_path = NULL;
	char *final_path = NULL;
	char *copy_env;

	i = 0;
	while (environ[i] != NULL)
	{
		copy_env = _strdup(environ[i]);

		if (copy_env == NULL)
		{
			free(copy_env);
			return (NULL);
		}
		find_path = strtok(copy_env, "=");

		if (_strcmp(find_path, s) == 0)
		{
			final_path = _strstr(environ[i], "/");
		}
		i++;
	free(copy_env);
	}
	return (final_path);
}
