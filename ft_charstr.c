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

char	*ft_wctos(wchar_t c)
{
	char	*s;
	char	*e;

	s = ft_memalloc(sizeof(*s) * 5);
	if ((e = s) && c <= 0x7F)
		*e++ = c;
	else if (c <= 0x7FF)
	{
		*e++ = (c >> 6) + 0xC0;
		*e++ = (c & 0x3F) + 0x80;
	}
	else if (c <= 0xFFFF)
	{
		*e++ = (c >> 12) + 0xE0;
		*e++ = ((c >> 6) & 0x3F) + 0x80;
		*e++ = (c & 0x3F) + 0x80;
	}
	else if (c <= 0x10FFFF)
	{
		*e++ = (c >> 18) + 0xF0;
		*e++ = ((c >> 12) & 0x3F) + 0x80;
		*e++ = ((c >> 6) & 0x3F) + 0x80;
		*e++ = (c & 0x3F) + 0x80;
	}
	return (s);
}

char	*ft_wtoc_strndup(wchar_t *w, size_t n)
{
	char	*s;
	char	*t;
	int		len;

	if (w && (s = ft_memalloc(sizeof(*s) * (n + 1))))
	{
		len = n;
		while (*w)
		{
			t = ft_wctos(*w++);
			len -= ft_strlen(t);
			if (len < 0)
				break ;
			s = ft_strcat(s, t);
		}
	}
	else
		s = NULL;
	return (s);
}

char	*ft_wtoc_strdup(wchar_t *w)
{
	wchar_t	*t;
	size_t	len;
	short	size;

	len = 0;
	size = sizeof(wchar_t) / sizeof(char);
	t = w;
	if (t)
		while (*t++)
			len += size;
	return (ft_wtoc_strndup(w, len));
}

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
