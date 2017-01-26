/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 23:10:06 by mchen             #+#    #+#             */
/*   Updated: 2016/12/04 19:57:05 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_factorial(int nb)
{
	int i;
	int factorial;

	factorial = 1;
	i = 0;
	if (nb >= 0 && nb <= 12)
		while (i++ < nb)
			factorial *= i;
	else
		factorial = 0;
	return (factorial);
}
