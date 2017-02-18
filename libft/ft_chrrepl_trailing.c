/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrrepl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:51:16 by mchen             #+#    #+#             */
/*   Updated: 2016/12/17 15:04:16 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chrrepl_trailing(char *s, char c, char r)
{
	char *str;
	char a;

	str = s;
	if (s && *s)
	{
		a = *s;
		*s = 0;
		s++;
		while (*s)
			s++;
		if (str - s)
			while (*(--s) == c)
				*s = r;
		*str = a;
	}
	return (str);
}
