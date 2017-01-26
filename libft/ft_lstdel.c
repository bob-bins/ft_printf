/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:21:59 by mchen             #+#    #+#             */
/*   Updated: 2016/12/02 14:21:05 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (*alst)
	{
		tmp = *alst;
		while (tmp)
		{
			del(tmp->content, tmp->content_size);
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2);
			tmp2 = NULL;
		}
		*alst = NULL;
	}
}
