/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_secondary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:11:18 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/11 01:39:44 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_pile **lst, t_pile *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstdelone(t_pile *lst)
{
	if (!lst)
		return ;
	free (lst);
}

void	ft_lstiter(t_pile *lst, void (*f)(int))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

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
		tmp = ft_lstnew(tmp2, 0);
		if (!tmp)
			return (ft_lstclear(&ret), NULL);
		ft_lstadd_back(&ret, tmp);
		lst = lst->next;
	}
	return (ret);
}
