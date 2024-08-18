#include "shell.h"
/**
 * exec_mngr - directs cmd table to appropriate execution flow
 * @argv: cmd table (i.e. list of user args)
 *
 * Return: 0 on Success, -1 on Failure
 */
int exec_mngr(char *const *argv)
{
	int r_val;

	r_val = exec_builtin(argv); /* search and execute built-in */
	if (r_val == 0) /* execution success */
		return (0);

	if (err_msg == 2)
	{
		r_val = (exec_external(argv)); /* search and execute external cmd */
		if (r_val == 0) /* execution success */
			return (0);
	}

	return (-1); /* return error */
}
/**
 * exec_builtin - identify and execute built-in commands
 * @argv: cmd table (i.e. list of user args)
 *
 * Return: 0 on Sucess, -1 on Failure
 */
int exec_builtin(char *const *argv)
{
	built_in fps[] = { /* stores func pointers to built-in commands */
		{"exit", builtin_exit},
		{"env", builtin_env},
		{"cd", builtin_cd},
		{NULL, NULL}
	};

	int i;
	int (*built_in_fp)(char *const *argv); /* func pointer prototype */

	/* compare args to built-ins */
	for (i = 0; fps[i].cmd; i++) /* iterate till NULL */
		if ((_strcmp(argv[0], fps[i].cmd)) == 0) /* if strings match */
		{
			built_in_fp = fps[i].fp; /* assign func pointer */

			if ((built_in_fp(argv)) == 0) /* execute built-in */
				return (0); /* success */

			err_msg = 3;
			return (-1); /* error */
		}
	err_msg = 2;
	return (-1); /* command not found */
}
/**
 * exec_external - identify and execute external commands
 * @argv: cmd table (i.e. list of user args)
 *
 * Return: 0 on Sucess, -1 on Failure
 */
int exec_external(char *const *argv)
{
	char **path = NULL; /* array of paths */
	pid_t pid; /* process ID */
	int status, i; /* monitor child state changes */

	if (path_check(argv)) /* if command name is path */
	{
		/* allocate memory for path list */
		path = (char **)alloc_mngr((char *)path, (sizeof(char *) * 2));
		/* allocate for first row - cmd name/path */
		path[0] = alloc_mngr(path[0], (sizeof(char) * (_strlen(argv[0]) + 1)));
		_strncpy(path[0], argv[0], _strlen(argv[0])); /* copy arg to path array */
		path[1] = NULL; /* null-terminate list */
	}
	else /* if command name is not path */
		path = get_path(argv); /* retrieve separated, concat paths */

	for (i = 0; path[i]; i++) /* for every path */
		if (access(path[i], (R_OK | X_OK)) == 0) /* check if exists and exec perm */
		{
			switch ((pid = fork())) /* fork current process */
			{
				case -1: /* fork failure */
					return (-1);
				case 0: /* returned to child */
					execve(path[i], argv, environ); /* execute cmd */
					err_msg = 1; /* errno has been set */

					exit(EXIT_FAILURE); /* exits child, not parent ???? */
				default: /* returned to parent */
					if ((waitpid(pid, &status, 0)) == -1)
						return (-1); /* wait failure */
					else
						return (0); /* success */
			}
		}

	err_msg = 2;
	return (-1); /* file/dir not found */
}
