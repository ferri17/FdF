/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:59:40 by fbosch            #+#    #+#             */
/*   Updated: 2023/05/29 21:19:28 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_arguments(va_list args, char c)
{
	unsigned int	printed;

	printed = 0;
	if (c == 'c')
		printed = ft_print_char(va_arg(args, int));
	else if (c == 's')
		printed = ft_print_string(va_arg(args, char *));
	else if (c == 'p')
		printed = ft_print_pointer(va_arg(args, unsigned long));
	else if (c == 'i' || c == 'd')
		printed = ft_print_integer_signed(va_arg(args, int));
	else if (c == 'u')
		printed = ft_print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		printed = ft_print_hexa(va_arg(args, unsigned int), 0);
	else if (c == 'X')
		printed = ft_print_hexa(va_arg(args, unsigned int), 1);
	else if (c == '%')
		printed = ft_print_char('%');
	else
		printed = ft_print_char(c);
	return (printed);
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	int				printed;
	int				temp;

	va_start(args, str);
	printed = 0;
	while (*str)
	{
		if (*str == '%')
		{
			temp = print_arguments(args, *(str + 1));
			str++;
		}
		else
			temp = ft_print_char(*str);
		if (temp < 0)
			return (-1);
		printed += temp;
		str++;
	}
	va_end(args);
	return (printed);
}

/*#include <stdio.h>

int	main(void)
{
	int ft_print;
	int real;

	char c = 'P';
	char *str1 = "Hola";
	char *str2 = NULL;
	int x = -2147483648;
	unsigned int y = 4147483648;
	int z = 255;

	ft_print = ft_printf("Char: %c, Str: %s, Str(null): %s, Pointer: %p, 
	Decimal: %d, Integer: %i, Unsigned: %u, Hexa_low: %x, 
	Hexa_upper: %X, %% %k\n", c, str1, str2, str1, x, x, y, z, z);
	real = printf("Char: %c, Str: %s, Str(null): %s, Pointer: %p, 
	Decimal: %d, Integer: %i, Unsigned: %u, Hexa_low: %x, 
	Hexa_upper: %X, %% %k\n", c, str1, str2, str1, x, x, y, z, z);
	printf("ft_print: %i\n", ft_print);
	printf("real: %i\n", real);
}*/
