/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 03:33:45 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/07 17:50:04 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_if_error_fork(t_file *file, t_cmd **list_cmd)
{
	if (file->here_doc == 0 && file->infile_access == 0)
		close(file->infile);
	close(file->outfile);
	close_pipefd_exept(file, -1, -1, -1);
	error_exit("Error forking\n", file, list_cmd);
}

void	error_exit(char *msg, t_file *file, t_cmd **list_cmd)
{
	int	i;

	i = 0;
	ft_lstclear(list_cmd);
	if (file)
	{
		if (file->pids)
			free(file->pids);
		if (file->pipefd)
		{
			while (i < file->nb_cmd - 1)
				free(file->pipefd[i++]);
			free(file->pipefd);
		}
	}
	ft_putstr_fd(msg, 2);
	exit(0);
}

static void	close_all_fds_and_exit(t_file *file, t_cmd **list_cmd)
{
	if (file->infile_access == 0)
		close(file->infile);
	if (file->outfile_access == 0)
		close(file->outfile);
	close_pipefd_exept(file, -1, -1, -1);
	error_exit("", file, list_cmd);
}

void	verif_file_access(t_file *file, t_cmd **list_cmd)
{
	if (file->here_doc == 0)
	{
		if (file->infile_access == 1)
		{
			ft_putstr_fd(file->argv[1], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			close_all_fds_and_exit(file, list_cmd);
		}
		else if (file->infile_access == 2)
		{
			ft_putstr_fd(file->argv[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			close_all_fds_and_exit(file, list_cmd);
		}
	}
	if (file->outfile_access == 1)
	{
		ft_putstr_fd(file->argv[file->argc - 1], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		close_all_fds_and_exit(file, list_cmd);
	}
}
