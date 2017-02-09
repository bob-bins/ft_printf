/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:27:23 by mchen             #+#    #+#             */
/*   Updated: 2017/02/06 21:02:12 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
# include <locale.h>

int	ft_vfdprintf(int fd, const char *format, va_list a_list)
{
	t_placehold	*p;
	const char	*e;
	size_t		count;

	setlocale(LC_CTYPE, "");
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
#include <limits.h>
#include <stdio.h>
# include <locale.h>
int main()
{
    setlocale(LC_CTYPE, "");
	int i = 250;//1000;//0xA2;
	ft_printf("%lc:\n", i);
	printf("%lc:\n", i);
	return 0;
}
*/
