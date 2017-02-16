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
		while (*e)
		{
			if (*e == '%')
			{
				count += write(fd, format, e++ - format);
				eval_fields(p, &e, a_list);
				count += print_eval(fd, p, a_list, count);
				format = e + 1;
			}
			e += *e ? 1 : 0;
			if (!*e)
				count += ft_putnstr_fd(fd, format, e - format);
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

#include <limits.h>
#include <stdio.h>
# include <locale.h>
int main()
{
    setlocale(LC_CTYPE, "");
    ft_printf("ft_printf: %d % 0.10d %li %%\n", 13, 18, 3049600000);
       printf("ac_printf: %d % 0.10d %li %%\n", 13, 18, 3049600000);
    ft_printf("ft_printf: %d %-#*lx %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d %-#*lx %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d % 0*.10ld %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d % 0*.10ld %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d %-*lx %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d %-*lx %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d %-*lo %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d %-*lo %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d -%6c- %i %%\n", 13, 0, -4078);
       printf("ac_printf: %d -%6c- %i %%\n", 13, 0, -4078);
    ft_printf("ft_printf: %d %6lc %i %%\n", 13, 180, -4078);
       printf("ac_printf: %d %6lc %i %%\n", 13, 180, -4078);
    ft_printf("ft_printf: %d %-10c %i %%\n", 13, 50, -4078);
       printf("ac_printf: %d %-10c %i %%\n", 13, 50, -4078);
    ft_printf("ft_printf: %d %-*c %i %%\n", 13, 18, 333, -4078);
       printf("ac_printf: %d %-*c %i %%\n", 13, 18, 333, -4078);
    ft_printf("ft_printf: %d %-*.5s %i %%\n", 13, 18, "testing 123", -4078);
       printf("ac_printf: %d %-*.5s %i %%\n", 13, 18, "testing 123", -4078);
    ft_printf("ft_printf: %d %-*.13ls %i %5.5%\n", 13, 18, L"ζέες καὶ μυρτιὲς δὲν θὰ βρῶ πιὰ στὸ χ", -4078);
       printf("ac_printf: %d %-*.13ls %i %5.5%\n", 13, 18, L"ζέες καὶ μυρτιὲς δὲν θὰ βρῶ πιὰ στὸ χ", -4078);
    ft_printf("ft_printf: %d %-*.13s %i %5.5%\n", 13, 18, "", -4078);
       printf("ac_printf: %d %-*.13s %i %5.5%\n", 13, 18, "", -4078);
    ft_printf("ft_printf: %d %*.13s %i %5.5%\n", 13, 18, NULL, -4078);
       printf("ac_printf: %d %*.13s %i %5.5%\n", 13, 18, NULL, -4078);
    ft_printf("ft_printf: %d %-*.13ls %i %5.5%\n", 13, 18, L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B", -4078);
       printf("ac_printf: %d %-*.13ls %i %5.5%\n", 13, 18, L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B", -4078);
    ft_printf("ft_printf: %S\n", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
       printf("ac_printf: %S\n", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
}
