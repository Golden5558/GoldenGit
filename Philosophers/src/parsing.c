/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:32:41 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/16 04:18:55 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	pars_argv(t_table *table, char **argv)
{
	table->nb_philosophers = ft_atoi(argv[1]);
	if (table->nb_philosophers <= 0)
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
}

t_philo	*init_philosophers(t_table *table)
{
	t_philo	*philosophers;
	t_philo	*temp;
	int		i;

	i = 1;
	philosophers = NULL;
	while (i <= table->nb_philosophers)
	{
		if (i < table->nb_philosophers)
			temp = ft_lstnew(&table->forks[i - 1], &table->forks[i], table, i);
		else
			temp = ft_lstnew(&table->forks[i - 1], &table->forks[0], table, i);
		if (!temp)
			return (ft_lstclear(&philosophers), NULL);
		ft_lstadd_back(&philosophers, temp);
		i++;
	}
	return (philosophers);
}

void	destroy_forks(t_table *table, int nb_forks)
{
	int	i;

	i = 0;
	while (i < nb_forks)
		pthread_mutex_destroy(&table->forks[i++].lock);
	free(table->forks);
	table->forks = NULL;
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(t_fork) * table->nb_philosophers);
	if (!table->forks)
		error_exit("Error malloc fork\n", table, NULL);
	while (i < table->nb_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i].lock, NULL))
		{
			destroy_forks(table, i - 1);
			error_exit("Error initializing mutex\n", table, NULL);
		}
		table->forks[i].in_use = false;
		table->forks[i].id_fork = i;
		i++;
	}
}
