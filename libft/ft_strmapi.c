/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:45:24 by mchen             #+#    #+#             */
/*   Updated: 2016/12/01 20:11:57 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	str = (char*)malloc(sizeof(*str) * len + 1);
	if (str)
	{
		i = -1;
		while (++i < len)
			str[i] = f(i, *s++);
		str[i] = 0;
	}
	return (str);
}
