/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:44:48 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/24 18:56:24 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdio.h"

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
	// segfault
	while (tmp[++i])
		tmp[i] = ft_strjoin(tmp[i], "/");
		// protection
	return (tmp);
}

void	exec_cmd(t_pipex *p, char **env, int argc)
{
	char	*tmp;
	int		j;

	j = 0;
	if (access(p->cmd[0], F_OK) == 0)
		if (access(p->cmd[0], X_OK) == 0)
			execve(p->cmd[0], p->cmd, env);
	if (argc >= 2)
	{
		while (p->path[j])
		{
			tmp = ft_strjoin(p->path[j], p->cmd[0]);
			// protection
			if (access(tmp, F_OK) == 0)
				if (access(tmp, X_OK) == 0)
					execve(tmp, p->cmd, env);
			free (tmp);
			j++;
		}
	}
	if (!p->path[j])
	// free les commandes et autres avant d'exit (tous les precedents malloc)
		exit ((free (p->path), ft_putstr_fd("command not found\n", 2), 1));
}

void	cmd_1(t_pipex *p, char **argv, int argc, char **env)
{
	int	i;

	i = 0;
	if (p->pid1 == 0)
	{
		// proteges tes dup2
		dup2(p->fd1, STDIN_FILENO);
		dup2(p->fd[1], STDOUT_FILENO);
		close(p->fd[0]);
		close(p->fd[1]);
		close(p->fd1);
		close(p->fd2);
		p->cmd = ft_split(argv[2], ' ');
		// protection du split
		while (p->cmd[i])
		{
			p->cmd[i] = ft_strtrim(p->cmd[i], "\"");
			// verifier le retour du malloc
			i++;
		}
		p->path = find_path(env);
		exec_cmd(p, env, argc);
		// Tu n'arriveras jamais ici
		ft_free_double_tab(p->cmd);
		exit ((write(2, "Error\n", 6), 1));
	}
}

void	cmd_2(t_pipex *p, char **argv, int argc, char **env)
{
	int	i;

	i = 0;
	if (p->pid2 == 0)
	{
		dup2(p->fd2, STDOUT_FILENO);
		dup2(p->fd[0], STDIN_FILENO);
		close(p->fd[0]);
		close(p->fd[1]);
		close(p->fd2);
		close(p->fd1);
		// faut close le fichier d'entree et de sortie
		awk_gest(argv, p);
		while (p->cmd[i])
		{
			p->cmd[i] = ft_strtrim(p->cmd[i], "\"");
			p->cmd[i] = ft_strtrim(p->cmd[i], " ");
			i++;
		}
		p->path = find_path(env);
		exec_cmd(p, env, argc);
		// Tu n;arriveras jamais ici
		ft_free_double_tab(p->cmd);
		exit ((perror("Error\n"), 1));
	}
}

/*
Quand la commande n'est pas trouvee puis la suivante est trouvee, il faut quitter directement le programme
et ne pas executer la premiere ni la deuxieme (pour eviter les prompt non voulus)
*/
int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		status;

	if (argc != 5)
		exit (1);
	pipex.fd1 = open(argv[1], O_RDONLY, 0777);
	if (pipex.fd1 == -1)
		exit ((perror("Error\n"), 1));
	pipex.fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (pipex.fd2 == -1)
		// close fd1
	if (pipe(pipex.fd) == -1)
		// close fd1 & fd2
		exit ((perror("Error\n"), 1));
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
	// close pipes + fd1 & fd2
		exit ((perror("Error\n"), 1));
	cmd_1(&pipex, argv, argc, env);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		exit ((perror("Error\n"), 1));
	cmd_2(&pipex, argv, argc, env);
	close_fd(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &status, 0);
	exit_end(status);
}
