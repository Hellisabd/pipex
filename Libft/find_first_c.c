/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_first_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:25:55 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/02/01 11:30:27 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	find_first_c(char *str, char c2, char c1)
{
	int	i;

	i = 0;
	while (str[i] != c1 && str[i] != c2)
		i++;
	if (str[i] == c1)
		return (c1);
	if (str[i] == c2)
		return (c2);
	return (0);
}
