/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 00:17:24 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/23 04:42:19 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_pile(t_pile *pile)
{
	while (pile)
	{
		ft_printf("%d --> index : %d", pile->content, pile->index);
		ft_printf(" --> target : %d", pile->target);
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
	// print_pile(a);
	ft_lstclear(&a);
	ft_lstclear(&b);
}
