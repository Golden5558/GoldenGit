/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 05:37:48 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/10 14:15:17 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL)
{
	std::cout << BLUE << _name << YELLOW << " woke up empty handed" << RESET << std::endl;
}

HumanB::~HumanB()
{
	std::cout << BLUE << _name << YELLOW << " went back to sleep..." << RESET << std::endl;
}

void	HumanB::setWeapon(Weapon & weapon)
{
	this->_weapon = &weapon;
}

void	HumanB::attack()
{
	if (_weapon)
		std::cout << BLUE << _name << YELLOW << " attacked with " << MAGENTA << *_weapon << RESET << std::endl;
	else
		std::cout << BLUE << _name << YELLOW << " tried to attack but has no weapon!" << RESET << std::endl;
}