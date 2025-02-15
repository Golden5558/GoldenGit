/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:32:41 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/15 03:01:03 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	pars_argv(t_table *table, char **argv)
{
	table->philosophers = ft_atoi(argv[1]);
	if (table->philosophers <= 0)
		error_exit("Error : Invalid number of philosophers\n", table, NULL);
	table->time_to_die = ft_atoi(argv[2]);
	if (table->time_to_die <= 0)
		error_exit("Error : Invalid time to die\n", table, NULL);		
	table->time_to_eat = ft_atoi(argv[3]);
	if (table->time_to_eat <= 0)
		error_exit("Error : Invalid time to eat\n", table, NULL);	
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->time_to_sleep <= 0)
		error_exit("Error : Invalid time to sleep\n", table, NULL);	
	table->forks = malloc(sizeof(t_fork) * table->philosophers);
	if (!table->forks)
		error_exit("Error : Malloc fork\n", table, NULL);
}

t_philo	*init_philosophers(t_table *table)
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
