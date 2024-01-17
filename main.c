/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:04:02 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/17 15:51:23 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdio.h"

char	*find_path(char **env)
{
	int i;
	
	i = 0;
	while (0 != ft_strncmp(env[i], "PATH=", 5))
		i++;
	return (env[i][5])
}

char	*find_cmd(char **argv, t_pipex p)
{
	static int	idx_env;
	int	i;
	int idx_param;

	i = -1;
	while (argv[++i])
	{
		if (access(argv[i], F_OK) == 0)
			if(access(argv[i], X_OK) == 0)
				break ;
	}
	i = idx_env;
	while (argv[++i][0] == '-')
	{
		p->cmd_args[idx_param] = ft_memcpy();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	char	*tmp;

	tmp = find_path(env);
	pipex.path = ft_split(tmp, ':');
	pipex.cmd = find_cmd(argv, pipex);
	
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
