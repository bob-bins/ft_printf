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
	if (e = format)
	{
		p = malloc(sizeof(*p));
		while (*e)
		{
			if (*e == '%')
			{
				count += ft_putnstr_fd(fd, format, e++ - format);
				eval_fields(p, &e, a_list);
				count += print_eval(fd, p, a_list, count);
				format = e + 1;
			}
			if (!*(e += *e ? 1 : 0))
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

/*#include <limits.h>
#include <stdio.h>
# include <locale.h>
int main()
{
    setlocale(LC_CTYPE, "");
    ft_printf("ft_printf: %d % 0.10d %li %%\n", 13, 18, 3049600000);
       printf("ac_printf: %d % 0.10d %li %%\n", 13, 18, 3049600000);
    ft_printf("ft_printf: %d %-#*lx %i %%\n", 13, -18, 3049600000, -4078);
       printf("ac_printf: %d %-#*lx %i %%\n", 13, -18, 3049600000, -4078);
    ft_printf("ft_printf: %d % 0*.10ld %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d % 0*.10ld %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d %-*lx %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d %-*lx %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d %-*lo %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d %-*lo %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d -%6c- %i %%\n", 13, 0, -4078);
       printf("ac_printf: %d -%6c- %i %%\n", 13, 0, -4078);
    ft_printf("ft_printf: %d %6c %i %%\n", 13, L'¥', -4078);
       printf("ac_printf: %d %6c %i %%\n", 13, L'¥', -4078);
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
    
	double d = .19487534534367567;
	printf("pp%.15a\n", .75);
	ft_printf("ft%.15a\n", .75);
	printf("pp%.a\n", d);
	ft_printf("ft%.a\n", d);
	printf("pp%.15a\n", d);
	ft_printf("ft%.15a\n", d);
	printf("pp%.5a\n", d);
	ft_printf("ft%.5a\n", d);
	printf("pp{%A}\n", 1.42);
	ft_printf("ft{%A}\n", 1.42);
	printf("pp{%.6a}\n", 1.42);
	ft_printf("ft{%.6a}\n", 1.42);
	printf("pp{%.6a}\n", 0.0);
	ft_printf("ft{%.6a}\n", 0.0);
	printf("pp%.15g\n", d);
	ft_printf("ft%.15g\n", d);
	printf("pp%.5g\n", d);
	ft_printf("ft%.5g\n", d);
	printf("pp{%g}\n", 1.42);
	ft_printf("ft{%g}\n", 1.42);
	printf("pp{%.6G}\n", 1.42);
	ft_printf("ft{%.6G}\n", 1.42);
	printf("pp{%.6G}\n", 0.0);
	ft_printf("ft{%.6G}\n", 0.0);
	printf("pp%.15f\n", d);
	ft_printf("ft%.15f\n", d);
	printf("pp%.5f\n", d);
	ft_printf("ft%.5f\n", d);
	printf("pp{%f}\n", 1.42);
	ft_printf("ft{%f}\n", 1.42);
	printf("pp{%.6F}\n", 1.42);
	ft_printf("ft{%.6F}\n", 1.42);
	printf("pp{%.6F}\n", 0.0);
	ft_printf("ft{%.6F}\n", 0.0);
	printf("pp%.15g\n", d);
	ft_printf("ft%.15g\n", d);
	printf("pp%.5g\n", d);
	ft_printf("ft%.5g\n", d);
	printf("pp{%g}\n", 1.42);
	ft_printf("ft{%g}\n", 1.42);
	printf("pp{%.6G}\n", 1.42);
	ft_printf("ft{%.6G}\n", 1.42);
	printf("pp{%.6G}\n", 0.0);
	ft_printf("ft{%.6G}\n", 0.0);
	//printf("%lc:\n", i);
	//printf("pp%.15f\n", 1.0/0);
	return 0;
}
*/