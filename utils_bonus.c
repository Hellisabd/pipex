/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:44 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/30 11:09:31 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_end(t_pipex *p, int status)
{
	while (p->n >= 2)
	{
		waitpid(p->pid, &status, 0);
		p->n--;
	}
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit (1);
}

void	awk_gest(char **argv, t_pipex *p)
{
	if (ft_strncmp(argv[p->n], "awk '", 5) == 0)
		p->cmd = ft_split(argv[p->n], '\'');
	else if (ft_strncmp(argv[p->n], "awk \"", 5) == 0)
		p->cmd = ft_split(argv[p->n], '"');
	else
		p->cmd = ft_split(argv[p->n], ' ');
}

void	close_fd(t_pipex *p)
{
	close(p->fd[0]);
	close(p->fd[1]);
	close(p->fdout);
	close(p->fdin);
}

void	open_files(t_pipex *p, char **argv, int argc)
{
	p->fdin = open(argv[1], O_RDONLY, 0777);
	if (p->fdin == -1)
		exit ((perror("Error\n"), 1));
	if (1)
	{
		p->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->fdout == -1)
			exit ((perror("Error\n"), 1));
	}
	else
	{
		p->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
		if (p->fdout == -1)
			exit ((perror("Error\n"), 1));
	}
}
