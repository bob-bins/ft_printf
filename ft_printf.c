#include "includes/ft_printf.h"
#include <stdio.h>

void	ft_strrev(char *s)
{
	char *e;
	char t;

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

void    ft_putnstr_fd(int fd, char *s, size_t n)
{
    if (n > 0)
    {
        while (*s && n-- > 0)
            ft_putchar_fd(*s++, fd);
    }
}

void    ft_putnchar_fd(int fd, char c, intmax_t n)
{
    while (n-- > 0)
        write(fd, &c, 1);
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
    p->base = 0;
    p->signed_num = 0;
    p->uppercase = 0;
}

/*int     printf_replace(t_format *f, va_list a_list)
{
    char    *eval;
    char    *temp;
    
    //first eval the str in between m and e
    if (eval = format_pf_string(f, a_list))
    {
        //then malloc enough space for strlen(*s) - (e - m) + evaled + 1
        if (temp = malloc(sizeof(*temp) * (ft_strlen(f->s - (f->e - f->m) + ft_strlen(eval) + 1)))
        {
            //then strcopy s until m, eval, and e until null term
            temp = ft_strncat(temp, f->s, f->m - f->s);
            temp = ft_strcat(temp, eval);
            temp = ft_strcat(temp, f->e);
            f->m = f->e + 1;
            free(f->s);
            f->s = temp;
            //^^ "return" m as e + 1 and s as start of string always.
            return (0);
        }
    }
    return (1);
}*/

void    set_hash(t_placehold *p, t_format *f)
{
    if (p->hash)
    {
        if (ft_strchr("oO", *(f->e)))
            p->hash = "0";
        else if (ft_strchr("x", *(f->e)))
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
        if (ft_strchr("dDi", *(f->e)))
            p->base = 10;
        else if (ft_strchr("oO", *(f->e)))
            p->base = 8;
        else if (ft_strchr("xX", *(f->e)))
        {
            p->base = 16;
            if (*(f->e) == 'X')
                p->uppercase = 1;
        }
        if (ft_strchr("DOUCS", *(f->e)))
        {
            if (p->length)
                free(p->length);
            p->length = "l";
        }
        if (ft_strchr("dDi", *(f->e)))
            p->signed_num = 1;
        p->padding = ft_strchr("cCsS", *(f->e)) ? ' ' : p->padding;
        p->sign = (p->base != 10 ? 0 : p->sign);
        set_hash(p, f);
        p->type = *(f->e);
    }
}

/*void     set_parameter_field(t_placehold *p, t_format *f)
{
    char *s;
    
    s = f->e;
    while (*s != '$' && !ft_strchr("sSpdDioOuUxXcC", *s) && *s)
        s++;
    if (*s == '$')
    {
        p->parameter = ft_atoi(f->e);
        f->e = s + 1;
    }
}*/

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
        else if (*(f->e) >= '1' && *(f->e) <= '9')
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
    //set_parameter_field(p, f);
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
            return (cast_signed_size_t(num)); //RETURN "SIGNED" size_t instead. check sizeof to see if it's equal to another type. then cast as that type
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
    while (num != 0 && i == 0)
    {
        i++;
        num = num / base;
    }
    return (i);
}

char	*ft_uitoa_base(uintmax_t value, unsigned short base, unsigned short uppercase, int digits)
{
	char	*ret;
	char	*dig;
	int		i;

	dig = "0123456789abcdef0123456789ABCDEF";
    dig += 16 * uppercase;
	ret = malloc(sizeof(*ret) * (ft_uintmax_len(value, base) + 1));
	i = 0;
	while (value != 0 || i == 0 || i < digits)
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

char    *ft_printf_itoa_base(t_placehold *p, va_list a_list)
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
    return (ft_uitoa_base(uint, p->base, p->uppercase, p->precision));
}

char        *ft_wctos(wchar_t c)
{
    char    *s;
    char    *e;
    
    s = malloc(sizeof(*s) * 5);
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
	*e = 0;
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

char	*ft_printf_str(t_placehold *p, size_t n, va_list a_list)
{
    char *s;

    if (p->length != NULL && !ft_strcmp(p->length, "l"))
    {
        if (p->precision >= 0)
            s = ft_strndup((char*)va_arg(a_list, wchar_t*), n); //FIX THIS ONE so that partial unicode characters aren't included!!!
        else
            s = ft_strdup((char*)va_arg(a_list, wchar_t*)); //FIX THIS TOO IN CASE......
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

void    print_eval(t_placehold *p, va_list a_list)
{
    char    *str;
    size_t  slen;

    if (ft_strchr("dDioOuUxX", p->type))
        str = ft_printf_itoa_base(p, a_list);
    else if (ft_strchr("cC", p->type))
        str = ft_printf_ctos(p, a_list);
    else if (ft_strchr("sS", p->type))
        str = ft_printf_str(p, p->precision, a_list);
    else if (p->type == '%')
		str = ft_strdup("%");
	else
		return ;
    slen = (ft_strchr("cC", p->type) ? 1 : ft_strlen(str)) + ft_strlen(p->hash);
    if (p->precision == -1)
    {
        ft_putstr_fd(p->hash, 1);
        ft_putchar_fd(p->sign, 1);
    }
    if (p->leftalign == 0)
        ft_putnchar_fd(1, p->padding, p->width - slen - (p->sign != 0 ? 1 : 0));
    if (p->precision > 0)
    {
        ft_putstr_fd(p->hash, 1);
        ft_putchar_fd(p->sign, 1);
    }
    ft_putnstr_fd(1, str, p->precision == -1 ? slen : p->precision);
    if (p->leftalign)
        ft_putnchar_fd(1, p->padding, p->width - slen);
    if (str)
    {
        free(str);
        str = NULL;
    }
    if (p->length)
        free(p->length);
}

int     ft_printf(const char *format, ...)
{
    t_placehold *p;
    t_format    *f;
    va_list     a_list;

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
                print_eval(p, a_list);
                f->s = f->e;
            }
            else
                ft_putchar(*(f->s));
            if (*(f->s))
                f->s++;
        }
        va_end(a_list);
    }
    return (0);
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
    return (0);
}*/
