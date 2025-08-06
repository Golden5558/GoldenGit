/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 08:07:23 by nberthal          #+#    #+#             */
/*   Updated: 2025/05/10 17:00:11 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Replace.hpp"

int	main(int argc, char **argv)
{
	if (argc != 4) {
		std::cerr << "Wrong number of arguments -- exiting..." << std::endl;
		return 1;
	}
	Replacer	replace = Replacer(argv);
	try {
		replace.run();
	} catch (std::exception const & err) {
		std::cerr << YELLOW << err.what() << " -- exiting..." << RESET << std::endl;
		return 1;
	}
}
