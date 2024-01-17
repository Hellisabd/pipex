/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:04:02 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/16 18:36:24 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "stdio.h"

int	main(int argc, char **argv, char **env)
{
	int i;
	int boul;
	char **path;

	i = 0;
	boul = 1;
	while (0 != ft_strncmp(env[i], "PATH=", 5))
		i++;
	path = ft_split(env[i], ':');
	i = 1;
	while (path[i])
	{
		if (access(path[i], F_OK) == 0)
		{
			if (access(path[i], X_OK) == 0)
			{
				boul = 0;
				break ;
			}
		}
	}
	(void) argc;
	(void) argv;
	if (boul = 1)

	else
		exit ((perror("Error"), 1));
	i = 0;
	// gestion d erreur de proc enfant 

	int wstatus;
	int scode;
	
	wait(&wstatus);
	if (WIFEXITED(wstatus))
			if (0 == WEXITSTATUS(wstatus));
				exit (1);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

	// char	**path;

	// path = find_path(env);
	// if (argc != 5)
	// 	return (write(2, "Arguments Error\n", 17));
