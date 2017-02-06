/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:33:23 by mchen             #+#    #+#             */
/*   Updated: 2017/02/05 17:39:12 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnstr_fd(int fd, char *s, int n)
{
	int len;

	len = ft_strlen(s);
	if (s)
	{
		if (n < len)
			len = n;
		write(fd, s, len);
	}
	return (len);
}
