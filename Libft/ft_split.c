/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:41:59 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/30 18:28:15 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c && j == 0)
		{
			j = 1;
			i++;
		}
		else if (*s == c)
			j = 0;
		s++;
	}
	return (i);
}

char	*fill_dest(char *s, t_m *var)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (var->i - var->h + 1));
	if (!dest)
		return (NULL);
	while ((size_t)var->h < var->i)
	{
		dest[i] = s[var->h];
		var->h++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	free_split(char **res, int j)
{
	while (j >= 0)
	{
		free (res[j]);
		j--;
	}
	free (res);
	return (0);
}

static	int	ft_splitsplit(char *s, char c, t_m *var, char **res)
{
	if (s[var->i] != c && var->h < 0)
		var->h = var->i;
	else if ((s[var->i] == c || var->i == ft_strlen(s)) && var->h >= 0)
	{
		res[var->j] = fill_dest(s, var);
		if (!res[var->j++] && free_split(res, var->j - 1) == 0)
			return (0);
		var->h = -1;
	}
	var->i++;
	return (1);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	t_m		var;

	if (!s)
		return (NULL);
	var.j = 0;
	var.h = -1;
	var.i = 0;
	res = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (var.i <= ft_strlen(s))
	{
		if (ft_splitsplit(s, c, &var, res) == 0)
			return (NULL);
	}
	res[var.j] = 0;
	return (res);
}
