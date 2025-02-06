/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:22:44 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/07 00:33:00 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_command(t_cmd *cmd, t_file *file, t_cmd **list_cmd)
{
	if (cmd->cmd_found == 0)
	{
		file->i = 0;
		close_pipefd_exept(file, -1, -1, -1);
		ft_putstr_fd(cmd->cmd_args[0], 2);
		error_exit(": command not found\n", file, list_cmd);
	}
	if (cmd->cmd_found == 2)
	{
		file->i = 0;
		close_pipefd_exept(file, -1, -1, -1);
		ft_putstr_fd(cmd->cmd_args[0], 2);
		error_exit(": permission denied\n", file, list_cmd);
	}
	execve(cmd->path, cmd->cmd_args, file->envp);
	file->i = 0;
	close_pipefd_exept(file, -1, -1, -1);
	ft_putstr_fd(cmd->cmd_args[0], 2);
	error_exit(": Exec format error\n", file, list_cmd);
}

static void	child_first_fork(t_file *file, t_cmd **list_cmd)
{
	t_cmd	*cmd;

	cmd = *list_cmd;
	if (file->here_doc == 1)
	{
		dup2(file->pipe_fd_hd[0], STDIN_FILENO);
		close(file->pipe_fd_hd[0]);
	}
	else
	{
		if (file->infile_access == 0)
		{
			dup2(file->infile, STDIN_FILENO);
			close(file->infile);
		}
	}
	dup2(file->pipefd[0][1], STDOUT_FILENO);
	close_pipefd_exept(file, 0, 1, -1);
	close(file->outfile);
	execute_command(cmd, file, list_cmd);
}

void	first_fork(t_file *file, t_cmd **list_cmd)
{
	file->pids[0] = fork();
	if (file->pids[0] == -1)
		exit_if_error_fork(file, list_cmd);
	if (file->pids[0] == 0)
		child_first_fork(file, list_cmd);
	else
	{
		if (file->here_doc == 0 && file->infile_access == 0)
			close(file->infile);
		else if (file->here_doc == 1)
			close(file->pipe_fd_hd[0]);
		close(file->pipefd[0][1]);
	}
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
			if (file->here_doc == 0 && file->infile_access == 0)
				close(file->infile);
			close(file->outfile);
			close_pipefd_exept(file, file->i, 0, ((file->i + 1) * 10) + 1);
			execute_command(cmd, file, list_cmd);
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
		if (file->here_doc == 0 && file->infile_access == 0)
			close(file->infile);
		dup2(file->pipefd[file->i][0], STDIN_FILENO);
		dup2(file->outfile, STDOUT_FILENO);
		close(file->outfile);
		close_pipefd_exept(file, file->i, 0, -1);
		execute_command(cmd_last, file, list_cmd);
	}
	else
	{
		close(file->outfile);
		close(file->pipefd[file->i][0]);
	}
}
