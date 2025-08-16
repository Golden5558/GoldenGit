/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 07:47:58 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/10 13:58:22 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_H
# define HARL_H

# include <string.h>
# include <iostream>

#include "templates.tpp"

# define RESET   "\033[0m"
# define YELLOW  "\033[33m"
# define RED     "\033[31m"
# define CYAN    "\033[36m"
# define BLACK   "\033[30m"
# define GREEN   "\033[32m"
# define MAGENTA "\033[35m"

class	Harl
{
	public:
		Harl();
		~Harl();
	
		void	complain(std::string level);

	private:
		void	debug(void);
		void	info(void);
		void	warning(void);
		void	error(void);
		
		static void	(Harl::*_myfunc[4])(void);
		static const std::string	_level[4];
};

#endif