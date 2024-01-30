/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:44 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/30 15:34:36 by bgrosjea         ###   ########.fr       */
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

void	here_doc(t_pipex *p, char **argv)
{
	char	*tmp;

	if (pipe(p->fd) == -1)
		exit ((perror("Error"), 1));
	p->pid = fork();
	if (p->pid < 0)
		exit ((perror("Error"), 1));
	if (p->pid == 0)
	{
		while (1)
		{
			tmp = get_next_line(0);
			if (0 == ft_strncmp(argv[2], tmp, ft_strlen(argv[2])
				&& tmp[ft_strlen(argv[2])]))
				exit ((free(tmp), 0));
			ft_putstr_fd(tmp, p->fd[1]);
			free(tmp);
		}
	}
	else
	{
		close (p->fd[1]);
		dup2(p->fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	open_files(t_pipex *p, char **argv, int argc)
{
	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
	{
		p->fdin = open(argv[1], O_RDONLY, 0777);
		if (p->fdin == -1)
			exit ((perror("Error\n"), 1));
		p->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->fdout == -1)
			exit ((perror("Error\n"), 1));
	}
	else
	{
		p->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (p->fdout == -1)
			exit ((perror("Error\n"), 1));
		p->n = 3;
		here_doc(p, argv);
	}
}
