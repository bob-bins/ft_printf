/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:06:35 by mchen             #+#    #+#             */
/*   Updated: 2016/12/20 20:10:56 by mchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size, int num)
{
	t_list	*node;

	node = (t_list*)malloc(sizeof(*node));
	if (node)
	{
		if (!content)
		{
			node->num = num;
			node->content_size = 0;
			node->content = NULL;
		}
		else
		{
			node->num = num;
			node->content_size = content_size;
			node->content = malloc(content_size);
			ft_memcpy(node->content, (void*)content, content_size);
		}
		node->next = NULL;
	}
	return (node);
}
