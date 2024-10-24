/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:50:15 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/24 04:40:39 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lsts;
	t_list	*lstfinal;

	if (!lst || !del || !*lst)
		return ;
	lsts = *lst;
	lstfinal = *lst;
	while (*lst)
	{
		lsts = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lsts;
	}
	lstfinal = NULL;
}
