/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 07:47:40 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/10 13:12:04 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Harl.hpp"

Harl::Harl()
{
	return ;
}

Harl::~Harl(void)
{
	return ;
}

void	(Harl::*Harl::_myfunc[4])(void) = {
	&Harl::debug,
	&Harl::info,
	&Harl::warning,
	&Harl::error
};

const std::string	Harl::_level[4] = {
	"DEBUG",
	"INFO",
	"WARNING",
	"ERROR"
};

void	Harl::complain(std::string level)
{
	for (int i = 0; i < 4; ++i) {
		if (_level[i] == level) {
			(this->*Harl::_myfunc[i])();
			std::cout << std::endl;
		}
	};
}

void	Harl::debug(void)
{
	std::cout << GREEN << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger." << std::endl;
	std::cout << "I really do!" << RESET << std::endl;
}

void	Harl::info(void)
{
	std::cout << CYAN << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money." << std::endl;
	std::cout << "You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << RESET << std::endl;
}

void	Harl::warning(void)
{
	std::cout << YELLOW << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free." << std::endl;
	std::cout << "I’ve been coming for years, whereas you started working here just last month." << RESET << std::endl;
}

void	Harl::error(void)
{
	std::cout << RED << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now." << RESET << std::endl;
}
