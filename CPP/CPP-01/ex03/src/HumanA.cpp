/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 05:37:29 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/09 07:03:29 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HumanA.hpp"

HumanA::HumanA(std::string name, Weapon & weapon) : _name(name), _weapon(weapon)
{
	std::cout << RED << _name << CYAN << " woke up and took his " << MAGENTA << _weapon << RESET << std::endl;
}

HumanA::~HumanA()
{
	std::cout << RED << _name << CYAN << " went back to sleep..." << RESET << std::endl;
}

void	HumanA::attack()
{
	std::cout << RED << _name << CYAN << " attacked with " << MAGENTA << _weapon << RESET << std::endl;
}
