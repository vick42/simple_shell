#include "shell.h"

/**
* _strlen - Function that finds the length of a string
* @s: string that the length of is found
*
* Return: length of s, 0 if s is NULL
*/
size_t _strlen(char *s)
{
	/* variable to loop through string to get length */
	size_t len = 0;

	if (s) /* if NULL pointer, return 0 */
		while (s[len] != '\0') /* Loop string til null byte */
			len++;

	return (len);
}

/**
 * *_strncpy - copies n bytes of src to dest string
 * @dest: string to copy to
 * @src: string to copy from
 * @n: number of bytes of src to copy
 *
 * Return: string copied to i.e dest
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i = 0;

	while (i < n)
	{
		if (src[i] == '\0')
			break;
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/**
 * _strcmp - Compares two strings
 * @s1: string to compare
 * @s2: string to compare against
 *
 * Return: num < 0 if s1 is lesser, num > 0 if greater, 0 if equal
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0')
	{
		if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s2[i] != '\0')
		return (s1[i] - s2[i]);
	return (0);
}

/**
 * _strncmp - compare strings up to n bytes
 * @s1: string to compare
 * @s2: string to compare against
 * @n: bytes to compare
 *
 * Return: n < 0 if s1 is lesser, n > 0 if greater, 0 if equal
 */
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0;

	while (i < n && s1[i] != '\0') /* iterate until null-byte or till n bytes*/
	{
		if (s1[i] < s2[i]) /* if s1 is less, return neg num */
			return (s1[i] - s2[i]);
		if (s1[i] > s2[i]) /* if s1 is greater, return pos num */
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n && s2[i] != '\0')
		return (s1[i] - s2[i]);

	return (0);
}

/**
 * *_strcat - concatenates two strings
 * @dest: string to append to
 * @src: sring to append
 *
 * Return: pointer to concatenated string
 */
char *_strcat(char *dest, char *src)
{
	int src_i = 0, dest_i = 0;

	for (; dest[dest_i] != '\0';)
		dest_i++;

	for (; src[src_i] != '\0';)
	{
		dest[dest_i] = src[src_i];
		src_i++;
		dest_i++;
	}

	dest[dest_i] = '\0';

	return (dest);
}
