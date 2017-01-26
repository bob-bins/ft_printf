/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:40:15 by mchen             #+#    #+#             */
/*   Updated: 2016/12/01 19:41:13 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*ret;
	int		sign;
	int		len;

	len = ft_itoalen(n, 10);
	ret = (char*)malloc(sizeof(*ret) * len + 1);
	if (ret)
	{
		sign = 1;
		if (n < 0)
			sign = -1;
		ret[len--] = 0;
		if (n == 0)
			ret[len] = '0';
		while (n != 0)
		{
			ret[len--] = (n % 10) * sign + '0';
			n = n / 10;
		}
		if (sign == -1)
			ret[len] = '-';
	}
	return (ret);
}
