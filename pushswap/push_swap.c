/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 00:17:24 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/26 04:35:34 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	print_piles(t_pile *a, t_pile *b)
{
	ft_printf("\na pile :\n");
	while (a)
	{
		ft_printf("%d --> target : %d", a->content, a->target);
		ft_printf(" --> op_cost : %d", a->op_cost);
		ft_printf(" --> index : %d", a->index);
		a = a->next;
		ft_printf("\n");
	}
	ft_printf("\nb pile :\n");
	while (b)
	{
		ft_printf("%d --> target : %d", b->content, b->target);
		ft_printf(" --> op_cost : %d", b->op_cost);
		ft_printf(" --> index : %d", b->index);
		b = b->next;
		ft_printf("\n");
	}
}

void	small_pile(t_pile **to_sort, t_pile **pile_2)
{
	t_pile	*max_value;
	int		to_sort_len;

	to_sort_len = ft_lstsize(*to_sort);
	if (to_sort_len == 2)
	{
		if ((*to_sort)->content > (*to_sort)->next->content)
			apply_operator(to_sort, pile_2, sa);
	}
	else if (to_sort_len == 3)
	{
		updt_index(to_sort, pile_2);
		max_value = get_max_node(to_sort);
		if (max_value && max_value->index == 0)
			apply_operator(to_sort, pile_2, ra);
		else if (max_value && max_value->index == 1)
			apply_operator(to_sort, pile_2, rra);
		if ((*to_sort)->content > (*to_sort)->next->content)
			apply_operator(to_sort, pile_2, sa);
	}
}

int	main(int argc, char **argv)
{
	t_pile	*a;
	t_pile	*b;

	a = NULL;
	b = NULL;
	if (argc == 1)
		error_exit("Error\n");
	pars_args_and_check_inputs(argc, argv, &a);
	if (ft_lstsize(a) <= 3)
		small_pile(&a, &b);
	else if (ft_lstsize(a) > 3)
		sort_piles(&a, &b);
	print_piles(a, b);
	ft_lstclear(&a);
	ft_lstclear(&b);
}
