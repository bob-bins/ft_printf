/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:37:14 by mchen             #+#    #+#             */
/*   Updated: 2016/12/04 17:01:35 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_str(char **word, char *start, char *end)
{
	int i;

	*word = (char*)malloc(sizeof(**word) * (end - start + 1));
	if (*word)
	{
		i = 0;
		while (start < end)
			(*word)[i++] = *start++;
		(*word)[i] = '\0';
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**words;
	char	*b;
	char	*e;
	int		i;
	int		s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_wordcount((char*)s, c);
	words = (char**)malloc(sizeof(*words) * (s_len + 1));
	if (words && (i = 0) == 0)
	{
		b = (char*)s;
		while (i < s_len)
		{
			while ((e = b) && *b == c && *b)
				b++;
			while (*e != c && *e)
				e++;
			add_str(&words[i++], b, e);
			b = e + 1;
		}
		words[i] = 0;
	}
	return (words);
}
