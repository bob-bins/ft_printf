/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:26:48 by mchen             #+#    #+#             */
/*   Updated: 2017/02/03 22:32:54 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	set_hash(t_placehold *p, const char *e)
{
	if (p->hash || *e == 'p')
	{
		if (ft_strchr("oO", *e))
			p->hash = "0";
		else if (ft_strchr("pxb", *e))
			p->hash = "0x";
		else if (ft_strchr("X", *e))
			p->hash = "0X";
		else
		{
			p->hash = NULL;
			return ;
		}
		p->sign = 0;
	}
}

void	init_placehold(t_placehold *p)
{
	p->leftalign = 0;
	p->sign = 0;
	p->padding = ' ';
	p->hash = NULL;
	p->width = 0;
	p->precision = -1;
	p->length = NULL;
	p->type = 0;
	p->base = 10;
	p->signed_num = 0;
	p->uppercase = 0;
}

void	eval_fields(t_placehold *p, const char **e, va_list a_list)
{
	init_placehold(p);
	set_flag_field(p, e);
	set_width_field(p, e, a_list);
	set_precision_field(p, e, a_list);
	set_length_field(p, e);
	set_type_field(p, *e);
}

size_t	ft_puteval(int fd, t_placehold *p, char *str, size_t slen)
{
	size_t	count;

	count = 0;
	if (p->padding == '0')
	{
		count += ft_putstr_fd(p->hash, fd);
		count += ft_putchar_fd(p->sign, fd);
	}
	if (!p->leftalign)
		count += ft_putnchar_fd(fd, p->padding, p->width - slen);
	if (p->padding == ' ')
	{
		count += ft_putstr_fd(p->hash, fd);
		count += ft_putchar_fd(p->sign, fd);
	}
	count += ft_putnstr_fd(fd, str, p->precision == -1 ? slen : p->precision);
	count += (ft_strchr("cC", p->type) && ft_strlen(str) == 0) ? 1 : 0;
	if (p->leftalign)
		count += ft_putnchar_fd(fd, p->padding, p->width - slen);
	if (p->length)
		free(p->length);
	return (count);
}

size_t	print_eval(int fd, t_placehold *p, va_list a_list, size_t cnt)
{
	char	*str;
	size_t	slen;
	size_t	count;

	str = NULL;
	if (ft_strchr("dDioOuUxXb", p->type))
		str = ft_printf_itoa_base(p, a_list);
	else if (ft_strchr("cC", p->type))
		str = ft_printf_ctos(p, a_list);
	else if (ft_strchr("sS", p->type))
		str = ft_printf_str(p, p->precision, a_list);
	else if (p->type == 'p')
		str = ft_printf_itoa_base(p, a_list);
	else if (p->type == '%')
		str = ft_strdup("%");
	else if (p->type == 'n')
		*va_arg(a_list, int*) = cnt;
	if (ft_strchr("nz", p->type))
		return (0);
	slen = (ft_strchr("cC", p->type) ? 1 : ft_strlen(str)) +
			ft_strlen(p->hash) + (p->sign != 0 ? 1 : 0);
	count = ft_puteval(fd, p, str, slen);
	if (str)
		free(str);
	return (count);
}
