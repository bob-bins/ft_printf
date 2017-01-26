#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <wchar.h>
# include <locale.h>
# include "../libft/libft.h"
typedef struct      s_format
{
    char *s;
    char *e;
}                   t_format;

typedef struct      s_placehold
{
    int             leftalign;
    char            sign;
    char            padding;
    char            *hash;
    int             width; //min output length
    int             precision; //max output length (ignored for integers)
    char            *length;
    char            type;
    unsigned short  base;
    int             signed_num;
    unsigned short  uppercase;
}                   t_placehold;

#endif

