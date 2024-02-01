/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:29:07 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/02/01 10:46:35 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "Libft/libft.h"

typedef struct pipex
{
	char	**path;
	char	**cmd;
	int		fd[2];
	int		i;
	int		fdin;
	int		fdout;
	int		pid;
	int		n;
	int		boul;
}	t_pipex;

void	exit_end(t_pipex *p, int status, int boul);
void	open_files(t_pipex *p, char **argv, int argc, char **env);
void	awk_gest(char **argv, t_pipex *p);
void	close_fd(t_pipex *p);
char	**find_path(char **env);
void	parsing_cmd(t_pipex *p, char **argv);

#endif