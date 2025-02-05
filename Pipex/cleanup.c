/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:33:23 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/05 04:44:23 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipefd_exept(t_file *file, int keep_p1, int keep_fd1, int p2_fd2)
{
	int	j;
	int	keep_pipe2;
	int	keep_fd2;

	keep_pipe2 = -1;
	keep_fd2 = -1;
	if (p2_fd2 >= 0)
	{
		keep_pipe2 = p2_fd2 / 10;
		keep_fd2 = p2_fd2 % 10;
	}
	while (file->i < file->nb_cmd - 1)
	{
		j = 0;
		while (j < 2)
		{
			if (!((file->i == keep_p1 && j == keep_fd1)
					|| (file->i == keep_pipe2 && j == keep_fd2)))
				close(file->pipefd[file->i][j]);
			j++;
		}
		file->i++;
	}
}

void	free_pipes_and_exit(t_file *file, t_cmd **list_cmd, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(file->pipefd[j++]);
	free(file->pipefd);
	file->pipefd = NULL;
	error_exit("Error malloc pipefd", file, list_cmd);
}

void	wait_and_finishing_up(t_file *file, t_cmd **list_cmd)
{
	int	i;

	i = 0;
	waitpid(file->pid_hd, NULL, 0);
	while (i < file->nb_cmd)
		waitpid(file->pids[i++], NULL, 0);
	ft_lstclear(list_cmd);
	if (file->pids)
		free(file->pids);
	i = 0;
	if (file->pipefd)
	{
		while (i < file->nb_cmd - 1)
			free(file->pipefd[i++]);
		free(file->pipefd);
	}
	exit(0);
}