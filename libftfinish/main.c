/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 05:19:09 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/23 20:44:03 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*map_length(void *s)
{
	char	*str;

	str = malloc(30);
	if (str != NULL)
		sprintf(str, "__%lX", strlen((char *)s));
	return (str);
}

void	delete(void *content)
{
	char	*str;

	str = (char *)content;
	if (str == NULL)
		return ;
	free(content);
}

int	main(void)
{
	t_list	*s;
	t_list	*t;
	t_list	*y;

	s = ft_lstnew(ft_strdup("1"));
	t = s;
	printf("Element %s\n", (char *)s->content);
	s->next = ft_lstnew(ft_strdup("2"));
	s = s->next;
	printf("Element %s\n", (char *)s->content);
	s->next = ft_lstnew(ft_strdup("3"));
	s = s->next;
	printf("Element %s\n", (char *)s->content);
	y = ft_lstmap(t, map_length, delete);
	ft_lstclear(&t, delete);
	ft_lstclear(&y, delete);
}
