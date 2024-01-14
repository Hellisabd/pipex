/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:17:02 by bgrosjea          #+#    #+#             */
/*   Updated: 2023/12/13 12:37:15 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr(int n)
{
	int		printed;
	char	*res;

	res = ft_itoa(n);
	if (ft_prints(res) == -1)
		return (-1);
	printed = (int)ft_strlen(res);
	free (res);
	return (printed);
}

int	ft_printunbr(unsigned int n)
{
	char	*res;
	int		printed;

	res = ft_uitoa(n);
	printed = (int)ft_strlen(res);
	if (ft_prints(res) == -1)
		return (-1);
	free (res);
	return (printed);
}

int	ft_printhexlow(unsigned int n)
{
	char	*res;
	int		printed;

	res = ft_itoa_base(n, 0);
	if (ft_prints(res) == -1)
		return (-1);
	printed = (int)ft_strlen(res);
	free (res);
	return (printed);
}

int	ft_printhexup(unsigned int n)
{
	char	*res;
	int		printed;

	res = ft_itoa_base(n, 1);
	if (ft_prints(res) == -1)
		return (-1);
	printed = (int)ft_strlen(res);
	free (res);
	return (printed);
}

int	ft_printp(uintptr_t n)
{
	char	*res;
	int		printed;

	if (ft_prints("0x") == -1)
		return (-1);
	printed = 2;
	if (n == 0)
	{
		printed = 3;
		write(1, "0", 1);
		return (printed);
	}
	else
	{
		res = ft_itoa_base_uintptr_t(n);
		if (ft_prints(res) == -1)
			return (-1);
		printed += (int)ft_strlen(res);
		free (res);
		return (printed);
	}
}
