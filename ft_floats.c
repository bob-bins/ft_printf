#include "includes/ft_printf.h"

long double ft_ld_get_mantissa(long double ld)
{
    long double u;
    uintmax_t   d;
    
    u = 1;
    while (u < ld / 1000000000)
        u *= 1000000000;
    while (ld >= 1)
    {
        d = (uintmax_t)(ld / u);
        ld -= d * u;
        u /= 1000000000;
    }
    return (ld);
}

long double ft_ld_badround(long double ld, int precision)
{
    long double m;
    long double c;
    int         i;
    
    m = ft_ld_get_mantissa(ld);
    c = ld - m;
    i = precision;
    while (i-- > 0)
        m *= 10;
    if (ft_ld_get_mantissa(m) >= .5)
        m = m - ft_ld_get_mantissa(m) + 1.5;
    else
        m = m - ft_ld_get_mantissa(m) + .5;
    while (++i < precision)
        m /= 10;
    return (c + m);
}

char    *ft_uld_mantissatoa(long double ld, int precision, short base)
{
    int     i;
    char    *s;

    s = ft_memalloc(sizeof(*s));
    while (precision-- > 0)
    {
        i = ld * base;
        s = ft_strjoin(s, ft_itoa_base(i, base));
        ld *= base;
        ld -= i;
    }
    return (s);
}

char    *ft_uld_itoa(long double ld, int precision, short base)
{
    long double u;
    uintmax_t   d;
    char        *s;

    u = 1;
    while (u < ld / 100000000 * base)
        u *= 100000000 * base;
    s = ft_memalloc(sizeof(*s));
    while (ld >= 1 || !ft_strlen(s))
    {
        d = (uintmax_t)(ld / u);
        s = ft_strjoin(s, ft_uitoa_base(d, base, 0, 1));
        ld -= d * u;
        u /= 100000000 * base;
    }
    if (precision > 0)
    {
        s = ft_strjoin(s, ".");
        s = ft_strjoin(s, ft_uld_mantissatoa(ld, precision, base));
    }
    return (s);
}

char    *ft_printf_ftoa_handler(t_placehold *p, long double ld, int precision, short base)
{
    long double d;
    char        *s;
    
    if (ft_strchr("fF", p->type))
        s = ft_uld_itoa(ft_ld_badround(ld, p->precision), p->precision, p->base);
    else if (ft_strchr("eE", p->type))
    {
        d = 1;
        if (ld >= 1)
        {
            while (ld / d >= 10)
                d *= 10;
            s = ft_uld_itoa(ft_ld_badround(ld / d, p->precision), p->precision, p->base);
        }
        else
        {
            while (ld && ld * d < 1)
                d *= 10;
            s = ft_uld_itoa(ft_ld_badround(ld * d, p->precision), p->precision, p->base);
        }
        s = ft_strjoin(s, p->type == 'e' ? "e" : "E");
        s = ft_strjoin(s, ld >= 1 ? "+" : "-");
        s = ft_strjoin(s, ft_uitoa_base(ft_uintmax_len(d, 10) - 1, p->base, 0, 2));
    }
    return (s);
}

char    *ft_printf_ftoa(t_placehold *p, va_list a_list)
{
    long double     ld;
    char            *s;

    ld = 0;
    if (p->length && !ft_strcmp(p->length, "L"))
        ld = va_arg(a_list, long double);
    else
        ld += va_arg(a_list, double);
    p->sign = (ld < 0 ? '-' : p->sign);
    ld = (ld < 0 ? -ld : ld);
    p->precision = (p->precision == -1 ? 6 : p->precision);
    if (ft_strchr("gG", p->type))
    {
        if (ld && ld < .00001 || ft_ld_integerpower(10, p->precision) <= ld) //100000.00 precision 5 is 100000 so thisll convert to e
            p->type -= 2;
        else
            p->type -= 1;
    }
    s = ft_printf_ftoa_handler(p, ld, p->precision, p->base);
    p->precision = ft_strlen(s);
    return (s);
}