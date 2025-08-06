/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:57:15 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/09 03:46:11 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Zombie.hpp"

static bool	getInputs(std::string & hordeSize, size_t & size_horde)
{
	if (!std::getline(std::cin, hordeSize))
	{
		if (std::cin.eof())
			throw std::runtime_error("[EOF detected - exiting]");
		else {
            std::cin.clear();
            std::cout << "[Input error — try again]" << std::endl;
            return true;
        }
	}
	if (!convert(hordeSize, size_horde))
		throw std::runtime_error("Invalid number!\n");
	else if (size_horde > 1000){
		std::cin.clear();
		std::cout << "[Input error — try again]" << std::endl;
		return true;
	}
	return false;
}

int	main(void)
{
	std::string	hordeSize;
	std::string	hordeNames;
	size_t 		size_horde;

	std::cout << GREEN << "Enter Horde Size :" << RESET << std::endl;
	while (1)
	{
		try {
			if (getInputs(hordeSize, size_horde))
				continue;
			std::cout << GREEN << "Enter Horde Names :" << RESET << std::endl;
			if (!std::getline(std::cin, hordeNames)) {
				if (std::cin.eof()) {
					std::cout << std::endl;
					throw std::runtime_error("[EOF detected - exiting]");
				}
			}
			std::cout << BLACK << "/*" << std::setfill('=') << std::setw(40)
				<< "*\\" << RESET << std::endl;
			break;
		}
		catch (std::exception const & i){
			std::cerr << YELLOW << "Error : " << i.what() << RESET << std::endl;
			return 0;
		}
	}
	Zombie* H = zombieHorde(size_horde, hordeNames);
	delete [] H;
	return 0;
}
