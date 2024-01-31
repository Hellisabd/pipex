/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:29:07 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/01/31 10:55:16 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "Libft/libft.h"

typedef struct pipex
{
	char	**path;
	char	**cmd;
	int		fd[2];
	int		fd1;
	int		fd2;
	int		pid1;
	int		pid2;
}	t_pipex;

void	exit_end(int status);
void	awk_gest(char **argv, t_pipex *p);
void	close_fd(t_pipex *p);

#endif