/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouleim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:59:24 by msouleim          #+#    #+#             */
/*   Updated: 2024/09/07 18:12:26 by msouleim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

void	rush(int x, int y)
{
	int	a;
	int	b;

	a = 1;
	b = 1;
	while (b <= y)
	{
		while (a <= x)
		{
			if (((b == 1) || (b == y)) && (a == 1))
				ft_putchar('A');
			if (((b == 1) || (b == y)) && (a == x))
				ft_putchar('C');
			if (((a > 1) && (a < x)) && ((b == 1) || (b == y)))
				ft_putchar('B');
			if (((b > 1) && (b < y)) && ((a == 1) || (a == x)))
				ft_putchar('B');
			if (((b > 1) && (b < y)) && ((a > 1) && (a < x)))
				ft_putchar(' ');
			a++;
		}
		b++;
		ft_putchar('\n');
		a = 1;
	}
}
