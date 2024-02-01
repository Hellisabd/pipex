/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:44 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/02/01 11:49:24 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	parsing_cmd(t_pipex *p, char **argv)
{
	char	c;
	int		i;

	c = ' ';
	if (1 != count_words(argv[p->n], '"') && 1 != count_words(argv[p->n], '\''))
		c = find_first_c(argv[p->n], '"', '\'');
	else if (1 != count_words(argv[p->n], '"'))
		c = '"';
	else if (1 != count_words(argv[p->n], '\''))
		c = '\'';
	p->cmd = ft_split((i = -1, argv[p->n]), c);
	if (!p->cmd)
		exit ((ft_free_tab(p->path), close_fd(p), 1));
	while (p->cmd[++i])
	{
		p->cmd[i] = ft_strtrim(p->cmd[i], " ");
		if (!p->cmd)
			exit ((ft_free_tab(p->path), close_fd(p), 1));
		p->cmd[i] = ft_strtrim(p->cmd[i], "\"");
		if (!p->cmd)
			exit ((ft_free_tab(p->path), close_fd(p), 1));
		p->cmd[i] = ft_strtrim(p->cmd[i], "'");
		if (!p->cmd)
			exit ((ft_free_tab(p->path), close_fd(p), 1));
	}
}

void	open_files(t_pipex *p, char **argv, int argc, char **env)
{
	if (argc != 5)
		exit ((write(2, "Error\n", 6), 1));
	p->path = find_path((p->boul = 0, env));
	if (!p->path)
		exit ((close (p->fdin), close (p->fdout), 1));
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
