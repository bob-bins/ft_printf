#include "includes/ft_printf.h"

long double ft_get_mantissa(long double ld)
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
    
    m = ft_get_mantissa(ld);
    c = ld - m;
    i = precision;
    while (i-- > 0)
        m *= 10;
    if (ft_get_mantissa(m) >= .5)
        m = m - ft_get_mantissa(m) + 1.5;
    else
        m = m - ft_get_mantissa(m) + .5;
    while (++i < precision)
        m /= 10;
    return (c + m);
}

char    *ft_ulfdecimaltoa(long double ld, int precision)
{
    int     i;
    char    *s;

    s = ft_memalloc(sizeof(*s));
    while (precision-- > 0)
    {
        i = ld * 10;
        s = ft_strjoin(s, ft_itoa_base(i, 10));
        ld *= 10;
        ld -= i;
    }
    return (s);
}

char    *ft_ulfitoa(long double ld, int precision)
{
    long double u;
    uintmax_t   d;
    char        *s; 

    u = 1;
    while (u < ld / 1000000000)
        u *= 1000000000;
    s = ft_memalloc(sizeof(*s));
    while (ld >= 1 || !ft_strlen(s))
    {
        d = (uintmax_t)(ld / u);
        s = ft_strjoin(s, ft_uitoa_base(d, 10, 0, 1));
        ld -= d * u;
        u /= 1000000000;
    }

    if (precision > 0)
    {
        s = ft_strjoin(s, ".");
        s = ft_strjoin(s, ft_ulfdecimaltoa(ld, precision));
    }
    return (s);
}

char    *ft_printf_ftoa(t_placehold *p, va_list a_list)
{
    long double ld;
    char        *s;

    ld = 0;
    if (p->length && !ft_strcmp(p->length, "L"))
        ld = va_arg(a_list, long double);
    else
        ld += va_arg(a_list, double);
    if (ld < 0)
    {
        p->sign = '-';
        ld = -ld;
    }
    p->precision = (p->precision == -1 ? 6 : p->precision);
    ld = ft_ld_badround(ld, p->precision);
    s = ft_ulfitoa(ld, p->precision);
    p->precision = ft_strlen(s);
    return (s);
}