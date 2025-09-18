/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:54:37 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/11 17:57:39 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
void	ft_print_hexa(unsigned char c)
{
	ft_putchar("0123456789abcdef"[c / 16]);
	ft_putchar("0123456789abcdef"[c % 16]);
}

void	ft_convhexa(int n)
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

int	main(void)
{
	ft_putstr_non_printable("\x01 \x7F \x80 ucou\ntu vas bien ?");
}
