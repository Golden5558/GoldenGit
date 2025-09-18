/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompose_nb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduarte <vduarte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:00:13 by vduarte           #+#    #+#             */
/*   Updated: 2024/09/22 22:32:32 by vduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*fill_zero(char	*str, int to_size)
{
	char	*res;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(str);
	res = malloc(sizeof(char) * to_size + 1);
	if (!res)
		return ("0");
	i = 0;
	while (i < (to_size - size))
	{
		res[i] = '0';
		i ++;
	}
	j = 0;
	while (i <= to_size)
	{
		res[i] = str[j];
		i ++;
		j ++;
	}
	str[i] = '\0';
	return (res);
}

void	tens(char *dico, char *str, int nb)
{
	if (*str == '2')
		show_text_number(ft_strstr(dico, "20"));
	if (*str == '3')
		show_text_number(ft_strstr(dico, "30"));
	if (*str == '4')
		show_text_number(ft_strstr(dico, "40"));
	if (*str == '5')
		show_text_number(ft_strstr(dico, "50"));
	if (*str == '6')
		show_text_number(ft_strstr(dico, "60"));
	if (*str == '7')
		show_text_number(ft_strstr(dico, "70"));
	if (*str == '8')
		show_text_number(ft_strstr(dico, "80"));
	if (*str == '9')
		show_text_number(ft_strstr(dico, "90"));
	if (nb != 1 || str[1] != '0')
		ft_putchar(' ');
}

void	decompose(char *dico, char *str, int nb)
{
	char	c[2];

	if (*str != '0')
	{
		c[0] = *str;
		c[1] = '\0';
		show_text_number(ft_strstr(dico, c));
		ft_putchar(' ');
		show_text_number(ft_strstr(dico, "100"));
		ft_putchar(' ');
	}
	if (str[1] != '0')
	{
		if (str[1] == '1')
		{
			show_text_number(ft_strstr(dico, &str[1]));
			if (nb != 1)
				ft_putchar(' ');
		}
		else
			tens(dico, &str[1], nb);
	}
	if (str[1] != '1')
		unit(dico, str, nb);
}

char	*cut_to_3(char *str)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * 3 + 1);
	if (!res)
		return ("0");
	i = 0;
	while (i != 3)
	{
		res[i] = str[i];
		i ++;
	}
	return (res);
}

void	decompose_nb(char *dico, char *str)
{
	int		nb_3;
	int		mul_3;
	char	*tstr;

	mul_3 = 3;
	while (mul_3 < ft_strlen(str))
		mul_3 += 3;
	if (!(mul_3 == ft_strlen(str)))
		str = fill_zero(str, mul_3);
	nb_3 = ft_strlen(str) / 3;
	if (verif_zero(dico, str) == 0)
		return ;
	while (nb_3 > 0)
	{
		tstr = cut_to_3(str);
		decompose(dico, tstr, nb_3);
		if ((nb_3 > 1) && !(tstr[0] == 0 && tstr[1] == 0 && tstr[2] == 0))
			show_text_number(ft_strstr(dico, ft_getdec(ft_strlen(str))));
		nb_3 --;
		if (nb_3 > 0)
			ft_putchar(' ');
		str += 3;
	}
}
