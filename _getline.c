#include "shell.h"

int check_buffer(char *buffer);
void shift_buffer(char *buffer, ssize_t offset);
ssize_t copy_buffer(char **line, char *buffer, ssize_t *offset);

/**
 * _getline - retrieve command line
 * @line: buffer to store command line
 *
 * Return: Number of lines read on success or -1 on fail
 */
ssize_t _getline(char **line)
{
	ssize_t read_cnt = 0, copied = 0;
	static ssize_t read_total;
	ssize_t offset = 0; /* line offset for each iteration */
	static char buffer[1024];

	if ((check_buffer(buffer)) == 0) /* if buffer is empty */
	{
		/* read stdin to dynamic buffer */
		while ((read_cnt = read(STDIN_FILENO, buffer, 1023)) > 0)
		{
			if (read_cnt == -1) /* check for read failure */
				return (-1);

			read_total += read_cnt; /* add num of bytes last read to total */

			buffer[read_cnt] = '\0'; /* null-terminate buffer */

			/* copy read bytes from buffer to line */
			copied = copy_buffer(&(*line), buffer, &offset);

			/* if more read than copied, '\n' encountered */
			if (copied < read_cnt)
			{
				offset = 0;
				return (read_total); /* continue shell loop */
			}
		}
		read_total = 0;
	}
	else
	{
		/* copy remaining bytes from buffer up to newline */
		copied = (copy_buffer(&(*line), buffer, &offset) + 1);
	}
	return (read_total); /* return total number of bytes read */
}

/**
 * check_buffer - check if buffer is empty
 * @buffer: buffer to test
 *
 * Return: number of bytes written in buffer
 */
int check_buffer(char *buffer)
{
	int bytes = 0;

	while (buffer[bytes])
		bytes++;

	return (bytes);
}

/**
 * copy_buffer - copy from buffer till '\n' or '\0'
 * @line: copy dest
 * @buffer: copy src
 * @offset: already copied to line
 *
 * Return: bytes copied
 */
ssize_t copy_buffer(char **line, char *buffer, ssize_t *offset)
{
	size_t i = 0, cpy_cnt = 0;

	/* count bytes till command end or end of buffer (i.e. '\n' or '\0') */
	for (; buffer[i] != '\n' && buffer[i] != '\0'; i++)
		cpy_cnt++;

	if (buffer[i] == '\n')
	{
		/* allocate line to hold bytes to copy */
		*line = alloc_mngr(*line, (sizeof(char) * (cpy_cnt + *offset + 1)));
		if (!(*line)) /* check for allocation fail */
			return (-1);

		_strncpy((*line + *offset), buffer, cpy_cnt); /* copy cmd to line */
		/* shift buffer contents past copied to index [0] */
		shift_buffer(buffer, (cpy_cnt + 1));

		return (cpy_cnt);
	}
	if (buffer[i] == '\0')
	{
		/* allocate line to hold bytes to copy */
		*line = alloc_mngr(*line, (sizeof(char) * (cpy_cnt + *offset + 1)));
		if (!(*line)) /* check for allocation fail */
			return (-1);

		/* copy buffer to line from current offset */
		_strncpy((*line + *offset), buffer, (cpy_cnt));

		*offset += cpy_cnt; /* advance line offset */

		return (cpy_cnt);
	}

	return (cpy_cnt);
}
/**
 * shift_buffer - shift buffer contents left
 * @buffer: buffer shift
 * @n: number of bytes to shift buffer
 */
void shift_buffer(char *buffer, ssize_t n)
{
	ssize_t i = 0;

	while (buffer[n] != '\0') /* shift buffer left n bytes */
	{
		buffer[i] = buffer[n];
		i++;
		n++;
	}

	/* set remaining bytes to null */
	_memset(&buffer[i], 0, (1024 - n)); /* memset till end of buffer */
}
