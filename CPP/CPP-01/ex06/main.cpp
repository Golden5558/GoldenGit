/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 07:47:16 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/10 16:09:00 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Harl.hpp"

int	main(int argc, char **argv)
{
	Harl 		Harl;
	std::string	input;

	try {
		if (argc != 2)
			throw std::invalid_argument("Error Wrong number of arguments");
		if (!convert(argv[1], input))
			throw std::runtime_error("Error converting char * to std::string");
	}
	catch (std::exception & e) {
		std::cout << YELLOW << e.what() << " -- exiting..." << RESET << std::endl;
		return 1;
	}
	Harl.complain(input);

	return 0;
}
