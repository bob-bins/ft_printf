/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 20:00:23 by mchen             #+#    #+#             */
/*   Updated: 2017/01/25 20:45:04 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	char	*str;

	if (s1)
	{
		str = malloc(sizeof(*str) * (len + 1));
		if (str)
			str = ft_strncpy(str, s1, len);
	}
	else
		str = NULL;
	return (str);
}
