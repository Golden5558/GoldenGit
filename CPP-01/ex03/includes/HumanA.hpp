/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 05:34:19 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/09 07:03:05 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_H
# define HUMANA_H

#include "Weapon.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"

class HumanA
{
	public:
		HumanA(std::string name, Weapon & weapon);
		~HumanA();

		void	attack();

	private:
		std::string	_name;
		Weapon &	_weapon;

};

#endif