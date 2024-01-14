/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:38:30 by bgrosjea          #+#    #+#             */
/*   Updated: 2023/11/17 17:21:21 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_check_hexalow(int nbr)
{
	char	c;

	if (nbr < 10)
		c = nbr + '0';
	if (nbr > 9)
		c = nbr + 'a' - 10;
	return (c);
}

char	ft_check_hexaup(int nbr)
{
	char	c;

	if (nbr < 10)
		c = nbr + '0';
	if (nbr > 9)
		c = nbr + 'A' - 10;
	return (c);
}

static int	get_nb_digit_hex(int n, t_m *var)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	if (var->sign == -1)
		i++;
	return (i);
}

static void	ft_convert_hex(char *res, ssize_t nbr, unsigned int nb_d, t_m *var)
{
	int	quotient;
	int	rest;

	res[nb_d] = '\0';
	nb_d--;
	if (nbr == 0)
		res[nb_d] = '0';
	while (nbr > 0)
	{
		quotient = nbr / 16;
		rest = nbr % 16;
		if (var->i == 1)
			res[nb_d] = ft_check_hexaup(rest);
		else
			res[nb_d] = ft_check_hexalow(rest);
		nb_d--;
		nbr = quotient;
	}
	if (var->sign == -1)
		res[0] = '-';
}

char	*ft_itoa_base(int n, int low_or_up)
{
	char		*res;
	ssize_t		nbr;
	t_m			var;

	var.i = low_or_up;
	if (n < 0)
	{
		nbr = (ssize_t)n * -1;
		var.sign = -1;
	}
	else
	{
		var.sign = 0;
		nbr = (ssize_t)n;
	}
	res = malloc(sizeof(char) * (get_nb_digit_hex((long) n, &var) + 1));
	ft_convert_hex(res, nbr, get_nb_digit_hex((long)n, &var), &var);
	return (res);
}
