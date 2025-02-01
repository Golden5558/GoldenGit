/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:40:58 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/01 19:48:50 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char	**join_arg_after_cmd(char **args)
// {
// 	char	**new_cmd_args;
// 	int		i;
//
// 	i = 0;
// }

static char	*get_path(char *cmd, char **envp)
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

void	pars_cmds(char **argv, char **envp, t_file *file, t_cmd **list_cmd)
{
	t_cmd	*tmp;
	char	**cmd_args;
	char	*path;
	int		start;
	int		index;

	index = 0;
	start = file->start_cmd;
	tmp = *list_cmd;
	while (index < file->nb_cmd)
	{
		cmd_args = ft_split(argv[start++], ' ');
		if (!cmd_args)
			error_exit(strerror(errno), file, list_cmd);
		if (ft_strchr(cmd_args[0], '/'))
		{
			if (access(cmd_args[0], X_OK) == 0)
				path = ft_strdup(cmd_args[0]);
		}
		else
			path = get_path(cmd_args[0], envp);
		// if (ft_strchr(argv[start_cmd], '\'') || ft_strchr(argv[start_cmd], '\"'))
		tmp = ft_lstnew(path, cmd_args, index++);
		ft_lstadd_back(list_cmd, tmp);
	}
}

void	open_files(char **argv, int ac, t_file *file, t_cmd **list_cmd)
{
	if (file->here_doc == 0)
	{
		file->infile = open(argv[1], O_RDONLY);
		if (file->infile < 0)
		{
			close_all_pipefd(file, -1);
			error_exit(strerror(errno), file, list_cmd);
		}
		file->outfile = open(argv[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->outfile < 0)
		{
			close_all_pipefd(file, file->infile);
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

void	init_fd_and_pids(t_file *file, t_cmd **list_cmd)
{
	file->pids = malloc(sizeof(pid_t) * file->nb_cmd);
	if (!file->pids)
		error_exit(strerror(errno), file, list_cmd); // keep errno here ? custom
}
