/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:50:36 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/15 02:23:44 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_lst.h"

void	*ft_free_all(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		free (tab[i++]);
	if (tab)
		free (tab);
	tab = NULL;
	return (NULL);
}

int	ft_atoi(const char *nptr)
{
	int	minus;
	int	a;
	int	i;

	a = 0;
	i = 1;
	minus = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus = 1;
		nptr++;
	}
	while (*nptr && *nptr >= '0' && *nptr <= '9')
		a = a * 10 + (*nptr++ - 48);
	if (minus == 1)
		a = -a;
	return (a);
}
