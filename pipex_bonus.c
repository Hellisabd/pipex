/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:44:48 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/30 11:09:10 by bgrosjea         ###   ########.fr       */
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
	while (tmp[++i])
		tmp[i] = ft_strjoin(tmp[i], "/");
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
	while (p->path[j])
	{
		tmp = ft_strjoin(p->path[j], p->cmd[0]);
		if (access(tmp, F_OK) == 0)
			if (access(tmp, X_OK) == 0)
				execve(tmp, p->cmd, env);
		free (tmp);
		j++;
	}
	if (!p->path[j])
		exit ((free (p->path), ft_putstr_fd("command not found\n", 2), 1));
}

void	cmd(t_pipex *p, char **argv, char **env)
{
	int	i;

	i = 0;
	p->cmd = ft_split(argv[p->n], ' ');
	while (p->cmd[i])
	{
		p->cmd[i] = ft_strtrim(p->cmd[i], "\"");
		if (!p->cmd[i])
			exit ((ft_free_double_tab(p->cmd), ft_free_double_tab(p->path), 1));
		p->cmd[i] = ft_strtrim(p->cmd[i], " ");
		if (!p->cmd[i])
			exit ((ft_free_double_tab(p->cmd), ft_free_double_tab(p->path), 1));
		i++;
	}
	p->path = find_path(env);
	exec_cmd(p, env);
	ft_free_double_tab(p->cmd);
	exit ((write(2, "Error\n", 6), 1));
}
void	do_pipe(t_pipex *p, char **argv, char **env)
{
	if (pipe(p->fd) == -1)
		exit ((perror("Error"), 1));
	p->pid = fork();
	if (p->pid < 0)
		exit ((perror("Error"), 1));
	if (p->pid == 0)
	{
		close (p->fd[0]);
		dup2(p->fd[1], 1);
		cmd(p, argv, env);
	}
	else
	{
		close (p->fd[1]);
		dup2(p->fd[0], 0);
	}
}


int	main(int argc, char **argv, char **env)
{
	t_pipex	p;
	int		status;

	status = 0;
	p.n = 2;
	if (argc < 5)
		exit ((write(2, "Error\n", 6), 1));
	open_files(&p, argv, argc);
	dup2(p.fdin, 0);
	while (p.n < argc - 2)
	{
		do_pipe(&p, argv, env);
		p.n++;
	}
	dup2(p.fdout, 1);
	cmd(&p, argv, env);
	close_fd(&p);
	exit_end(&p, status);
}
