/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:18:25 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/25 01:47:23 by nberthal         ###   ########.fr       */
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
	data->index_target = 0;
	data->op_cost = 0;
	data->index = index;
	data->target_n = NULL;
	data->prev = NULL;
	data->next = NULL;
	return (data);
}
