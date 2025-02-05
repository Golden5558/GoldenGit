/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:40:58 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/05 05:28:16 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_envp(char *cmd, char **envp, t_file *file)
{
	char	**path;
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	if (!cmd || !envp || !(*envp))
		return (NULL);
	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	path = ft_split(*envp, ':');
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (ft_free_all(path));
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (file->cmd_found = 1, ft_free_all(path), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_all(path));
}

static char	*find_cmd_path(char **cmd_args, char **envp, t_file *file)
{
	if (ft_strchr(cmd_args[0], '/'))
	{
		if (access(cmd_args[0], X_OK) == 0)
		{
			file->cmd_found = 1;
			return (ft_strdup(cmd_args[0]));
		}
		return (NULL);
	}
	return (get_path_envp(cmd_args[0], envp, file));
}

void	pars_cmds(char **argv, char **envp, t_file *file, t_cmd **list_cmd)
{
	t_cmd	*tmp;
	char	**cmd_args;
	char	*path;
	int		start;
	int		i;             // add cmd_found to list_cmd ?

	i = 0;
	start = file->start_cmd;
	while (i < file->nb_cmd)
	{
		cmd_args = ft_split(argv[start++], ' ');
		if (!cmd_args)
			error_exit("Error --> split cmd_args\n", file, list_cmd);
		path = find_cmd_path(cmd_args, envp, file);
		tmp = ft_lstnew(path, cmd_args, i++);
		if (!tmp)
		{
			ft_free_all(cmd_args);
			if (path)
				free(path);
			error_exit("Error --> lst_new parsing cmd\n", file, list_cmd);
		}
		ft_lstadd_back(list_cmd, tmp);
	}
}
static void	close_pipes_and_exit(t_file *file, t_cmd **list_cmd, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		close(file->pipefd[j][0]);
		close(file->pipefd[j][1]); // see bottom
		j++;
	}
	error_exit(strerror(errno), file, list_cmd);
}

void	init_fd_and_pids(t_file *file, t_cmd **list_cmd)
{
	int	i;

	i = 0;
	file->pipefd = malloc(sizeof(int *) * (file->nb_cmd - 1));
	if (!file->pipefd)
		error_exit("Error malloc pipefd", file, list_cmd);
	file->pids = malloc(sizeof(pid_t) * file->nb_cmd);
	if (!file->pids)
		error_exit("Error malloc pids", file, list_cmd);
	while (i < file->nb_cmd - 1)
	{
		file->pipefd[i] = malloc(sizeof(int) * 2);
		if (!file->pipefd[i])
			free_pipes_and_exit(file, list_cmd, i);
		if (pipe(file->pipefd[i]) == -1) // to fuse
			close_pipes_and_exit(file, list_cmd, i);
		i++;
	}
}
