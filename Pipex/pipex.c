/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:08:24 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/02 23:22:02 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_command_amount(int argc, char **argv, char **envp, t_file *file)
{
	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
	{
		ft_putstr_fd("Too few arguments\n", 2);
		exit (1);
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
	file->argv = argv;
	file->envp = envp;
}

static void	wait_and_finishing_up(t_file *file, t_cmd **list_cmd)
{
	int	i;

	i = 0;
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
	exit (0);
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
	open_files(argv, argc, &file, &list_cmd);
	first_fork(&file, &list_cmd);
	if (file.nb_cmd > 2)
		create_forks_loop(&file, &list_cmd);
	last_fork(&file, &list_cmd);
	wait_and_finishing_up(&file, &list_cmd);
}
