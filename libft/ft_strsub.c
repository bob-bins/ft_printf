/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 21:51:04 by mchen             #+#    #+#             */
/*   Updated: 2016/12/01 19:29:46 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	str = (char*)malloc(sizeof(*str) * len + 1);
	if (str && s)
	{
		i = 0;
		while (i < len)
			str[i++] = s[start++];
		str[i] = 0;
	}
	return (str);
}
