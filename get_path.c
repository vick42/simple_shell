#include "shell.h"
/**
 * get_path - locate, separate, and concat paths with cmd into pointer array
 * @argv: command table (inly cmd name used)
 *
 * Return: pointer to array of concatenated paths
 */
char **get_path(char *const *argv)
{
	char *path_ptr = NULL; /* pointer to PATH in environ */
	char *ref = "PATH="; /* ref to compare to */
	char **path = NULL; /* list of possible concatenated paths */
	size_t path_cnt, env_i = 0, p_i;
	size_t path_cat_size; /* size of path after concat */

	while (environ[env_i]) /* until end of env list */
	{
		if (_strncmp(ref, environ[env_i], 5) == 0) /* check for match */
		{
			path_ptr = &environ[env_i][5]; /* assign ptr to begin of PATH value */
			path_cnt = path_count(path_ptr); /* take num of paths */
			/* allocate memory for pointer to n pointers (+1 NULL row) */
			path = (char **)alloc_mngr((char *)path, (sizeof(char *) * (path_cnt + 1)));

			for (p_i = 0; p_i < path_cnt; p_i++) /* iterate for each path */
			{
				/* add length of path, '/', cmd & '\0' */
				path_cat_size = (path_len(path_ptr) + _strlen(argv[0]) + 2);
				/* allocate for path cat */
				path[p_i] = alloc_mngr(path[p_i], (sizeof(char) * path_cat_size));

				_strncpy(path[p_i], path_ptr, path_len(path_ptr)); /* copy path */
				_strcat(path[p_i], "/"); /* concatenate forward slash */
				_strcat(path[p_i], argv[0]); /* concat cmd name */

				/* move ptr to beginning of next path */
				path_ptr = (path_ptr + (path_len(path_ptr) + 1));
			}
			path[p_i] = NULL; /* null-terminate list */
			return (path);
		}
		env_i++;
	}
	return (NULL); /* failed to retrieve PATH */
}

/**
 * path_check - determine if command name includes path
 * @argv: command table
 *
 * Return: 1 if path, 0 if not path
 */
size_t path_check(char *const *argv)
{
	size_t i = 0, is_path = 0;

	while (argv[0][i]) /* iterate thru command name */
	{
		if (argv[0][i] == '/') /* if name conatins "/" */
		{
			is_path = 1; /* name is path */
			break;
		}
		i++;
	}

	return (is_path);
}
/**
 * path_count - count paths
 * @paths: PATH line of environ
 *
 * Return: number of paths, 0 if paths NULL
 */
size_t path_count(char *paths)
{
	size_t i, path_cnt = 0;

	if (!paths) /* if path is NULL */
		return (0);

	/* iterates to counts number of paths */
	for (i = 0; paths[i]; i++)
		if ((paths[i + 1] == ':' || paths[i + 1] == '\0'))
			path_cnt++;

	return (path_cnt);
}
/**
* path_len - take length of current path
* @path_ptr: pointer to current path
*
* Return: length of path
*/
size_t path_len(char *path_ptr)
{
	size_t i = 0;

	if (path_ptr) /* if not NULL */
		while (path_ptr[i] != ':' && path_ptr[i] != '\0') /* loop unitl colon */
			i++;

	return (i); /* return length of path */
}
