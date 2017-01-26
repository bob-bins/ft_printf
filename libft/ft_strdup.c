/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 20:00:23 by mchen             #+#    #+#             */
/*   Updated: 2016/12/06 10:58:23 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*str;

	if (s1)
	{
		len = ft_strlen(s1);
		str = malloc(sizeof(*str) * len + 1);
		if (str)
			str = ft_strcpy(str, s1);
	}
	else
		str = NULL;
	return (str);
}
