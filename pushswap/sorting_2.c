/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:18:44 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/25 02:12:35 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_pile	*get_lower_op_cost_node(t_pile **pile)
{
	t_pile	*p;
	t_pile	*node;
	int		op_cost;

	if (!pile || !(*pile))
		return (NULL);
	p = *pile;
	node = p;
	op_cost = p->op_cost;
	while (p)
	{
		if (p->op_cost < op_cost)
		{
			op_cost = p->op_cost;
			node = p;
		}
		p = p->next;
	}
	return (node);
}

static void	apply_r_and_rr(t_pile **from, t_pile **to, t_pile *to_move)
{
	if (to_move->index <= ft_lstsize(*from) / 2 && to_move->index != 0)
	{
		apply_operator(from, to, ra);
		to_move->op_cost--;
	}
	else if (to_move->index > ft_lstsize(*from) / 2 && to_move->index != 0)
	{
		apply_operator(from, to, rra);
		to_move->op_cost--;
	}
	if (to_move->target_n->index <= ft_lstsize(*to) / 2
		&& to_move->target_n->index != 0)
	{
		apply_operator(from, to, rb);
		to_move->op_cost--;
	}
	else if (to_move->target_n->index > ft_lstsize(*to) / 2
		&& to_move->target_n->index != 0)
	{
		apply_operator(from, to, rrb);
		to_move->op_cost--;
	}
}

void	move_targets_to_top(t_pile **from, t_pile **to, t_pile *to_move)
{
	while ((to_move->index != 0 || to_move->target_n->index != 0) && to_move
		&& to_move->target_n)
	{
		if (to_move->index <= ft_lstsize(*from) / 2 && to_move->target_n->index
			<= ft_lstsize(*to) / 2 && to_move->index != 0
			&& to_move->target_n->index != 0)
		{
			apply_operator(from, to, rr);
			to_move->op_cost--;
		}
		else if (to_move->index > ft_lstsize(*from) / 2
			&& to_move->target_n->index > ft_lstsize(*to) / 2
			&& to_move->index != 0 && to_move->target_n->index != 0)
		{
			apply_operator(from, to, rrr);
			to_move->op_cost--;
		}
		else
			apply_r_and_rr(from, to, to_move);
	}
}
