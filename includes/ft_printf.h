/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:27:35 by mchen             #+#    #+#             */
/*   Updated: 2017/02/03 22:47:29 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <float.h>
# include "../libft/libft.h"
# define MAX(a, b) (a > b ? a : b)

typedef struct		s_placehold
{
	int				leftalign;
	char			sign;
	char			padding;
	char			*hash;
	int				width;
	int				prec;
	char			*length;
	char			type;
	unsigned short	base;
	int				signed_num;
	unsigned short	uppercase;
	int				sigfig;
	short			exp_base;
	char			exp_char;
	short			exp_len;
}					t_placehold;

int					ft_printf(const char *format, ...);
int					ft_vfdprintf(int fd, const char *format, va_list a_list);
int					ft_fdprintf(int fd, const char *format, ...);
void				set_hash(t_placehold *p, const char *e);
void				eval_fields(t_placehold *p, const char **e, va_list a_list);
size_t				print_eval(int fd, t_placehold *p, va_list a_list, size_t cnt);
void				set_type_field(t_placehold *p, const char *e);
void				set_flag_field(t_placehold *p, const char **e);
void				set_width_field(t_placehold *p, const char **e,
						va_list a_list);
void				set_precision_field(t_placehold *p, const char **e,
						va_list a_list);
void				set_length_field(t_placehold *p, const char **e);
char				*ft_uitoa_base(uintmax_t value, unsigned short base,
						unsigned short uppercase, int digits);
char				*ft_printf_itoa_base(t_placehold *p, va_list a_list);
char				*ft_printf_ctos(t_placehold *p, va_list a_list);
char				*ft_printf_str(t_placehold *p, size_t n, va_list a_list);
char                *ft_printf_ftoa(t_placehold *p, va_list a_list);
long double			ft_uld_get_mantissa(long double ld, short base);

#endif
