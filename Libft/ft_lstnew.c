/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:41:59 by bgrosjea          #+#    #+#             */
/*   Updated: 2023/12/13 16:12:57 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_Node	*ft_lstnew(int number)
{
	t_Node	*new;

	new = (t_Node *)malloc(sizeof(t_Node));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->nbr = number;
	return (new);
}
