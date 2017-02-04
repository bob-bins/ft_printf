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

unsigned short	ft_uintmax_len(uintmax_t num, unsigned short base)
{
	unsigned int	i;

	i = 0;
	while (num != 0 || i == 0)
	{
		i++;
		num = num / base;
	}
	return (i);
}
