/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:41:59 by bgrosjea          #+#    #+#             */
/*   Updated: 2023/11/04 17:07:28 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_nb_digit(long n_l)
{
	unsigned int	nb_digit;

	if (n_l == 0)
		return (1);
	nb_digit = 0;
	while (n_l > 0)
	{
		n_l /= 10;
		nb_digit++;
	}
	return (nb_digit);
}

static void	convert_nb(char *outstr, long n_l, unsigned int nb_digit)
{
	outstr[nb_digit] = '\0';
	outstr[--nb_digit] = n_l % 10 + '0';
	n_l /= 10;
	while (n_l > 0)
	{
		outstr[--nb_digit] = n_l % 10 + '0';
		n_l /= 10;
	}
}

char	*ft_uitoa(unsigned int n)
{
	char			*outstr;
	size_t			n_l;
	unsigned int	nb_digit;

	n_l = n;
	nb_digit = get_nb_digit(n_l);
	outstr = malloc(sizeof(char) * (nb_digit + 1));
	if (!outstr)
		return (NULL);
	convert_nb(outstr, n_l, nb_digit);
	return (outstr);
}
