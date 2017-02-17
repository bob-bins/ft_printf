#include "includes/ft_printf.h"

char    *ft_ulfdecimaltoa(long double ld, int precision)
{
    int     i;
    char    *s;
    
    s = ft_memalloc(sizeof(*s));
    while (precision-- > 0)
    {
        i = ld * 10;
       /* if (precision == 0) //only rounds digit rather than entire number. bad bad bad. fix this tomorrow
        {
            ld *= 10;
            ld -= i;
            if (ld * 10 >= 5)
                i++;
        }*/
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
    while (ld >= 1)
    {
        d = (uintmax_t)(ld / u);
        s = ft_strjoin(s, ft_uitoa_base(d, 10, 0, 1));
        ld -= d * u;
        u /= 1000000000;
    }
    if (precision > 0 || precision == -1)
    {
        
        precision = (precision == -1 ? 6 : precision);
        s = ft_strjoin(s, ".");
        s = ft_strjoin(s, ft_ulfdecimaltoa(ld, precision));
    }
    return (s);
}

char    *ft_printf_ftoa(t_placehold *p, va_list a_list)
{
    long double ld;
    double      d;
    char        *s;

    ld = 0;
    if (p->length && !ft_strcmp(p->length, "L"))
        ld = va_arg(a_list, long double);
    else
    {
        d = va_arg(a_list, double);
        ld += d;
    }
    if (ld < 0)
    {
        p->sign = '-';
        ld = -ld;
    }
    s = ft_ulfitoa(ld, p->precision);
    p->precision = ft_strlen(s);
    return (s);
}