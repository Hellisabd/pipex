/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_uintptr_t.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:38:30 by bgrosjea          #+#    #+#             */
/*   Updated: 2023/11/17 17:20:47 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	fts_check_hexalow(int nbr)
{
	char	c;

	if (nbr < 10)
		c = nbr + '0';
	if (nbr >= 10)
		c = nbr + 'a' - 10;
	return (c);
}

static int	get_nb_digit_hex(uintptr_t n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static void	fts_convert_hex(char *res, uintptr_t nbr, int nb_d)
{
	uintptr_t	quotient;
	uintptr_t	rest;

	res[nb_d] = '\0';
	nb_d--;
	while (nbr > 0)
	{
		quotient = nbr / 16;
		rest = nbr % 16;
		res[nb_d] = fts_check_hexalow(rest);
		nb_d--;
		nbr = quotient;
	}
}

char	*ft_itoa_base_uintptr_t(uintptr_t n)
{
	char	*res;

	res = malloc(sizeof(char) * (get_nb_digit_hex((uintptr_t) n) + 1));
	if (!res)
		return (NULL);
	fts_convert_hex(res, n, get_nb_digit_hex((uintptr_t)n));
	return (res);
}
