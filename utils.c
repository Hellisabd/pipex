/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:44 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/24 17:13:32 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_end(int status)
{
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit (1);
}

void	awk_gest(char **argv, t_pipex *p)
{
	if (ft_strncmp(argv[3], "awk '", 5) == 0)
		p->cmd = ft_split(argv[3], '\'');
	else if (ft_strncmp(argv[3], "awk \"", 5) == 0)
		p->cmd = ft_split(argv[3], '"');
	else
		p->cmd = ft_split(argv[3], ' ');
}

void	close_fd(t_pipex *p)
{
	close(p->fd[0]);
	close(p->fd[1]);
	close(p->fd1);
	close(p->fd2);
}
