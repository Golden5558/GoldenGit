/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 00:17:24 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/27 09:29:56 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(void)
{
	ft_putstr_fd("Error\n", 2);
	exit (EXIT_FAILURE);
}

void	small_pile(t_pile **to_sort, t_pile **pile_2)
{
	t_pile	*max_value;

	if (ft_lstsize(*to_sort) == 2)
	{
		if ((*to_sort)->content > (*to_sort)->next->content)
			apply_operator(to_sort, pile_2, sa);
	}
	else if (ft_lstsize(*to_sort) == 3)
	{
		updt_index(to_sort, pile_2);
		max_value = get_max_node(to_sort);
		if (max_value && max_value->index == 0)
		{
			apply_operator(to_sort, pile_2, ra);
			ft_putstr_fd("ra\n", 1);
		}
		else if (max_value && max_value->index == 1)
		{
			apply_operator(to_sort, pile_2, rra);
			ft_putstr_fd("rra\n", 1);
		}
		if ((*to_sort)->content > (*to_sort)->next->content)
			apply_operator(to_sort, pile_2, sa);
	}
}

static int	check_if_sorted(t_pile **a)
{
	t_pile	*tmp;

	if (!a || !(*a))
		return (1);
	tmp = *a;
	while (tmp)
	{
		if (tmp->next)
		{
			if (tmp->content > tmp->next->content)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_pile	*a;
	t_pile	*b;

	a = NULL;
	b = NULL;
	if (argc == 1)
		error_exit();
	pars_args_and_check_inputs(argv, &a);
	if (check_if_sorted(&a) == 1)
	{
		ft_lstclear(&a);
		ft_lstclear(&b);
		return (0);
	}
	if (ft_lstsize(a) <= 3)
		small_pile(&a, &b);
	else if (ft_lstsize(a) > 3)
		sort_piles(&a, &b);
	ft_lstclear(&a);
	ft_lstclear(&b);
}
