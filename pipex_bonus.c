/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:44:48 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/24 18:16:08 by bgrosjea         ###   ########.fr       */
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

void	cmd(t_pipex *p, char **argv, char **env, int format)
{
	int	i;

	i = 0;
	if (format == 1)
	{
		dup2(p->fdin, STDIN_FILENO);
		dup2(p->fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(p->fdout, STDOUT_FILENO);
		dup2(p->fd[0], STDIN_FILENO);
		close(p->fdout);
		fprintf(stderr, "lol\n");
	}
	close(p->fd[0]);
	close(p->fd[1]);
	awk_gest(argv, p);
	while (p->cmd[i])
	{
		p->cmd[i] = ft_strtrim(p->cmd[i], "\"");
		p->cmd[i] = ft_strtrim(p->cmd[i], " ");
		i++;
	}
	p->path = find_path(env);
	exec_cmd(p, env);
	ft_free_double_tab(p->cmd);
	exit ((write(2, "Error\n", 6), 1));
}

void	create_pipe(t_pipex *p, char **argv, char **env, int format)
{
	if (pipe(p->fd) == -1)
		exit ((perror("Error\n"), 1));
	cmd(p, argv, env, format);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	p;
	int		status;

	p.n = 1;
	fprintf (stderr, "%d", argc);
	if (argc < 5)
		exit ((perror("Error\n"), 1));
	open_files(&p, argv, argc);
	while (p.n < argc - 2)
	{
		p.pid = fork();
		if (p.pid == 0)
			create_pipe(&p, argv, env, 0);
		waitpid(p.pid, &status, 0);
		p.n++;
	}
	create_pipe(&p, argv, env, 1);
	waitpid(p.pid, &status, 0);
	close_fd(&p);
	exit_end(status);
}
