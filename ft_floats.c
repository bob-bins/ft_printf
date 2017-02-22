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

static long double  ft_uld_badround(long double ld, int precision, short base)
{
    long double m;
    long double c;
    int         i;

    if ((i = precision) != -1)
    {
        m = ft_uld_get_mantissa(ld, base);
        c = ld - m;
        while (i-- > 0)
            m *= base;
        if (ft_uld_get_mantissa(m, base) >= .5)
            m = m - ft_uld_get_mantissa(m, base) + 1.1;
        else
            m = m - ft_uld_get_mantissa(m, base) + .1;
        while (++i < precision)
            m /= base;
        return (c + m);
    }
    return (ld);
}

static char         *ft_uld_mantissatoa(long double ld, int precision, short base)
{
    int     i;
    char    *s;

    s = ft_memalloc(sizeof(*s));
    while (precision > 0 || (precision < 0 && ld))
    {
        if (precision)
            precision--;
        i = ld * base;
        s = ft_strjoin_free(s, ft_uitoa_base(i, base, 0, 1));
        ld *= base;
        ld -= i;
    }
    return (s);
}
static char         *ft_uld_itoa(long double ld, int sigfig, int precision, short base)
{
    long double u;
    uintmax_t   d;
    char        *s;

    u = 1;
    while (u < ld / base)
        u *= base;
    s = ft_memalloc(sizeof(*s));
    while (sigfig && (u >= 1 || !ft_strlen(s)))
    {
        d = (uintmax_t)(ld / u);
        s = ft_strjoin_free(s, ft_uitoa_base(d, base, 0, 1));
        if (!(*s == '0' && ft_strlen(s) == 1))
            sigfig--;
        ld -= d * u;
        u /= base;
    }
    if (sigfig && (precision > 0 || precision == -1) && ld)
    {
        precision = sigfig > 0 ? sigfig : precision;
        s = ft_strjoin_free(s, ft_strdup("."));
        s = ft_strjoin_free(s, ft_uld_mantissatoa(ld, precision, base));
    }
    return (s);
}

static char         *ft_printf_ftoa_handler(t_placehold *p, long double ld)
{
    long double d;
    char        *s;
    short       c;

    if (ft_strchr("fF", p->type))
        s = ft_uld_itoa(ft_uld_badround(ld, p->prec, p->base), p->sigfig,
            p->prec, p->base);
    else if ((d = 1))
    {
        c = 0;
        if (ld >= 1)
            while (ld / d >= p->exp_base && ++c)
                d *= p->exp_base;
        else
            while (ld && ld / d < 1 && ++c)
                d /= p->exp_base;
        s = ft_uld_itoa(ft_uld_badround(ld / d, p->prec, p->base), p->sigfig,
            p->prec, p->base);
        s = ft_strjoin_free(s, ft_strdup(ft_memset(ft_memalloc(2), p->exp_char,
            1)));
        s = ft_strjoin_free(s, (ld >= 1 || ld == 0) ? ft_strdup("+") :
            ft_strdup("-"));
        s = ft_strjoin_free(s, ft_uitoa_base(c, 10, 0, p->exp_len));
    }
    return (s = p->uppercase ? ft_strucase(s) : s);
}

char                *ft_printf_ftoa(t_placehold *p, va_list a_list)
{
    long double ld;
    char        *s;

    ld = 0;
    if (p->length && !ft_strcmp(p->length, "L"))
        ld = va_arg(a_list, long double);
    else
        ld += va_arg(a_list, double);
    p->sign = (ld < 0 ? '-' : p->sign);
    ld = (ld < 0 ? -ld : ld);
    p->prec = (p->prec == -1 && !ft_strchr("aA", p->type) ? 6 : p->prec);
    if (ft_strchr("gG", p->type))
    {
        p->prec = (p->prec == 0 ? 1 : p->prec);
        p->sigfig = p->prec;
        if ((ld && ld < .00001) || ft_ld_integerpower(p->base, p->prec) <= ld)
            p->type -= 2;
        else
            p->type -= 1;
        s = ft_printf_ftoa_handler(p, ld);
        s = ft_chrrepl_trailing(ft_chrrepl_trailing(s, '0', 0), '.', 0);
    }
    else
        s = ft_printf_ftoa_handler(p, ld);
    return (s);
}
