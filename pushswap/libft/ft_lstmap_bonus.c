/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:52:05 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/16 00:58:20 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pile	*ft_lstmap(t_pile *lst, int (*f)(int))
{
	t_pile	*ret;
	t_pile	*tmp;
	int		tmp2;

	if (!lst || !f)
		return (NULL);
	ret = NULL;
	while (lst)
	{
		tmp2 = f(lst->content);
		tmp = ft_lstnew(tmp2);
		if (!tmp)
			return (ft_lstclear(&ret), NULL);
		ft_lstadd_back(&ret, tmp);
		lst = lst->next;
	}
	return (ret);
}
