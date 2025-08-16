/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:57:13 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/10 14:13:32 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_H
# define WEAPON_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class Weapon
{
	public:
		Weapon(std::string type);
		~Weapon();

		const std::string& getType(void);
		void	setType(std::string const newtype);

	private:
		std::string	_type;
};

std::ostream & operator<<(std::ostream & o, Weapon & w);

#endif
