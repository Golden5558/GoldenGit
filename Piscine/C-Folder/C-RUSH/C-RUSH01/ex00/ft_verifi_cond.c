/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifi_cond.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amulet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:48:15 by amulet            #+#    #+#             */
/*   Updated: 2024/09/15 20:23:37 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_error(void);

int	ft_verifi_cond(int argc, char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (argv[1][j])
		j++;
	if (argc != 2 || j != 31)
		ft_error();
	while (argv[1][i] && i < j)
	{
		if (argv[1][i] != ' ' && (argv[1][i] < '1' || argv[1][i] > '4'))
			ft_error();
		i++;
		if (argv[1][i] != ' ' && i < j)
			ft_error();
		i++;
	}
	return (0);
}

int	ft_error(void)
{
	write(1, "Error\n", 6);
	return (1);
}
/*

int	main()
{
	int o;

	o = ft_verifi_cond("1 2 3 4 1 2 3 4 5");
	printf("%d\n", o);
}*/
