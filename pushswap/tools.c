/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 05:50:30 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/17 09:05:20 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_pile **pile)
{
	t_pile	*tmp1;
	t_pile	*tmp2;

	if (!pile || !(*pile) || !(*pile)->next)
		return ;
	tmp1 = *pile;
	tmp2 = (*pile)->next;
	tmp1->next = tmp2->next;
	if (tmp2->next)
		tmp2->next->prev = tmp1;
	tmp2->prev = NULL;
	tmp2->next = tmp1;
	tmp1->prev = tmp2;
	*pile = tmp2;
}

void	push(t_pile **pile_1, t_pile **pile_2)
{
	t_pile	*from;
	t_pile	*to;

	if (!pile_1 || !(*pile_1))
		return ;
	from = *pile_1;
	to = *pile_2;
	if (to)
		to->prev = from;
	from->next = to;
	from->prev = NULL;
	*pile_1 = from->next;
	if (*pile_1)
		(*pile_1)->prev = NULL;
}

void	rotate(t_pile **pile)
{
	t_pile	*new_bottom;
	t_pile	*actual_bottom;

	if (!pile || !(*pile) || !(*pile)->next)
		return ;
	new_bottom = *pile;
	actual_bottom = ft_lstlast(*pile);
	new_bottom->next->prev = NULL;
	actual_bottom->next = new_bottom;
	new_bottom->next = NULL;
	new_bottom->prev = actual_bottom;
	*pile = (*pile)->next;
}

void	reverse_rotate(t_pile **pile)
{
	t_pile	*new_top;
	t_pile	*actual_top;

	if (!pile || !(*pile) || !(*pile)->next)
		return ;
	actual_top = *pile;
	new_top = ft_lstlast(*pile);
	new_top->prev->next = NULL;
	new_top->prev = NULL;
	new_top->next = actual_top;
	actual_top->prev = new_top;
	*pile = new_top;
}
