/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:17:07 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/15 02:33:51 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Librairies :

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

// Includes :

# include "./includes/structures.h"
# include "./includes/ft_lst.h"

// Parsing :

t_philo	*init_philos(t_table *table);
void	check_argv(t_table *table, char **argv);

#endif