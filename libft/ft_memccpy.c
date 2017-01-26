/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:01:32 by mchen             #+#    #+#             */
/*   Updated: 2016/12/06 10:55:54 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (n)
	{
		d = (unsigned char*)dst;
		s = (unsigned char*)src;
		while (n-- != 0)
			if ((*d++ = *s++) == (unsigned char)c)
				return (d);
	}
	return (NULL);
}
