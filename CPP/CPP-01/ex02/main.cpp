/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:57:15 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/09 05:29:59 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define YELLOW  "\033[33m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"

int	main(void)
{
	std::string stringORI = "HI THIS IS BRAIN";
	std::string* stringPTR = &stringORI;
	std::string& stringREF = stringORI;
	
	std::cout << BLACK << "|*" << std::setfill('=') << std::setw(48) << "*|" << RESET << std::endl;
	std::cout << std::endl;

	std::cout << CYAN << "Memory address of the stringORI : " << &stringORI << RESET << std::endl;
	std::cout << YELLOW << "Memory address of the stringPTR : " << stringPTR << RESET << std::endl;
	std::cout << MAGENTA << "Memory address of the stringREF : " << &stringREF << RESET << std::endl;

	std::cout << std::endl;
	std::cout << BLACK << "|*" << std::setfill('=') << std::setw(48) << "*|" << RESET << std::endl;
	std::cout << std::endl;

	std::cout << CYAN << "Value of the stringORI : " << stringORI << RESET << std::endl;
	std::cout << YELLOW << "Value of the stringPTR : " << *stringPTR << RESET << std::endl;
	std::cout << MAGENTA << "Value of the stringREF : " << stringREF << RESET << std::endl;
	
	std::cout << std::endl;
	std::cout << BLACK << "|*" << std::setfill('=') << std::setw(48) << "*|" << RESET << std::endl;
	
	return 0;
}
