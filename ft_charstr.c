/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:26:27 by mchen             #+#    #+#             */
/*   Updated: 2017/02/03 22:30:26 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

char	*ft_printf_ctos(t_placehold *p, va_list a_list)
{
	wchar_t c;

	if (p->length != NULL && !ft_strcmp(p->length, "l"))
		c = (wchar_t)va_arg(a_list, wint_t);
	else
		c = (char)(unsigned char)va_arg(a_list, int);
	return (ft_wctos(c));
}

char	*ft_printf_str(t_placehold *p, size_t n, va_list a_list)
{
	char	*s;

	if (p->length != NULL && !ft_strcmp(p->length, "l"))
	{
		if (p->precision >= 0)
			s = ft_wtoc_strndup(va_arg(a_list, wchar_t*), n);
		else
			s = ft_wtoc_strdup(va_arg(a_list, wchar_t*));
	}
	else
	{
		if (p->precision >= 0)
			s = ft_strndup(va_arg(a_list, char*), n);
		else
			s = ft_strdup(va_arg(a_list, char*));
	}
	if (!s)
		s = ft_strdup("(null)");
	return (s);
}
