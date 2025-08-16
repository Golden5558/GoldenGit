/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:24:54 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/07 19:05:07 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

static bool	getInput(std::string & input)
{
	if (!std::getline(std::cin, input))
	{
		if (std::cin.eof())
			throw std::runtime_error("[EOF detected - exiting]");
		else {
            std::cin.clear();
            std::cout << "[Input error — try again]" << std::endl;
            return true;
        }
	}
	return false;
}

int	main(void)
{
	std::string		input;
	PhoneBook		phonebook = PhoneBook();

	while (1)
	{
		std::cout << GREEN << "Enter Commands ( ADD, SEARCH, EXIT ) :" << RESET << std::endl;
		try {
			if (getInput(input))
				continue;
		}
		catch (std::exception const & i){
			std::cerr << YELLOW << "Error : " << i.what() << RESET << std::endl;
			return 0;
		}
		try {	
			if (input == "ADD") {
				phonebook.addContact();
			}
			else if (input == "SEARCH") {
					phonebook.searchList();
			}
			else if (input == "EXIT")
				return 0;
		}
		catch (std::exception const & e) {
			std::cerr << YELLOW << "Error : " << e.what() << RESET << std::endl;
			if (std::string(e.what()) == "[EOF detected - exiting]")
				return 1;
		}
	}
	return 0;
}
