/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:04:02 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/18 14:27:33 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdio.h"

char	**find_path(char **env)
{
	char	**tmp;
	int		i;
	
	i = -1;
	while (0 != ft_strncmp(*env, "PATH=", 5))
		env++;
	tmp = ft_split(*env + 5, ':');
	while (tmp[++i])
		tmp[i] = ft_strjoin(tmp[i], "/");
	return (tmp);
	
}

void exec_cmd(t_pipex *p, char **env, int argc)
{
	char *tmp;
	// int i;
	int j;
	
	// i = 1;
	j = 0;
	if (argc >= 2)
	{
		while (p->path[j])
		{
			tmp = ft_strjoin(p->path[j], p->cmd[0]);
			if (access(tmp, F_OK) == 0)
				if (access(tmp, X_OK) == 0)
					execve(tmp, p->cmd, env);
			free (tmp);
			j++;
		}
	}
	free (p->path);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		fd[2];
	int		fd1;
	int		fd2;
	int		pid1;
	int		pid2;
	
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_WRONLY | O_CREAT, 777);
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd1, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		pipex.cmd = ft_split(argv[2], ' ');
		pipex.path = find_path(env);
		exec_cmd(&pipex, env, argc);
		ft_free_double_tab(pipex.cmd);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd2, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		pipex.cmd = ft_split(argv[3], ' ');
		pipex.path = find_path(env);
		exec_cmd(&pipex, env, argc);
		ft_free_double_tab(pipex.cmd);
	}
	close(fd[0]);
	close(fd[1]);
	close(fd1);
	close(fd2);
	waitpid(pid2, NULL, 0);
	waitpid(pid1, NULL, 0);
}

	// char	**path;

	// path = find_path(env);
	// if (argc != 5)
	// 	return (write(2, "Arguments Error\n", 17));
