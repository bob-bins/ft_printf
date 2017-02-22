/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:26:27 by mchen             #+#    #+#             */
/*   Updated: 2017/02/06 22:04:42 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

/*
** Converts wide character to a char* using UTF-8 formatting
*/

static char	*ft_wctos(wchar_t c)
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

/*
** Converts each wide character in w to UTF-8 string and concatenates it to the
** return string
*/

static char	*ft_wtoc_strndup(wchar_t *w, size_t n)
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
			if (t)
				free(t);
		}
	}
	else
		s = NULL;
	return (s);
}

/*
** Finds the num of bits of w, then calls ft_wtoc_strndup on that size
*/

static char	*ft_wtoc_strdup(wchar_t *w)
{
	wchar_t	*t;
	size_t	len;

	len = 0;
	t = w;
	if (t)
		while (*t++)
			len += sizeof(wchar_t);
	return (ft_wtoc_strndup(w, len));
}

/*
** Handles %cC
*/

char		*ft_printf_ctos(t_placehold *p, va_list a_list)
{
	char	*s;

	if (p->length != NULL && !ft_strcmp(p->length, "l") && MB_CUR_MAX > 1)
		s = ft_wctos((wchar_t)va_arg(a_list, wint_t));
	else
	{
		s = ft_memalloc(sizeof(*s) * 2);
		*s = (unsigned char)va_arg(a_list, int);
	}
	return (s);
}

/*
** Handles %sS
*/

char		*ft_printf_str(t_placehold *p, size_t n, va_list a_list)
{
	char	*s;

	if (p->length != NULL && !ft_strcmp(p->length, "l"))
	{
		if (p->prec >= 0)
			s = ft_wtoc_strndup(va_arg(a_list, wchar_t*), n);
		else
			s = ft_wtoc_strdup(va_arg(a_list, wchar_t*));
	}
	else
	{
		if (p->prec >= 0)
			s = ft_strndup(va_arg(a_list, char*), n);
		else
			s = ft_strdup(va_arg(a_list, char*));
	}
	if (!s && p->prec != 0)
		s = ft_strdup("(null)");
	else if (!s)
		s = ft_memalloc(sizeof(*s));
	return (s);
}
