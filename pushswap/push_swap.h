/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 00:17:04 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/25 01:54:46 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

typedef enum s_operations
{
	sa,
	sb,
	ss,
	pa,
	pb,
	ra,
	rb,
	rr,
	rra,
	rrb,
	rrr
}	t_operations;

// Parsing & utils:

void	check_input(char **args, t_pile **a);
void	pars_args_and_check_inputs(int argc, char **argv, t_pile **a);
void	error_exit(char *msg);
void	*ft_freeall(char **tab);

// Sorting :

int		get_index_from_value(t_pile **pile, int value);
void	apply_operator(t_pile **a, t_pile **b, t_operations op);
void	updt_index(t_pile **a, t_pile **b);
void	small_pile(t_pile **to_sort, t_pile **pile_2);
void	sort_piles(t_pile **a, t_pile **b);
void	move_targets_to_top(t_pile **from, t_pile **to, t_pile *to_move);
t_pile	*get_max_node(t_pile **pile);
t_pile	*get_lower_op_cost_node(t_pile **pile);

// To remove :

void	print_pile(t_pile *pile);

#endif