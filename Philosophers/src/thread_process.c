/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 04:53:03 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/15 06:06:51 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	wait_for(t_table *table, long long time_to_wait)
{
	long long		start;
	long long		last;

	start = table->time_in_ms;
	last = table->time_in_ms;
	while (start - last < time_to_wait)
		last = table->time_in_ms;
}

void	*philosophers_actions(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->live)
	{
		if (philo->id % 2 == 0)
			// use fork first
			// then left for time eating
		if (philo->id % 2 == 1)
			// then left for time eating
			// use fork for time eating
		printf("%lld %d is sleeping\n", philo->table->time_in_ms, philo->id);
		wait_for(philo->table, philo->table->time_to_sleep);
		printf("%lld %d is thinking\n", philo->table->time_in_ms, philo->id);
		
	}
	return (NULL);
}