/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:02:50 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/09/08 11:07:04 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	rush(int x, int y)
{
	int	a;
	int	b;

	b = 0;
	while (++b <= y)
	{
		a = 0;
		while (++a <= x)
		{
			if ((a == 1 && b == 1) || ((a == x && b == y) && (x > 1 && y > 1)))
				ft_putchar('/');
			if ((a == x && b == 1) && (x > 1))
				ft_putchar('\\');
			if ((a == 1 && b == y) && (y > 1))
				ft_putchar('\\');
			if ((a > 1 && a < x) && (b == 1 || b == y))
				ft_putchar('*');
			if ((b > 1 && b < y) && (a == 1 || a == x))
				ft_putchar('*');
			if ((a > 1 && a < x) && (b > 1 && b < y))
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
