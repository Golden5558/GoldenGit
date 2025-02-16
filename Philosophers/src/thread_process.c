/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 04:53:03 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/16 04:16:33 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	wait_for(t_table *table, long long time_to_wait)
{
	long long	start;
	long long	last;

	start = table->time_in_ms;
	last = table->time_in_ms;
	while (last - start < time_to_wait && table->end == false)
		last = table->time_in_ms;
}

static void	take_fork_left_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->lock);
	if (philo->table->end == true)
	{
		pthread_mutex_unlock(&philo->left_fork->lock);
		return ;
	}
	printf("%lld %d has taken a fork\n", philo->table->time_in_ms, philo->id);
	pthread_mutex_lock(&philo->right_fork->lock);
	if (philo->table->end == true)
	{
		pthread_mutex_unlock(&philo->right_fork->lock);
		pthread_mutex_unlock(&philo->left_fork->lock);
		return ;
	}
	printf("%lld %d has taken a fork\n", philo->table->time_in_ms, philo->id);
}

static void	take_fork_right_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->lock);
	if (philo->table->end == true)
	{
		pthread_mutex_unlock(&philo->right_fork->lock);
		return ;
	}
	printf("%lld %d has taken a fork\n", philo->table->time_in_ms, philo->id);
	pthread_mutex_lock(&philo->left_fork->lock);
	if (philo->table->end == true)
	{
		pthread_mutex_unlock(&philo->right_fork->lock);
		pthread_mutex_unlock(&philo->left_fork->lock);
		return ;
	}
	printf("%lld %d has taken a fork\n", philo->table->time_in_ms, philo->id);
}

static void	*philosophers_actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->table->end == false)
	{
		printf("%lld %d is thinking\n", philo->table->time_in_ms, philo->id);
		if (philo->id % 2 == 0)
			take_fork_right_first(philo);
		if (philo->id % 2 == 1)
			take_fork_left_first(philo);
		printf("%lld %d is eating\n", philo->table->time_in_ms, philo->id);
		philo->last_meal = philo->table->time_in_ms;
		wait_for(philo->table, philo->table->time_to_eat);
		pthread_mutex_unlock(&philo->right_fork->lock);
		pthread_mutex_unlock(&philo->left_fork->lock);
		if (philo->table->end == true)
			return (NULL);
		printf("%lld %d is sleeping\n", philo->table->time_in_ms, philo->id);
		wait_for(philo->table, philo->table->time_to_sleep);
	}
	return (NULL);
}

void	launch_threads_philo(t_table *table, t_philo **philosophers)
{
	t_philo	*philo;
	t_philo	*temp;

	philo = *philosophers;
	temp = *philosophers;
	while (philo)
	{
		if (pthread_create(&philo->tread_id, NULL, philosophers_actions,
				(void *)philo))
		{
			table->end = true;
			while (temp != philo)
			{
				pthread_join(temp->tread_id, NULL);
				temp = temp->next;
			}
			error_exit("Error creating thread\n", table, *philosophers);
		}
		philo = philo->next;
	}
}
