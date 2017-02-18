/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 23:04:37 by mchen             #+#    #+#             */
/*   Updated: 2016/12/06 11:17:23 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long double	ft_ld_integerpower(long double nb, long double power)
{
	long double i;
	long double num;

	num = nb;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	i = 1;
	while (i++ < power)
		num *= nb;
	return (num);
}
