/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:57:13 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/09 05:48:38 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_H
# define ZOMBIE_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

#include "templates.tpp"

class	Zombie
{
	public:
	
	Zombie();
	Zombie(std::string name);
	~Zombie();

	void	setName(std::string name);
	
	void	announce( void ); 
	
	private:
		std::string	_name;
	
};

Zombie* zombieHorde(int N, std::string name);

#endif
