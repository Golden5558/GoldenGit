/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:31:15 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/23 04:47:23 by nberthal         ###   ########.fr       */
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

void	refresh_index(t_pile **pile)
{
	int		i;
	t_pile	*tmp;

	tmp = *pile;
	i = 1;
	if (!pile || !(*pile))
		return ;
	while (tmp)
	{
		tmp->index = i++;
		tmp = tmp->next;
	}
}

int	get_max_value(t_pile **pile)
{
	t_pile	*tmp;
	int		max_value;

	if (!pile || !(*pile))
		return (0);
	tmp = *pile;
	max_value = tmp->content;
	while (tmp)
	{
		if (tmp->content > max_value)
		{
			max_value = tmp->content;
		}
		tmp = tmp->next;
	}
	return (max_value);
}
