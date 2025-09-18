/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduarte <vduarte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:28:46 by vduarte           #+#    #+#             */
/*   Updated: 2024/09/21 16:28:56 by vduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow(char *str, int d)
{
	int	res;

	res = 1;
	while (str[d + 1] >= '0' && str[d + 1] <= '9')
	{
		res = res * 10;
		d ++;
	}
	return (res);
}

int	ft_atoi(char *str)
{
	int	i;
	int	m;
	int	res;

	i = 0;
	m = 0;
	res = 0;
	while (str[i] != '\0' && ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13)))
		i ++;
	while ((str[i] != '\0') && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			m ++;
		i ++;
	}
	while ((str[i] != '\0') && (str[i] >= '0' && str[i] <= '9'))
	{
		res += (str[i] - 48) * ft_pow(str, i);
		i ++;
	}
	if (m % 2 == 1)
		return (-res);
	return (res);
}
