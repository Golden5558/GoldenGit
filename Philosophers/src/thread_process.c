/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:27:07 by nberthal          #+#    #+#             */
/*   Updated: 2025/04/27 18:09:06 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->lock);
	if (check_if_end(philo))
	{
		pthread_mutex_unlock(&philo->left_fork->lock);
		return (1);
	}
	print_action(philo, TAKE, NOTHING);
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_unlock(&philo->right_fork->lock);
		usleep((philo->table->time_to_die * 1000) + 1000);
		return (1);
	}
	pthread_mutex_lock(&philo->right_fork->lock);
	if (check_if_end(philo))
	{
		pthread_mutex_unlock(&philo->left_fork->lock);
		pthread_mutex_unlock(&philo->right_fork->lock);
		return (1);
	}
	print_action(philo, TAKE, NOTHING);
	return (0);
}

static void	*philosophers_actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (check_if_end(philo))
			break ;
		print_action(philo, THINK, NOTHING);
		if (take_fork(philo))
			break ;
		if (check_if_end(philo))
			break ;
		print_action(philo, EAT, EATING);
		pthread_mutex_unlock(&philo->left_fork->lock);
		pthread_mutex_unlock(&philo->right_fork->lock);
		if (check_if_end(philo))
			break ;
		print_action(philo, SLEEP, SLEEPING);
	}
	return (NULL);
}

int	launch_threads_philo(t_table *table, t_philo **philo)
{
	int	i;

	i = 0;
	while (philo && philo[i])
	{
		if (pthread_create(&philo[i]->tread_id, NULL, philosophers_actions,
				(void *)philo[i]))
		{
			table->end = true;
			while (philo[--i])
			{
				if (pthread_join(philo[i]->tread_id, NULL))
					ft_putstr_fd("Error joining thread\n", 2);
			}
			clear_philosophers(philo, true);
			destroy_mutex(table);
			destroy_forks(table, table->nb_philo);
			ft_putstr_fd("Error creating thread\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
