/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:27:10 by mchen             #+#    #+#             */
/*   Updated: 2017/02/03 22:46:01 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	set_type_field(t_placehold *p, const char *e)
{
	if (*e && ft_strchr("sSpdDioOuUxXcCbfFeEgGaA", *e))
	{
		p->uppercase = (ft_strchr("XEGA", *e) ? 1 : p->uppercase);
		p->base = (*e == 'b' ? 2 : p->base);
		p->base = (ft_strchr("oO", *e) ? 8 : p->base);
		p->base = (ft_strchr("pxXaA", *e) ? 16 : p->base);
		p->exp_base = (ft_strchr("aA", *e) ? 2 : p->exp_base);
		p->exp_len = (ft_strchr("aA", *e) ? 1 : p->exp_len);
		p->exp_char = (ft_strchr("aA", *e) ? *e + 15 : p->exp_char);
		p->exp_char = (ft_strchr("eEgG", *e) ? 'e' + p->uppercase * 32 : p->exp_char);
		if (ft_strchr("DOUCS", *e))
		{
			if (p->length)
				free(p->length);
			p->length = ft_strdup("l");
		}
		p->signed_num = (ft_strchr("dDi", *e) ? 1 : p->signed_num);
		set_hash(p, e);
	}
	else
		p->prec = 1;
	p->sign = (!ft_strchr("dDifFfFeEgGaA", *e) ? 0 : p->sign);
	p->padding = (ft_strchr("pdDioOuUxXb", *e) && p->prec >= 0 &&
		p->leftalign == 0) ? ' ' : p->padding;
	p->type = *e;
}

void	set_flag_field(t_placehold *p, const char **e)
{
	while (1)
	{
		if (**e == '+')
			p->sign = '+';
		else if (**e == ' ')
			p->sign = (p->sign == 0 ? ' ' : p->sign);
		else if (**e == '-')
		{
			p->leftalign = 1;
			p->padding = ' ';
		}
		else if (**e == '0')
			p->padding = (p->leftalign == 0 ? '0' : p->padding);
		else if (**e == '#')
			p->hash = "#";
		else
			break ;
		(*e)++;
	}
}

void	set_width_field(t_placehold *p, const char **e, va_list a_list)
{
	if (**e == '*')
	{
		if ((p->width = va_arg(a_list, int)) < 0)
		{
			p->width = p->width * -1;
			p->leftalign = 1;
			p->padding = ' ';
		}
		(*e)++;
	}
	else if (**e >= '1' && **e <= '9')
	{
		while (**e >= '0' && **e <= '9')
		{
			p->width = p->width * 10 + **e - '0';
			(*e)++;
		}
	}
}

void	set_precision_field(t_placehold *p, const char **e, va_list a_list)
{
	if (**e == '.')
	{
		p->prec = 0;
		(*e)++;
		if (**e == '*')
		{
			p->prec = va_arg(a_list, int);
			if (p->prec < 0)
				p->prec = -1;
			(*e)++;
		}
		else
		{
			while (**e >= '0' && **e <= '9')
			{
				p->prec = p->prec * 10 + **e - '0';
				(*e)++;
			}
		}
	}
}

void	set_length_field(t_placehold *p, const char **e)
{
	if (**e && ft_strchr("hljzqL", **e))
	{
		(*e)++;
		if (**e == 'h' || **e == 'l')
			p->length = ft_strndup((*e)++ - 1, 2);
		else
			p->length = ft_strndup(*e - 1, 1);
	}
}
