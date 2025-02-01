/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:08:32 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/01 14:38:11 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include "./lst_functions/ft_lst.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_file
{
	char	**argv;
	char	**envp;
	pid_t	*pids;
	int		infile;
	int		outfile;
	int		here_doc;
	int		nb_cmd;
	int		start_cmd;
	int		**pipefd;
}	t_file;

void	error_exit(char *msg, t_file *file, t_cmd **list_cmd);
void	close_all_pipefd(t_file *file, int to_close);

// Parsing :

void	open_files(char **argv, int ac, t_file *file, t_cmd **list_cmd);
void	init_fd_and_pids(t_file *file, t_cmd **list_cmd);
void	pars_cmds(char **argv, char **envp, t_file *file, t_cmd **list_cmd);

// Forks :

void	first_fork(t_file *file, t_cmd **list_cmd);
void	create_forks_loop(t_file *file, t_cmd **list_cmd);
void	last_fork(t_file *file, t_cmd **list_cmd);

#endif

// a tester et reproduire --> cat | cat | ls