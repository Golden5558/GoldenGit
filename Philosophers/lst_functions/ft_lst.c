/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:08:27 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/15 05:48:58 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lst.h"

t_philo	*ft_lstnew(t_fork *r_fork, t_fork *l_fork, t_table *table, int id)
{
	t_philo	*data;

	data = malloc(sizeof(t_philo));
	if (!data)
		return (NULL);
	data->tread_id = 0;
	data->id = id;
	data->live = true;
	data->table = table;
	data->right_fork = r_fork;
	data->left_fork = l_fork;
	data->next = NULL;
	return (data);
}

void	ft_lstclear(t_philo **lst)
{
	t_philo	*current;
	t_philo	*next;

	if (!lst || !(*lst))
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

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (lst);
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_philo *lst)
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

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*prev;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		prev = ft_lstlast(*lst);
		prev->next = new;
	}
}
