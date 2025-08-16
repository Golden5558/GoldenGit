/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:57:19 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/09 05:50:24 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Zombie.hpp"

Zombie::Zombie( std::string name ) : _name( name )
{
	return ;
}

Zombie::~Zombie( void )
{
	std::cout << YELLOW << this->_name << BLACK << ": died in excruciating pain !!!"
		<< RESET << std::endl;
}

void	Zombie::announce( void )
{
	std::cout << YELLOW << this->_name << RED << ": BraiiiiiiinnnzzzZ..."
		<< RESET << std::endl;
}
