/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:18:44 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/26 04:04:17 by nberthal         ###   ########.fr       */
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

static void	apply_rr(t_pile **from, t_pile **to, t_pile *to_move, int i)
{
	if (to_move->target_n->index <= ft_lstsize(*to) / 2
		&& to_move->target_n->index != 0)
	{
		apply_operator(from, to, rb);
		if (i == 0)
			ft_putstr_fd("rb\n", 1);
		else
			ft_putstr_fd("ra\n", 1);
	}
	else if (to_move->target_n->index > ft_lstsize(*to) / 2
		&& to_move->target_n->index != 0)
	{
		apply_operator(from, to, rrb);
		if (i == 0)
			ft_putstr_fd("rrb\n", 1);
		else
			ft_putstr_fd("rra\n", 1);
	}
}

static void	apply_r_and_rr(t_pile **from, t_pile **to, t_pile *to_move, int i)
{
	if (to_move->index <= ft_lstsize(*from) / 2 && to_move->index != 0)
	{
		apply_operator(from, to, ra);
		if (i == 0)
			ft_putstr_fd("ra\n", 1);
		else
			ft_putstr_fd("rb\n", 1);
	}
	else if (to_move->index > ft_lstsize(*from) / 2 && to_move->index != 0)
	{
		apply_operator(from, to, rra);
		if (i == 0)
			ft_putstr_fd("rra\n", 1);
		else
			ft_putstr_fd("rrb\n", 1);
	}
	apply_rr(from, to, to_move, i);
}

void	move_targets_to_top(t_pile **from, t_pile **to, t_pile *to_move, int i)
{
	while (to_move && to_move->target_n && (to_move->index != 0
			|| to_move->target_n->index != 0))
	{
		if (to_move->index <= ft_lstsize(*from) / 2 && to_move->target_n->index
			<= ft_lstsize(*to) / 2 && to_move->index != 0
			&& to_move->target_n->index != 0)
			apply_operator(from, to, rr);
		else if (to_move->index > ft_lstsize(*from) / 2
			&& to_move->target_n->index > ft_lstsize(*to) / 2
			&& to_move->index != 0 && to_move->target_n->index != 0)
			apply_operator(from, to, rrr);
		else
			apply_r_and_rr(from, to, to_move, i);
	}
}

void	final_rotate_a(t_pile **a, t_pile **b)
{
	t_pile	*tmp;

	tmp = get_min_node(a);
	if (!tmp || !a || !(*a))
		return ;
	if (tmp->index <= ft_lstsize(*a) / 2)
	{
		while (tmp != *a)
		{
			apply_operator(a, b, ra);
			ft_putstr_fd("ra\n", 1);
		}
	}
	else
	{
		while (tmp != *a)
		{
			apply_operator(a, b, rra);
			ft_putstr_fd("rra\n", 1);
		}
	}
}
