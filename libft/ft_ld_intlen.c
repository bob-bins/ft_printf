/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintmax_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:26:07 by mchen             #+#    #+#             */
/*   Updated: 2017/02/03 22:47:08 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned short	ft_ld_intlen(long double ld, unsigned short base)
{
	unsigned int	i;

	i = 0;
	while (ld >= 1 || ld <= -1 || i == 0)
	{
		i++;
		ld /= base;
	}
	return (i);
}
