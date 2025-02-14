/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:17:07 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/14 02:25:52 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

# include "./lst_functions/ft_lst.h"

typedef struct s_fork
{
	int				id_fork;
	bool			in_use;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_table
{
	unsigned int	philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	t_fork			*forks;
	struct timeval	*time;
}	t_table;

#endif