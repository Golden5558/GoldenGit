/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:24:27 by nberthal          #+#    #+#             */
/*   Updated: 2025/04/27 07:38:45 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../philosophers.h"

# define EAT "is eating"
# define SLEEP "is sleeping"
# define TAKE "has taken a fork"
# define THINK "is thinking"

typedef enum s_action
{
	EATING,
	SLEEPING,
	NOTHING
}					t_action;

typedef struct s_fork
{
	int				id_fork;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_table
{
	bool			end;
	int				nb_philo;
	int				to_eat;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	pthread_mutex_t	end_lock;
	t_fork			*forks;
}					t_table;

typedef struct s_philo
{
	bool			finished;
	int				id;
	int				eaten;
	long long		last_meal;
	pthread_t		tread_id;
	pthread_mutex_t	state_lock;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_table			*table;
}					t_philo;

#endif