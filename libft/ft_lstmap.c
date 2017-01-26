/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:33:24 by mchen             #+#    #+#             */
/*   Updated: 2016/12/03 00:27:09 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *ret;
	t_list *cur;
	t_list *prv;

	if (!lst || !f)
		return (NULL);
	ret = (t_list*)malloc(sizeof(*ret));
	if (ret)
	{
		ret = f(lst);
		lst = lst->next;
		prv = ret;
		while (lst)
		{
			cur = (t_list*)malloc(sizeof(*ret));
			cur = f(lst);
			prv->next = cur;
			prv = cur;
			lst = lst->next;
		}
	}
	return (ret);
}
