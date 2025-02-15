/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:32:41 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/15 02:33:20 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	check_argv(t_table *table, char **argv)
{
	table->philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->forks = malloc(sizeof(t_fork) * table->philosophers);
	if (!table->forks)
		exit(0);
}

t_philo	*init_philos(t_table *table)
{
	t_philo	*philosophers;
	t_philo	*temp;
	int		i;

	i = 0;
	philosophers = NULL;
	while ((unsigned int)i < table->philosophers)
	{
		if ((unsigned int)i < table->philosophers - 1)
			temp = ft_lstnew(&table->forks[i], &table->forks[i + 1], i);
		else
			temp = ft_lstnew(&table->forks[i], &table->forks[0], i);
		if (!temp)
			return (ft_lstclear(&philosophers), NULL);
		ft_lstadd_back(&philosophers, temp);
		i++;
	}
	return (philosophers);
}
