/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:39:09 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/22 23:55:49 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

// int	main(void)
// {
// 	t_list	*l;
// 	t_list	*n;

// 	n = malloc(sizeof(t_list));
// 	l = NULL;
// 	n->next = NULL;
// 	n->content = ft_strdup("OK");
// 	ft_lstadd_back(&l, n);
// 	printf("%s\n", (char *)l->content);
// }