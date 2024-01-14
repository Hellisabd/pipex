/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:04:09 by bgrosjea          #+#    #+#             */
/*   Updated: 2023/10/24 14:17:32 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (dst == src || n == 0)
		return (dst);
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	while (n--)
		*s1++ = *s2++;
	return (dst);
}
