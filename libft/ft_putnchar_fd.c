/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:37:27 by mchen             #+#    #+#             */
/*   Updated: 2017/02/03 22:38:05 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnchar_fd(int fd, char c, int n)
{
	int count;

	count = 0;
	while (n-- > 0)
	{
		write(fd, &c, 1);
		count++;
	}
	return (count);
}