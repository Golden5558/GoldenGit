/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 03:00:43 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/26 03:47:30 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	substract_rrr(t_pile **a, t_pile **b, t_pile *pile_a, int *op_cost)
{
	int	len_a;
	int	len_b;
	int	to_remove;

	len_a = ft_lstsize(*a);
	len_b = ft_lstsize(*b);
	if (pile_a->index <= len_a / 2 && pile_a->index_target
		<= len_b / 2 && pile_a->index != 0 && pile_a->index_target != 0)
	{
		if (pile_a->index_target > pile_a->index)
			to_remove = pile_a->index;
		else
			to_remove = pile_a->index_target;
		*op_cost -= to_remove;
	}
	else if (pile_a->index > len_a / 2 && pile_a->index_target
		> len_b / 2 && pile_a != *a && pile_a->index_target != 0)
	{
		if ((len_a - pile_a->index) > (len_b
				- pile_a->index_target))
			to_remove = (len_b - pile_a->index_target);
		else
			to_remove = (len_a - pile_a->index);
		*op_cost -= to_remove;
	}
}

static void	calculate_op_cost(t_pile **a, t_pile **b)
{
	t_pile	*pile_a;
	int		op_cost;

	pile_a = *a;
	while (pile_a)
	{
		op_cost = 0;
		if (pile_a->index <= ft_lstsize(*a) / 2)
			op_cost += pile_a->index;
		else if (pile_a->index > ft_lstsize(*a) / 2)
			op_cost += ft_lstsize(*a) - pile_a->index;
		if (pile_a->index_target <= ft_lstsize(*b) / 2)
			op_cost += pile_a->index_target;
		else if (pile_a->index_target > ft_lstsize(*b) / 2)
			op_cost += ft_lstsize(*b) - pile_a->index_target;
		substract_rrr(a, b, pile_a, &op_cost);
		pile_a->op_cost = op_cost;
		pile_a = pile_a->next;
	}
}

static void	set_closest_smaller_target(t_pile **a, t_pile **b)
{
	t_pile	*b_temp;
	t_pile	*a_temp;
	t_pile	*smaller;

	a_temp = *a;
	while (a_temp)
	{
		b_temp = *b;
		if (b_temp)
			smaller = b_temp;
		while (b_temp)
		{
			if (b_temp->content < a_temp->content && (b_temp->content
					> smaller->content || smaller->content > a_temp->content))
				smaller = b_temp;
			b_temp = b_temp->next;
		}
		if (smaller->content == (*b)->content && a_temp->content
			< smaller->content)
			smaller = get_max_node(b);
		a_temp->target = smaller->content;
		a_temp->target_n = smaller;
		a_temp->index_target = smaller->index;
		a_temp = a_temp->next;
	}
}

static void	set_closest_bigger_target(t_pile **a, t_pile **b)
{
	t_pile	*b_temp;
	t_pile	*a_temp;
	t_pile	*bigger;

	a_temp = *a;
	while (a_temp)
	{
		b_temp = *b;
		if (b_temp)
			bigger = b_temp;
		while (b_temp)
		{
			if (b_temp->content > a_temp->content && (b_temp->content
					< bigger->content || bigger->content < a_temp->content))
				bigger = b_temp;
			b_temp = b_temp->next;
		}
		if (bigger->content == (*b)->content && a_temp->content
			> bigger->content)
			bigger = get_min_node(b);
		a_temp->target = bigger->content;
		a_temp->target_n = bigger;
		a_temp->index_target = bigger->index;
		a_temp = a_temp->next;
	}
}

void	sort_piles(t_pile **a, t_pile **b)
{
	while (ft_lstsize(*a) > 3 && ft_lstsize(*b) < 2)
		apply_operator(a, b, pb);
	while (ft_lstsize(*a) > 3)
	{
		set_closest_smaller_target(a, b);
		calculate_op_cost(a, b);
		move_targets_to_top(a, b, get_lower_op_cost_node(a), 0);
		apply_operator(a, b, pb);
	}
	small_pile(a, b);
	while (ft_lstsize(*b) > 0)
	{
		set_closest_bigger_target(b, a);
		calculate_op_cost(b, a);
		move_targets_to_top(b, a, get_lower_op_cost_node(b), 1);
		apply_operator(b, a, pb);
	}
	final_rotate_a(a, b);
}
