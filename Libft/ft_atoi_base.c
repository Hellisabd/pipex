/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:27:58 by bgrosjea          #+#    #+#             */
/*   Updated: 2023/10/24 14:15:03 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	ssize_t	get_value(char c)
{
	if (ft_isdigit(c))
		return (c - '0' < 16);
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10 < 16);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10 < 16);
	return (0);
}

ssize_t	ft_atoi_base(const char *nptr, char *base)
{
	int		sign;
	size_t	res;
	size_t	i;

	sign = 1;
	i = 0;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		res *= 10;
		res += get_value(nptr[i]);
		i++;
	}
	return ((ssize_t)sign * res);
}
