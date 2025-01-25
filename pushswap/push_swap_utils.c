/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:31:15 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/24 23:01:08 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	*ft_freeall(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free (tab[i++]);
	if (tab)
		free (tab);
	tab = NULL;
	return (NULL);
}

void	updt_index(t_pile **a, t_pile **b)
{
	int		i;
	t_pile	*pile_a;
	t_pile	*pile_b;

	if (!a)
		return ;
	pile_a = *a;
	i = 0;
	while (pile_a)
	{
		pile_a->index = i++;
		pile_a = pile_a->next;
	}
	i = 0;
	if (!b || !(*b))
		return ;
	pile_b = *b;
	while (pile_b)
	{
		pile_b->index = i++;
		pile_b = pile_b->next;
	}
}

int	get_index_from_value(t_pile **pile, int value)
{
	t_pile	*tmp;

	if (!pile || !(*pile))
		return (-1);
	tmp = *pile;
	while (tmp)
	{
		if (tmp->content == value)
			return (tmp->index);
		tmp = tmp->next;
	}
	return (-1);
}

t_pile	*get_max_node(t_pile **pile)
{
	t_pile	*tmp;
	t_pile	*max_value;

	if (!pile || !(*pile))
		return (NULL);
	tmp = *pile;
	max_value = tmp;
	while (tmp)
	{
		if (tmp->content > max_value->content)
		{
			max_value = tmp;
		}
		tmp = tmp->next;
	}
	return (max_value);
}
