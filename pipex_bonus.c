/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:44:48 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/31 13:41:09 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

char	**find_path(char **env)
{
	char	**tmp;
	int		i;

	i = -1;
	while (*env && 0 != ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
		exit (1);
	tmp = ft_split(*env + 5, ':');
	if (!tmp)
		return (NULL);
	while (tmp[++i])
	{
		tmp[i] = ft_strjoin(tmp[i], "/");
		if (!tmp[i])
			return (ft_free_double_tab(tmp), NULL);
	}
	return (tmp);
}

void	exec_cmd(t_pipex *p, char **env)
{
	char	*tmp;
	int		j;

	j = 0;
	if (access(p->cmd[0], F_OK) == 0)
		if (access(p->cmd[0], X_OK) == 0)
			execve(p->cmd[0], p->cmd, env);
	while (p->path && p->path[j])
	{
		tmp = ft_strjoin(p->path[j], p->cmd[0]);
		if (access(tmp, F_OK) == 0)
			if (access(tmp, X_OK) == 0)
				execve(tmp, p->cmd, env);
		free (tmp);
		j++;
	}
	exit ((free (p->path), ft_free_double_tab(p->cmd), \
	ft_putstr_fd("command not found\n", 2), close_fd(p), 1));
}

void	cmd(t_pipex *p, char **argv, char **env)
{
	int	i;

	i = 0;
	p->cmd = ft_split(argv[p->n], ' ');
	if (!p->cmd)
		exit ((ft_free_double_tab(p->path), close_fd(p), 1));
	while (p->cmd[i])
	{
		p->cmd[i] = ft_strtrim(p->cmd[i], "\"");
		if (!p->cmd[i])
			exit ((ft_free_double_tab(p->cmd), close_fd(p), \
			ft_free_double_tab(p->path), 1));
		p->cmd[i] = ft_strtrim(p->cmd[i], " ");
		if (!p->cmd[i])
			exit ((ft_free_double_tab(p->cmd), close_fd(p), \
			ft_free_double_tab(p->path), 1));
		i++;
	}
	exec_cmd(p, env);
}

void	do_pipe(t_pipex *p, char **argv, char **env)
{
	if (pipe(p->fd) == -1)
		exit ((ft_free_double_tab(p->path), close_fd(p), perror("Error"), 1));
	p->pid = fork();
	if (p->pid < 0)
		exit ((close_fd(p), ft_free_double_tab(p->path), perror("Error"), 1));
	if (p->pid == 0)
	{
		if (dup2(p->fd[1], 1) < 0)
			exit ((close_fd(p), \
			ft_free_double_tab(p->path), perror("Error"), 1));
		close_fd(p);
		cmd(p, argv, env);
	}
	else
	{
		close (p->fd[1]);
		if (dup2(p->fd[0], 0))
			exit ((close_fd(p), \
			ft_free_double_tab(p->path), perror("Error"), 1));
		close (p->fd[0]);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	p;
	int		status;

	status = 0;
	p.n = 2;
	open_files(&p, argv, argc, env);
	while (p.n < argc - 2)
	{
		do_pipe(&p, argv, env);
		p.n++;
		waitpid(p.pid, &status, 0);
	}
	p.pid = fork();
	if (p.pid < 0)
		exit ((close_fd(&p), \
		ft_free_double_tab(p.path), perror("Error"), 1));
	if (p.pid == 0)
	{
		if (dup2(p.fdout, 1) < 0)
			exit ((close_fd(&p), \
			ft_free_double_tab(p.path), perror("Error"), 1));
		cmd(&p, argv, env);
	}
	close_fd((ft_free_double_tab(p.path), &p));
	exit_end(&p, status);
}
