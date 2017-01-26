/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 21:08:00 by mchen             #+#    #+#             */
/*   Updated: 2016/12/06 11:06:00 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	int			n;
	int			dlength;

	d = dst;
	n = size;
	while (*d && n--)
		d++;
	dlength = d - dst;
	n = size - dlength;
	if (n == 0)
		return (dlength + ft_strlen(src));
	s = src;
	while (*s)
	{
		if (--n > 0)
			*d++ = *s;
		s++;
	}
	*d = 0;
	return (dlength + s - src);
}
