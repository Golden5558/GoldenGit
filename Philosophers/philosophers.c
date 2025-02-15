/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:12:57 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/15 02:33:17 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*time_loop(void *arg)
{
	t_table			*table;
	struct timeval	time;
	long long		since_start;
	long long		start;

	table = (t_table *)arg;
	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (table->end == false)
	{
		gettimeofday(&time, NULL);
		since_start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		table->time_in_ms = since_start - start;
		// printf("Time : %lld\n", table->time_in_ms);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philosophers;

	if (argc != 5)
		return (printf("Wrong number of arguments\n"), 0);
	memset(&table, 0, sizeof(t_table));
	check_argv(&table, argv);
	philosophers = init_philos(&table);
	if (!philosophers)
		return (free(table.forks), 0);
	pthread_create(&table.time_thread_id, NULL, time_loop, (void *)&table);
	pthread_join(table.time_thread_id, NULL);
}
