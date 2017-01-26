/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 21:54:00 by mchen             #+#    #+#             */
/*   Updated: 2016/12/04 16:16:09 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char *e;
	char *str;
	char *tmp;

	if (!s)
		return (NULL);
	while (*s && (*s == ' ' || *s == '\t' || *s == '\n'))
		s++;
	e = (char*)s;
	if (*e)
	{
		while (*e)
			e++;
		while (*(e - 1) == ' ' || *(e - 1) == '\t' || *(e - 1) == '\n')
			e--;
	}
	str = (char*)malloc(sizeof(*str) * (e - s + 1));
	if (str)
	{
		tmp = str;
		while (s < e)
			*tmp++ = *s++;
		*tmp = 0;
	}
	return (str);
}
