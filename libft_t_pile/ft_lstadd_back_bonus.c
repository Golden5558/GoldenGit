/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:39:09 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/16 05:50:42 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_pile **lst, t_pile *new)
{
	t_pile	*prev;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		prev = ft_lstlast(*lst);
		prev->next = new;
		new->prev = prev;
	}
}
