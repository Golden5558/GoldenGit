/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:18:25 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/23 03:49:16 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_pile	*ft_lstnew(int content, int index)
{
	t_pile	*data;

	data = malloc(sizeof(t_pile));
	if (!data)
		return (NULL);
	data->content = content;
	data->target = 0;
	data->op_cost = 0;
	data->index = index;
	data->prev = NULL;
	data->next = NULL;
	return (data);
}
