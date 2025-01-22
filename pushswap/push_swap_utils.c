/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:31:15 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/17 09:07:14 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	*ft_freeall(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free (tab[i++]);
	if (tab)
		free (tab);
	tab = NULL;
	return (NULL);
}

void	print_pile(t_pile *pile)
{
	while (pile)
	{
		ft_printf("%d", pile->content);
		pile = pile->next;
	}
	ft_printf("\n");
}
