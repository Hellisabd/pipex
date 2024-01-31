/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:44 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/31 17:03:12 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_end(t_pipex *p, int status, int boul)
{
	if (boul == 1)
	{
		while (p->n >= 2)
		{
			waitpid(p->pid, &status, 0);
			p->n--;
		}
	}
	else
		ft_free_tab(p->path);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit (1);
}

void	close_fd(t_pipex *p)
{
	close(p->fd[0]);
	close(p->fd[1]);
	close(p->fdout);
	if (p->boul == 0)
		close(p->fdin);
}

void	here_doc(t_pipex *p, char **argv)
{
	char	*tmp;

	if (pipe(p->fd) == -1)
		exit ((ft_free_tab(p->path), perror("Error"), 1));
	p->pid = fork();
	if (p->pid < 0)
		exit ((ft_free_tab(p->path), close_fd(p), perror("Error"), 1));
	if (p->pid == 0)
	{
		while (1)
		{
			tmp = get_next_line(0);
			if (0 == ft_strncmp(argv[2], tmp, ft_strlen(argv[2])))
				if (tmp[ft_strlen(argv[2])] == '\n')
					exit ((ft_free_tab(p->path), close_fd(p), free(tmp), 0));
			ft_putstr_fd(tmp, p->fd[1]);
			free(tmp);
		}
	}
	else
	{
		if (dup2(p->fd[0], STDIN_FILENO) < 0)
			exit ((ft_free_tab(p->path), close_fd(p), perror("Error"), 1));
		wait((close ((close (p->fd[1]), p->fd[0])), NULL));
	}
}

void	open_files(t_pipex *p, char **argv, int argc, char **env)
{
	if (argc < 5)
		exit ((write(2, "Error\n", 6), 1));
	p->path = find_path((p->boul = 0, env));
	if (!p->path)
		exit ((close (p->fdin), close (p->fdout), 1));
	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
	{
		p->fdin = open(argv[1], O_RDONLY, 0777);
		if (p->fdin == -1)
			exit ((ft_free_tab(p->path), perror("Error\n"), 1));
		p->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->fdout == -1)
			exit ((ft_free_tab(p->path), perror("Error\n"), \
			close (p->fdin), 1));
		if (0 > dup2((p->fdin), 0))
			exit ((ft_free_tab(p->path), close_fd(p), 1));
	}
	else
	{
		p->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (p->fdout == -1)
			exit ((ft_free_tab(p->path), perror("Error\n"), 1));
		p->n = 3;
		here_doc((p->boul = 1, p), argv);
	}
}
