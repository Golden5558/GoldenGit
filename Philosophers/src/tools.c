/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:50:36 by nberthal          #+#    #+#             */
/*   Updated: 2025/04/23 04:48:15 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	*ft_free_all(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		free(tab[i++]);
	if (tab)
		free(tab);
	tab = NULL;
	return (NULL);
}

static int	handle_digits(const char *nb, int *valid, int i, int sign)
{
	long	result;

	result = 0;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		result = (result * 10) + (nb[i++] - '0');
		if ((sign == 1 && result > INT_MAX) || (sign == -1 && (result * -1)
				< INT_MIN))
		{
			*valid = 0;
			return (0);
		}
	}
	if (nb[i] != '\0' || (i == 0 || (i == 1 && (nb[0] == '+' || nb[0] == '-'))))
		*valid = 0;
	return ((int)(sign * result));
}

int	ft_atoi_verif(const char *nb, int *valid)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	*valid = 1;
	while (nb[i] == 32 || (nb[i] >= 9 && nb[i] <= 13))
		i++;
	if (nb[i] == '+' || nb[i] == '-')
	{
		if (nb[i++] == '-')
			sign = -1;
	}
	return (handle_digits(nb, valid, i, sign));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return (0);
	return (write(fd, s, ft_strlen(s)));
}
