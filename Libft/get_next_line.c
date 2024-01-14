/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:09:03 by basile            #+#    #+#             */
/*   Updated: 2024/01/12 14:53:53 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_next(char *src)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (src[i] != '\n' && src[i])
		i++;
	if (!src[i] || src[i] == '\n')
		return (free (src), NULL);
	dest = malloc(sizeof(char) * (ft_strlen(src) - i + 1));
	if (!dest)
		return (NULL);
	i++;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	free(src);
	return (dest);
}

static char	*ft_actual(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	if (!src[i])
		return (NULL);
	while (src[i] != '\n' && src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] != '\n' && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_transfer_buff(int fd, char *line)
{
	int		read_bytes;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(line, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			if (line)
				free (line);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*res[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	res[fd] = ft_transfer_buff(fd, res[fd]);
	if (!res[fd])
		return (NULL);
	line = ft_actual(res[fd]);
	res[fd] = ft_next(res[fd]);
	return (line);
}
