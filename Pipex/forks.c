/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:22:44 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/01 19:37:31 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exit_if_error_fork(t_file *file, t_cmd **list_cmd)
{
	if (file->here_doc == 0)
		close(file->infile);
	close_all_pipefd(file, file->outfile);
	error_exit(strerror(errno), file, list_cmd);
}

static void	handle_here_doc(t_file *file, t_cmd **list_cmd)
{
	char	*limiter;
	char	*line;

	limiter = ft_strjoin(file->argv[2], "\n");
	if (!limiter)
		error_exit(strerror(errno), file, list_cmd); // keep strerror here ?
	ft_putstr_fd("pipe heredoc>", 1);
	while (1)
	{
		line = get_next_line(1);
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			free(limiter);
			break;
		}
		if (line)
			ft_putstr_fd("pipe heredoc>", 1);
		ft_putstr_fd(line, file->pipefd[0][1]);
		free(line);
	}
}

void	first_fork(t_file *file, t_cmd **list_cmd)
{
	file->pids[0] = fork();
	if (file->pids[0] == -1)
		exit_if_error_fork(file, list_cmd);
	if (file->pids[0] == 0)
	{
		if (file->here_doc == 0)
		{
			dup2(file->infile, STDIN_FILENO);
			dup2(file->pipefd[0][1], STDOUT_FILENO);
			close(file->infile);
		}
		else
			handle_here_doc(file, list_cmd);
		// close_all_pipefd(file, file->outfile);
		execve((*list_cmd)->path, (*list_cmd)->cmd_args, file->envp);
		error_exit(strerror(errno), file, list_cmd);
	}
}

void	create_forks_loop(t_file *file, t_cmd **list_cmd)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = *list_cmd;
	cmd = cmd->next;
	while (cmd && (i < file->nb_cmd - 2))
	{
		file->pids[i + 1] = fork();
		if (file->pids[i + 1] == -1)
			exit_if_error_fork(file, list_cmd);
		if (file->pids[i + 1] == 0)
		{
			dup2(file->pipefd[i][0], STDIN_FILENO);
			dup2(file->pipefd[i + 1][1], STDOUT_FILENO);
			if (file->here_doc == 0)
				close(file->infile);
			// close_all_pipefd(file, file->outfile);
			execve(cmd->path, cmd->cmd_args, file->envp);
			error_exit(strerror(errno), file, list_cmd);
		}
		i++;
		cmd = cmd->next;
	}
}

void	last_fork(t_file *file, t_cmd **list_cmd)
{
	int		last;
	t_cmd	*cmd_last;

	last = file->nb_cmd - 2;
	cmd_last = ft_lstlast(*list_cmd);
	file->pids[last + 1] = fork();
	if (file->pids[last + 1] == -1)
		exit_if_error_fork(file, list_cmd);
	if (file->pids[last + 1] == 0)
	{
		if (file->here_doc == 0)
			close(file->infile);
		dup2(file->pipefd[last][0], STDIN_FILENO);
		dup2(file->outfile, STDOUT_FILENO);
		// close_all_pipefd(file, file->outfile);
		execve(cmd_last->path, cmd_last->cmd_args, file->envp);
		error_exit(strerror(errno), file, list_cmd);
	}
}
