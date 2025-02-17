/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:41:06 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/24 19:15:57 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
