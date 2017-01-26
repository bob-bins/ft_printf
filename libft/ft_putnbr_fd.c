/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:44:19 by mchen             #+#    #+#             */
/*   Updated: 2016/12/01 21:12:44 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int sign;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		ft_putchar_fd('-', fd);
	}
	if (n < 10 && n > -10)
		ft_putchar_fd(n * sign + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10 * sign, fd);
		ft_putnbr_fd(n % 10 * sign, fd);
	}
}
