/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:12:57 by nberthal          #+#    #+#             */
/*   Updated: 2025/04/27 16:24:34 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(long long start)
{
	long long		actual_time;
	long long		since_start;
	struct timeval	time;

	gettimeofday(&time, NULL);
	actual_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	since_start = actual_time - start;
	return (since_start);
}

static int	all_philo_filled(t_philo **philo)
{
	int	i;
	int	philo_finished;
	int	nb_philo;

	i = 0;
	philo_finished = 0;
	nb_philo = philo[i]->table->nb_philo;
	while (philo[i])
	{
		pthread_mutex_lock(&philo[i]->state_lock);
		if (philo[i]->finished == true)
			philo_finished++;
		pthread_mutex_unlock(&philo[i]->state_lock);
		i++;
	}
	if (philo_finished == nb_philo)
		return (1);
	return (0);
}

static void	monitor_death(t_table *table, t_philo **philo)
{
	int			i;
	long long	time;

	while (1)
	{
		i = -1;
		while (philo[++i])
		{
			pthread_mutex_lock(&philo[i]->state_lock);
			time = get_time(table->start_time);
			if (time - philo[i]->last_meal > table->time_to_die)
			{
				pthread_mutex_lock(&table->end_lock);
				table->end = true;
				pthread_mutex_unlock(&table->end_lock);
				pthread_mutex_unlock(&philo[i]->state_lock);
				printf("%lld %d died\n", time, philo[i]->id);
				return ;
			}
			pthread_mutex_unlock(&philo[i]->state_lock);
			usleep(100);
		}
		if (all_philo_filled(philo))
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	**philo;

	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"), 0);
	memset(&table, 0, sizeof(t_table));
	if (pars_argv(&table, argc, argv) || init_forks(&table))
		return (1);
	table.start_time = get_time(0);
	philo = init_philosophers(&table);
	if (!philo)
		return (destroy_forks(&table, table.nb_philo), 1);
	if (init_mutex(&table, philo) || launch_threads_philo(&table, philo))
		return (1);
	monitor_death(&table, philo);
	join_treads_philo(philo);
	clear_philosophers(philo, true);
	destroy_forks(&table, table.nb_philo);
	return (0);
}
