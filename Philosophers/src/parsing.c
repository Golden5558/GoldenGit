/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:32:41 by nberthal          #+#    #+#             */
/*   Updated: 2025/04/27 15:59:55 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	pars_argv(t_table *table, int argc, char **argv)
{
	int	valid;

	table->nb_philo = ft_atoi_verif(argv[1], &valid);
	if (table->nb_philo <= 0 || !valid)
		return (ft_putstr_fd("Error : Invalid number of philosophers\n", 2));
	table->time_to_die = ft_atoi_verif(argv[2], &valid);
	if (table->time_to_die <= 0 || !valid)
		return (ft_putstr_fd("Error : Invalid time to die\n", 2));
	table->time_to_eat = ft_atoi_verif(argv[3], &valid);
	if (table->time_to_eat <= 0 || !valid)
		return (ft_putstr_fd("Error : Invalid time to eat\n", 2));
	table->time_to_sleep = ft_atoi_verif(argv[4], &valid);
	if (table->time_to_sleep <= 0 || !valid)
		return (ft_putstr_fd("Error : Invalid time to sleep\n", 2));
	if (argc == 6)
	{
		table->to_eat = ft_atoi_verif(argv[5], &valid);
		if (table->to_eat <= 0 || !valid)
			return (ft_putstr_fd("Error : Invalid number of time to eat\n", 2));
	}
	else if (argc == 5)
		table->to_eat = -1;
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(t_fork) * table->nb_philo);
	if (!table->forks)
		return (ft_putstr_fd("Error malloc fork\n", 2));
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i].lock, NULL))
		{
			destroy_forks(table, i - 1);
			ft_putstr_fd("Error initializing mutex\n", 2);
			return (1);
		}
		table->forks[i].id_fork = i;
		i++;
	}
	return (0);
}

static t_philo	**init_philo_mutex(t_philo **philosophers)
{
	int	i;

	i = 0;
	while (philosophers && philosophers[i])
	{
		if (pthread_mutex_init(&philosophers[i]->state_lock, NULL))
		{
			while (--i >= 0)
			{
				while (pthread_mutex_destroy(&philosophers[i]->state_lock))
					continue ;
			}
			ft_putstr_fd("Error initializing mutex\n", 2);
			return (clear_philosophers(philosophers, false));
		}
		i++;
	}
	return (philosophers);
}

t_philo	**init_philosophers(t_table *table)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo *) * (table->nb_philo + 1));
	if (!philo)
		return (ft_putstr_fd("Error malloc philosophers\n", 2), NULL);
	memset(philo, 0, sizeof(t_philo *) * (table->nb_philo + 1));
	while (++i <= table->nb_philo)
	{
		philo[i - 1] = malloc(sizeof(t_philo));
		if (!philo[i - 1])
		{
			ft_putstr_fd("Error malloc philosophers\n", 2);
			return (clear_philosophers(philo, false));
		}
		memset(philo[i - 1], 0, sizeof(t_philo));
		philo[i - 1]->id = i;
		philo[i - 1]->table = table;
		philo[i - 1]->last_meal = 0;
		philo[i - 1]->left_fork = &table->forks[(i - 1) % table->nb_philo];
		philo[i - 1]->right_fork = &table->forks[i % table->nb_philo];
	}
	philo[i - 1] = NULL;
	return (init_philo_mutex(philo));
}

int	init_mutex(t_table *table, t_philo **philosophers)
{
	if (pthread_mutex_init(&table->end_lock, NULL))
	{
		destroy_forks(table, table->nb_philo);
		clear_philosophers(philosophers, true);
		ft_putstr_fd("Error initializing mutex\n", 2);
		return (1);
	}
	return (0);
}
