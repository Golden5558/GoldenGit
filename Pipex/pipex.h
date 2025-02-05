/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:08:32 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/05 05:12:04 by nberthal         ###   ########.fr       */
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
	int		argc;
	char	**argv;
	char	**envp;
	pid_t	*pids;
	pid_t	pid_hd;
	int		**pipefd;
	int		pipe_fd_hd[2];
	int		i;
	int		infile;
	int		infile_access;
	int		outfile;
	int		outfile_access;
	int		here_doc;
	int		cmd_found;
	int		nb_cmd;
	int		start_cmd;
}	t_file;

void	error_exit(char *msg, t_file *file, t_cmd **list_cmd);
void	close_pipefd_exept(t_file *file, int keep_p1, int keep_fd1, int p2_fd2);
void	exit_if_error_fork(t_file *file, t_cmd **list_cmd);
void	wait_and_finishing_up(t_file *file, t_cmd **list_cmd);
void	error_file_access(t_file *file, t_cmd **list_cmd);
void	free_pipes_and_exit(t_file *file, t_cmd **list_cmd, int i);

// Parsing :

void	init_fd_and_pids(t_file *file, t_cmd **list_cmd);
void	pars_cmds(char **argv, char **envp, t_file *file, t_cmd **list_cmd);

// Forks :

void	first_fork(t_file *file, t_cmd **list_cmd);
void	create_forks_loop(t_file *file, t_cmd **list_cmd);
void	last_fork(t_file *file, t_cmd **list_cmd);

#endif

// a tester et reproduire --> cat | cat | ls
// bash history command error oli


// access + open -1 to differenciate bettween :

// - namefile: No such file or directory

// - namefile: Permission denied

// access + errno on cmd_path to differenciate bettween :

// - Command not found