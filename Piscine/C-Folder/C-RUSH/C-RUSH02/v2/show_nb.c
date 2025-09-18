/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_nb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduarte <vduarte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:52:37 by vduarte           #+#    #+#             */
/*   Updated: 2024/09/22 18:37:21 by vduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_getdec(int dec)
{
	char	*cdec;
	int		i;

	i = 0;
	cdec = malloc(sizeof(char) * dec + 1);
	if (!dec)
		return (NULL);
	if (dec <= 6)
		return ("1000");
	cdec[i] = '1';
	while (i++ < dec - 1)
		cdec[i] = '0';
	cdec[i] = '\0';
	return (cdec);
}

void	show_text_number(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i] != ':')
		i ++;
	i ++;
	while (str[i] != '\n' && str[i] == ' ')
		i ++;
	while (str[i] != '\n')
	{
		if ((str[i] == ' ') && ((str[i + 1] != ' ') && (str[i + 1] != '\n')))
		{
			ft_putchar(str[i]);
		}
		else if (str[i] != ' ')
			ft_putchar(str[i]);
		i ++;
	}
}
