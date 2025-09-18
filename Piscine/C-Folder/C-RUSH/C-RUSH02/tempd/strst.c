/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:59:06 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/21 16:08:55 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	str_len(char *to_find, int j);
int	ft_strncmp(char *s1, char *s2, int n);

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	length;
	int	compare;

	i = 0;
	length = 0;
	compare = -1;
	length = str_len(to_find, length);
	if (*to_find == '\0')
		return (str);
	while (str[i])
	{
		if (str[i] == *to_find)
			compare = ft_strncmp(&str[i], to_find, length);
		if (compare == 0)
			return (&str[i]);
		i++;
	}
	return (0);
}

int	str_len(char *to_find, int j)
{
	while (to_find[j])
		j++;
	return (j);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}