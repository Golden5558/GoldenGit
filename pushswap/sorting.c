/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 03:00:43 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/23 04:49:54 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_pile(t_pile **to_sort, t_pile **pile_2)
{
	int	size_a;
	int	max_value;

	size_a = ft_lstsize(*to_sort);
	if (size_a == 2)
	{
		if ((*to_sort)->content > (*to_sort)->next->content)
			apply_operator(to_sort, pile_2, sa);
	}
	else if (size_a == 3)
	{
		max_value = get_max_value(to_sort);
		if ((*to_sort)->content == max_value)
			apply_operator(to_sort, pile_2, ra);
		else if ((*to_sort)->next->content == max_value)
			apply_operator(to_sort, pile_2, rra);
		if ((*to_sort)->content > (*to_sort)->next->content)
			apply_operator(to_sort, pile_2, sa);
	}
	refresh_index(to_sort);
	refresh_index(pile_2);
}

static void	calculate_op_cost(t_pile **a, t_pile **b)
{
	int	op_cost;
	
	
}

static void	set_target(t_pile **a, t_pile **b)
{
	t_pile	*b_temp;
	t_pile	*a_temp;
	int		closest_smaller;

	a_temp = *a;
	while (a_temp)
	{
		b_temp = *b;
		if (b_temp)
			closest_smaller = b_temp->content;
		while (b_temp)
		{
			if (b_temp->content < a_temp->content && b_temp->content
				>= closest_smaller)
				closest_smaller = b_temp->content;
			b_temp = b_temp->next;
		}
		a_temp->target = closest_smaller;
		a_temp = a_temp->next;
	}
}

void	sort_piles(t_pile **a, t_pile **b)
{
	while (ft_lstsize(*a) > 3 && ft_lstsize(*b) < 2)
		apply_operator(a, b, pb);
	if (ft_lstsize(*a) == 3)
	{
		small_pile(a, b);
		// to follow;
	}
	set_target(a, b);
	refresh_index(a);
	refresh_index(b);
	calculate_op_cost(a, b);
	ft_printf("\na pile :\n");
	print_pile(*a);
	ft_printf("\nb pile :\n");
	print_pile(*b);
}
