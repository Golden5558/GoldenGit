/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:08:24 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/29 10:06:01 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *msg, t_file *file, t_cmd **list_cmd)
{
	ft_lstclear(list_cmd);
	if (file)
	{
		if (file->pids)
			// free
		if (file->pipefd)
			// free
		return ; //to remove
	}
	ft_putstr_fd(msg, stderr);
	exit (EXIT_FAILURE);
}

static void	get_commands_amount(int argc, char **argv, t_file *file)
{
	if (argc < 5 || (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
	{
		ft_putstr_fd("Too few arguments\n", stderr);
		exit (1);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		file->nb_cmd = argc - 4;
		file->start_cmd = 3;
		file->here_doc = 1;
	}
	else
	{
		file->nb_cmd = argc - 3;
		file->start_cmd = 2;
	}
}

void	create_forks_loop(t_file *file, t_cmd ** list_cmd)
{
	int	i;

	i = 0;
	while (i < file->nb_cmd - 2)
	{
		file->pids[i] = fork();
		if (file->pids[i] == -1)
		{
			// handle
		}
		if (file->pids[i] == 0)
		{
			dup2(file->pipefd[i][0], STDIN_FILENO);
			dup2(file->pipefd[i][1], STDOUT_FILENO);
		}
	}
}

void	first_fork(t_file *file, t_cmd **list_cmd, char *envp)
{
	file->pids[0] = fork();
	if (file->pids[0] == -1)
	{
		if (file->here_doc == 0)
			close(file->infile);
		else
			// handle close here doc
		close(file->outfile);
		close(file->pipefd[0][0]);
		close(file->pipefd[0][1]);
		error_exit(strerror(errno), file, list_cmd);
	}
	if (file->pids[0] == 0)
	{
		if (file->here_doc == 0)
			dup2(file->infile, STDIN_FILENO);
		else
		 // handle here doc
		dup2(file->pipefd[1], STDOUT_FILENO);
		close(file->infile);
		close(file->outfile);
		close(file->pipefd[0][0]);
		close(file->pipefd[0][1]);
		execve((*list_cmd)->path, (*list_cmd)->cmd_args, envp);
		error_exit(strerror(errno), file, list_cmd);
	}
}

void	last_fork(t_file *file, t_cmd **list_cmd, char *envp)
{
	file->pids[0] = fork();
	if (file->pids[0] == -1)
	{
		if (file->here_doc == 0)
			close(file->infile);
		else
			// handle close here doc
		close(file->outfile);
		close(file->pipefd[0][0]);
		close(file->pipefd[0][1]);
		error_exit(strerror(errno), file, list_cmd);
	}
	if (file->pids[0] == 0)
	{
		if (file->here_doc == 0)
			dup2(file->infile, STDIN_FILENO);
		else
		 // handle here doc
		dup2(file->pipefd[1], STDOUT_FILENO);
		close(file->infile);
		close(file->outfile);
		close(file->pipefd[0][0]);
		close(file->pipefd[0][1]);
		execve((*list_cmd)->path, (*list_cmd)->cmd_args, envp);
		error_exit(strerror(errno), file, list_cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_file	file;
	t_cmd	*list_cmd;

	list_cmd = NULL;
	ft_memset(&file, 0, sizeof(t_file));
	get_commands_amount(argc, argv, &file);
	pars_cmds(argv, envp, &file, &list_cmd);
	init_fd_and_pids(&file, &list_cmd);
	open_files(argv, argc, &file, &list_cmd);
	
}
