/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:24:27 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/15 06:00:10 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../philosophers.h"

typedef struct s_fork
{
	int				id_fork;
	bool			in_use;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_table
{
	t_fork			*forks;
	long long		nb_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_in_ms;
	pthread_t		time_thread_id;
	bool			end;
}	t_table;

typedef struct s_philo
{
	int				id;
	bool			live;
	pthread_t		tread_id;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_table			*table;
	struct s_philo	*next;
}	t_philo;

#endif