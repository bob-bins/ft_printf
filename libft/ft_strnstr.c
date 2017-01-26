/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 21:34:52 by mchen             #+#    #+#             */
/*   Updated: 2016/12/02 22:32:47 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t l_len;

	if (big == little)
		return ((char*)big);
	if ((l_len = ft_strlen(little)) == 0)
		return ((char*)big);
	while (*big)
	{
		if (len-- < l_len)
			break ;
		if (ft_strncmp(big, little, l_len) == 0)
			return ((char*)(big));
		big++;
	}
	return (NULL);
}
