/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:34:26 by bgrosjea          #+#    #+#             */
/*   Updated: 2023/12/12 19:34:38 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_format(const char format, va_list args)
{
	int	printed;

	printed = 0;
	if (format == 'c')
		printed = ft_printchar(va_arg(args, int));
	else if (format == 's')
		printed = ft_prints(va_arg(args, char *));
	else if (format == 'p')
		printed = ft_printp(va_arg(args, uintptr_t));
	else if (format == 'd')
		printed = ft_printnbr(va_arg(args, int));
	else if (format == 'i')
		printed = ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		printed = ft_printunbr(va_arg(args, unsigned int));
	else if (format == 'x')
		printed = ft_printhexlow(va_arg(args, unsigned int));
	else if (format == 'X')
		printed = ft_printhexup(va_arg(args, unsigned int));
	else if (format == '%')
		printed = ft_printchar('%');
	return (printed);
}

int	ft_splitprint(const char *str, va_list args)
{
	int		printed;
	int		tmp;

	printed = 0;
	while (*str)
	{
		if (*str == '%')
		{
			tmp = ft_format(*(str + 1), args);
			if (tmp == -1)
				return (-1);
			printed += tmp;
			str++;
		}
		else
		{
			ft_printchar(*str);
			printed++;
		}
		str++;
	}
	return (printed);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		printed;

	printed = 0;
	va_start(args, str);
	printed = ft_splitprint(str, args);
	if (printed == -1)
		return (-1);
	va_end(args);
	return (printed);
}
