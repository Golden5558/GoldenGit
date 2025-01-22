/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 00:17:04 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/17 09:06:25 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

// Parsing & utils:

void	check_input(char **args, t_pile **a);
void	pars_args_and_check_inputs(int argc, char **argv, t_pile **a);
void	error_exit(char *msg);
void	*ft_freeall(char **tab);
void	print_pile(t_pile *pile);

#endif