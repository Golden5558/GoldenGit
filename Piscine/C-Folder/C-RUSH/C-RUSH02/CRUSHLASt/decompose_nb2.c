/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompose_nb2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:50:54 by vduarte           #+#    #+#             */
/*   Updated: 2024/09/22 23:36:32 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	unit(char *dico, char *str, int nb)
{
    if (str[2] != '0')
        show_text_number(ft_strstr(dico, &str[2]));
	if (nb != 1)
		ft_putchar(' ');
}
