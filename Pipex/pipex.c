/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:08:24 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/07 16:46:54 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_here_doc(t_file *file, t_cmd **list_cmd)
{
	char	*limiter;
	char	*line;

	limiter = ft_strjoin(file->argv[2], "\n");
	if (!limiter)
		error_exit("Error --> strjoin limiter\n", file, list_cmd);
	ft_putstr_fd("pipe heredoc>", 1);
	while (1)
	{
		line = get_next_line(0);
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			free(limiter);
			break ;
		}
		if (line)
			ft_putstr_fd("pipe heredoc>", 1);
		ft_putstr_fd(line, file->pipe_fd_hd[1]);
		free(line);
	}
}

static void	pipe_here_doc(t_file *file, t_cmd **list_cmd)
{
	int	i;

	i = 0;
	if (pipe(file->pipe_fd_hd) == -1)
		exit_if_error_fork(file, list_cmd);
	file->pid_hd = fork();
	if (file->pid_hd == -1)
		exit_if_error_fork(file, list_cmd);
	if (file->pid_hd == 0)
	{
		handle_here_doc(file, list_cmd);
		close_pipefd_exept(file, -1, -1, -1);
		close(file->outfile);
		close(file->pipe_fd_hd[0]);
		close(file->pipe_fd_hd[1]);
		ft_lstclear(list_cmd);
		if (file->pids)
			free(file->pids);
		while (i < file->nb_cmd - 1)
			free(file->pipefd[i++]);
		free(file->pipefd);
		exit(0);
	}
	waitpid(file->pid_hd, NULL, 0);
	close(file->pipe_fd_hd[1]);
}

static void	open_files(char **argv, int ac, t_file *file)
{
	if (file->here_doc == 0)
	{
		file->infile = open(argv[1], O_RDONLY);
		if (file->infile < 0)
		{
			if (access(argv[1], F_OK) == -1)
				file->infile_access = 2;
			else
				file->infile_access = 1;
		}
		file->outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->outfile < 0)
			file->outfile_access = 1;
	}
	else if (file->here_doc == 1)
	{
		file->outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file->outfile < 0)
		{
			file->outfile_access = 1;
		}
	}
}

static void	get_command_amount(int argc, char **argv, char **envp, t_file *file)
{
	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
	{
		ft_putstr_fd("Too few arguments\n", 2);
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
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
	file->argc = argc;
	file->argv = argv;
	file->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_file	file;
	t_cmd	*list_cmd;

	list_cmd = NULL;
	ft_memset(&file, 0, sizeof(t_file));
	get_command_amount(argc, argv, envp, &file);
	pars_cmds(argv, envp, &file, &list_cmd);
	init_fd_and_pids(&file, &list_cmd);
	open_files(argv, argc, &file);
	if (file.infile < 0 || file.outfile < 0)
		verif_file_access(&file, &list_cmd);
	if (file.here_doc == 1)
		pipe_here_doc(&file, &list_cmd);
	first_fork(&file, &list_cmd);
	if (file.nb_cmd > 2)
		create_forks_loop(&file, &list_cmd);
	last_fork(&file, &list_cmd);
	wait_and_finishing_up(&file, &list_cmd);
}
