/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:13:01 by bgrosjea          #+#    #+#             */
/*   Updated: 2023/12/13 16:00:20 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_Node	*ft_lstmap(t_Node *lst, int (*f)(int), void (*del)(int))
{
	t_Node	*new;
	t_Node	*tmp;
	t_Node	*begin;
	int		e;

	if (!lst || !del || !f)
		return (NULL);
	tmp = lst;
	begin = NULL;
	while (tmp)
	{
		e = f(tmp->nbr);
		new = ft_lstnew(e);
		if (!new)
		{
			del(e);
			ft_lstdelone(new);
			ft_lstclear(&begin);
			return (begin);
		}
		ft_lstadd_back(&begin, new);
		tmp = tmp->next;
	}
	return (begin);
}
