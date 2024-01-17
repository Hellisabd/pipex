/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:04:02 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/17 17:32:56 by bgrosjea         ###   ########.fr       */
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

char	*find_cmd(char **argv, t_pipex *p)
{
	char *tmp;
	int i;
	int j;
	int	idx_param;
	
	i = 1;
	j = 0;
	while (p->path[j])
	{
		tmp = ft_strjoin(p->path[j], argv[i]);
		printf("%s\n", tmp);
		while (argv[++i])
		{
		if (access(tmp, F_OK) == 0)
			if (access(tmp, X_OK) == 0)
				break ;
		}
		j++;
		free (tmp);
	}
	if (!p->path[j])
		exit((perror("Error"), 1));
	idx_param = i;
	while (argv[++idx_param][0] == '-')
	{
		p->cmd_args[idx_param] = ft_strdup(argv[i]);
		printf("%s\n", p->cmd_args[idx_param]);
	}
	return (tmp);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	
	(void)argc;
	(void)argv;
	pipex.path = find_path(env);
	pipex.cmd = find_cmd(argv, &pipex);
	
	// pipex.cmd = find_cmd(argv, pipex);
	
	// gestion d erreur de proc enfant 

	// int wstatus;
	// int scode;
	
	// wait(&wstatus);
	// if (WIFEXITED(wstatus))
	// 		if (0 == WEXITSTATUS(wstatus));
	// 			exit (1);
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
}

	// char	**path;

	// path = find_path(env);
	// if (argc != 5)
	// 	return (write(2, "Arguments Error\n", 17));
