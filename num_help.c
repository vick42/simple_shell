#include "shell.h"

/**
* _itoa - Function that converts a number to string
* @number: value to be converted to a string
* @buffer: array that stores null-termintated string result
* @base: value of the string
*
* Return: converted string
*/
char *_itoa(size_t number, char *buffer, int base)
{
	int sign = 1, i = 0;
	size_t remainder = 0;

	/* if number is 0, hard code result */
	if (number == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
	}
	/*
	 * if negative, convert to pos and track sign
	 * if (number < 0 && base == 10)
	 * {
	 *	number *= -1;
	 *	sign *= -1;
	 * }
	 */
	/* if number is not 0 */
	while (number)
	{
		remainder = number % base;
		buffer[i++] = '0' + remainder;
		number /= base;
	}
	/* if negative, add sign char */
	if (sign < 0)
		buffer[i++] = '-';

	/* terminate string */
	if (number)
		buffer[i] = '\0';
	return (_revstr(buffer));
}

/**
 * count_digit - Returns how many digits make up a number
 * @num: The number to count the amount of digits
 *
 * Return: Always a size_t
 */
size_t count_digit(size_t num)
{
	size_t count = 0;

	while (num != 0)
	{
		num /= 10;
		count++;
	}

	return (count);
}
