/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnwstr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:36:04 by mchen             #+#    #+#             */
/*   Updated: 2017/02/03 22:43:09 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnwstr_fd(int fd, wchar_t *s, int n)
{
	int count;

	count = 0;
	if (n > 0)
	{
		while (*s && n-- > 0)
		{
			ft_putwchar_fd(*s++, fd);
			count++;
		}
	}
	return (count);
}
