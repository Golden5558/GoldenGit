/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:55:34 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/15 20:09:35 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	ft_init_coord(char **argv, int coord[4][4]);
void	ft_init_matrix(int matrix[4][4]);
void	ft_verifi_cond(int argc, char **argv);
/*void ft_solve(coord[4][4], matrix[4][4]);*/

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	coord[4][4];
	int	matrix[4][4];

	ft_verifi_cond(argc, argv);
	ft_init_coord(argv, coord);
	ft_init_matrix(matrix);
}
/*	ft_solve(matrix, coord);

	i = -1;
	while (++i <= 3)
	{
		j = -1;
		while (++j <= 3)
			printf("%d", coord[i][j]);
		printf("\n");
	}


	i = -1;
	while (++i <= 3)
	{
		j = -1;
		while (++j <= 3)
			printf("%d", matrix[i][j]);
		printf("\n");
	}*/
