#include "main.h"

/**
 * printFormatted - a function that prints formatted text according to format
 * specified.
 * @format: string containing text and format specifiers.
 * @print_array: array of format specifiers and associated functions.
 * @args: variable argument list to handle format specifiers.
 *
 * Return: number of characters printed.
 */

int printFormatted(const char *format, fmat_t *print_array, va_list args)
{
	char a, percent = '%';
	int b, c, count = 0;

	b = 0;
	a = format[b];
	while (a != '\0')
	{
		if (a == '%')
		{
			c = 0;
			b++;
			a = format[b];
			while (print_array[c].type != NULL &&
			       a != *(print_array[c].type))
				c++;
			if (print_array[c].type != NULL)
				count += print_array[c].f(args); /*
								  * call the
								  * appropriate
								  * print
								  * function
								  */
			else
			{
				if (a == '\0')
					return (-1);
				if (a != '%')
				{
					char ch = a;
					/* print the character using write */
					write(1, &ch, 1);
					count++;
				}
				/* print a '%' */
				write(1, &percent, 1);
				count++;
			}
		}
		else
		{
			char ch = a;
			/* print the character using write */
			write(1, &ch, 1);
			count++;
		}
		b++;
		a = format[b];
	}
	return (count); /* Return the total number of characters printed */
}

/**
 * _printf - a function that produces output according to a format.
 * @format: string containing text and format specifiers.
 *
 * Return: the number of characters printed.
 */

int _printf(const char *format, ...)
{
	va_list args;
	int i = 0;

	fmat_t ops[] = {
		{"c", print_char},
		{"s", print_str},
		{NULL, NULL}
	};

	if (format == NULL)
		return (-1);
	va_start(args, format);
	i = printFormatted(format, ops, args);
	va_end(args);

	return (i);
}
