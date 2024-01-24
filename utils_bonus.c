/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:44 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/24 18:22:36 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	close(p->fdin);
	close(p->fdout);
}

void	open_files(t_pipex *p, char **argv, int argc)
{
	p->fdin = open(argv[1], O_RDONLY, 0777);
	if (p->fdin == -1)
		exit ((perror("Error\n"), 1));
	p->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fdout == -1)
		exit ((perror("Error\n"), 1));
}
