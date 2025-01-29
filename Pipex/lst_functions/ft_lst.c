/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:08:27 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/28 06:52:58 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_cmd	*ft_lstnew(char *cmd, char **cmd_args, int index)
{
	t_cmd	*data;

	data = malloc(sizeof(t_cmd));
	if (!data)
		return (NULL);
	data->cmd = cmd;
	data->cmd_args = cmd_args;
	data->index = index;
	data->path = NULL;
	data->next = NULL;
	return (data);
}

void	ft_lstclear(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->path)
			free(current->path);
		ft_free_all(current->cmd_args);
		free(current);
		current = next;
	}
	*lst = NULL;
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_cmd *lst)
{
	int				i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*prev;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		prev = ft_lstlast(*lst);
		prev->next = new;
	}
}