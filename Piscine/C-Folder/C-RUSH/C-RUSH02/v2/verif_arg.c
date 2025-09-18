/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduarte <vduarte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:33:52 by vduarte           #+#    #+#             */
/*   Updated: 2024/09/22 22:31:44 by vduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	verif_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i ++;
	}
	return (1);
}

int	verif_zero(char *dico, char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (str[i] == '0')
		i ++;
	if (i == size)
	{
		show_text_number(ft_strstr(dico, "0"));
		return (0);
	}
	return (1);
}