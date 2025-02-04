/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:22:44 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/04 17:41:20 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_if_error_fork(t_file *file, t_cmd **list_cmd)
{
	if (file->here_doc == 0)
		close(file->infile);
	close(file->outfile);
	close_pipefd_exept(file, -1, -1, -1);
	error_exit(strerror(errno), file, list_cmd);
}

void	first_fork(t_file *file, t_cmd **list_cmd)
{
	file->pids[0] = fork();
	if (file->pids[0] == -1)
		exit_if_error_fork(file, list_cmd);
	if (file->pids[0] == 0)
	{
		if (file->here_doc == 1)
		{
			dup2(file->pipe_fd_hd[0], STDIN_FILENO);
			close(file->pipe_fd_hd[0]);
		}
		else
		{
			dup2(file->infile, STDIN_FILENO);
			close(file->infile);
		}
		dup2(file->pipefd[0][1], STDOUT_FILENO);
		close_pipefd_exept(file, 0, 1, -1);
		close(file->outfile);
		execve((*list_cmd)->path, (*list_cmd)->cmd_args, file->envp);
		error_exit(strerror(errno), file, list_cmd);
	}
	if (file->here_doc == 0)
		close(file->infile);
	else
		close(file->pipe_fd_hd[0]);
	close(file->pipefd[0][1]);
}

void	create_forks_loop(t_file *file, t_cmd **list_cmd)
{
	t_cmd	*cmd;

	cmd = *list_cmd;
	cmd = cmd->next;
	while (cmd && cmd->next && file->i < file->nb_cmd - 2)
	{
		file->pids[file->i + 1] = fork();
		if (file->pids[file->i + 1] == -1)
			exit_if_error_fork(file, list_cmd);
		if (file->pids[file->i + 1] == 0)
		{
			dup2(file->pipefd[file->i][0], STDIN_FILENO);
			dup2(file->pipefd[file->i + 1][1], STDOUT_FILENO);
			if (file->here_doc == 0)
				close(file->infile);
			close(file->outfile);
			close_pipefd_exept(file, file->i, 0, ((file->i + 1) * 10) + 1);
			execve(cmd->path, cmd->cmd_args, file->envp);
			error_exit(strerror(errno), file, list_cmd);
		}
		close(file->pipefd[file->i][0]);
		close(file->pipefd[file->i + 1][1]);
		file->i++;
		cmd = cmd->next;
	}
}

void	last_fork(t_file *file, t_cmd **list_cmd)
{
	t_cmd	*cmd_last;

	cmd_last = ft_lstlast(*list_cmd);
	file->pids[file->nb_cmd - 1] = fork();
	if (file->pids[file->nb_cmd - 1] == -1)
		exit_if_error_fork(file, list_cmd);
	if (file->pids[file->nb_cmd - 1] == 0)
	{
		if (file->here_doc == 0)
			close(file->infile);
		dup2(file->pipefd[file->i][0], STDIN_FILENO);
		dup2(file->outfile, STDOUT_FILENO);
		close(file->outfile);
		close_pipefd_exept(file, file->i, 0, -1);
		execve(cmd_last->path, cmd_last->cmd_args, file->envp);
		error_exit(strerror(errno), file, list_cmd);
	}
	else
	{
		close(file->outfile);
		close(file->pipefd[file->i][0]);
	}
}
