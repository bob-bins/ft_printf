#include "includes/ft_printf.h"
#include <stdio.h>

void	ft_strrev(char *s)
{
	char *e;
	char t;

	if (!s)
		return ;
	e = s;
	while (*e)
		e++;
	e--;
	while (s < e)
	{
		t = *s;
		*s++ = *e;
		*e-- = t;
	}
}

int    ft_putnstr_fd(int fd, char *s, int n)
{
    int count;
    
    count = 0;
    if (n > 0)
    {
        while (*s && n-- > 0)
        {
            ft_putchar_fd(*s++, fd);
            count++;
        }
    }
    return (count);
}

int    ft_putnchar_fd(int fd, char c, int n)
{
    int count;
    
    count = 0;
    while (n-- > 0)
	{
        write(fd, &c, 1);
		count++;
	}
    return (count);
}

void    init_placehold(t_placehold *p)
{
    p->leftalign = 0;
    p->sign = 0;
    p->padding = ' ';
    p->hash = NULL;
    p->width = 0;
    p->precision = -1;
    p->length = NULL;
    p->type = 0;
    p->base = 10;
    p->signed_num = 0;
    p->uppercase = 0;
}

void    set_hash(t_placehold *p, t_format *f)
{
    if (p->hash || *(f->e) =='p')
    {
        if (ft_strchr("oO", *(f->e)))
            p->hash = "0";
        else if (ft_strchr("px", *(f->e)))
            p->hash = "0x";
        else if (ft_strchr("X", *(f->e)))
            p->hash = "0X";
        else
        {
            p->hash = NULL;
            return ;
        }
        p->sign = 0;
    }
}

void     set_type_field(t_placehold *p, t_format *f)
{
    if (ft_strchr("%sSpdDioOuUxXcC", *(f->e)))
    {
        if (ft_strchr("oO", *(f->e)))
            p->base = 8;
        else if (ft_strchr("pxX", *(f->e)))
        {
            p->base = 16;
            p->uppercase = (*(f->e) == 'X' ? 1 : p->uppercase);
        }
        if (ft_strchr("DOUCS", *(f->e)))
        {
            if (p->length)
                free(p->length);
            p->length = ft_strdup("l");
        }
        p->signed_num = (ft_strchr("dDi", *(f->e)) ? 1 : p->signed_num);
		p->precision = (ft_strchr("%", *(f->e)) ? 1 : p->precision);
        p->padding = (ft_strchr("cCsS", *(f->e)) ? ' ' : p->padding);
        p->sign = (!ft_strchr("dDi", *(f->e)) ? 0 : p->sign);
        set_hash(p, f);
        p->type = *(f->e);
    }
    else
        p->type = '%';
}

void     set_flag_field(t_placehold *p, t_format *f)
{
    while (1)
    {
        if (*(f->e) == '+')
            p->sign = '+';
        else if (*(f->e) == ' ')
            p->sign = (p->sign == 0 ? ' ' : p->sign);
        else if (*(f->e) == '-')
        {
            p->leftalign = 1;
            p->padding = ' ';
        }
        else if (*(f->e) == '0')
            p->padding = (p->leftalign == 0 ? '0' : p->padding);
        else if (*(f->e) == '#')
            p->hash = "#";
        else
            break;
        f->e++;
    }
}

void     set_width_field(t_placehold *p, t_format *f, va_list a_list)
{
    if (*(f->e) == '*')
    {
        if ((p->width = va_arg(a_list, int)) < 0)
        {
            p->leftalign = 1;
            p->padding = ' ';
        }
        f->e++;
    }
    else if (*(f->e) >= '1' && *(f->e) <= '9')
    {
        while (*(f->e) >= '0' && *(f->e) <= '9')
            p->width = p->width * 10 + (*(f->e++) - '0');
    }
}

void     set_precision_field(t_placehold *p, t_format *f, va_list a_list)
{
    if (*(f->e) == '.')
    {
        p->precision = 0;
        if (*(++f->e) == '*')
        {
            p->precision = va_arg(a_list, int);
            f->e++;
        }
        else
        {
            while (*(f->e) >= '0' && *(f->e) <= '9')
                p->precision = p->precision * 10 + (*(f->e++) - '0');
        }
        p->padding = ' ';
    }
}

void     set_length_field(t_placehold *p, t_format *f)
{
    if (ft_strchr("hljzq", *(f->e)))
    {
        f->e++;
        if (*(f->e) == 'h' || *(f->e) == 'l')
            p->length = ft_strndup(f->e++ - 1, 2);
        else
            p->length = ft_strndup(f->e - 1, 1);
    }
}

void     eval_fields(t_placehold *p, t_format *f, va_list a_list)
{
    set_flag_field(p, f);
    set_width_field(p, f, a_list);
    set_precision_field(p, f, a_list);
    set_length_field(p, f);
    set_type_field(p, f);
}

intmax_t    cast_signed_size_t(intmax_t num)
{
    if (sizeof(size_t) == sizeof(short))
        return ((short)num);
    else if (sizeof(size_t) == sizeof(int))
        return ((int)num);
    else if (sizeof(size_t) == sizeof(long))
        return ((long long)num);
    else if (sizeof(size_t) == sizeof(long long))
        return ((long long)num);
    else
        return (num);
}

intmax_t    cast_intmax(intmax_t num, t_placehold *p)
{
    if (p->length != NULL)
    {
        if (!ft_strcmp(p->length, "hh"))
            return ((char)num);
        else if (!ft_strcmp(p->length, "h"))
            return ((short)num);
        else if (!ft_strcmp(p->length, "l"))
            return ((long)num);
        else if (!ft_strcmp(p->length, "ll"))
            return ((long long)num);
        else if (!ft_strcmp(p->length, "j"))
            return (num);
        else if (!ft_strcmp(p->length, "z"))
            return (cast_signed_size_t(num));
    }
    return ((int)num);
}

uintmax_t   cast_uintmax(uintmax_t num, t_placehold *p)
{
    if (p->length != NULL)
    {
        if (!ft_strcmp(p->length, "hh"))
            return ((unsigned char)num);
        else if (!ft_strcmp(p->length, "h"))
            return ((unsigned short)num);
        else if (!ft_strcmp(p->length, "l"))
            return ((unsigned long)num);
        else if (!ft_strcmp(p->length, "ll"))
            return ((unsigned long long)num);
        else if (!ft_strcmp(p->length, "j"))
            return (num);
        else if (!ft_strcmp(p->length, "z"))
            return ((size_t)num);
    }
    return ((unsigned int)num);
}

unsigned short  ft_uintmax_len(uintmax_t num, unsigned short base)
{
    unsigned int    i;
    
    i = 0;
    while (num != 0 || i == 0)
    {
        i++;
        num = num / base;
    }
    return (i);
}

int max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

char	*ft_uitoa_base(uintmax_t value, unsigned short base, unsigned short uppercase, int digits)
{
	char	*ret;
	char	*dig;
	int		i;

	dig = "0123456789abcdef0123456789ABCDEF";
    dig += 16 * uppercase;
	ret = malloc(sizeof(*ret) * (digits + 1));
	i = 0;
	while (value != 0 || (i == 0 && digits != 0) || i < digits)
	{
		ret[i++] = dig[value % base];
		value /= base;
	}
	ret[i] = 0;
	ft_strrev(ret);
	return (ret);
}

/*
** Casts integer appropriately, stores its sign in p, then prints out the number as unsigned with p->sign in front
*/

char    *ft_printf_itoa_base(t_placehold *p, t_format *f, va_list a_list)
{
    intmax_t    sint;
    uintmax_t   uint;

    if (p->signed_num == 1)
    {
        sint = cast_intmax(va_arg(a_list, intmax_t), p);
        if (sint < 0)
        {
            p->sign = '-';
            uint = -sint;
        }
        else
            uint = sint;
    }
    else
        uint = cast_uintmax(va_arg(a_list, uintmax_t), p);
	if (uint == 0 && !ft_strchr("oOp", p->type))
		p->hash = NULL;
    else if (uint > 0)
        p->precision = max(ft_uintmax_len(uint, p->base), p->precision);
    return (ft_uitoa_base(uint, p->base, p->uppercase, p->precision));
}

char        *ft_wctos(wchar_t c)
{
    char    *s;
    char    *e;
    
    s = ft_memalloc(sizeof(*s) * 5);
    e = s;
	if (c <= 0x7F)
		*e++ = c;
	else if (c <= 0x7FF)
	{
	    *e++ = (c >> 6) + 0xC0;
		*e++ = (c & 0x3F) + 0x80;
	}
	else if (c <= 0xFFFF)
	{
		*e++ = (c >> 12) + 0xE0;
		*e++ = ((c >> 6) & 0x3F) + 0x80;
		*e++ = (c & 0x3F) + 0x80;
	}
	else if (c <= 0x10FFFF)
	{
		*e++ = (c >> 18) + 0xF0;
		*e++ = ((c >> 12) & 0x3F) + 0x80;
		*e++ = ((c >> 6) & 0x3F) + 0x80;
		*e++ = (c & 0x3F) + 0x80;
	}
	return (s);
}

char    *ft_printf_ctos(t_placehold *p, va_list a_list)
{
    wchar_t c;

    if (p->length != NULL && !ft_strcmp(p->length, "l"))
        c = (wchar_t)va_arg(a_list, wint_t);
    else
        c = (char)(unsigned char)va_arg(a_list, int);
    return (ft_wctos(c));
}

char    *ft_wstrndup(wchar_t *w, size_t n)
{
    char    *s;
    
    s = ft_memalloc(sizeof(*s) * (n + 1));
    if (s && w)
        while (*w)
            s = ft_strcat(s, ft_wctos(*w++));
    else
        s = NULL;
    return (s);
}

char    *ft_wstrdup(wchar_t *w)
{
    wchar_t *t;
    size_t  len;
    
    len = 0;
    t = w;
	if (t)
    	while (*t++)
			len++;
    return (ft_wstrndup(w, len));
}

char	*ft_printf_str(t_placehold *p, size_t n, va_list a_list)
{
    char *s;

    if (p->length != NULL && !ft_strcmp(p->length, "l"))
    {
        if (p->precision >= 0)
            s = ft_wstrndup(va_arg(a_list, wchar_t*), n);
        else
            s = ft_wstrdup(va_arg(a_list, wchar_t*));
    }
    else
    {
        if (p->precision >= 0)
            s = ft_strndup(va_arg(a_list, char*), n);
        else
            s = ft_strdup(va_arg(a_list, char*));
    }
    if (!s)
        s = ft_strdup("(null)");
    return (s);
}

unsigned int    print_eval(t_placehold *p, t_format *f, va_list a_list)
{
    char            *str;
    size_t          slen;
    int             count;

	count = 0;
    if (ft_strchr("dDioOuUxX", p->type))
        str = ft_printf_itoa_base(p, f, a_list);
    else if (ft_strchr("cC", p->type))
        str = ft_printf_ctos(p, a_list);
    else if (ft_strchr("sS", p->type))
        str = ft_printf_str(p, p->precision, a_list);
    else if (p->type == 'p')
        str = ft_printf_itoa_base(p, f, a_list);
    else if (p->type == '%')
		str = ft_strdup("%");
	else
		return (count);
    slen = (ft_strchr("cC", p->type) ? 1 : ft_strlen(str)) + ft_strlen(p->hash) + (p->sign != 0 ? 1 : 0);
    if (p->padding == '0')
    {
        count += ft_putstr_fd(p->hash, 1);
        count += ft_putchar_fd(p->sign, 1);
    }
    if (p->leftalign == 0)
        count += ft_putnchar_fd(1, p->padding, p->width - slen);
    if (p->padding == ' ')
    {
        count += ft_putstr_fd(p->hash, 1);
        count += ft_putchar_fd(p->sign, 1);
    }
    count += ft_putnstr_fd(1, str, p->precision == -1 ? slen : p->precision);
    count += (ft_strchr("cC", p->type) && ft_strlen(str) == 0) ? 1 : 0;
    if (p->leftalign)
        count += ft_putnchar_fd(1, p->padding, p->width - slen);
    if (str)
    {
        free(str);
        str = NULL;
    }
    if (p->length)
        free(p->length);
    return (count);
}

int     ft_printf(const char *format, ...)
{
    t_placehold *p;
    t_format    *f;
    va_list     a_list;
    int count;

    count = 0;
    if (format)
    {
        f = malloc(sizeof(*f));
        f->s = ft_strdup(format);
        va_start(a_list, format);
        while (*(f->s))
        {
            if (*(f->s) == '%')
            {
                p = malloc(sizeof(*p));
                init_placehold(p);
                f->e = f->s + 1;
                eval_fields(p, f, a_list);
                count += print_eval(p, f, a_list);
                f->s = f->e;
            }
            else
                count += ft_putchar_fd(*(f->s), 1);
            if (*(f->s))
                f->s++;
        }
        va_end(a_list);
    }
    return (count);
}
/*
int main()
{
    setlocale(LC_ALL, "");
    ft_printf("ft_printf: %d % 0.10d %li %%\n", 13, 18, 3049600000);
       printf("ac_printf: %d % 0.10d %li %%\n", 13, 18, 3049600000);
    ft_printf("ft_printf: %d %-#*lx %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d %-#*lx %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d % 0*.10ld %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d % 0*.10ld %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d %-*lx %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d %-*lx %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d %-*lo %i %%\n", 13, 18, 3049600000, -4078);
       printf("ac_printf: %d %-*lo %i %%\n", 13, 18, 3049600000, -4078);
    ft_printf("ft_printf: %d -%6c- %i %%\n", 13, 0, -4078);
       printf("ac_printf: %d -%6c- %i %%\n", 13, 0, -4078);
    ft_printf("ft_printf: %d %6c %i %%\n", 13, L'¥', -4078);
       printf("ac_printf: %d %6c %i %%\n", 13, L'¥', -4078);
    ft_printf("ft_printf: %d %-10c %i %%\n", 13, 50, -4078);
       printf("ac_printf: %d %-10c %i %%\n", 13, 50, -4078);
    ft_printf("ft_printf: %d %-*c %i %%\n", 13, 18, 333, -4078);
       printf("ac_printf: %d %-*c %i %%\n", 13, 18, 333, -4078);
    ft_printf("ft_printf: %d %-*.5s %i %%\n", 13, 18, "testing 123", -4078);
       printf("ac_printf: %d %-*.5s %i %%\n", 13, 18, "testing 123", -4078);
    ft_printf("ft_printf: %d %-*.13ls %i %5.5%\n", 13, 18, "ζέες καὶ μυρτιὲς δὲν θὰ βρῶ πιὰ στὸ χ", -4078);
       printf("ac_printf: %d %-*.13ls %i %5.5%\n", 13, 18, L"ζέες καὶ μυρτιὲς δὲν θὰ βρῶ πιὰ στὸ χ", -4078);
    ft_printf("ft_printf: %d %-*.13s %i %5.5%\n", 13, 18, "", -4078);
       printf("ac_printf: %d %-*.13s %i %5.5%\n", 13, 18, "", -4078);
    ft_printf("ft_printf: %d %*.13s %i %5.5%\n", 13, 18, NULL, -4078);
       printf("ac_printf: %d %*.13s %i %5.5%\n", 13, 18, NULL, -4078); 
       char *s, *p;
       
       //s = "hello man";
       //p = NULL;
        printf("ret: %d\n", ft_printf("{%.25p}\n", p));
		       printf("ret: %d\n", printf("{%.25p}\n", p));
    

    return (0);
}*/
