/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:17:07 by nberthal          #+#    #+#             */
/*   Updated: 2025/04/27 05:59:46 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*============================================================================*/
/*                              LIBRAIRIES                 	 				  */
/*============================================================================*/

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
# include <limits.h>

/*============================================================================*/
/*                              INCLUDES                   	 				  */
/*============================================================================*/

# include "./includes/structures.h"
# include "./includes/utils.h"

/*============================================================================*/
/*                              PARSING                   	 				  */
/*============================================================================*/

int			init_forks(t_table *table);
int			init_mutex(t_table *table, t_philo **philosophers);
int			check_if_end(t_philo *philo);
int			launch_threads_philo(t_table *table, t_philo **philosophers);
int			pars_argv(t_table *table, int argc, char **argv);
long long	get_time(long long start);
void		print_action(t_philo *philo, char *msg, t_action action);
t_philo		**init_philosophers(t_table *table);

/*============================================================================*/
/*                              CLEANUP                   	 				  */
/*============================================================================*/

void		*clear_philosophers(t_philo **philosophers, bool destroy_mutex);
void		destroy_mutex(t_table *table);
void		destroy_forks(t_table *table, int nb_forks);
void		join_treads_philo(t_philo **philo);

#endif