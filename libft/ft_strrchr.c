/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 21:21:22 by mchen             #+#    #+#             */
/*   Updated: 2016/11/29 22:40:34 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char *str;

	str = 0;
	while (*s)
	{
		if (*s == c)
			str = (char*)s;
		s++;
	}
	if (c == 0)
		return ((char*)s);
	return (str);
}
