/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 21:29:40 by mchen             #+#    #+#             */
/*   Updated: 2016/12/06 11:07:12 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t len;

	if (*little == 0)
		return ((char*)big);
	len = ft_strlen(little);
	while (*big)
	{
		if (ft_strncmp(big, little, len) == 0)
			return ((char*)(big));
		big++;
	}
	return (NULL);
}
