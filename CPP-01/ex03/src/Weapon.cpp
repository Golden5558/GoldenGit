/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 05:37:05 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/10 14:13:26 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Weapon.hpp"

Weapon::Weapon(std::string type) : _type(type)
{
	return ;
}

Weapon::~Weapon()
{
	return ;
}

const std::string & Weapon::getType(void)
{
	return this->_type;
}

void	Weapon::setType(std::string const newtype)
{
	this->_type = newtype;
}

std::ostream & operator<<(std::ostream & o, Weapon & w)
{
	o << w.getType();
	return o;
}
