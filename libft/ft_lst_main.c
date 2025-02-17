/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:08:27 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/11 01:39:38 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pile	*ft_lstnew(int content, int index)
{
	t_pile	*data;

	data = malloc(sizeof(t_pile));
	if (!data)
		return (NULL);
	data->content = content;
	data->target = 0;
	data->index_target = 0;
	data->op_cost = 0;
	data->index = index;
	data->target_n = NULL;
	data->prev = NULL;
	data->next = NULL;
	return (data);
}

void	ft_lstclear(t_pile **lst)
{
	t_pile	*current;
	t_pile	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

t_pile	*ft_lstlast(t_pile *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_pile *lst)
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

void	ft_lstadd_back(t_pile **lst, t_pile *new)
{
	t_pile	*prev;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		prev = ft_lstlast(*lst);
		prev->next = new;
		new->prev = prev;
	}
}
