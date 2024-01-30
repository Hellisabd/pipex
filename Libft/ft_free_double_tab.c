/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:52:12 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/30 17:38:14 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab && tab[i])
	{
		while (tab[i] != NULL)
		{
			if (tab[i])
				free (tab[i]);
			i++;
		}
		if (tab)
			free (tab);
	}
}
