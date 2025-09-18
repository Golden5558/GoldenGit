/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:54:37 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/11 18:29:10 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_convhexa(unsigned int n)
{
	char	*hexa;
	int		i;
	int		j;

	hexa = "0123456789abcdef";
	i = n / 16;
	j = n % 16;
	write(1, &hexa[i], 1);
	write(1, &hexa[j], 1);
}

void	ft_putstr_non_printable(char *str)
{
	char		c;

	c = '\\';
	while (*str)
	{
		if (*str < 32 || *str > 126)
		{
			write(1, &c, 1);
			ft_convhexa((unsigned char)*str);
			str++;
		}
		else
			write(1, str++, 1);
	}
}
/*
int	main(void)
{
	ft_putstr_non_printable("\x01 \x7F \x80 ucou\ntu vas bien ?");
	ft_putstr_non_printable("Coucou\ntu vas bien ?");
}*/
