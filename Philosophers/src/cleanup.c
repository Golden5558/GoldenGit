/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:39:18 by nberthal          #+#    #+#             */
/*   Updated: 2025/04/27 17:49:52 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	destroy_mutex(t_table *table)
{
	if (pthread_mutex_destroy(&table->end_lock))
		ft_putstr_fd("Error destroying end mutex\n", 2);
}

void	destroy_forks(t_table *table, int nb_forks)
{
	int	i;

	i = 0;
	while (i < nb_forks)
	{
		if (pthread_mutex_destroy(&table->forks[i++].lock))
		{
			ft_putstr_fd("Error destroying fork mutex\n", 2);
		}
	}
	free(table->forks);
	table->forks = NULL;
}

void	*clear_philosophers(t_philo **philosophers, bool destroy_mutex)
{
	size_t	i;

	i = 0;
	if (!philosophers)
		return (NULL);
	while (philosophers[i])
	{
		if (destroy_mutex)
			if (pthread_mutex_destroy(&philosophers[i]->state_lock))
				ft_putstr_fd("Error destroying state mutex\n", 2);
		free(philosophers[i++]);
	}
	if (philosophers)
		free(philosophers);
	philosophers = NULL;
	return (NULL);
}

void	join_treads_philo(t_philo **philo)
{
	int	i;

	i = 0;
	while (philo && philo[i])
	{
		if (pthread_join(philo[i]->tread_id, NULL))
			ft_putstr_fd("Error joining thread\n", 2);
		i++;
	}
}
