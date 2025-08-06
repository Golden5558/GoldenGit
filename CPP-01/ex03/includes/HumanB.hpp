/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 05:34:17 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/09 07:03:03 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_H
# define HUMANB_H

#include "Weapon.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

# define RESET   "\033[0m"
# define YELLOW  "\033[33m"
# define MAGENTA "\033[35m"
# define BLUE    "\033[34m"

class HumanB
{
	public:
		HumanB(std::string name);
		~HumanB();
		
		void	attack();
		void	setWeapon(Weapon & weapon);

	private:
		std::string	_name;
		Weapon		*_weapon;
};

#endif
