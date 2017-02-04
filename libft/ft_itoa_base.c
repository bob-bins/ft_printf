/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 09:02:04 by exam              #+#    #+#             */
/*   Updated: 2016/12/06 11:35:02 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_base(int value, int base)
{
	char	*num;
	char	*temp;
	char	*dig;
	int		sign;

	dig = "0123456789ABCDEF";
	num = (char*)malloc(sizeof(*num) * ft_itoalen(value, base));
	if (num)
	{
		sign = 1;
		if (value < 0)
			sign = -1;
		temp = num;
		while (value || temp == num)
		{
			*temp = dig[value % base * sign];
			value /= base;
			temp++;
		}
		if (base == 10 && sign == -1)
			*temp++ = '-';
		*temp = 0;
		ft_strrev(num);
	}
	return (num);
}
