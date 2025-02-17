/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:59:45 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/17 15:33:36 by nberthal         ###   ########.fr       */
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

void	ft_putnbr_base_fd(long long nbr, char *base, int fd)
{
	int	base_len;

	base_len = check_base(base);
	if (base_len == -1)
		return ;
	if (nbr == -LLONG_MIN)
	{
		write(fd, "-", 1);
		ft_putnbr_base_fd(-(nbr / base_len), base, fd);
		ft_putchar_fd(base[-(nbr % base_len)], fd);
		return ;
	}
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= base_len)
		ft_putnbr_base_fd((nbr / base_len), base, fd);
	ft_putchar_fd(base[nbr % base_len], fd);
}
