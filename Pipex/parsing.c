/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:40:58 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/02 23:28:57 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_envp(char *cmd, char **envp)
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
			return (ft_free_all(path), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_all(path));
}

static char	*find_cmd_path(char **cmd_args, char **envp)
{
	if (ft_strchr(cmd_args[0], '/'))
	{
		if (access(cmd_args[0], X_OK) == 0)
			return (ft_strdup(cmd_args[0]));
		return (NULL);
	}
	return (get_path_envp(cmd_args[0], envp));
}

void	pars_cmds(char **argv, char **envp, t_file *file, t_cmd **list_cmd)
{
	char	**cmd_args;
	char	*path;
	int		start;
	int		i;

	i = 0;
	start = file->start_cmd;
	while (i < file->nb_cmd)
	{
		cmd_args = ft_split(argv[start++], ' ');
		if (!cmd_args)
			error_exit(strerror(errno), file, list_cmd);
		path = find_cmd_path(cmd_args, envp);
		if (!path)
		{
			ft_free_all(cmd_args);
			error_exit(strerror(errno), file, list_cmd);
		}
		ft_lstadd_back(list_cmd, ft_lstnew(path, cmd_args, i++));
	}
}

void	open_files(char **argv, int ac, t_file *file, t_cmd **list_cmd)
{
	if (file->here_doc == 0)
	{
		file->infile = open(argv[1], O_RDONLY);
		if (file->infile < 0)
		{
			close_pipefd_exept(file, -1, -1, -1);
			error_exit(strerror(errno), file, list_cmd);
		}
		file->outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->outfile < 0)
		{
			close(file->infile);
			close_pipefd_exept(file, -1, -1, -1);
			error_exit(strerror(errno), file, list_cmd);
		}
	}
	else if (file->here_doc == 1)
	{
		file->outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file->outfile < 0)
		{
			error_exit(strerror(errno), file, list_cmd);
		}
	}
}
