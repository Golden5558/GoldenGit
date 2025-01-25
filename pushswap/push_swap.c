/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 00:17:24 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/23 23:29:26 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_pile(t_pile *pile)
{
	while (pile)
	{
		ft_printf("%d --> target : %d", pile->content, pile->target);
		ft_printf(" --> op_cost : %d", pile->op_cost);
		ft_printf(" --> index : %d", pile->index);
		pile = pile->next;
		ft_printf("\n");
	}
}

int	main(int argc, char **argv)
{
	t_pile	*a;
	t_pile	*b;

	a = NULL;
	b = NULL;
	if (argc == 1)
		error_exit("Error : No argument given\n");
	pars_args_and_check_inputs(argc, argv, &a);
	if (ft_lstsize(a) <= 3)
		small_pile(&a, &b);
	else if (ft_lstsize(a) > 3)
		sort_piles(&a, &b);
	ft_printf("\na pile :\n");
	print_pile(a);
	ft_printf("\nb pile :\n");
	print_pile(b);
	ft_lstclear(&a);
	ft_lstclear(&b);
}
