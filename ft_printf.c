/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:27:23 by mchen             #+#    #+#             */
/*   Updated: 2017/02/05 17:37:58 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int	ft_vfdprintf(int fd, const char *format, va_list a_list)
{
	t_placehold	*p;
	const char	*e;
	size_t		count;

	count = 0;
	if (format)
	{
		p = malloc(sizeof(*p));
		e = format;
		while (*format)
		{
			if (*format == '%')
			{
				e = format + 1;
				eval_fields(p, &e, a_list);
				count += print_eval(fd, p, a_list, count);
				format = e;
			}
			else
				count += ft_putchar_fd(*(format), fd);
			format += *format ? 1 : 0;
		}
		free(p);
	}
	return (count);
}

int	ft_fdprintf(int fd, const char *format, ...)
{
	va_list a_list;
	size_t	count;

	va_start(a_list, format);
	count = ft_vfdprintf(fd, format, a_list);
	va_end(a_list);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list a_list;
	size_t	count;

	va_start(a_list, format);
	count = ft_vfdprintf(1, format, a_list);
	va_end(a_list);
	return (count);
}

/*
#include <locale.h>
#include <stdio.h>
#include <limits.h>
int main()
{
	setlocale(LC_ALL, "");
	wchar_t w = 8805;
	printf("::%d\n", ft_printf("{%05.c}", 0));
	printf("::%d\n", printf("{%05.c}", 0));
	return (0);
}*/