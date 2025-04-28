/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 00:34:01 by nberthal          #+#    #+#             */
/*   Updated: 2025/04/27 18:01:56 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_if_end(t_philo *philo)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&philo->state_lock);
	pthread_mutex_lock(&philo->table->end_lock);
	if (philo->table->end == true || philo->eaten == philo->table->to_eat)
	{
		check = 1;
		philo->finished = true;
	}
	pthread_mutex_unlock(&philo->state_lock);
	pthread_mutex_unlock(&philo->table->end_lock);
	return (check);
}

void	print_action(t_philo *philo, char *msg, t_action action)
{
	long long	time;

	time = get_time(philo->table->start_time);
	printf("%lld %d %s\n", time, philo->id, msg);
	if (action == EATING)
	{
		pthread_mutex_lock(&philo->state_lock);
		philo->last_meal = time;
		philo->eaten++;
		pthread_mutex_unlock(&philo->state_lock);
		usleep(philo->table->time_to_eat * 1000);
	}
	if (action == SLEEPING)
		usleep(philo->table->time_to_sleep * 1000);
}
