/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:40:58 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/06 23:22:54 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_envp(char *cmd, char **envp, int *cmf)
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
			return (*cmf = 1, ft_free_all(path), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_all(path));
}

static char	*find_cmd_path(char **cmd_args, char **envp, int *cmf)
{
	if (ft_strchr(cmd_args[0], '/'))
	{
		if (access(cmd_args[0], X_OK) == 0)
		{
			*cmf = 1;
			return (ft_strdup(cmd_args[0]));
		}
		if (access(cmd_args[0], F_OK) == 0)
			*cmf = 2;
		return (NULL);
	}
	return (get_path_envp(cmd_args[0], envp, cmf));
}

void	pars_cmds(char **argv, char **envp, t_file *file, t_cmd **list_cmd)
{
	t_cmd	*tmp;
	char	**cmd_args;
	char	*path;
	int		cmd_found;
	int		i;

	i = 0;
	while (i < file->nb_cmd)
	{
		cmd_found = 0;
		cmd_args = ft_split(argv[file->start_cmd++], ' ');
		if (!cmd_args || !(*cmd_args))
			return (ft_free_all(cmd_args),
				error_exit("Error : Parsing cmd_args\n", file, list_cmd));
		path = find_cmd_path(cmd_args, envp, &cmd_found);
		tmp = ft_lstnew(path, cmd_args, i++, cmd_found);
		if (!tmp)
		{
			ft_free_all(cmd_args);
			if (path)
				free(path);
			error_exit("Error : Parsing ft_lstnew\n", file, list_cmd);
		}
		ft_lstadd_back(list_cmd, tmp);
	}
}

void	init_fd_and_pids(t_file *file, t_cmd **list_cmd)
{
	int	i;

	i = 0;
	file->pipefd = malloc(sizeof(int *) * (file->nb_cmd - 1));
	if (!file->pipefd)
	{
		ft_lstclear(list_cmd);
		ft_putstr_fd("Error malloc pipefd", 2);
		exit(0);
	}
	file->pids = malloc(sizeof(pid_t) * file->nb_cmd);
	if (!file->pids)
		return (ft_lstclear(list_cmd), free(file->pipefd),
			ft_putstr_fd("Error malloc pids", 2), exit(0));
	while (i < file->nb_cmd - 1)
	{
		file->pipefd[i] = malloc(sizeof(int) * 2);
		if (!file->pipefd[i])
			free_pipes_and_exit(file, list_cmd, i);
		if (pipe(file->pipefd[i]) == -1)
			free_pipes_and_exit(file, list_cmd, i);
		i++;
	}
}
