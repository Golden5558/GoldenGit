/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:52:05 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/24 04:31:03 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*tmp;
	void	*tmp2;

	if (!lst || !f || !del)
		return (NULL);
	ret = NULL;
	while (lst)
	{
		tmp2 = f(lst->content);
		tmp = ft_lstnew(tmp2);
		if (!tmp)
			return (del(tmp2), ft_lstclear(&ret, del), NULL);
		ft_lstadd_back(&ret, tmp);
		lst = lst->next;
	}
	return (ret);
}
