/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 22:45:23 by mchen             #+#    #+#             */
/*   Updated: 2017/02/17 22:45:39 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

long double ft_uld_get_mantissa(long double ld, short base)
{
    long double u;
    uintmax_t   d;

    u = 1;
    while (u < ld / ft_ld_integerpower(base, 8))
        u *= ft_ld_integerpower(base, 8);
    while (ld >= 1)
    {
        d = (uintmax_t)(ld / u);
        ld -= d * u;
        u /= ft_ld_integerpower(base, 8);
    }
    return (ld);
}
