/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:59:45 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/11 01:38:15 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	check_base(char *base)
{
	int	i;
	int	len;

	if (!base || !*base || !*(base + 1))
		return (-1);
	len = 0;
	while (base[len])
	{
		if (base[len] == '-' || base[len] == '+')
			return (-1);
		i = len + 1;
		while (base[i])
		{
			if (base[i] == base[len])
				return (-1);
			i++;
		}
		len++;
	}
	return (len);
}

void	ft_putnbr_base(long long nbr, char *base)
{
	int	base_len;

	base_len = check_base(base);
	if (base_len == -1)
		return ;
	if (nbr == -LLONG_MIN)
	{
		write(1, "-", 1);
		ft_putnbr_base(-(nbr / base_len), base);
		ft_putchar_fd(base[-(nbr % base_len)], 1);
		return ;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= base_len)
		ft_putnbr_base((nbr / base_len), base);
	ft_putchar_fd(base[nbr % base_len], 1);
}

void	fputnbr_base(FILE *stream, long long nbr, char *base)
{
	int	base_len;

	base_len = check_base(base);
	if (base_len == -1)
		return ;
	if (nbr == -LLONG_MIN)
	{
		fwrite("-", 1, 1, stream);
		fputnbr_base(stream, -(nbr / base_len), base);
		ft_fputchar(stream, base[-(nbr % base_len)]);
		return ;
	}
	if (nbr < 0)
	{
		fwrite("-", 1, 1, stream);
		nbr = -nbr;
	}
	if (nbr >= base_len)
		fputnbr_base(stream, (nbr / base_len), base);
	ft_fputchar(stream, base[nbr % base_len]);
}
