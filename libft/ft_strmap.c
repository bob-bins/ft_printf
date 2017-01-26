/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:44:43 by mchen             #+#    #+#             */
/*   Updated: 2016/12/01 20:12:13 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	char	*tmp;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = (char*)malloc(sizeof(*str) * len + 1);
	if (str)
	{
		tmp = str;
		while (len-- > 0)
			*tmp++ = f(*s++);
		*tmp = 0;
	}
	return (str);
}
