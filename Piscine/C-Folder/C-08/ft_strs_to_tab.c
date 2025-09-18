/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:38:46 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/25 17:49:31 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_str.h"
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dup;

	i = 0;
	while (src[i])
		i++;
	dup = malloc((i + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

struct s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	struct s_stock_str	*data;
	int					i;

	i = 0;
	data = malloc(sizeof(t_stock_str) * (ac + 1));
	if (!data)
		return (NULL);
	while (i < ac)
	{
		data[i].str = av[i];
		data[i].size = ft_strlen(av[i]);
		data[i].copy = ft_strdup(av[i]);
		i++;
	}
	data[i].str = NULL;
	return (data);
}
/*
#include <stdio.h>
int	main(void)
{
	struct s_stock_str *show;
	
	int i = 0;
	int j = 5;
	char *strs[5];
	strs[0] = "test1";	
	strs[1] = "test2";	
	strs[2] = "test3";	
	strs[3] = "test4";	
	strs[4] = "test5";

	while (i < j)
	{
		show = ft_strs_to_tab(j, strs);
		printf("str --> %s\n", show[i].str);  
		printf("size--> %d\n", show[i].size);  
		printf("copy--> %s\n", show[i].copy);  
		i++;
	}
}*/
