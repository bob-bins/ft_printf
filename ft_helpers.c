/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:26:07 by mchen             #+#    #+#             */
/*   Updated: 2017/02/03 22:47:08 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

unsigned short	ft_uintmax_len(uintmax_t num, unsigned short base)
{
	unsigned int	i;

	i = 0;
	while (num != 0 || i == 0)
	{
		i++;
		num = num / base;
	}
	return (i);
}

char			*ft_uitoa_base(uintmax_t value, unsigned short base,
								unsigned short uppercase, int digits)
{
	char	*ret;
	char	*dig;
	int		i;

	dig = "0123456789abcdef0123456789ABCDEF";
	dig += 16 * uppercase;
	if ((ret = malloc(sizeof(*ret) * (digits + 1))))
	{
		i = 0;
		while (value != 0 || (i == 0 && digits != 0) || i < digits)
		{
			ret[i++] = dig[value % base];
			value /= base;
		}
		ret[i] = 0;
		ft_strrev(ret);
	}
	return (ret);
}

char			*ft_wctos(wchar_t c)
{
	char	*s;
	char	*e;

	s = ft_memalloc(sizeof(*s) * 5);
	e = s;
	if (c <= 0x7F)
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

char			*ft_wtoc_strndup(wchar_t *w, size_t n)
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

char			*ft_wtoc_strdup(wchar_t *w)
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
